 }
 static int authn_cache_post_config(apr_pool_t *pconf, apr_pool_t *plog,
                                    apr_pool_t *ptmp, server_rec *s)
 {
     apr_status_t rv;
     static struct ap_socache_hints authn_cache_hints = {64, 32, 60000000};
+    const char *errmsg;
 
     if (!configured) {
         return OK;    /* don't waste the overhead of creating mutex & cache */
     }
     if (socache_provider == NULL) {
         ap_log_perror(APLOG_MARK, APLOG_CRIT, 0, plog, APLOGNO(01674)
                       "Please select a socache provider with AuthnCacheSOCache "
                       "(no default found on this platform). Maybe you need to "
                       "load mod_socache_shmcb or another socache module first");
         return 500; /* An HTTP status would be a misnomer! */
     }
 
+    /* We have socache_provider, but do not have socache_instance. This should
+     * happen only when using "default" socache_provider, so create default
+     * socache_instance in this case. */
+    if (socache_instance == NULL) {
+        errmsg = socache_provider->create(&socache_instance, NULL,
+                                          ptmp, pconf);
+        if (errmsg) {
+            ap_log_perror(APLOG_MARK, APLOG_CRIT, 0, plog, APLOGNO(02612)
+                        "failed to create mod_socache_shmcb socache "
+                        "instance: %s", errmsg);
+            return 500;
+        }
+    }
+
     rv = ap_global_mutex_create(&authn_cache_mutex, NULL,
                                 authn_cache_id, NULL, s, pconf, 0);
     if (rv != APR_SUCCESS) {
         ap_log_perror(APLOG_MARK, APLOG_CRIT, rv, plog, APLOGNO(01675)
                       "failed to create %s mutex", authn_cache_id);
         return 500; /* An HTTP status would be a misnomer! */
