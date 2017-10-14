static apr_status_t lua_setup_filter_ctx(ap_filter_t* f, request_rec* r, lua_filter_ctx** c) {
    apr_pool_t *pool;
    ap_lua_vm_spec *spec;
    int n, rc;
    lua_State *L;
    lua_filter_ctx *ctx;    
    ap_lua_server_cfg *server_cfg = ap_get_module_config(r->server->module_config,
                                                        &lua_module);
    const ap_lua_dir_cfg *cfg = ap_get_module_config(r->per_dir_config,
                                                    &lua_module);
    
    ctx = apr_pcalloc(r->pool, sizeof(lua_filter_ctx));
    ctx->broken = 0;
    *c = ctx;
    /* Find the filter that was called */
    for (n = 0; n < cfg->mapped_filters->nelts; n++) {
        ap_lua_filter_handler_spec *hook_spec =
            ((ap_lua_filter_handler_spec **) cfg->mapped_filters->elts)[n];

        if (hook_spec == NULL) {
            continue;
        }
        if (!strcasecmp(hook_spec->filter_name, f->frec->name)) {
            spec = create_vm_spec(&pool, r, cfg, server_cfg,
                                    hook_spec->file_name,
                                    NULL,
                                    0,
                                    hook_spec->function_name,
                                    "filter");
            L = ap_lua_get_lua_state(pool, spec, r);
            if (L) {
                L = lua_newthread(L);
            }

            if (!L) {
                ap_log_rerror(APLOG_MARK, APLOG_CRIT, 0, r, APLOGNO(02328)
                                "lua: Failed to obtain lua interpreter for %s %s",
                                hook_spec->function_name, hook_spec->file_name);
                ap_lua_release_state(L, spec, r);
                return APR_EGENERAL;
            }
            if (hook_spec->function_name != NULL) {
                lua_getglobal(L, hook_spec->function_name);
                if (!lua_isfunction(L, -1)) {
                    ap_log_rerror(APLOG_MARK, APLOG_CRIT, 0, r, APLOGNO(02329)
                                    "lua: Unable to find function %s in %s",
                                    hook_spec->function_name,
                                    hook_spec->file_name);
                    ap_lua_release_state(L, spec, r);
                    return APR_EGENERAL;
                }

                ap_lua_run_lua_request(L, r);
            }
            else {
                int t;
                ap_lua_run_lua_request(L, r);

                t = lua_gettop(L);
                lua_setglobal(L, "r");
                lua_settop(L, t);
            }
            ctx->L = L;
            ctx->spec = spec;
            
            /* If a Lua filter is interested in filtering a request, it must first do a yield, 
             * otherwise we'll assume that it's not interested and pretend we didn't find it.
             */
            rc = lua_resume(L, 1);
            if (rc == LUA_YIELD) {
                return OK;
            }
            else {
                ap_lua_release_state(L, spec, r);
                return APR_ENOENT;
            }
        }
    }
    return APR_ENOENT;
}