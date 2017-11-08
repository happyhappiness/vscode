static int cmd_trace2(lua_State *L)
{
    cmd_log_at(L, APLOG_TRACE2);
    return 0;
}