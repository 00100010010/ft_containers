#!/bin/bash
###############################################################################
mkdir -p bin
clang++ -D NAMESPACE=ft srcs/set_test.cpp    -o bin/set_for_valgrd.bin;
clang++ -D NAMESPACE=ft srcs/map_test.cpp    -o bin/map_for_valgrd.bin;
clang++ -D NAMESPACE=ft srcs/vector_test.cpp -o bin/vector_for_valgrd.bin;
clang++ -D NAMESPACE=ft srcs/stack_test.cpp  -o bin/stack_for_valgrd.bin;
printf "\n VALGRIND ----> SET\n\n";
valgrind --leak-check=full ./bin/set_for_valgrd.bin	> /dev/null;
printf "\n VALGRIND ----> MAP\n\n";
valgrind --leak-check=full ./bin/map_for_valgrd.bin	> /dev/null;
printf "\n VALGRIND ----> VECTOR\n\n";
valgrind --leak-check=full ./bin/vector_for_valgrd.bin  > /dev/null;
printf "\n VALGRIND ----> STACK\n\n";
valgrind --leak-check=full ./bin/stack_for_valgrd.bin   > /dev/null;
