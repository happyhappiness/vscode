static void json_enum_option(lua_State *l, const char **options,
                             int *opt1, int *opt2)
{
    int setting;

    if (lua_gettop(l)) {
        if (lua_isboolean(l, 1))
            setting = lua_toboolean(l, 1) * 3;
        else
            setting = luaL_checkoption(l, 1, NULL, options);

        *opt1 = setting & 1 ? 1 : 0;
        *opt2 = setting & 2 ? 1 : 0;
    } else {
        setting = *opt1 | (*opt2 << 1);
    }

    if (setting)
        lua_pushstring(l, options[setting]);
    else
        lua_pushboolean(l, 0);
}