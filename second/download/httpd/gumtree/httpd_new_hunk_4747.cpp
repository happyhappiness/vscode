            ap_lua_mapped_handler_spec *hook_spec =
                ((ap_lua_mapped_handler_spec **) hook_specs->elts)[i];

            if (hook_spec == NULL) {
                continue;
            }
            spec = create_vm_spec(&pool, r, cfg, server_cfg,
                                  hook_spec->file_name,
                                  hook_spec->bytecode,
                                  hook_spec->bytecode_len,
                                  hook_spec->function_name,
                                  "request hook");

            L = ap_lua_get_lua_state(pool, spec);

            if (!L) {
                ap_log_rerror(APLOG_MARK, APLOG_CRIT, 0, r, APLOGNO(01477)
                              "lua: Failed to obtain lua interpreter for %s %s",
