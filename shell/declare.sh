#! /bin/bash


declare -A array=(
	[a]="A"
	[b]="B"
)

##定义之后设置打印
##trap "declare -p array" RETURN
##trap "declare -p array" DEBUG

declare -p array;

test1()
{
	return;
}

declare -f;
declare -F;

#declare_test="a";

main()
{
	local declare_test=0;
	echo $declare_test;

	declare -g declare_test;
	echo $declare_test;
}

main;
declare -g declare_test;
echo $declare_test;

##定义变量x，并将一个算数式赋值给他
x=6/3

##此时打印出的是算数式
echo "x = $x"

##定义变量x为整数
declare -i x

##定义为整型，但存储内容仍是一个表达式
echo "x = $x"

##再次赋值同一个算数表达式
x=6/3

##定义成整型之后赋值同一个表达式，结果不一样了
echo "x = $x"

##将字符串赋值给变量x，赋值的内容无效，保持原值
x=hello

echo "x=hello: x = $x"

##将浮点数赋值给整型，类型无效，错误
x=3.14
echo "x=3.14: x = $x"

##取消变量x的整数属性
declare +i x

##重新将算数表达式赋值给变量x
x=6/3

echo "declare +i x; x=6/3 : x = $x"

##求表达式的值
x=$[6/3]

echo " x=\$[6/3] :x = $x"

##另一种方法求表达式的值

x=$((6/3))
echo " x=\$((6/3)) :x = $x"

##加只读属性
declare -r x

echo "declare -r x: x = $x"

##尝试为只读变量赋值
x=5
echo "x = $x" ##值没有发生改变，赋值失败
