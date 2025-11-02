
all: main

main: obj/main.o obj/decoder.o
	g++ -Wall -o ./bin/$@ $^ -lpthread

obj/main.o: src/main.cpp
	g++ -Wall -O2 -std=c++14 -march=native -mtune=native src/main.cpp -c -o obj/main.o

obj/decoder.o: src/decoder.cpp src/archi.hpp src/f_function_proba_in.hpp src/g_function_proba_in.hpp src/middle_node_pruned_rep_after_g.hpp src/argmax_x86.hpp src/fix_xor_list.hpp src/middle_node_pruned_rate_0.hpp src/normalize_c.hpp src/decoder.cpp src/fwht.hpp src/middle_node_pruned_rate_1_after_f.hpp src/dedicated_execute.hpp src/fwht_norm.hpp src/middle_node_pruned_rate_1_after_g.hpp src/f_function_freq_in.hpp src/g_function_freq_in.hpp  src/middle_node_pruned_rep_after_f.hpp
	g++ -Wall -O2 -std=c++14 -march=native -mtune=native src/decoder.cpp -c -o obj/decoder.o

clean:
	rm -rf obj/*.o
	rm -rf bin/main
