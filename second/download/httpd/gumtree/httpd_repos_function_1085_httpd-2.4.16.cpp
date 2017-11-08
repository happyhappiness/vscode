static int cmd_crit(lua_State *L)
{
    return cmd_log_at(L, APLOG_CRIT);
}