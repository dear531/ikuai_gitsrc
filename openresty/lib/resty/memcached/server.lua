local new_tab = require "table.new"
local str_sub = string.sub
local re_find = ngx.re.find
local mc_shdict = ngx.shared.memcached
local _M = { _VERSION = '0.01' }

local function parse_args(s, start)
    local arr = {}
    while true do
        local from, to = re_find(s, [[\S+]], "jo", {pos = start})
        if not from then
            break
        end
        table.insert(arr, str_sub(s, from, to))
        start = to + 1
    end
    return arr
end

function _M.get(tcpsock, keys)
    local reply = ""
    for i = 1, #keys do
        local key = keys[i]
        local value, flags = mc_shdict:get(key)
        if value then
            local flags  = flags or 0
            reply = reply .. "VALUE" .. key .. " " .. flags .. " " .. #value .. "\r\n" .. value .. "\r\n"
        end
    end
    reply = reply ..  "END\r\n"
    tcpsock:settimeout(1000)  -- one second timeout
    local bytes, err = tcpsock:send(reply)
    if not err then
	return 1
    else
	return 0
    end
end

function _M.set(tcpsock, res)
    local reply =  ""
    local key = res[1]
    local flags = tostring(res[2]) or "0"
    local exptime = tostring(res[3]) or "0"
    local bytes = res[4]
    local value, err = tcpsock:receive(tonumber(bytes) + 2)
    local cjson = require "cjson"
    if str_sub(value, -2, -1) == "\r\n" then
	--os.execute("echo \"value:" .. value .. ", bytes:" .. bytes .. ":" .. "\" >> /tmp/nginx.log")
	--os.execute("echo \"" .. "str_sub(" .. value .. ", 1, ".. bytes .. ") :" .. str_sub(value, 1, bytes) .. "\" >> /tmp/nginx.log")
	--os.execute("echo \"" .. key .. ":" .. str_sub(value, 1, bytes) .. ":" .. exptime .. ":" .. flags .. ":" .. cjson.encode(res) .. "\" >> /tmp/nginx.log")
        local succ, err, forcible = mc_shdict:set(key, str_sub(value, 1, bytes))
        --local succ, err, forcible = mc_shdict:set("dog", "32", 0, 0)
        if succ then
            reply = reply .. "STORED\r\n"
        else
            reply = reply .. "SERVER_ERROR " .. err .. "\r\n"
        end
    else
        reply = reply .. "ERROR\r\n"
    end
    tcpsock:settimeout(1000)  -- one second timeout
    local bytes, err = tcpsock:send(reply)
end

function _M.run()
    local tcpsock = assert(ngx.req.socket(true))
    while true do
        tcpsock:settimeout(60000) -- 60 seconds
        local data, err = tcpsock:receive("*l")
        local command, args
        if data then
            local from, to, err = re_find(data, [[(\S+)]], "jo")
	os.execute("echo \"" .. data .. ":" .. from .. ":" .. to .. ":" .. "\" >> /tmp/nginx.log")
            if from then
                command = str_sub(data, from, to)
                args = parse_args(data, to + 1)
            end
        end
        if args then
            local args_len = #args
            if command == 'get' and args_len > 0 then
               if 0 ~= _M.get(tcpsock, args) then
			break
	       end
            elseif command == "set" and args_len == 4 then
                _M.set(tcpsock, args)
            end
        end
    end
end

return _M
