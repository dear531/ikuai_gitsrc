#! /bin/bash

## leocheung@leocheung-CW65S:~/source/ikuai_gitsrc/shell$ bash exit_status.sh 
## 0
## 1
## leocheung@leocheung-CW65S:~/source/ikuai_gitsrc/shell$ echo $?
## 1


return_status()
{
	return 1;
}

ls > /dev/null 2>&1
echo $?

return_status;
echo $?

return_status;
exit
