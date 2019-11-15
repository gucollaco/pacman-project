#!/bin/bash

# compile and run
g++ classes/*.cpp main.cpp -o pacman -lglut -lGLU -lGL
./pacman
