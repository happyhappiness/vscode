     lua_getglobal(L, "require");
     lua_pushliteral(L, "jit.");
     lua_pushvalue(L, -3);
     lua_concat(L, 2);
     if (lua_pcall(L, 1, 1, 0)) {
         const char *msg = lua_tostring(L, -1);
-        ap_log_perror(APLOG_MARK, APLOG_DEBUG, 0, lifecycle_pool,
+        ap_log_perror(APLOG_MARK, APLOG_DEBUG, 0, lifecycle_pool, APLOGNO(01480)
                       "Failed to init LuaJIT: %s", msg);
         return 1;
     }
     lua_getfield(L, -1, "start");
     lua_remove(L, -2);  /* drop module table */
     return 0;
 }
 
 #endif
 
-AP_LUA_DECLARE(lua_State*)ap_lua_get_lua_state(apr_pool_t *lifecycle_pool,
-                                               ap_lua_vm_spec *spec,
-                                               apr_array_header_t *package_paths,
-                                               apr_array_header_t *package_cpaths,
-                                               ap_lua_state_open_callback cb,
-                                               void *btn)
+static apr_status_t vm_construct(void **vm, void *params, apr_pool_t *lifecycle_pool)
 {
+    lua_State* L;
 
-    lua_State *L;
+    ap_lua_vm_spec *spec = params;
 
-    if (!apr_pool_userdata_get((void **) &L, spec->file, lifecycle_pool)) {
-        ap_log_perror(APLOG_MARK, APLOG_DEBUG, 0, lifecycle_pool,
-                      "creating lua_State with file %s", spec->file);
-        /* not available, so create */
-        L = luaL_newstate();
+    L = luaL_newstate();
 #ifdef AP_ENABLE_LUAJIT
-        luaopen_jit(L);
+    luaopen_jit(L);
 #endif
-        luaL_openlibs(L);
-        if (package_paths) {
-            munge_path(L, "path", "?.lua", "./?.lua", lifecycle_pool,
-                       package_paths, spec->file);
-        }
-        if (package_cpaths) {
-            munge_path(L, "cpath", "?.so", "./?.so", lifecycle_pool,
-                       package_cpaths, spec->file);
-        }
+    luaL_openlibs(L);
+    if (spec->package_paths) {
+        munge_path(L, 
+                   "path", "?.lua", "./?.lua", 
+                   lifecycle_pool,
+                   spec->package_paths, 
+                   spec->file);
+    }
+    if (spec->package_cpaths) {
+        munge_path(L, "cpath", "?.so", "./?.so", lifecycle_pool,
+            spec->package_cpaths, spec->file);
+    }
 
-        if (cb) {
-            cb(L, lifecycle_pool, btn);
-        }
+    if (spec->cb) {
+        spec->cb(L, lifecycle_pool, spec->cb_arg);
+    }
 
-        apr_pool_userdata_set(L, spec->file, &cleanup_lua, lifecycle_pool);
 
-        if (spec->bytecode && spec->bytecode_len > 0) {
-            luaL_loadbuffer(L, spec->bytecode, spec->bytecode_len, spec->file);
-            lua_pcall(L, 0, LUA_MULTRET, 0);
-        }
-        else {
-            int rc;
-            ap_log_perror(APLOG_MARK, APLOG_DEBUG, 0, lifecycle_pool,
-                          "loading lua file %s", spec->file);
-            rc = luaL_loadfile(L, spec->file);
-            if (rc != 0) {
-                char *err;
-                switch (rc) {
-                case LUA_ERRSYNTAX: 
-                    err = "syntax error"; 
+    if (spec->bytecode && spec->bytecode_len > 0) {
+        luaL_loadbuffer(L, spec->bytecode, spec->bytecode_len, spec->file);
+        lua_pcall(L, 0, LUA_MULTRET, 0);
+    }
+    else {
+        int rc;
+        ap_log_perror(APLOG_MARK, APLOG_DEBUG, 0, lifecycle_pool, APLOGNO(01481)
+            "loading lua file %s", spec->file);
+        rc = luaL_loadfile(L, spec->file);
+        if (rc != 0) {
+            char *err;
+            switch (rc) {
+                case LUA_ERRSYNTAX:
+                    err = "syntax error";
                     break;
-                case LUA_ERRMEM:    
-                    err = "memory allocation error"; 
+                case LUA_ERRMEM:
+                    err = "memory allocation error";
                     break;
-                case LUA_ERRFILE:   
-                    err = "error opening or reading file"; 
+                case LUA_ERRFILE:
+                    err = "error opening or reading file";
                     break;
                 default:
-                    err = "unknown error"; 
+                    err = "unknown error";
                     break;
-                }
-                ap_log_perror(APLOG_MARK, APLOG_ERR, 0, lifecycle_pool,
-                              "Loading lua file %s: %s",
-                              spec->file, err);
-                return NULL;
             }
-            lua_pcall(L, 0, LUA_MULTRET, 0);
+            ap_log_perror(APLOG_MARK, APLOG_ERR, 0, lifecycle_pool, APLOGNO(01482)
+                "Loading lua file %s: %s",
+                spec->file, err);
+            return APR_EBADF;
         }
+        lua_pcall(L, 0, LUA_MULTRET, 0);
+    }
 
 #ifdef AP_ENABLE_LUAJIT
-        loadjitmodule(L, lifecycle_pool);
+    loadjitmodule(L, lifecycle_pool);
 #endif
-        lua_pushlightuserdata(L, lifecycle_pool);
-        lua_setfield(L, LUA_REGISTRYINDEX, "Apache2.Wombat.pool");
+    lua_pushlightuserdata(L, lifecycle_pool);
+    lua_setfield(L, LUA_REGISTRYINDEX, "Apache2.Wombat.pool");
+    *vm = L;
+
+    return APR_SUCCESS;
+}
+
+/**
+ * Function used to create a lua_State instance bound into the web
+ * server in the appropriate scope.
+ */
+AP_LUA_DECLARE(lua_State*)ap_lua_get_lua_state(apr_pool_t *lifecycle_pool,
+                                               ap_lua_vm_spec *spec)
+{
+    lua_State *L = NULL;
+
+    if (apr_pool_userdata_get((void **)&L, spec->file,
+                              lifecycle_pool) == APR_SUCCESS) {
+      
+      if(L==NULL) {
+        ap_log_perror(APLOG_MARK, APLOG_DEBUG, 0, lifecycle_pool, APLOGNO(01483)
+                      "creating lua_State with file %s", spec->file);
+        /* not available, so create */
+        
+        if(!vm_construct((void **)&L, spec, lifecycle_pool)) {
+          apr_pool_userdata_set(L, 
+                                spec->file, 
+                                cleanup_lua,
+                                lifecycle_pool);
+        }
+      }
     }
+        /*}*/
 
     return L;
 }
