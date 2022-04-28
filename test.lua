local zzz = require('zzz')
local floor = math.floor

---@param s string
---@return boolean[]
local function fun(s)
    local res = {}
    for i = 1, #s do
        local a, b = floor((i - 1) / 10), (i - 1) % 10
        local j = (floor(#s / 10) - a - 1) * 10 + b + 1
        res[i] = s:sub(j, j) == '0'
    end
    while #res < 400 do
        res[#res + 1] = false
    end
    return res
end

local field = fun(''
    .. '  0   000 '
    .. '0000   000'
    .. '00000 0000'
)
print('name:', zzz.name())
print('keys:', zzz.run(field, 'T', ' ', true, 'SIJOLZ'))
