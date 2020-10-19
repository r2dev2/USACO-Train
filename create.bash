#!/bin/bash
cat $1.c &> /dev/null || sed "s/taskname/$1/g" /mnt/c/Users/ronak/Documents/Workspace/USACO-Attempts/train/template.c > $1.c
touch $1.in
echo "gcc -O2 -o ../bin/$1 $1.c -lm && time ../bin/$1 && cat $1.out"
printf "gcc -O2 -o ../bin/$1 $1.c -lm && time ../bin/$1 && cat $1.out" | powershell.exe -c clip
