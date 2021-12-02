#! /usr/bin/luajit

local t = {}
 for i=1,100 do
     t[i] = i
 end
 
 for i=1, 1000 do
     for j=1,1000 do
         for k,v in pairs(t) do
             --
         end
     end
 end
