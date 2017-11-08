static int req_emerg(lua_State *L)
{
    req_log_at(L, APLOG_EMERG);
    return 0;
}