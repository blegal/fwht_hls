//
//
//
//////////////////////////////////////////////////////////////////////
//
//
//
#include "impl/types.hpp"
#include "impl/f_datapath.hpp"
#include "impl/f_decision.hpp"
#include "impl/f_xor_processor.hpp"
//
//
//
//////////////////////////////////////////////////////////////////////
//
//
//
#define N            256
#define log2N        8
//
//
//
//////////////////////////////////////////////////////////////////////
//
//
//
FILE* fou = nullptr;
inline void init_file(const std::string fname)
{
	fou = fopen(fname.c_str(), "w");
	if (fou == nullptr) {
		printf("error opening file (%s)\n", fname.c_str());
		exit(-1);
	}
}
inline void close_file( ) {
	fclose(fou);
}
inline void dump_values(const t_i_memo& v, const std::string name, const int idx) {
	fprintf(fou, "%s [%d]\n", name.c_str(), idx);
	for (int i = 0; i < gf_size; i++) {
		if (i     == 0)      fprintf(fou, "%3d :",   i);
		else if (i % 8 == 0) fprintf(fou, "\n%3d :", i);
		fprintf(fou, "%+12d ", v.value[i].to_int());
	}
	fprintf(fou, "\n\n");
}
//
//
//
//////////////////////////////////////////////////////////////////////
//
//
//
void the_decoder_v3(
			t_i_memo channel[N],
			uint8_t  decoded[N])
{
	//// debug code
	init_file("processor.txt");
	//// debug code

	t_i_memo internal[N];
#pragma HLS ARRAY_PARTITION dim=2 type=complete variable=internal

	static uint8_t symbols[N];
#pragma HLS ARRAY_PARTITION dim=1 type=cyclic variable=symbols_l  factor=4
#pragma HLS bind_storage variable=symbols_l type=RAM_1WNR impl=BRAM

	static uint8_t xor_proc_i[N];
#pragma HLS ARRAY_PARTITION dim=1 type=complete variable=xor_proc_i
	static uint8_t xor_proc_o[N];
#pragma HLS ARRAY_PARTITION dim=1 type=complete variable=xor_proc_o

//	t_i_memo lwht_in_a, lwht_in_b;
//#pragma HLS ARRAY_PARTITION dim=1 type=complete variable=lwht_in_a.value
//#pragma HLS ARRAY_PARTITION dim=1 type=complete variable=lwht_in_b.value
	int cnt_u  = 0; //

	t_i_memo memo_in_a;
#pragma HLS ARRAY_PARTITION dim=1 type=complete variable=memo_in_a.value

	// operation (Fn, Gn, Fn+LWHT, Gn+Fn+LWHT, F0, G1, G1+Fn+LWHT, XOR)
	// counter
	// - n symbols
	// - Channel  RAM (read 1, read 2)
	// - Internal RAM (read 1, read 2, write 1)
	// - Symbol   RAM (read 1, read 2, write 1)
	// - Decoded  RAM (read 1, read 2, write 1)

	typedef struct instr{
		bool  is_f_g_rep_spc;
		int   loop_size; // amount of loop iterations
		bool  is_channel;
		bool  is_g_function;
		bool  fwht_conv;
		bool  is_decision; // incr. cnt_u (symbol decodé)
		bool  is_decoded;
		bool  is_rate0;
		bool  is_rep;
		int   cnt_c;  // dest de datapath
		int   cnt_a;  // src 1 de datapath
		int   cnt_b;  // src 2 de datapath
		int   cnt_rw; // pour les XOR @r1 et @w
		int   cnt_rd; // pour les XOR @r2
	} instr;

	instr t_ins[] = {
		//
		// 0 : loop 0 : f_function_proba_in : OK
		//
		{
		true, 128, true, false, true,
		 false, false, false, false,
		0, 0, 128, 0, 0
		},
		//
		// 1 : loop 3 : g function (rate 0) : OK
		//
	{
			true, 64, false, true, true,
			true, true, true, false,
			128, 0, 64, 0, 0 /*useless*/
		},
		//
		// 2 : loop 5 : g function (rate 0) : OK
		//
	{
		true, 32, false, true, false,
		false, false, true, false,
		192, 128, 160, 64, 64 /*useless*/
		},
		//
		// 3 : loop 7 : g function (rate 0) : OK
		//
	{
		true, 16, false, true, false,
		false, false, true, false,
		224, 192, 208, 96, 96  /*useless*/
		},
		//
		// 4 : loop 9 : g function (rate 0) : OK
		//
	{
		true, 8, false, true, false,
		false, false, true, false,
		240, 224, 232, 112, 112
		},
		//
		// 5 : loop 10 : rate 1 : OK
		//
	{
		true, 8, false, false, false,
		false, false, true, false,
		248, 240, 248, 120, 120
		},

	{ // oups c pas cool !
		true, 1, false, false, true,
		false, false, false, false,
		62, 60, 61, 16, 16
		}
};

	for (int i = 0; i < 5; i += 1) {
	//
	// LA BOUCLE SUR LES INSTRUCTIONS (debut)
	//

		const instr ins = t_ins[i];

		int cnt_a  = ins.cnt_a;
		int cnt_b  = ins.cnt_b;
		int cnt_c  = ins.cnt_c;
		int cnt_rd = ins.cnt_rd;
		int cnt_rw = ins.cnt_rw;

		loop1 : for (int s = 0; s < ins.loop_size; s++) {
#pragma HLS PIPELINE

			//
			// On selection les données qui vont rentrer dans le datapath
			//
			const auto chn_in_a = channel [cnt_a];
			const auto chn_in_b = channel [cnt_b];
			const auto int_in_a = internal[cnt_a];
			const auto int_in_b = internal[cnt_b];
			const auto lwht_in_a= ins.is_channel ? chn_in_a : int_in_a;
			const auto lwht_in_b= ins.is_channel ? chn_in_b : int_in_b;

			//
			// on incremente ou pas les counter
			//
			cnt_a += 1;
			cnt_b += 1;

			//
			// input symbol ou zero
			//
			const uint8_t m_symb   = symbols[cnt_rd];
			const uint8_t symbol_i = (ins.is_g_function && !ins.is_rate0) ?  m_symb : 0; // si f function alors le symbol = 0
			cnt_rd += 1;

			//
			//
			//
			const auto memo_in_a = datapath(lwht_in_a, lwht_in_b, symbol_i, ins.fwht_conv);
			const auto symbol_v    = vec_decision( memo_in_a, ins.fwht_conv ); // conversion is common with datapath

			internal[cnt_c] = memo_in_a; // on store la datat
			cnt_c += 1;

			// On memorise tous les symboles décodés, utiles ou pas...
			xor_proc_i[s] = symbol_v;

			// entrée de decoded
			// soit c symbol_v, soit xor_proc_o[s] ou zero
			const uint8_t e_symb  = ins.is_rate0 ? 0 : symbol_v; // OK pour rate 0
			const uint8_t f_symb  = ins.is_rep   ? 0 : symbol_v;
			// ATTENTION AU REP c uniquement à size -1 !!!
			decoded[cnt_u]  = f_symb;
			cnt_u = (ins.is_decoded) ? (cnt_u + 1) : 0;

			// entrée de symbol
			// soit c symbol_v, soit  zero, soit symbols_l xor symbols_l
			symbols[cnt_rw] = e_symb;
			cnt_rw = (ins.is_decoded) ? (cnt_rw + 1) : 0;
			// incr ou pas (read et write en single)
		}

		v64_xor_processor(xor_proc_o, xor_proc_i, 7);

	//
	// LA BOUCLE SUR LES INSTRUCTIONS (debut)
	//
	//// debug code
	for (int s = 0; s < ins.loop_size; s += 1)
		dump_values(internal[ins.cnt_c + s], "loop", s);
	//// debug code
	}

	close_file();
	//// debug code

}

