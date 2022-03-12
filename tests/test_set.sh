#!/bin/bash
###############################################################################
flags="-Wall -Wextra -Werror -std=c++98"
sanitize="-g3 -fsanitize=address"
file="srcs/set_test.cpp"
###############################################################################
mkdir -p bin out
clang++ ${flags} ${sanitize} -D NAMESPACE=ft   ${file} -o bin/ft_set.bin  && ./bin/ft_set.bin  > out/ft_set.out;
clang++ ${flags} ${sanitize} -D NAMESPACE=std  ${file} -o bin/std_set.bin && ./bin/std_set.bin > out/std_set.out;
echo "diff --->"
diff out/ft_set.out out/std_set.out
