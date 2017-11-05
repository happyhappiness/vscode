static int cmd_foo(lua_State *L)
{
    cmd_parms *cmd = check_cmd_parms(L, 1);
    ap_log_error(APLOG_MARK, APLOG_ERR, 0, cmd->server, "FOO!");
    return 0;
}