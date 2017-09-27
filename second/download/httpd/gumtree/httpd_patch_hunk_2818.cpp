     util_ldap_state_t *st_vhost;
 
     util_ldap_state_t *st = (util_ldap_state_t *)
                             ap_get_module_config(s->module_config,
                                                  &ldap_module);
 
-    void *data;
-    const char *userdata_key = "util_ldap_init";
     apr_ldap_err_t *result_err = NULL;
     int rc;
 
     /* util_ldap_post_config() will be called twice. Don't bother
      * going through all of the initialization on the first call
      * because it will just be thrown away.*/
-    apr_pool_userdata_get(&data, userdata_key, s->process->pool);
-    if (!data) {
-        apr_pool_userdata_set((const void *)1, userdata_key,
-                               apr_pool_cleanup_null, s->process->pool);
+    if (ap_state_query(AP_SQ_MAIN_STATE) == AP_SQ_MS_CREATE_PRE_CONFIG) {
 
 #if APR_HAS_SHARED_MEMORY
-        /* If the cache file already exists then delete it.  Otherwise we are
-         * going to run into problems creating the shared memory. */
-        if (st->cache_file) {
+        /*
+         * If we are using shared memory caching and the cache file already
+         * exists then delete it.  Otherwise we are going to run into problems
+         * creating the shared memory.
+         */
+        if (st->cache_file && st->cache_bytes > 0) {
             char *lck_file = apr_pstrcat(ptemp, st->cache_file, ".lck",
                                          NULL);
             apr_file_remove(lck_file, ptemp);
         }
 #endif
         return OK;
     }
 
 #if APR_HAS_SHARED_MEMORY
-    /* initializing cache if shared memory size is not zero and we already
-     * don't have shm address
+    /*
+     * initializing cache if we don't already have a shm address
      */
-    if (!st->cache_shm && st->cache_bytes > 0) {
+    if (!st->cache_shm) {
 #endif
         result = util_ldap_cache_init(p, st);
         if (result != APR_SUCCESS) {
-            ap_log_error(APLOG_MARK, APLOG_ERR, result, s,
+            ap_log_error(APLOG_MARK, APLOG_ERR, result, s, APLOGNO(01315)
                          "LDAP cache: could not create shared memory segment");
             return DONE;
         }
 
         result = ap_global_mutex_create(&st->util_ldap_cache_lock, NULL,
                                         ldap_cache_mutex_type, NULL, s, p, 0);
