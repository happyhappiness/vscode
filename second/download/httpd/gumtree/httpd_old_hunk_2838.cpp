static int lua_open_hook(lua_State *L, apr_pool_t *p)
{
    lua_open_callback(L, p, NULL);
    return OK;
}

/*
static apr_status_t luahood(ap_filter_t *f, apr_bucket_brigade *bb) {
    apr_bucket* b;
    apr_status_t rs;
    for ( b = APR_BRIGADE_FIRST(bb);
          b != APR_BRIGADE_SENTINEL(bb);
          b = APR_BUCKET_NEXT(b)) 
    {
        if (APR_BUCKET_IS_EOS(b)) {kl
            break;
        }
        const char *buffer;
        size_t bytes;
        if (( rs = apr_bucket_read(b, &buffer, &bytes, APR_BLOCK_READ))) {
            ap_log_rerror(APLOG_MARK, APLOG_WARNING, rs, f->r, "read failure in luahood");
            return rs;
        }
        char *mine = apr_pstrmemdup(f->r->pool, buffer, bytes);
        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, f->r, "sending '%s'", mine);
    }
    
    ap_pass_brigade(f->next, bb);
    
    return OK;
}
*/

/**
 * "main"
 */
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



/**
 * Like mod_alias except for lua handler fun :-) 
 */
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

/* ---------------- Configury stuff --------------- */

/** harnesses for magic hooks **/

static int lua_request_rec_hook_harness(request_rec *r, const char *name)
{
    int rc;
    lua_State *L;
    ap_lua_vm_spec *spec;
    ap_lua_server_cfg *server_cfg = ap_get_module_config(r->server->module_config,
                                                      &lua_module);
    const ap_lua_dir_cfg *cfg =
        (ap_lua_dir_cfg *) ap_get_module_config(r->per_dir_config,
                                             &lua_module);
    apr_array_header_t *hook_specs =
        apr_hash_get(cfg->hooks, name, APR_HASH_KEY_STRING);
    if (hook_specs) {
        int i;
        for (i = 0; i < hook_specs->nelts; i++) {
            ap_lua_mapped_handler_spec *hook_spec =
                ((ap_lua_mapped_handler_spec **) hook_specs->elts)[i];

            if (hook_spec == NULL) {
                continue;
            }
            spec = apr_pcalloc(r->pool, sizeof(ap_lua_vm_spec));

            spec->file = hook_spec->file_name;
            spec->code_cache_style = hook_spec->code_cache_style;
            spec->scope = hook_spec->scope;
            spec->bytecode = hook_spec->bytecode;
            spec->bytecode_len = hook_spec->bytecode_len;
            spec->pool = r->pool;

            apr_filepath_merge(&spec->file, server_cfg->root_path,
                               spec->file, APR_FILEPATH_NOTRELATIVE, r->pool);
            L = ap_lua_get_lua_state(r->pool,
                                  spec,
                                  cfg->package_paths,
                                  cfg->package_cpaths,
                                  &lua_open_callback, NULL);



            if (!L) {
                ap_log_rerror(APLOG_MARK, APLOG_CRIT, 0, r,
                              "lua: Failed to obtain lua interpreter for %s %s",
                              hook_spec->function_name, hook_spec->file_name);
                return HTTP_INTERNAL_SERVER_ERROR;
            }

            if (hook_spec->function_name != NULL) {
                lua_getglobal(L, hook_spec->function_name);
                if (!lua_isfunction(L, -1)) {
                    ap_log_rerror(APLOG_MARK, APLOG_CRIT, 0, r,
                                  "lua: Unable to find function %s in %s",
                                  hook_spec->function_name,
                                  hook_spec->file_name);
                    return HTTP_INTERNAL_SERVER_ERROR;
                }

