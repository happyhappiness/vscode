static int req_err(lua_State *L)
{
    req_log_at(L, APLOG_ERR);
    return 0;
}