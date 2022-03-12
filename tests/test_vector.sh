#!/bin/bash
###############################################################################
flags="-Wall -Wextra -Werror -std=c++98"
sanitize="-g3 -fsanitize=address"
file="srcs/vector_test.cpp"
file_speed_test="srcs/vector_speed_test.cpp"
###############################################################################
mkdir -p bin out
clang++ ${flags} ${sanitize} -D NAMESPACE=ft   ${file} -o bin/ft_vector.bin  && ./bin/ft_vector.bin  > out/ft_vector.out;
clang++ ${flags} ${sanitize} -D NAMESPACE=std  ${file} -o bin/std_vector.bin && ./bin/std_vector.bin > out/std_vector.out;
echo "diff --->"
diff out/ft_vector.out out/std_vector.out
###############################################################################
clang++ ${flags} -D NAMESPACE=ft   ${file_speed_test} -o ft  && time ./ft  > ftspeed.out;
clang++ ${flags} -D NAMESPACE=std  ${file_speed_test} -o std && time ./std > stdspeed.out;
rm -rf ft std ftspeed.out stdspeed.out
