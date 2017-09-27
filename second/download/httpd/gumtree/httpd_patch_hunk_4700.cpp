 static int socache_precfg(apr_pool_t *pconf, apr_pool_t *plog, apr_pool_t *ptmp)
 {
     apr_status_t rv = ap_mutex_register(pconf, cache_socache_id, NULL,
             APR_LOCK_DEFAULT, 0);
     if (rv != APR_SUCCESS) {
         ap_log_perror(APLOG_MARK, APLOG_CRIT, rv, plog, APLOGNO(02390)
-        "failed to register %s mutex", cache_socache_id);
+                "failed to register %s mutex", cache_socache_id);
         return 500; /* An HTTP status would be a misnomer! */
     }
 
     /* Register to handle mod_status status page generation */
     socache_status_register(pconf);
 
