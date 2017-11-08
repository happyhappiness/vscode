static int cmd_trace1(lua_State *L)
{
    cmd_log_at(L, APLOG_TRACE1);
    return 0;
}