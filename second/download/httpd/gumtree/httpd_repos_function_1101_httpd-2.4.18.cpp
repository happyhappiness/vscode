static int cmd_notice(lua_State *L)
{
    return cmd_log_at(L, APLOG_NOTICE);
}