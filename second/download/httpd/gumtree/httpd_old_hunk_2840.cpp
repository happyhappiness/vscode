}

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

static int lua_request_hook(lua_State *L, request_rec *r)
{
    ap_lua_push_request(L, r);
    return OK;
}

static void lua_register_hooks(apr_pool_t *p)
{
    /* ap_register_output_filter("luahood", luahood, NULL, AP_FTYPE_RESOURCE); */
    ap_hook_handler(lua_handler, NULL, NULL, APR_HOOK_MIDDLE);
    ap_hook_create_request(create_request_config, NULL, NULL,
                           APR_HOOK_MIDDLE);

    /* http_request.h hooks */
    ap_hook_translate_name(lua_translate_name_harness, NULL, NULL,
                           APR_HOOK_MIDDLE);
    ap_hook_fixups(lua_fixup_harness, NULL, NULL, APR_HOOK_MIDDLE);
    ap_hook_map_to_storage(lua_map_to_storage_harness, NULL, NULL,
                           APR_HOOK_MIDDLE);
    ap_hook_check_user_id(lua_check_user_id_harness, NULL, NULL,
                          APR_HOOK_MIDDLE);
    ap_hook_type_checker(lua_type_checker_harness, NULL, NULL,
                         APR_HOOK_MIDDLE);
    ap_hook_access_checker(lua_access_checker_harness, NULL, NULL,
                           APR_HOOK_MIDDLE);
    ap_hook_auth_checker(lua_auth_checker_harness, NULL, NULL,
                         APR_HOOK_MIDDLE);
    ap_hook_insert_filter(lua_insert_filter_harness, NULL, NULL,
                          APR_HOOK_MIDDLE);
    ap_hook_quick_handler(lua_quick_harness, NULL, NULL, APR_HOOK_FIRST);

    /* ap_hook_translate_name(lua_alias_munger, NULL, NULL, APR_HOOK_MIDDLE); */
    ap_hook_translate_name(lua_alias_munger, NULL, NULL, APR_HOOK_MIDDLE);

    APR_OPTIONAL_HOOK(ap_lua, lua_open, lua_open_hook, NULL, NULL,
                      APR_HOOK_REALLY_FIRST);

    APR_OPTIONAL_HOOK(ap_lua, lua_request, lua_request_hook, NULL, NULL,
                      APR_HOOK_REALLY_FIRST);
}

AP_DECLARE_MODULE(lua) = {
    STANDARD20_MODULE_STUFF,
    create_dir_config,          /* create per-dir    config structures */
    NULL,                       /* merge  per-dir    config structures */
    create_server_config,       /* create per-server config structures */
    NULL,                       /* merge  per-server config structures */
    lua_commands,               /* table of config file commands       */
    lua_register_hooks          /* register hooks                      */
};
