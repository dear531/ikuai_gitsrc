#! /usr/bin/luajit
local version = {
  major = 1,
  minor = 1,
  patch = 1
  }
version = setmetatable(version, {
    __tostring = function(t)
      return string.format("%d.%d.%d", t.major, t.minor, t.patch)
    end
  })
print(tostring(version))
