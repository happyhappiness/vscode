static int cmd_debug(lua_State *L)
{
    cmd_log_at(L, APLOG_DEBUG);
    return 0;
}