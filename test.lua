local zzz = require("zzz")
print(zzz.name())
local field = {
    true, false, true, true, false, false, false, false, false, false,
    false, false, false, false, false, false, false, false, false, false,
}
for i = 21, 400 do
    field[i] = false
end
print(zzz.run(field, "S", " ", true, "TIJOLZ"))
