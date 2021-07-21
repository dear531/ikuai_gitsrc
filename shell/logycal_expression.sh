#/bin/bash

[ -a $0 -a -r $0 ]
echo "[ -a \$0 -a -r \$0 ]:$?"

if [ -f $0 ]; then
	echo "$0 exists"	
fi

if test -f $0;then
	echo "to use test to test $0, $0 exists"
fi

[ "$0" == "logycal_expression.sh" ] && { echo "this file is logycal_expression.sh"; }

test "$0" == "logycal_expression.sh" && (echo "this file is logycal_expression.sh")

if [[ "a" == "a" && "b" == "b" ]]; then
	echo "this is expression"
fi
