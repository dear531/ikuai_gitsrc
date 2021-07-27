#!/bin/bash

##乘方
declare -i num=2**3

echo $num

num=`expr 2 + 5`
echo $num

tmpnum=`expr 2+5`
echo "\`expr 2+5\`: $tmpnum"

tmpnum=`expr 2 + 5`
echo "\`expr 2 + 5\`: $tmpnum"

tmpnum=`expr \( 2 + 5 \) \* 2`
echo "\`expr \\( 2 + 5 \\) \\* 2\`: $tmpnum"

tmpnum=$((2+6))
echo "\$((2+6)):$tmpnum"

tmpnum=$[2+7]
echo "\$[2+7] : $tmpnum"

echo "\$((1 > 2 ? 1 : 2)): $((1 > 2 ? 1 : 2))"
