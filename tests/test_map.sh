#!/bin/bash
###############################################################################
flags="-Wall -Wextra -Werror -std=c++98"
sanitize="-g3 -fsanitize=address"
file="srcs/map_test.cpp"
file_speed_test="srcs/map_speed_test.cpp"
###############################################################################\
mkdir -p bin out
clang++ ${flags} ${sanitize} -D NAMESPACE=ft   ${file} -o bin/ft_map.bin  && ./bin/ft_map.bin  > out/ft_map.out;
clang++ ${flags} ${sanitize} -D NAMESPACE=std  ${file} -o bin/std_map.bin && ./bin/std_map.bin > out/std_map.out;
echo "diff --->"
diff out/ft_map.out out/std_map.out
###############################################################################
clang++ ${flags} -D NAMESPACE=ft   ${file_speed_test} -o ft  && time ./ft  > ftspeed.out;
clang++ ${flags} -D NAMESPACE=std  ${file_speed_test} -o std && time ./std > stdspeed.out;
rm -rf ft std ftspeed.out stdspeed.out
