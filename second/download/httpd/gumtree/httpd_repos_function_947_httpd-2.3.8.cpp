static int lua_alias_munger(request_rec *r)
{
    ap_lua_vm_spec *spec;
    ap_lua_request_cfg *rcfg = ap_get_module_config(r->request_config,
                                                 &lua_module);
    const ap_lua_dir_cfg *cfg =
        ap_get_module_config(r->per_dir_config, &lua_module);
    int i;
    ap_regmatch_t matches[AP_MAX_REG_MATCH];

    for (i = 0; i < cfg->mapped_handlers->nelts; i++) {
        const ap_lua_mapped_handler_spec *cnd =
            ((const ap_lua_mapped_handler_spec **) cfg->mapped_handlers->elts)[i];

        if (OK ==
            ap_regexec(cnd->uri_pattern, r->uri, AP_MAX_REG_MATCH, matches,
                       0)) {
            mapped_request_details *d;
            r->handler = "lua-script";

            spec = apr_pcalloc(r->pool, sizeof(ap_lua_vm_spec));
            spec->file =
                ap_pregsub(r->pool, cnd->file_name, r->uri, AP_MAX_REG_MATCH,
                           matches);
            spec->scope = cnd->scope;
            spec->code_cache_style = cnd->code_cache_style;
            spec->bytecode = cnd->bytecode;
            spec->bytecode_len = cnd->bytecode_len;
            if (spec->scope == APL_SCOPE_ONCE) {
                spec->pool = r->pool;
            }

            d = apr_palloc(r->pool, sizeof(mapped_request_details));

            d->function_name =
                ap_pregsub(r->pool, cnd->function_name, r->uri,
                           AP_MAX_REG_MATCH, matches);
            d->spec = spec;

            /* now do replacement on method name where? */
            r->filename = apr_pstrdup(r->pool, spec->file);
            rcfg->mapped_request_details = d;
            return OK;
        }
    }
    return DECLINED;
}