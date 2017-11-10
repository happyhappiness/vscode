static ap_lua_dir_cfg *check_dir_config(lua_State *L, int index)
{
    ap_lua_dir_cfg *cfg;
    luaL_checkudata(L, index, "Apache2.DirConfig");
    cfg = (ap_lua_dir_cfg *) lua_unboxpointer(L, index);
    return cfg;
}