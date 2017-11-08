static const char *lua_map_handler(cmd_parms *cmd, void *_cfg,
                                   const char *path, const char *file,
                                   const char *function)
{
    ap_lua_dir_cfg *cfg = (ap_lua_dir_cfg *) _cfg;
    apr_status_t rv;
    const char *function_name;
    function_name = function ? function : "handle";
    rv = ap_lua_map_handler(cfg, file, function_name, path, "once");
    if (rv != APR_SUCCESS) {
        return apr_psprintf(cmd->pool,
                            "Unable to configure a lua handler for path '%s', handler %s#%s",
                            path, file, function_name);
    }
    return NULL;
}