static int req_crit(lua_State *L)
{
    req_log_at(L, APLOG_CRIT);
    return 0;
}