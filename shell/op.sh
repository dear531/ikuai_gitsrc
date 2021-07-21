#! /bin/bash

[ 1 -eq 1 ]
echo "[ 1 -eq 1 ]:$?"

[ 1 -lt 2 ]
echo "[ 1 -lt 2 ]:$?"

[ 1 -le 2 ]
echo "[ 1 -le 2 ]:$?"

[ 1 -ge 0 ]
echo "[ 1 -ge 0 ]:$?"

a=1
[ "$a" -eq 1 ]
echo "a=1; [ \"\$a\" -eq 1 ]:$?"

b=1
[ "$a" -eq "$b" ]
echo "a=1;b=1; [ \"\$a\" -eq \"\$b\" ] : $?"

[ -a op.sh ]
echo "[ -a op.sh ]:$?"

[ -b /dev/sda ]
echo "[ -b /dev/sda ] :$?"

[ -c /dev/tty ]
echo "[ -c /dev/tty ] :$?"

[ -r $0 ]
echo "[ -r \$0 ]:$?"

## arg1file newer than arg2file
[ $0 -nt /dev/tty ]
echo "[ $0 -nt /dev/tty ]:$?"
