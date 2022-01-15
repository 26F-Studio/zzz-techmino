extern "C" {
#include "lauxlib.h"
#include "lualib.h"
int luaopen_zzz(lua_State *L);
}
#define CODE(...) #__VA_ARGS__
char *code = CODE(
local zzz = require("zzz")
print(zzz.name())
local field = {
    true, false, true, true, false, false, false, false, false, false,
    false, false, false, false, false, false, false, false, false, false,
}
for i = 21, 400 do
    field[i] = false
end
print(zzz.run(field,"S"," ",true,"TIJOLZ"))
);

int main() {
    lua_State *L = luaL_newstate();
    luaL_openlibs(L);
    luaopen_zzz(L);
    if (luaL_dostring(L, code)) {
        printf("%s\n", lua_tostring(L, -1));
        lua_pop(L, 1);
        return 1;
    }
    lua_close(L);
    return 0;
}
