             ap_lua_mapped_handler_spec *hook_spec =
                 ((ap_lua_mapped_handler_spec **) hook_specs->elts)[i];
 
             if (hook_spec == NULL) {
                 continue;
             }
-            spec = apr_pcalloc(r->pool, sizeof(ap_lua_vm_spec));
-
-            spec->file = hook_spec->file_name;
-            spec->scope = cfg->vm_scope;
-            spec->bytecode = hook_spec->bytecode;
-            spec->bytecode_len = hook_spec->bytecode_len;
-            spec->pool = r->pool;
-            spec->package_paths = cfg->package_paths;
-            spec->package_cpaths = cfg->package_cpaths;
-            spec->cb = &lua_open_callback;
-            spec->cb_arg = NULL;
-
-            apr_filepath_merge(&spec->file, server_cfg->root_path,
-                               spec->file, APR_FILEPATH_NOTRELATIVE, r->pool);
-
-            ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(01476)
-                          "request details scope:%u, filename:%s, function:%s",
-                          spec->scope,
-                          spec->file,
-                          hook_spec->function_name ? hook_spec->function_name : "-");
-
-            switch (spec->scope) {
-            case AP_LUA_SCOPE_ONCE:
-            case AP_LUA_SCOPE_UNSET:
-             apr_pool_create(&pool, r->pool);
-              break;
-            case AP_LUA_SCOPE_REQUEST:
-              pool = r->pool;
-              break;
-            case AP_LUA_SCOPE_CONN:
-              pool = r->connection->pool;
-              break;
-            case AP_LUA_SCOPE_THREAD:
-              #if APR_HAS_THREADS
-              pool = apr_thread_pool_get(r->connection->current_thread);
-              break;
-              #endif
-            default:
-              ap_assert(0);
-            }
+            spec = create_vm_spec(&pool, r, cfg, server_cfg,
+                                  hook_spec->file_name,
+                                  hook_spec->bytecode,
+                                  hook_spec->bytecode_len,
+                                  hook_spec->function_name,
+                                  "request hook");
 
             L = ap_lua_get_lua_state(pool, spec);
 
             if (!L) {
                 ap_log_rerror(APLOG_MARK, APLOG_CRIT, 0, r, APLOGNO(01477)
                               "lua: Failed to obtain lua interpreter for %s %s",
