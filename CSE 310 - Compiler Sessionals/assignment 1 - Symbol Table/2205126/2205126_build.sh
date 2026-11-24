#!/bin/bash

FILE_NAME="2205126_symbol_table"

echo "Compiling ${FILE_NAME}.cpp..."

g++ -Wall -g -fsanitize=address ${FILE_NAME}.cpp -o ${FILE_NAME}.out

if [ $? -eq 0 ]; then
    echo "Build successful."
    echo "Running the program..."

    ./${FILE_NAME}.out sample_input.txt sample_output.txt
    
    echo "Done! Check sample_output.txt for your results."
else
    echo "Build failed."
    exit 1
fi