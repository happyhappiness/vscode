static int req_alert(lua_State *L)
{
    req_log_at(L, APLOG_ALERT);
    return 0;
}