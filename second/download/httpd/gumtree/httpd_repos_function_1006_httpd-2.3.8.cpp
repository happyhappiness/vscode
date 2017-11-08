static int cmd_warn(lua_State *L)
{
    cmd_log_at(L, APLOG_WARNING);
    return 0;
}