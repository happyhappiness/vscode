 #if APR_HAS_THREADS
     apr_status_t rv;
 #endif
 
     /* If nothing is configured, we shouldn't be here */
     if (cfg->name == no_dbdriver) {
-        ap_log_error(APLOG_MARK, APLOG_ERR, 0, s, "not configured");
+        ap_log_error(APLOG_MARK, APLOG_ERR, 0, s, APLOGNO(02654)
+                     "not configured");
         return NULL;
     }
 
     if (!cfg->persist) {
         /* Return a once-only connection */
         group = apr_pcalloc(pool, sizeof(dbd_group_t));
