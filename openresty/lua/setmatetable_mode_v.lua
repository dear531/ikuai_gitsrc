#! /usr/bin/luajit

local tb = {}
tb[1] = {red}
tb[2] = function() print("func") end
--[[
  如果 __mode 的值是 k，那就意味着这个 table 的 键 是弱引用。
  如果 __mode 的值是 v，那就意味着这个 table 的 值 是弱引用。
  当然，你也可以设置为 kv，表明这个表的键和值都是弱引用。
--]]
setmetatable(tb, {__mode = "v"})
print(#tb)  -- 2
collectgarbage()
print(#tb) -- 0
