                                  "request hook");

            L = ap_lua_get_lua_state(pool, spec, r);

            if (!L) {
                ap_log_rerror(APLOG_MARK, APLOG_CRIT, 0, r, APLOGNO(01477)
                    "lua: Failed to obtain lua interpreter for entry function '%s' in %s",
                              hook_spec->function_name, hook_spec->file_name);
                return HTTP_INTERNAL_SERVER_ERROR;
            }

            if (hook_spec->function_name != NULL) {
                lua_getglobal(L, hook_spec->function_name);
                if (!lua_isfunction(L, -1)) {
                    ap_log_rerror(APLOG_MARK, APLOG_CRIT, 0, r, APLOGNO(01478)
                               "lua: Unable to find entry function '%s' in %s (not a valid function)",
                                  hook_spec->function_name,
                                  hook_spec->file_name);
                    ap_lua_release_state(L, spec, r);
                    return HTTP_INTERNAL_SERVER_ERROR;
                }

