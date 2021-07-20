#! /bin/bash

for i in "${@}"; do
	echo "$i";
done

for i in "a${*}b"; do
	echo "111$i";
done
	echo "222"

for ((i = 0; i <= $#; i++)); do
	eval echo \${${i}}
	eval echo \$${i}
done

echo "IFS:[$IFS]"

echo "$*"
echo $@e
