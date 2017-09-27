  **********************************************************/
 
 static int isapi_pre_config(apr_pool_t *pconf, apr_pool_t *plog, apr_pool_t *ptemp)
 {
     apr_status_t rv;
 
-    apr_pool_sub_make(&loaded.pool, pconf, NULL);
+    apr_pool_create_ex(&loaded.pool, pconf, NULL, NULL);
     if (!loaded.pool) {
 	ap_log_error(APLOG_MARK, APLOG_ERR, APR_EGENERAL, NULL,
 	             "ISAPI: could not create the isapi cache pool");
         return APR_EGENERAL;
     }
-    
+
     loaded.hash = apr_hash_make(loaded.pool);
     if (!loaded.hash) {
         ap_log_error(APLOG_MARK, APLOG_ERR, 0, NULL,
                      "ISAPI: Failed to create module cache");
         return APR_EGENERAL;
     }
 
-    rv = apr_thread_mutex_create(&loaded.lock, APR_THREAD_MUTEX_DEFAULT, 
+    rv = apr_thread_mutex_create(&loaded.lock, APR_THREAD_MUTEX_DEFAULT,
                                  loaded.pool);
     if (rv != APR_SUCCESS) {
         ap_log_error(APLOG_MARK, rv, 0, NULL,
                      "ISAPI: Failed to create module cache lock");
         return rv;
     }
