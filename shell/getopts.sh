#/bin/bash

## leocheung@leocheung-CW65S:~/source/ikuai_gitsrc/shell$ bash getopts.sh -t
## OPTIND starts at 1
## Unknown option t
## OPTIND is now 2
## leocheung@leocheung-CW65S:~/source/ikuai_gitsrc/shell$ bash getopts.sh -t
## OPTIND starts at 1
## getopts.sh: 非法选项 -- t
## Unknown option 
## OPTIND is now 2


echo "OPTIND starts at $OPTIND"

## q:if a character is followed by a colon, the option is expected to have an argument, which should be separated from it by white space. 
while getopts ":pq:abc" optname
do
	## case word in [ [(] pattern [ | pattern ] ... ) list ;; ] ... esac
	case "$optname" in
		("a"|"b"|"c"|"p")
			echo "Option $optname is specified"
			;;
		"q")
			echo "Option $optname has value $OPTARG"
			;;
		"?")
			## If an invalid option is seen, getopts places ? into name and,
			## if not silent, prints an error message and unsets OPTARG.
			## If getopts is silent, the option character found is placed in OPTARG and no diagnostic message is printed.

			echo "Unknown option $OPTARG"
			;;
		":")
			echo "No argmanet value for option $OPTARG"
			;;
		"*")
			# should not occur
			echo "Unknown option $OPTARG"
			;;
	esac
	echo "OPTIND is now $OPTIND"
done
