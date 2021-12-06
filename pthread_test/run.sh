#! /bin/bash
for ((i = 0; i < 10000; i++))
do
	./a.out >> 1.txt;
done;
grep "x :0, y:0" 1.txt

