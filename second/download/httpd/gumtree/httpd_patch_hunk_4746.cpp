 static int lua_open_hook(lua_State *L, apr_pool_t *p)
 {
     lua_open_callback(L, p, NULL);
     return OK;
 }
 
+static const char *scope_to_string(unsigned int scope)
+{
+    switch (scope) {
+    case AP_LUA_SCOPE_ONCE:
+    case AP_LUA_SCOPE_UNSET:
+        return "once";
+    case AP_LUA_SCOPE_REQUEST:
+        return "request";
+    case AP_LUA_SCOPE_CONN:
+        return "conn";
+#if APR_HAS_THREADS
+    case AP_LUA_SCOPE_THREAD:
+        return "thread";
+#endif
+    default:
+        ap_assert(0);
+    }
+}
+
+static ap_lua_vm_spec *create_vm_spec(apr_pool_t **lifecycle_pool,
+                                      request_rec *r,
+                                      const ap_lua_dir_cfg *cfg,
+                                      const ap_lua_server_cfg *server_cfg,
+                                      const char *filename,
+                                      const char *bytecode,
+                                      apr_size_t bytecode_len,
+                                      const char *function,
+                                      const char *what)
+{
+    apr_pool_t *pool;
+    ap_lua_vm_spec *spec = apr_pcalloc(r->pool, sizeof(ap_lua_vm_spec));
+
+    spec->scope = cfg->vm_scope;
+    spec->pool = r->pool;
+    spec->package_paths = cfg->package_paths;
+    spec->package_cpaths = cfg->package_cpaths;
+    spec->cb = &lua_open_callback;
+    spec->cb_arg = NULL;
+    spec->bytecode = bytecode;
+    spec->bytecode_len = bytecode_len;
+
+    if (filename) {
+        char *file;
+        apr_filepath_merge(&file, server_cfg->root_path,
+                           filename, APR_FILEPATH_NOTRELATIVE, r->pool);
+        spec->file = file;
+    }
+    else {
+        spec->file = r->filename;
+    }
+    ap_log_rerror(APLOG_MARK, APLOG_TRACE2, 0, r, APLOGNO(02313)
+                  "%s details: scope: %s, file: %s, func: %s",
+                  what, scope_to_string(spec->scope), spec->file,
+                  function ? function : "-");
+
+    switch (spec->scope) {
+    case AP_LUA_SCOPE_ONCE:
+    case AP_LUA_SCOPE_UNSET:
+        apr_pool_create(&pool, r->pool);
+        break;
+    case AP_LUA_SCOPE_REQUEST:
+        pool = r->pool;
+        break;
+    case AP_LUA_SCOPE_CONN:
+        pool = r->connection->pool;
+        break;
+#if APR_HAS_THREADS
+    case AP_LUA_SCOPE_THREAD:
+        pool = apr_thread_pool_get(r->connection->current_thread);
+        break;
+#endif
+    default:
+        ap_assert(0);
+    }
+
+    *lifecycle_pool = pool;
+    return spec;
+}
+
 
 /**
  * "main"
  */
 static int lua_handler(request_rec *r)
 {
-    ap_lua_dir_cfg *dcfg;
-    apr_pool_t *pool;
     if (strcmp(r->handler, "lua-script")) {
         return DECLINED;
     }
-  
-    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(01472) "handling [%s] in mod_lua",
-                  r->filename);
-    dcfg = ap_get_module_config(r->per_dir_config, &lua_module);
+    ap_log_rerror(APLOG_MARK, APLOG_TRACE1, 0, r, APLOGNO(01472)
+                  "handling [%s] in mod_lua", r->filename);
 
+    /* XXX: This seems wrong because it may generate wrong headers for HEAD requests */
     if (!r->header_only) {
         lua_State *L;
+        apr_pool_t *pool;
         const ap_lua_dir_cfg *cfg = ap_get_module_config(r->per_dir_config,
                                                          &lua_module);
-        ap_lua_vm_spec *spec = NULL;
+        ap_lua_vm_spec *spec = create_vm_spec(&pool, r, cfg, NULL, NULL, NULL,
+                                              0, "handle", "request handler");
 
-        spec = apr_pcalloc(r->pool, sizeof(ap_lua_vm_spec));
-        spec->scope = dcfg->vm_scope;
-        spec->pool = r->pool;
-        spec->file = r->filename;
-        spec->package_paths = cfg->package_paths;
-        spec->package_cpaths = cfg->package_cpaths;
-        spec->cb = &lua_open_callback;
-        spec->cb_arg = NULL;
-      
-        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(01473)
-                      "request details scope:%u, filename:%s, function:%s",
-                      spec->scope,
-                      spec->file,
-                      "handle");
-
-        switch (spec->scope) {
-        case AP_LUA_SCOPE_ONCE:
-        case AP_LUA_SCOPE_UNSET:
-          apr_pool_create(&pool, r->pool);
-          break;
-        case AP_LUA_SCOPE_REQUEST:
-          pool = r->pool;
-          break;
-        case AP_LUA_SCOPE_CONN:
-          pool = r->connection->pool;
-          break;
-        case AP_LUA_SCOPE_THREAD:
-          #if APR_HAS_THREADS
-          pool = apr_thread_pool_get(r->connection->current_thread);
-          break;
-          #endif
-        default:
-          ap_assert(0);
-        }
-
-        L = ap_lua_get_lua_state(pool,
-                                 spec);
-        
+        L = ap_lua_get_lua_state(pool, spec);
         if (!L) {
             /* TODO annotate spec with failure reason */
             r->status = HTTP_INTERNAL_SERVER_ERROR;
             ap_rputs("Unable to compile VM, see logs", r);
             return HTTP_INTERNAL_SERVER_ERROR;
         }
-        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(01474) "got a vm!");
+        ap_log_rerror(APLOG_MARK, APLOG_TRACE3, 0, r, APLOGNO(01474) "got a vm!");
         lua_getglobal(L, "handle");
         if (!lua_isfunction(L, -1)) {
             ap_log_rerror(APLOG_MARK, APLOG_CRIT, 0, r, APLOGNO(01475)
                           "lua: Unable to find function %s in %s",
                           "handle",
                           spec->file);
