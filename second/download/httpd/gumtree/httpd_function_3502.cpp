static int lua_handler(request_rec *r)
{
    ap_lua_dir_cfg *dcfg;
    if (strcmp(r->handler, "lua-script")) {
        return DECLINED;
    }

    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, "handling [%s] in mod_lua",
                  r->filename);
    dcfg = ap_get_module_config(r->per_dir_config, &lua_module);

    if (!r->header_only) {
        lua_State *L;
        const ap_lua_dir_cfg *cfg = ap_get_module_config(r->per_dir_config,
                                                      &lua_module);
        ap_lua_request_cfg *rcfg =
            ap_get_module_config(r->request_config, &lua_module);
        mapped_request_details *d = rcfg->mapped_request_details;
        ap_lua_vm_spec *spec = NULL;

        if (!d) {
            d = apr_palloc(r->pool, sizeof(mapped_request_details));
            spec = apr_pcalloc(r->pool, sizeof(ap_lua_vm_spec));
            spec->scope = dcfg->vm_scope;
            spec->pool = r->pool;
            spec->file = r->filename;
            spec->code_cache_style = dcfg->code_cache_style;
            d->spec = spec;
            d->function_name = "handle";
        }

        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                      "request details scope:%u, cache:%u, filename:%s, function:%s",
                      d->spec->scope,
                      d->spec->code_cache_style,
                      d->spec->file,
                      d->function_name);
        L = ap_lua_get_lua_state(r->pool,
                              d->spec,
                              cfg->package_paths,
                              cfg->package_cpaths,
                              &lua_open_callback, NULL);

        if (!L) {
            /* TODO annotate spec with failure reason */
            r->status = HTTP_INTERNAL_SERVER_ERROR;
            ap_rputs("Unable to compile VM, see logs", r);
            return HTTP_INTERNAL_SERVER_ERROR;
        }
        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, "got a vm!");
        lua_getglobal(L, d->function_name);
        if (!lua_isfunction(L, -1)) {
            ap_log_rerror(APLOG_MARK, APLOG_CRIT, 0, r,
                          "lua: Unable to find function %s in %s",
                          d->function_name,
                          d->spec->file);
            return HTTP_INTERNAL_SERVER_ERROR;
        }
        ap_lua_run_lua_request(L, r);
        if (lua_pcall(L, 1, 0, 0)) {
            report_lua_error(L, r);
        }
    }
    return OK;
}