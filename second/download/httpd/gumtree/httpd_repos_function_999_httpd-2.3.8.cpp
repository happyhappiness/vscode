static int cfg_directory(lua_State *L)
{
    ap_lua_dir_cfg *cfg = check_dir_config(L, 1);
    lua_pushstring(L, cfg->dir);
    return 1;
}