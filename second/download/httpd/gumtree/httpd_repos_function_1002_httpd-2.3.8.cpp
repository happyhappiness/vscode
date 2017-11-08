static int cmd_emerg(lua_State *L)
{
    cmd_log_at(L, APLOG_EMERG);
    return 0;
}