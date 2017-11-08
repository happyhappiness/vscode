static int cmd_debug(lua_State *L)
{
    return cmd_log_at(L, APLOG_DEBUG);
}