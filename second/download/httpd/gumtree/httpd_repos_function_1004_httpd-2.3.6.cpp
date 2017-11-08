static int cmd_err(lua_State *L)
{
    cmd_log_at(L, APLOG_ERR);
    return 0;
}