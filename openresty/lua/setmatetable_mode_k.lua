#! /usr/bin/luajit

local tb = {}
tb[{color = red}] = "red"
local fc = function() print("func") end
tb[fc] = "func"
fc = nil
--当key值对应的value没有引用时，释放
setmetatable(tb, {__mode = "k"})
for k,v in pairs(tb) do
     print(v)
end
collectgarbage()
print("----------")
for k,v in pairs(tb) do
     print(v)
end
