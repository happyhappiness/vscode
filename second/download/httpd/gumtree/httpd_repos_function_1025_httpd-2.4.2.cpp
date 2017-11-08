static int cmd_info(lua_State *L)
{
    cmd_log_at(L, APLOG_INFO);
    return 0;
}