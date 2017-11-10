void ap_lua_load_config_lmodule(lua_State *L)
{
    luaL_newmetatable(L, "Apache2.DirConfig");  /* [metatable] */
    lua_pushvalue(L, -1);

    lua_setfield(L, -2, "__index");
    luaL_register(L, NULL, cfg_methods);        /* [metatable] */


    luaL_newmetatable(L, "Apache2.CommandParameters");
    lua_pushvalue(L, -1);

    lua_setfield(L, -2, "__index");
    luaL_register(L, NULL, cmd_methods);        /* [metatable] */

}