#include <cstdio>
extern "C" {
#include "lauxlib.h"
#include "lua.h"
#include "lualib.h"
}

static int say_hello(lua_State *L) {
    printf("Hello, from zzz!\n");
    return 0;
}

static const struct luaL_Reg funcList[] = {
    {"sayHello", say_hello},
    {0, 0}};

extern "C" int luaopen_zzz(lua_State *L) {
    luaL_register(L, "zzz", funcList);
    return 1;
}
