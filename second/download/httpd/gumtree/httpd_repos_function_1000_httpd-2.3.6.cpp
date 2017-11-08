static int cmd_log_at(lua_State *L, int level)
{
    const char *msg;
    cmd_parms *cmd = check_cmd_parms(L, 1);
    lua_Debug dbg;

    lua_getstack(L, 1, &dbg);
    lua_getinfo(L, "Sl", &dbg);

    msg = luaL_checkstring(L, 2);
    ap_log_error(dbg.source, dbg.currentline, APLOG_MODULE_INDEX, level, 0, cmd->server, msg);
    return 0;
}