#### the list of targets ####
add_executable(ugraph
        ugraph/main.cpp        
        ugraph/ugraph.hpp
        ugraph/lbl_ugraph.hpp
        ugraph/ugraph_algos.hpp
        ugraph/disj_set.hpp
        #
        grviz/gen_dot_writer.hpp
        grviz/ugraph_dotwriter.hpp
        #
        bitwise_tasks.cpp
    )

