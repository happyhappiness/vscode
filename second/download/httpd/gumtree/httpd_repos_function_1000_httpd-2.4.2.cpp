static const char *register_lua_scope(cmd_parms *cmd, 
                                      void *_cfg,
                                      const char *scope, 
                                      const char *min,
                                      const char *max)
{
    ap_lua_dir_cfg *cfg = (ap_lua_dir_cfg *) _cfg;
    if (strcmp("once", scope) == 0) {
        cfg->vm_scope = AP_LUA_SCOPE_ONCE;
    }
    else if (strcmp("request", scope) == 0) {
        cfg->vm_scope = AP_LUA_SCOPE_REQUEST;
    }
    else if (strcmp("conn", scope) == 0) {
        cfg->vm_scope = AP_LUA_SCOPE_CONN;
    }
    else if (strcmp("thread", scope) == 0) {
#if !APR_HAS_THREADS
        return apr_psprintf(cmd->pool,
                            "Scope type of '%s' cannot be used because this "
                            "server does not have threading support "
                            "(APR_HAS_THREADS)" 
                            scope);
#endif
        cfg->vm_scope = AP_LUA_SCOPE_THREAD;
    }
    else {
        return apr_psprintf(cmd->pool,
                            "Invalid value for LuaScope, '%s', acceptable "
                            "values are: 'once', 'request', 'conn', 'server'"
#if APR_HAS_THREADS
                            ", 'thread'"
#endif
                            ,scope);
    }

    return NULL;
}