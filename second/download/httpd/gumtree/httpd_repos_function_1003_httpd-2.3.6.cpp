static int cmd_crit(lua_State *L)
{
    cmd_log_at(L, APLOG_CRIT);
    return 0;
}