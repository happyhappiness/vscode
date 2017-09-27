     lua_setfield(L, LUA_REGISTRYINDEX, "Apache2.Wombat.pool");
     *vm = L;
 
     return APR_SUCCESS;
 }
 
+static ap_lua_vm_spec* copy_vm_spec(apr_pool_t* pool, ap_lua_vm_spec* spec) 
+{
+    ap_lua_vm_spec* copied_spec = apr_pcalloc(pool, sizeof(ap_lua_vm_spec));
+    copied_spec->bytecode_len = spec->bytecode_len;
+    copied_spec->bytecode = apr_pstrdup(pool, spec->bytecode);
+    copied_spec->cb = spec->cb;
+    copied_spec->cb_arg = NULL;
+    copied_spec->file = apr_pstrdup(pool, spec->file);
+    copied_spec->package_cpaths = apr_array_copy(pool, spec->package_cpaths);
+    copied_spec->package_paths = apr_array_copy(pool, spec->package_paths);
+    copied_spec->pool = pool;
+    copied_spec->scope = AP_LUA_SCOPE_SERVER;
+    copied_spec->codecache = spec->codecache;
+    return copied_spec;
+}
+
+static apr_status_t server_vm_construct(lua_State **resource, void *params, apr_pool_t *pool)
+{
+    lua_State* L;
+    ap_lua_server_spec* spec = apr_pcalloc(pool, sizeof(ap_lua_server_spec));
+    *resource = NULL;
+    if (vm_construct(&L, params, pool) == APR_SUCCESS) {
+        spec->finfo = apr_pcalloc(pool, sizeof(ap_lua_finfo));
+        if (L != NULL) {
+            spec->L = L;
+            *resource = (void*) spec;
+            lua_pushlightuserdata(L, spec);
+            lua_setfield(L, LUA_REGISTRYINDEX, "Apache2.Lua.server_spec");
+            return APR_SUCCESS;
+        }
+    }
+    return APR_EGENERAL;
+}
+
 /**
  * Function used to create a lua_State instance bound into the web
  * server in the appropriate scope.
  */
-AP_LUA_DECLARE(lua_State*)ap_lua_get_lua_state(apr_pool_t *lifecycle_pool,
-                                               ap_lua_vm_spec *spec)
+lua_State *ap_lua_get_lua_state(apr_pool_t *lifecycle_pool,
+                                               ap_lua_vm_spec *spec, request_rec* r)
 {
     lua_State *L = NULL;
-
-    if (apr_pool_userdata_get((void **)&L, spec->file,
-                              lifecycle_pool) == APR_SUCCESS) {
-      
-      if(L==NULL) {
+    ap_lua_finfo *cache_info = NULL;
+    int tryCache = 0;
+    
+    if (spec->scope == AP_LUA_SCOPE_SERVER) {
+        char *hash;
+        apr_reslist_t* reslist = NULL;
+        ap_lua_server_spec* sspec = NULL;
+        hash = apr_psprintf(r->pool, "reslist:%s", spec->file);
+#if APR_HAS_THREADS
+        apr_thread_mutex_lock(ap_lua_mutex);
+#endif
+        if (apr_pool_userdata_get((void **)&reslist, hash,
+                                  r->server->process->pool) == APR_SUCCESS) {
+            if (reslist != NULL) {
+                if (apr_reslist_acquire(reslist, (void**) &sspec) == APR_SUCCESS) {
+                    L = sspec->L;
+                    cache_info = sspec->finfo;
+                }
+            }
+        }
+        if (L == NULL) {
+            ap_lua_vm_spec* server_spec = copy_vm_spec(r->server->process->pool, spec);
+            if (
+                    apr_reslist_create(&reslist, spec->vm_min, spec->vm_max, spec->vm_max, 0, 
+                                (apr_reslist_constructor) server_vm_construct, 
+                                (apr_reslist_destructor) server_cleanup_lua, 
+                                server_spec, r->server->process->pool)
+                    == APR_SUCCESS && reslist != NULL) {
+                apr_pool_userdata_set(reslist, hash, NULL,
+                                            r->server->process->pool);
+                if (apr_reslist_acquire(reslist, (void**) &sspec) == APR_SUCCESS) {
+                    L = sspec->L;
+                    cache_info = sspec->finfo;
+                }
+                else {
+                    return NULL;
+                }
+            }
+        }
+#if APR_HAS_THREADS
+        apr_thread_mutex_unlock(ap_lua_mutex);
+#endif
+    }
+    else {
+        if (apr_pool_userdata_get((void **)&L, spec->file,
+                              lifecycle_pool) != APR_SUCCESS) {
+            L = NULL;
+        }
+    }
+    if (L == NULL) {
         ap_log_perror(APLOG_MARK, APLOG_DEBUG, 0, lifecycle_pool, APLOGNO(01483)
-                      "creating lua_State with file %s", spec->file);
+                        "creating lua_State with file %s", spec->file);
         /* not available, so create */
-        
-        if(!vm_construct(&L, spec, lifecycle_pool)) {
-          AP_DEBUG_ASSERT(L != NULL);
-          apr_pool_userdata_set(L, 
-                                spec->file, 
-                                cleanup_lua,
-                                lifecycle_pool);
+
+        if (!vm_construct(&L, spec, lifecycle_pool)) {
+            AP_DEBUG_ASSERT(L != NULL);
+            apr_pool_userdata_set(L, spec->file, cleanup_lua, lifecycle_pool);
+        }
+    }
+
+    if (spec->codecache == AP_LUA_CACHE_FOREVER || (spec->bytecode && spec->bytecode_len > 0)) {
+        tryCache = 1;
+    }
+    else {
+        char* mkey;
+        if (spec->scope != AP_LUA_SCOPE_SERVER) {
+            mkey = apr_psprintf(r->pool, "ap_lua_modified:%s", spec->file);
+            apr_pool_userdata_get((void **)&cache_info, mkey, lifecycle_pool);
+            if (cache_info == NULL) {
+                cache_info = apr_pcalloc(lifecycle_pool, sizeof(ap_lua_finfo));
+                apr_pool_userdata_set((void*) cache_info, mkey, NULL, lifecycle_pool);
+            }
+        }
+        if (spec->codecache == AP_LUA_CACHE_STAT) {
+            apr_finfo_t lua_finfo;
+            apr_stat(&lua_finfo, spec->file, APR_FINFO_MTIME|APR_FINFO_SIZE, lifecycle_pool);
+
+            /* On first visit, modified will be zero, but that's fine - The file is 
+            loaded in the vm_construct function.
+            */
+            if ((cache_info->modified == lua_finfo.mtime && cache_info->size == lua_finfo.size)
+                    || cache_info->modified == 0) {
+                tryCache = 1;
+            }
+            cache_info->modified = lua_finfo.mtime;
+            cache_info->size = lua_finfo.size;
+        }
+        else if (spec->codecache == AP_LUA_CACHE_NEVER) {
+            if (cache_info->runs == 0)
+                tryCache = 1;
+        }
+        cache_info->runs++;
+    }
+    if (tryCache == 0 && spec->scope != AP_LUA_SCOPE_ONCE) {
+        int rc;
+        ap_log_perror(APLOG_MARK, APLOG_DEBUG, 0, lifecycle_pool, APLOGNO(02332)
+            "(re)loading lua file %s", spec->file);
+        rc = luaL_loadfile(L, spec->file);
+        if (rc != 0) {
+            ap_log_perror(APLOG_MARK, APLOG_ERR, 0, lifecycle_pool, APLOGNO(02333)
+                          "Error loading %s: %s", spec->file,
+                          rc == LUA_ERRMEM ? "memory allocation error"
+                                           : lua_tostring(L, 0));
+            return 0;
         }
-      }
+        lua_pcall(L, 0, LUA_MULTRET, 0);
     }
-        /*}*/
 
     return L;
 }
