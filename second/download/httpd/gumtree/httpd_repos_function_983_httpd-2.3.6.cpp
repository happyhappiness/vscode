static const char *register_code_cache(cmd_parms *cmd, void *_cfg,
                                       const char *arg)
{
    ap_lua_dir_cfg *cfg = (ap_lua_dir_cfg *) _cfg;
    if (strcmp("stat", arg) == 0) {
        cfg->code_cache_style = APL_CODE_CACHE_STAT;
    }
    else if (strcmp("forever", arg) == 0) {
        cfg->code_cache_style = APL_CODE_CACHE_FOREVER;
    }
    else if (strcmp("never", arg) == 0) {
        cfg->code_cache_style = APL_CODE_CACHE_NEVER;
    }
    else {
        return apr_psprintf(cmd->pool,
                            "Invalid value for LuaCodeCache, '%s', acceptable values are %s",
                            arg, "'stat', 'forever', and 'never'");
    }
    return NULL;
}