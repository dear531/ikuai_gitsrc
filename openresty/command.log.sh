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

==== 调试关闭缓存设置，商用去掉该选项使其缓存，要不然会影响性能 ====

conf/nginx.conf

leocheung@leocheung-CW65S:~/source/ikuai_gitsrc/openresty$ kill -HUP `cat logs/nginx.pid`
leocheung@leocheung-CW65S:~/source/ikuai_gitsrc/openresty$ curl localhost:8080 -i
HTTP/1.1 200 OK
Server: openresty/1.19.3.1
Date: Wed, 01 Dec 2021 03:08:22 GMT
Content-Type: text/plain
Transfer-Encoding: chunked
Connection: keep-alive

hello, world by lua file and no cache
leocheung@leocheung-CW65S:~/source/ikuai_gitsrc/openresty$ vim lua/hello.lua 
leocheung@leocheung-CW65S:~/source/ikuai_gitsrc/openresty$ curl localhost:8080 -i
HTTP/1.1 200 OK
Server: openresty/1.19.3.1
Date: Wed, 01 Dec 2021 03:08:42 GMT
Content-Type: text/plain
Transfer-Encoding: chunked
Connection: keep-alive

hello, world by lua file and no cache2
leocheung@leocheung-CW65S:~/source/ikuai_gitsrc/openresty$ 

===== 安装restydoc命令，查看帮助 =====

$ sudo aptitude search resty
i   openresty                                                                                     - core server of OpenResty for production use                                                             
p   openresty-asan                                                                                - The AddressSanitizer (ASAN) version of OpenResty                                                        
p   openresty-asan-dbgsym                                                                         - Debug symbols for the openresty-asan package                                                            
p   openresty-dbgsym                                                                              - Debug symbols of OpenResty packages                                                                     
p   openresty-debug                                                                               - debug version of OpenResty core server                                                                  
p   openresty-debug-dbgsym                                                                        - Debug symbols of OpenResty packages - debug version                                                     
p   openresty-openssl                                                                             - OpenSSL library for use by OpenResty ONLY                                                               
p   openresty-openssl-dbgsym                                                                      - Debug symbols for OpenResty's OpenSSL library                                                           
p   openresty-openssl-debug                                                                       - Debug version of the OpenSSL library for OpenResty                                                      
p   openresty-openssl-debug-dbgsym                                                                - Debug symbols for OpenResty's OpenSSL library - debug version                                           
p   openresty-openssl-debug-dev                                                                   - Development files for OpenResty's OpenSSL library - debug version                                       
p   openresty-openssl-dev                                                                         - Development files for OpenResty's OpenSSL library                                                       
i A openresty-openssl111                                                                          - OpenSSL 1.1.1 library for use by OpenResty ONLY                                                         
p   openresty-openssl111-asan                                                                     - Clang AddressSanitizer Debug version of the OpenSSL library for OpenResty                               
p   openresty-openssl111-asan-dbgsym                                                              - Debug symbols for the openresty-openssl111-asan package                                                 
p   openresty-openssl111-asan-dev                                                                 - Clang AddressSanitizer version of development files for OpenResty's OpenSSL library                     
p   openresty-openssl111-dbgsym                                                                   - Debug symbols for OpenResty's OpenSSL 1.1.1 library                                                     
p   openresty-openssl111-debug                                                                    - Debug version of the OpenSSL 1.1.1 library for OpenResty                                                
p   openresty-openssl111-debug-dbgsym                                                             - Debug symbols for OpenResty's OpenSSL 1.1.1 library - debug version                                     
p   openresty-openssl111-debug-dev                                                                - Development files for OpenResty's OpenSSL 1.1.1 library - debug version                                 
p   openresty-openssl111-dev                                                                      - Development files for OpenResty's OpenSSL 1.1.1 library                                                 
i A openresty-opm                                                                                 - OpenResty Package Manager (OPM)                                                                         
i A openresty-pcre                                                                                - Perl-compatible regular expression library for use by OpenResty ONLY                                    
p   openresty-pcre-asan                                                                           - Clang AddressSanitizer version of the Perl-compatible regular expression library for OpenResty          
p   openresty-pcre-asan-dbgsym                                                                    - Debug symbols for the openresty-pcre-asan package                                                       
p   openresty-pcre-asan-dev                                                                       - Development files for openresty-pcre-asan                                                               
p   openresty-pcre-dbgsym                                                                         - Debug symbols for Perl-compatible regular expression library for use by OpenResty ONLY                  
p   openresty-pcre-dev                                                                            - Development files for Perl-compatible regular expression library for use by OpenResty ONLY              
i A openresty-resty                                                                               - resty command-line utility for OpenResty                                                                
p   openresty-restydoc                                                                            - OpenResty documentation tool, restydoc                                                                  
p   openresty-valgrind                                                                            - valgrind debug version of OpenResty core server                                                         
p   openresty-valgrind-dbgsym                                                                     - Debug symbols of OpenResty packages - valgrind debug version                                            
i A openresty-zlib                                                                                - The zlib compression library for use by Openresty ONLY                                                  
p   openresty-zlib-asan                                                                           - Gcc AddressSanitizer version for the zlib compression library for OpenResty                             
p   openresty-zlib-asan-dbgsym                                                                    - Debug symbols for the openresty-zlib-asan package                                                       
p   openresty-zlib-asan-dev                                                                       - Development files for OpenResty's zlib library                                                          
p   openresty-zlib-dbgsym                                                                         - Debug symbols for OpenResty's zlib library                                                              
p   openresty-zlib-dev                                                                            - Provides C header and static library for OpenResty's zlib library     


leocheung@leocheung-CW65S:/media/leocheung/sdb500g/source/resty-cli/bin$ sudo apt-get install openresty-restydoc
正在读取软件包列表... 完成
正在分析软件包的依赖关系树       
正在读取状态信息... 完成       
下列【新】软件包将被安装：
  openresty-restydoc
升级了 0 个软件包，新安装了 1 个软件包，要卸载 0 个软件包，有 89 个软件包未被升级。
需要下载 511 kB 的归档。
解压缩后会消耗 3,075 kB 的额外空间。
获取:1 http://openresty.org/package/ubuntu xenial/main amd64 openresty-restydoc amd64 1.19.9.1-1~xenial1 [511 kB]
已下载 511 kB，耗时 1秒 (434 kB/s)         
正在选中未选择的软件包 openresty-restydoc。
(正在读取数据库 ... 系统当前共安装有 318446 个文件和目录。)
正准备解包 .../openresty-restydoc_1.19.9.1-1~xenial1_amd64.deb  ...
正在解包 openresty-restydoc (1.19.9.1-1~xenial1) ...
正在设置 openresty-restydoc (1.19.9.1-1~xenial1) ...


==== 命令使用 ====

leocheung@leocheung-CW65S:/media/leocheung/sdb500g/source/resty-cli/bin$ restydoc -h
Usage:
    /usr/bin/restydoc [options] [module]

Options:
    -h              Print this help.

    -r DIR          Specify the root directory of docs. Default
                    to the OpenResty installation tree containing
                    the current restydoc tool.

    -s SECTION      Specify the section name to be searched

For bug reporting instructions, please see:

    <https://openresty.org/en/community.html>

Copyright (C) Yichun Zhang (agentzh). All rights reserved.



leocheung@leocheung-CW65S:/media/leocheung/sdb500g/source/resty-cli/bin$ restydoc -s ngx.say |cat 
  ngx.say
    syntax: *ok, err = ngx.say(...)*

    context: *rewrite_by_lua*, access_by_lua*, content_by_lua**

    Just as ngx.print but also emit a trailing newline.

==== 帮助命令 opm ====
leocheung@leocheung-CW65S:~/source/ikuai_gitsrc/openresty$ opm search http
openresty/lua-resty-upstream-healthcheck          Lua health-checker for Nginx upstream servers
openresty/lua-resty-upload                        Streaming reader and parser for HTTP file uploading based on ngx_lua cosocket
openresty/lua-resty-core                          New FFI-based Lua API for the ngx_lua module
dailymotion/lua-nginx-guard-jwt                   Verification of the JWT Token with mapping of the token claims values to the HTTP Headers of Query.
040Lab/lua-resty-openidc                          A library for NGINX implementing the OpenID Connect Relying Party (RP) and the OAuth 2.0 Resource Server (RS) functionality
upyun/lua-resty-checkups                          Manage Nginx upstreams in pure Lua
zmartzone/lua-resty-openidc                       A library for NGINX implementing the OpenID Connect Relying Party (RP) and the OAuth 2.0 Resource Server (RS) functionality
jobteaser/lua-resty-aws-signature                 AWS signature V4 headers generator
ledgetech/lua-resty-http                          Lua HTTP client cosocket driver for OpenResty/ngx_lua
ledgetech/lua-resty-http                          Lua HTTP client cosocket driver for OpenResty/ngx_lua
flex-runtime/lua-resty-cookie                     This library parses HTTP Cookie header for Nginx and returns each field in the cookie
bungle/lua-resty-reqargs                          HTTP Request Arguments and File Uploads Helper
bungle/lua-resty-session                          Session Library for OpenResty - Flexible and Secure
antonheryanto/lua-resty-post                      Openresty utility for parsing HTTP POST data
mashirozx/lua-resty-tencent-cos-signature         Tencent QCloud COS Openresty request signature authorization headers generator
ktalebian/lua-resty-cookie                        This library parses HTTP Cookie header for Nginx and returns each field in the cookie
ktalebian/twilio-lua-resty-cookie                 This library parses HTTP Cookie header for Nginx and returns each field in the cookie
GUI/lua-resty-aws-signature                       AWS signature V4 headers generator
pintsized/lua-resty-http                          Lua HTTP client cosocket driver for OpenResty/ngx_lua
brianloss/lua-resty-openidc                       A library for NGINX implementing the OpenID Connect Relying Party (RP) and the OAuth 2.0 Resource Server (RS) functionality
DevonStrawn/lua-resty-route                       URL Routing Library for OpenResty Supporting Pluggable Matching Engines
knight42/lua-resty-http-digest                    HTTP Digest Access Authentication in Lua for OpenResty
zandbelt/lua-resty-openidc                        A library for NGINX implementing the OpenID Connect Relying Party (RP) and the OAuth 2.0 Resource Server (RS) functionality
gnois/losty                                       Functional style web framework for OpenResty
slact/durpina                                     Dynamic Upstream Reversy Proxying wIth Nice API
toruneko/lua-resty-upstream                       pure lua nginx upstream management for OpenResty/LuaJIT
shayanh/lua-resty-checkups                        Manage Nginx upstreams in pure Lua
mycsj/lua-resty-rx-test                           Yet Another HTTP library for OpenResty
nmdguerreiro/lua-resty-opencage-geocoder          Lua client for the Opencage forward/reverse geocoding API
knyar/nginx-lua-prometheus                        Prometheus metric library for Nginx
tokers/lua-resty-requests                         Yet Another HTTP library for OpenResty
un-def/httoolsp                                   A collection of HTTP-related pure Lua helper functions
BoTranVan/nginx-module-vts                        New FFI-based Lua API for the ngx_lua module
KSDaemon/wiola                                    LUA WAMP router
firesnow/lua-resty-checkups                       Manage Nginx upstreams in pure ngx_lua
fffonion/lua-resty-shdict-server                  A HTTP and Redis protocol compatible interface for debugging ngx.shared API
fffonion/lua-resty-acme                           Automatic Let's Encrypt certificate serving and Lua implementation of ACME procotol
fffonion/lua-resty-multiplexer                    Transparent port service multiplexer for stream subsystem
jie123108/lua-resty-stats                         A statistical module for nginx base on ngx_lua, Statistical key and values are configurable, can use the nginx core's variables and this module's variables. The statistical result store in mongodb.(github.com/jie123108/lua-resty-stats)
hamishforbes/ledge                                An RFC compliant and ESI capable HTTP cache for Nginx / OpenResty, backed by Redis
hamishforbes/lua-resty-upstream                   Upstream connection load balancing and failover module
hamishforbes/lua-resty-consul                     Library to interface with the consul HTTP API
lilien1010/lua-resty-s3uploader                   an http s3 client for openresty
duhoobo/lua-resty-smtp                            A http to smtp bridge library for the ngx_lua module
duhoobo/lua-resty-auth                            A Lua resty module for HTTP Authentication (both basic and digest scheme supported, referring to RFC 2617)
starjun/openstar                                  using openresty build WAF...
p0pr0ck5/lua-resty-waf                            High-performance WAF built on the OpenResty stack
p0pr0ck5/lua-resty-influx                         OpenResty client writer for InfluxDB
p0pr0ck5/lua-resty-cookie                         Lua library for HTTP cookie manipulations for OpenResty/ngx_lua
agentzh/lua-resty-http                            Lua HTTP client cosocket driver for OpenResty/ngx_lua


============ websocket lib =====
leocheung@leocheung-CW65S:~/source/ikuai_gitsrc/openresty$ opm search lua-resty-websocket
openresty/lua-resty-websocket                     Lua WebSocket implementation for the ngx_lua module
openresty/lua-resty-websocket                     Lua WebSocket implementation for the ngx_lua module
d80x86/lua-resty-tofu                             (alpha) a modern framework
KSDaemon/wiola                                    LUA WAMP router


===========================

=============lua调用c库函数==============

可以看到lua和luajit的不同

leocheung@leocheung-CW65S:~/source/ikuai_gitsrc/openresty$ lua lua/c_lib_printf.lua 
lua: lua/c_lib_printf.lua:1: module 'ffi' not found:
	no field package.preload['ffi']
	no file './ffi.lua'
	no file '/usr/local/share/lua/5.1/ffi.lua'
	no file '/usr/local/share/lua/5.1/ffi/init.lua'
	no file '/usr/local/lib/lua/5.1/ffi.lua'
	no file '/usr/local/lib/lua/5.1/ffi/init.lua'
	no file '/usr/share/lua/5.1/ffi.lua'
	no file '/usr/share/lua/5.1/ffi/init.lua'
	no file './ffi.so'
	no file '/usr/local/lib/lua/5.1/ffi.so'
	no file '/usr/lib/x86_64-linux-gnu/lua/5.1/ffi.so'
	no file '/usr/lib/lua/5.1/ffi.so'
	no file '/usr/local/lib/lua/5.1/loadall.so'
stack traceback:
	[C]: in function 'require'
	lua/c_lib_printf.lua:1: in main chunk
	[C]: ?
leocheung@leocheung-CW65S:~/source/ikuai_gitsrc/openresty$ luajit lua/c_lib_printf.lua 
Hello world!
leocheung@leocheung-CW65S:~/source/ikuai_gitsrc/openresty$ 

======= 能被JIT和不能被JIT的实例 ===================
leocheung@leocheung-CW65S:~/source/ikuai_gitsrc/openresty$ resty -j v lua/JIT.lua 
[TRACE   1 regex.lua:1081 loop]
[TRACE   2 (1/10) regex.lua:1116 -> 1]
[TRACE   3 (1/21) regex.lua:1084 -> 1]
leocheung@leocheung-CW65S:~/source/ikuai_gitsrc/openresty$ resty -j v lua/NYI.lua 
[TRACE   1 NYI.lua:4 loop]
[TRACE --- NYI.lua:9 -- NYI: bytecode 72 at NYI.lua:10]
[TRACE --- NYI.lua:9 -- NYI: bytecode 72 at NYI.lua:10]
[TRACE --- NYI.lua:9 -- NYI: bytecode 72 at NYI.lua:10]
[TRACE --- NYI.lua:9 -- NYI: bytecode 72 at NYI.lua:10]
[TRACE --- NYI.lua:9 -- NYI: bytecode 72 at NYI.lua:10]
[TRACE --- NYI.lua:9 -- NYI: bytecode 72 at NYI.lua:10]
[TRACE --- NYI.lua:9 -- NYI: bytecode 72 at NYI.lua:10]
[TRACE --- NYI.lua:9 -- NYI: bytecode 72 at NYI.lua:10]
[TRACE --- NYI.lua:9 -- NYI: bytecode 72 at NYI.lua:10]
[TRACE --- NYI.lua:9 -- NYI: bytecode 72 at NYI.lua:10]
[TRACE --- NYI.lua:9 -- NYI: bytecode 72 at NYI.lua:10]
[TRACE --- NYI.lua:8 -- NYI: bytecode 72 at NYI.lua:10]
[TRACE --- NYI.lua:8 -- NYI: bytecode 72 at NYI.lua:10]
[TRACE --- NYI.lua:8 -- NYI: bytecode 72 at NYI.lua:10]
[TRACE --- NYI.lua:8 -- NYI: bytecode 72 at NYI.lua:10]
[TRACE --- NYI.lua:8 -- NYI: bytecode 72 at NYI.lua:10]


====== 弱引用设置 ============
leocheung@leocheung-CW65S:~/source/ikuai_gitsrc/openresty$ resty lua/setmatetable_mode_v.lua 
2
0

