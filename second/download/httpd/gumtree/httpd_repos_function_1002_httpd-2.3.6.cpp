static int cmd_alert(lua_State *L)
{
    cmd_log_at(L, APLOG_ALERT);
    return 0;
}