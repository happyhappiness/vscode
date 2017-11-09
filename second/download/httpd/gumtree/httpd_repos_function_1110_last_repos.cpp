static int cmd_err(lua_State *L)
{
    return cmd_log_at(L, APLOG_ERR);
}