static int cmd_info(lua_State *L)
{
    return cmd_log_at(L, APLOG_INFO);
}