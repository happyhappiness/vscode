static int cmd_warn(lua_State *L)
{
    return cmd_log_at(L, APLOG_WARNING);
}