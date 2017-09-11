    NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
};

static int json_config_key;

/* ===== CONFIGURATION ===== */

static json_config_t *json_fetch_config(lua_State *l)
{
    json_config_t *cfg;

    lua_pushlightuserdata(l, &json_config_key);
    lua_gettable(l, LUA_REGISTRYINDEX);
    cfg = lua_touserdata(l, -1);
    if (!cfg)
        luaL_error(l, "BUG: Unable to fetch CJSON configuration");

    lua_pop(l, 1);

    return cfg;
}

static void json_verify_arg_count(lua_State *l, int args)
{
    luaL_argcheck(l, lua_gettop(l) <= args, args + 1,
                  "found too many arguments");
}

/* Configures handling of extremely sparse arrays:
