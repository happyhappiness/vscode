static int cmd_emerg(lua_State *L)
{
    return cmd_log_at(L, APLOG_EMERG);
}