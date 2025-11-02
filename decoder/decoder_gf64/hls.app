<project xmlns="com.autoesl.autopilot.project" top="the_decoder" name="decoder_gf64" projectType="C/C++">
    <includePaths/>
    <libraryPaths/>
    <Simulation>
        <SimFlow name="csim"/>
    </Simulation>
    <files xmlns="">
        <file name="src/archi.hpp" sc="0" tb="false" cflags="" csimflags="" blackbox="false"/>
        <file name="src/argmax_x86.hpp" sc="0" tb="false" cflags="" csimflags="" blackbox="false"/>
        <file name="src/decoder.cpp" sc="0" tb="false" cflags="" csimflags="" blackbox="false"/>
        <file name="src/dedicated_execute.hpp" sc="0" tb="false" cflags="" csimflags="" blackbox="false"/>
        <file name="src/f_function_freq_in.hpp" sc="0" tb="false" cflags="" csimflags="" blackbox="false"/>
        <file name="src/f_function_proba_in.hpp" sc="0" tb="false" cflags="" csimflags="" blackbox="false"/>
        <file name="src/fix_xor_list.hpp" sc="0" tb="false" cflags="" csimflags="" blackbox="false"/>
        <file name="src/fwht.hpp" sc="0" tb="false" cflags="" csimflags="" blackbox="false"/>
        <file name="src/fwht_norm.hpp" sc="0" tb="false" cflags="" csimflags="" blackbox="false"/>
        <file name="src/g_function_freq_in.hpp" sc="0" tb="false" cflags="" csimflags="" blackbox="false"/>
        <file name="src/g_function_proba_in.hpp" sc="0" tb="false" cflags="" csimflags="" blackbox="false"/>
        <file name="src/middle_node_pruned_rate_0.hpp" sc="0" tb="false" cflags="" csimflags="" blackbox="false"/>
        <file name="src/middle_node_pruned_rate_1_after_f.hpp" sc="0" tb="false" cflags="" csimflags="" blackbox="false"/>
        <file name="src/middle_node_pruned_rate_1_after_g.hpp" sc="0" tb="false" cflags="" csimflags="" blackbox="false"/>
        <file name="src/middle_node_pruned_rep_after_f.hpp" sc="0" tb="false" cflags="" csimflags="" blackbox="false"/>
        <file name="src/middle_node_pruned_rep_after_g.hpp" sc="0" tb="false" cflags="" csimflags="" blackbox="false"/>
        <file name="src/normalize_c.hpp" sc="0" tb="false" cflags="" csimflags="" blackbox="false"/>
    </files>
    <solutions xmlns="">
        <solution name="artix7" status="active"/>
    </solutions>
</project>

