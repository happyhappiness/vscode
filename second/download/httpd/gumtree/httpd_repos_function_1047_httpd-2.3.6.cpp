static int req_warn(lua_State *L)
{
    req_log_at(L, APLOG_WARNING);
    return 0;
}