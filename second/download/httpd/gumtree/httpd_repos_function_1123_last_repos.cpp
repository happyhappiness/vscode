void ap_lua_load_config_lmodule(lua_State *L)
{
    luaL_newmetatable(L, "Apache2.DirConfig");  /* [metatable] */
    lua_pushvalue(L, -1);

    lua_setfield(L, -2, "__index");
    luaL_setfuncs_compat(L, cfg_methods);       /* [metatable] */


    luaL_newmetatable(L, "Apache2.CommandParameters");
    lua_pushvalue(L, -1);

    lua_setfield(L, -2, "__index");
    luaL_setfuncs_compat(L, cmd_methods);       /* [metatable] */

}