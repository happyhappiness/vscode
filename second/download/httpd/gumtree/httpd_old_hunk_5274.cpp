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

