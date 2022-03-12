#!/bin/bash
###############################################################################
file="srcs/RB_Tree_test.cpp"
###############################################################################
cat srcs/RBTree_rules.txt
clang++  -D NAMESPACE=ft  ${file} -o rb_tree.bin  && ./rb_tree.bin;
rm -rf rb_tree.bin
