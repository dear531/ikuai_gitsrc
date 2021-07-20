#! /bin/bash

a=hello
b=world

[ "$a" = "$b" ]
echo $?

test "$a" != "$b"
echo $?
