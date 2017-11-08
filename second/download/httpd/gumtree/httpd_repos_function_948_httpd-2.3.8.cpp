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

                ap_lua_run_lua_request(L, r);
            }
            else {
                int t;
                ap_lua_run_lua_request(L, r);

                t = lua_gettop(L);
                lua_setglobal(L, "r");
                lua_settop(L, t);
            }

            if (lua_pcall(L, 1, 1, 0)) {
                report_lua_error(L, r);
                return HTTP_INTERNAL_SERVER_ERROR;
            }
            rc = DECLINED;
            if (lua_isnumber(L, -1)) {
                rc = lua_tointeger(L, -1);
            }
            if (rc != DECLINED) {
                return rc;
            }
        }
    }
    return DECLINED;
}