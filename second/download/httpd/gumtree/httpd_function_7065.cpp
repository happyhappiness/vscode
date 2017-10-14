static int lua_handler(request_rec *r)
{
    ap_lua_dir_cfg *dcfg;
    apr_pool_t *pool;
    if (strcmp(r->handler, "lua-script")) {
        return DECLINED;
    }
  
    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(01472) "handling [%s] in mod_lua",
                  r->filename);
    dcfg = ap_get_module_config(r->per_dir_config, &lua_module);

    if (!r->header_only) {
        lua_State *L;
        const ap_lua_dir_cfg *cfg = ap_get_module_config(r->per_dir_config,
                                                         &lua_module);
        ap_lua_vm_spec *spec = NULL;

        spec = apr_pcalloc(r->pool, sizeof(ap_lua_vm_spec));
        spec->scope = dcfg->vm_scope;
        spec->pool = r->pool;
        spec->file = r->filename;
        spec->package_paths = cfg->package_paths;
        spec->package_cpaths = cfg->package_cpaths;
        spec->cb = &lua_open_callback;
        spec->cb_arg = NULL;
      
        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(01473)
                      "request details scope:%u, filename:%s, function:%s",
                      spec->scope,
                      spec->file,
                      "handle");

        switch (spec->scope) {
        case AP_LUA_SCOPE_ONCE:
        case AP_LUA_SCOPE_UNSET:
          apr_pool_create(&pool, r->pool);
          break;
        case AP_LUA_SCOPE_REQUEST:
          pool = r->pool;
          break;
        case AP_LUA_SCOPE_CONN:
          pool = r->connection->pool;
          break;
        case AP_LUA_SCOPE_THREAD:
          #if APR_HAS_THREADS
          pool = apr_thread_pool_get(r->connection->current_thread);
          break;
          #endif
        default:
          ap_assert(0);
        }

        L = ap_lua_get_lua_state(pool,
                                 spec);
        
        if (!L) {
            /* TODO annotate spec with failure reason */
            r->status = HTTP_INTERNAL_SERVER_ERROR;
            ap_rputs("Unable to compile VM, see logs", r);
            return HTTP_INTERNAL_SERVER_ERROR;
        }
        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(01474) "got a vm!");
        lua_getglobal(L, "handle");
        if (!lua_isfunction(L, -1)) {
            ap_log_rerror(APLOG_MARK, APLOG_CRIT, 0, r, APLOGNO(01475)
                          "lua: Unable to find function %s in %s",
                          "handle",
                          spec->file);
            return HTTP_INTERNAL_SERVER_ERROR;
        }
        ap_lua_run_lua_request(L, r);
        if (lua_pcall(L, 1, 0, 0)) {
            report_lua_error(L, r);
        }
    }
    return OK;
}