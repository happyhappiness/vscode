static int req_debug(lua_State *L)
{
    req_log_at(L, APLOG_DEBUG);
    return 0;
}