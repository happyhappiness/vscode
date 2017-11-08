static const char *register_lua_scope(cmd_parms *cmd, void *_cfg,
                                      const char *scope, const char *min,
                                      const char *max)
{
    ap_lua_dir_cfg *cfg = (ap_lua_dir_cfg *) _cfg;
    if (strcmp("once", scope) == 0) {
        cfg->vm_scope = APL_SCOPE_ONCE;
    }
    else if (strcmp("request", scope) == 0) {
        cfg->vm_scope = APL_SCOPE_REQUEST;
    }
    else if (strcmp("conn", scope) == 0) {
        cfg->vm_scope = APL_SCOPE_CONN;
    }
    else if (strcmp("server", scope) == 0) {
        cfg->vm_scope = APL_SCOPE_SERVER;
        if (min)
            cfg->vm_server_pool_min = atoi(min);
        if (max)
            cfg->vm_server_pool_max = atoi(max);
    }
    else {
        return apr_psprintf(cmd->pool,
                            "Invalid value for LuaScope, '%s', acceptable values are %s",
                            scope, "'once', 'request', 'conn', and 'server'");
    }
    return NULL;
}