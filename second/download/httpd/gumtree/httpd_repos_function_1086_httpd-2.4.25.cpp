static cmd_parms *check_cmd_parms(lua_State *L, int index)
{
    cmd_parms *cmd;
    luaL_checkudata(L, index, "Apache2.CommandParameters");
    cmd = (cmd_parms *) lua_unboxpointer(L, index);
    return cmd;
}