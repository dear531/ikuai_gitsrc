#! /bin/bash

a=hello
b=world

[ "$a" = "$b" ]
echo $?

test "$a" != "$b"
echo $?

## incrrect expression
[ "$a"=="$b" ]
echo $?

## incrrect expression
[ "$a"="$b" ]
echo $?

[ "$a" == "$b" ]
echo $?
