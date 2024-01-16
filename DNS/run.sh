#!/bin/bash
rm main

# Compile the program
g++ -I/opt/homebrew/Cellar/nlohmann-json/3.11.3/include -std=c++11 src/*.cpp main.cpp -o main
# Check if the compilation was successful
if [ $? -eq 0 ]; then
    # Run the compiled program
    ./main
else
    echo "Compilation failed."
fi