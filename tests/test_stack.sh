#!/bin/bash
###############################################################################
flags="-Wall -Wextra -Werror -std=c++98"
sanitize="-g3 -fsanitize=address"
file="srcs/stack_test.cpp"
###############################################################################
mkdir -p bin out
clang++ ${flags} ${sanitize} -D NAMESPACE=ft   ${file} -o bin/ft_stack.bin  && ./bin/ft_stack.bin  > out/ft_stack.out;
clang++ ${flags} ${sanitize} -D NAMESPACE=std  ${file} -o bin/std_stack.bin && ./bin/std_stack.bin > out/std_stack.out;
echo "diff --->"
diff out/ft_stack.out out/std_stack.out
