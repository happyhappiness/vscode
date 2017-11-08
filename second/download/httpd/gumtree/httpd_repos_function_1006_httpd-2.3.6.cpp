static int cmd_notice(lua_State *L)
{
    cmd_log_at(L, APLOG_NOTICE);
    return 0;
}