========= 第一调试程序 ==================
leocheung@leocheung-CW65S:~/source/openresty$ resty -e "ngx.say('hello world'); "
hello world


========= 原理查看 =================
leocheung@leocheung-CW65S:~/source/openresty$ resty -e "ngx.say('hello world'); ngx.sleep(10)" & 
[2] 16489
leocheung@leocheung-CW65S:~/source/openresty$ hello world

leocheung@leocheung-CW65S:~/source/openresty$ ps -ef |grep nginx
root      4857     1  0 10:00 ?        00:00:00 nginx: master process /usr/sbin/nginx -g daemon on; master_process on;
www-data  4859  4857  0 10:00 ?        00:00:00 nginx: worker process
www-data  4861  4857  0 10:00 ?        00:00:03 nginx: worker process
www-data  4862  4857  0 10:00 ?        00:00:03 nginx: worker process
www-data  4864  4857  0 10:00 ?        00:00:03 nginx: worker process
leocheu+ 16491 16489  0 18:46 pts/20   00:00:00 /usr/local/openresty/nginx/sbin/nginx -p /tmp/resty_YgZEGIRTHG/ -c conf/nginx.conf
leocheu+ 16493 14456  0 18:46 pts/20   00:00:00 grep --color=auto nginx
leocheung@leocheung-CW65S:~/source/openresty$ 
========= config ==================
mkdir logs
mkdir conf
vim conf/nginx.conf

leocheung@leocheung-CW65S:~/source/openresty$ cat conf/nginx.conf 
events {
    worker_connections 1024;
}
http {
    server {
        listen 8080;
        location / {
            content_by_lua '
                ngx.say("hello, world")
            ';
        }
    }
}


===启动，启动验证，停止，停止验证=================

leocheung@leocheung-CW65S:~/source/openresty$ openresty -p `pwd` -c conf/nginx.conf
leocheung@leocheung-CW65S:~/source/openresty$ curl -i 127.0.0.1:8080
HTTP/1.1 200 OK
Server: openresty/1.19.3.1
Date: Tue, 30 Nov 2021 10:48:01 GMT
Content-Type: text/plain
Transfer-Encoding: chunked
Connection: keep-alive

hello, world
leocheung@leocheung-CW65S:~/source/openresty$ openresty -s quit -p `pwd` -c conf/nginx.conf
leocheung@leocheung-CW65S:~/source/openresty$ curl -i 127.0.0.1:8080
curl: (7) Failed to connect to 127.0.0.1 port 8080: 拒绝连接

=====其他相关命令===============================
openresty -p `pwd` -c ./conf/nginx.conf 启动
openresty -p `pwd` -c ./conf/nginx.conf -s stop 停止
lsof -i:端口号 查看服务状态


============= 配置openresty调用lua文件代码 ===========
$ vim lua/hello.lua
$ vim conf/nginx.conf

重启
sudo kill -HUP `cat logs/nginx.pid`
或是启动
openresty -p `pwd` -c ./conf/nginx.con

cat logs/nginx.pid
查看nginx的pid文件，pid并没有发生变化

leocheung@leocheung-CW65S:~/source/ikuai_gitsrc/openresty$ curl localhost:8080 -i
HTTP/1.1 200 OK
Server: openresty/1.19.3.1
Date: Wed, 01 Dec 2021 02:51:11 GMT
Content-Type: text/plain
Transfer-Encoding: chunked
Connection: keep-alive

hello, world by lua file

