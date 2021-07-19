#! /bin/bash


declare -A array=(
	[a]="A"
	[b]="B"
)

for i in ${array[@]}; do
	echo $i;
done

for k in ${!array[@]}; do
	echo "k = $k";
	echo "array[${k}]:${array[$k]}";
done
