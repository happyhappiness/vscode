static void *create_dir_config(apr_pool_t *p, char *dir)
{
    ap_lua_dir_cfg *cfg = apr_pcalloc(p, sizeof(ap_lua_dir_cfg));
    cfg->package_paths = apr_array_make(p, 2, sizeof(char *));
    cfg->package_cpaths = apr_array_make(p, 2, sizeof(char *));
    cfg->mapped_handlers =
        apr_array_make(p, 1, sizeof(ap_lua_mapped_handler_spec *));
    cfg->code_cache_style = APL_CODE_CACHE_STAT;
    cfg->pool = p;
    cfg->hooks = apr_hash_make(p);
    cfg->dir = apr_pstrdup(p, dir);
    cfg->vm_scope = APL_SCOPE_ONCE;
    return cfg;
}