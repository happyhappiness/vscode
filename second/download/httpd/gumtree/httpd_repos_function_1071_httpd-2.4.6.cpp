static int cmd_alert(lua_State *L)
{
    return cmd_log_at(L, APLOG_ALERT);
}