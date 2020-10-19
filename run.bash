#!/bin/bash
g++ -lm -O2 -o ../bin/$1 $1.c && time ../bin/$1 && cat $1.out
