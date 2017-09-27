                                  hook_spec->file_name,
                                  hook_spec->bytecode,
                                  hook_spec->bytecode_len,
                                  hook_spec->function_name,
                                  "request hook");

            L = ap_lua_get_lua_state(pool, spec, r);

            if (!L) {
                ap_log_rerror(APLOG_MARK, APLOG_CRIT, 0, r, APLOGNO(01477)
                              "lua: Failed to obtain lua interpreter for %s %s",
                              hook_spec->function_name, hook_spec->file_name);
                return HTTP_INTERNAL_SERVER_ERROR;
