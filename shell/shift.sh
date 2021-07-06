#! /bin/bash

## leocheung@leocheung-CW65S:~/source/ikuai_gitsrc/shell$ bash shift.sh  1 2 "3 4"
## ${@}:1 2 3 4
## 3 parameters
## ${@}:2 3 4
## 2 parameters
## ${@}:3 4
## 1 parameters


while (($# > 0)); do
	echo "\${@}:${@}"
	echo $# parameters

	shift
done
