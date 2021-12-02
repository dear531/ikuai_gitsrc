#! /usr/bin/luajit
for i=1, 1000 do
      local newstr, n, err = ngx.re.gsub("hello, world", "([a-z])[a-z]+", "[$0,$1]", "i")
end
