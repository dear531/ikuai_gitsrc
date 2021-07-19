#! /bin/bash

x=0
y=1

let "x += 1" "y += 2"
echo "x = $x, y = $y"

echo $?

let "y += 2" "x -= 1"

## return value is 1 when last arg is 0
echo $?
echo "x = $x, y = $y"


sum=0
let "sum = sum++ + ++sum"
echo "sum = $sum"

sum=0
let "sum = sum + sum++"
echo "sum = $sum"

sum=0
let "sum = ++sum + ++sum"
echo "sum = $sum"

bit=1
let "bit = bit << 1"
echo "bit = 1, bit = bit << 1: bit = $bit"

let "bit = bit >> 1"
echo "bit = 2, bit = bit >> 1: bit = $bit"

let "bit = 2#0011"
echo "bit = 2#0011 : bit = $bit"

bit=2#0011
echo "bit = 2#0011 : bit = $bit"

let "bit = 64#A"
echo "bit = 64#A : bit = $bit"

let "bit = 64#Z"
echo "bit = 64#Z : bit = $bit"

let "bit = 64#@"
echo "bit = 64#@ : bit = $bit"

let "bit = 64#_"
echo "bit = 64#_ : bit = $bit"
