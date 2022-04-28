extern "C" {
#include "lauxlib.h"
#include "lualib.h"
int luaopen_zzz(lua_State *L);
}

int main() {
    lua_State *L = luaL_newstate();
    luaL_openlibs(L);
    luaopen_zzz(L);
    if (luaL_loadfile(L, "test.lua") || lua_pcall(L, 0, 0, 0)) {
        printf("%s\n", lua_tostring(L, -1));
        lua_pop(L, 1);
        return 1;
    }
    lua_close(L);
    printf("OK\n");
    return 0;
}
