static int req_notice(lua_State *L)
{
    req_log_at(L, APLOG_NOTICE);
    return 0;
}