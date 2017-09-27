     rs = ap_global_mutex_create(&lua_ivm_mutex, NULL, "lua-ivm-shm", NULL,
                             s, pconf, 0);
     if (APR_SUCCESS != rs) {
         return HTTP_INTERNAL_SERVER_ERROR;
     }
 
-    /* Create shared memory space */
-    rs = apr_temp_dir_get(&tempdir, pconf);
-    if (rs != APR_SUCCESS) {
-        ap_log_error(APLOG_MARK, APLOG_ERR, rs, s, APLOGNO(02664)
-                 "mod_lua IVM: Failed to find temporary directory");
-        return HTTP_INTERNAL_SERVER_ERROR;
+    /* Create shared memory space, anonymous first if possible. */
+    rs = apr_shm_create(&lua_ivm_shm, sizeof pool, NULL, pconf);
+    if (APR_STATUS_IS_ENOTIMPL(rs)) {
+        /* Fall back to filename-based; nuke any left-over first. */
+        lua_ivm_shmfile = ap_runtime_dir_relative(pconf, DEFAULT_LUA_SHMFILE);
+
+        apr_shm_remove(lua_ivm_shmfile, pconf);
+        
+        rs = apr_shm_create(&lua_ivm_shm, sizeof pool, lua_ivm_shmfile, pconf);
     }
-    lua_ivm_shmfile = apr_psprintf(pconf, "%s/httpd_lua_shm.%ld", tempdir,
-                           (long int)getpid());
-    rs = apr_shm_create(&lua_ivm_shm, sizeof(apr_pool_t**),
-                    (const char *) lua_ivm_shmfile, pconf);
     if (rs != APR_SUCCESS) {
         ap_log_error(APLOG_MARK, APLOG_ERR, rs, s, APLOGNO(02665)
             "mod_lua: Failed to create shared memory segment on file %s",
-                     lua_ivm_shmfile);
+                     lua_ivm_shmfile ? lua_ivm_shmfile : "(anonymous)");
         return HTTP_INTERNAL_SERVER_ERROR;
     }
     pool = (apr_pool_t **)apr_shm_baseaddr_get(lua_ivm_shm);
     apr_pool_create(pool, pconf);
     apr_pool_cleanup_register(pconf, NULL, shm_cleanup_wrapper,
                           apr_pool_cleanup_null);
