extern "C" {
#include "lauxlib.h"
}
#include "ai_zzz.h"
#include "rule_toj.h"
#include "search_tspin.h"
#include "tetris_core.h"

static const int boardW = 10, boardH = 40;
static m_tetris::TetrisEngine<rule_toj::TetrisRule, ai_zzz::TOJ, search_tspin::Search> tetris_ai;
static int combo_table[12] = {0, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 5};

// run(field, hand, hold, canhold, next)
static int run(lua_State *L) {
    if (!tetris_ai.prepare(boardW, boardH)) {
        lua_pushnil(L);
        lua_pushstring(L, "tetris_ai prepare failed");
        return 2;
    }
    if (!lua_istable(L, 1)) {
        lua_pushnil(L);
        lua_pushstring(L, "field should be a table");
        return 2;
    }
    const char *hand = lua_tostring(L, 2);
    const char *hold = lua_tostring(L, 3);
    bool canhold = lua_toboolean(L, 4);
    const char *next = lua_tostring(L, 5);
    tetris_ai.ai_config()->table = combo_table;
    tetris_ai.ai_config()->table_max = 12;
    uint8_t board[boardW * boardH];
    for (int i = 0; i < boardW * boardH; i++) {
        lua_rawgeti(L, 1, i + 1);
        board[i] = (uint8_t)lua_toboolean(L, -1);
        lua_pop(L, 1);
    }
    m_tetris::TetrisMap map(boardW, boardH);
    for (int y = 0, add = 0; y < boardH; ++y, add += boardW) {
        for (int x = 0; x < boardW; ++x) {
            if (board[x + add]) {
                map.top[x] = map.roof = y + 1;
                map.row[y] |= 1 << x;
                ++map.count;
            }
        }
    }
    m_tetris::TetrisBlockStatus status(*hand, 3, 20, 0);
    m_tetris::TetrisNode const *node = tetris_ai.get(status);
    auto target = tetris_ai.run_hold(map, node, *hold, canhold, next, strlen(next)).target;
    if (target != nullptr) {
        std::vector<char> ai_path = tetris_ai.make_path(node, target, map);
        lua_pushlstring(L, ai_path.data(), ai_path.size());
        return 1;
    }
    lua_pushnil(L);
    lua_pushstring(L, "got nothing");
    return 2;
}

static int name(lua_State *L) {
    lua_pushstring(L, tetris_ai.ai_name().c_str());
    return 1;
}

static const struct luaL_Reg funcList[] = {
    {"run", run},
    {"name", name},
    {0, 0}};

extern "C" __declspec(dllexport) int luaopen_zzz(lua_State *L) {
    luaL_register(L, "zzz", funcList);
    return 1;
}
