static void *create_server_config(apr_pool_t *p, server_rec *s)
{

    ap_lua_server_cfg *cfg = apr_pcalloc(p, sizeof(ap_lua_server_cfg));
    cfg->code_cache = apr_pcalloc(p, sizeof(ap_lua_code_cache));
    apr_thread_rwlock_create(&cfg->code_cache->compiled_files_lock, p);
    cfg->code_cache->compiled_files = apr_hash_make(p);
    cfg->vm_reslists = apr_hash_make(p);
    apr_thread_rwlock_create(&cfg->vm_reslists_lock, p);
    cfg->code_cache->pool = p;
    cfg->root_path = NULL;

    return cfg;
}