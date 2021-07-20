#! /bin/bash
a="abc"
test $a
echo $?
test -n "$a"
echo $?
test -z "$a"
echo $?

if [ -n $a ]; then
	echo "\$a = $a is not null"
fi

if [ -z $b ]; then
	echo "\$b = \"$b\" is null"
fi

if test $a; then
	echo "\$a = $a is not null"
fi

if test -n "$b"; then
	echo "test -n \"\$b\" :\$b = [$b] is null"
fi

if test -n "$b"; then
	echo "\$b = \"$b\" is null"
fi

if test -z "$b"; then
	echo "test -z \$b = \"$b\" is null"
fi

if ! test -z "$b"; then
	echo "! test -z \$b = \"$b\" is null"
fi
