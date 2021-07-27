#! /bin/bash

n=2
let "n = n>>1"
echo "n=2; n = n>>1: n = $n"

let "n = 8 & 4"
echo "n = 8 & 4: n = $n"

let "n = 8 | 4"
echo "n = 8 | 4: n = $n"

let "n = ~8"
echo "n = ~8: n = $n"

echo "2<<1 : $((2<<1))"

echo "4 ^ 6 : $[4 ^ 6]"

n=1
let "n |= 2"
echo "n=1; n |= 2; n = $n"

n=1
m=2
echo "n=$n;m=$m; n + m++ = $((n + m++))"
echo "n=$n;m=$m; n + ++m = $((n + ++m))"
