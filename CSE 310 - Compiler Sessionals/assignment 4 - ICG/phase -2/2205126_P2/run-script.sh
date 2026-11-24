#!/bin/bash

# Exit immediately if any command fails
set -e

# Run ANTLR tool using the command wrapper
antlr4 -v 4.13.2 -Dlanguage=Cpp -visitor -no-listener CSubset_2205126.g4 Lexer_2205126.g4

# Compile C++ files
g++ -std=c++17 -w -I/usr/local/include/antlr4-runtime main.cpp ICGVisitor.cpp CSubset_2205126Lexer.cpp CSubset_2205126Parser.cpp CSubset_2205126BaseVisitor.cpp CSubset_2205126Visitor.cpp -L/usr/local/lib/ -lantlr4-runtime -pthread -o icg.out

# Run compiler if input file is provided
if [ ! -z "$1" ]; then
    LD_LIBRARY_PATH=/usr/local/lib ./icg.out "$1"
fi