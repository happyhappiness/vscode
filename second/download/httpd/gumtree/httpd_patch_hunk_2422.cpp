     static struct ap_socache_hints authn_cache_hints = {64, 32, 60000000};
 
     if (!configured) {
         return OK;    /* don't waste the overhead of creating mutex & cache */
     }
     if (socache_provider == NULL) {
-        ap_log_perror(APLOG_MARK, APLOG_CRIT, 0, plog,
+        ap_log_perror(APLOG_MARK, APLOG_CRIT, 0, plog, APLOGNO(01674)
                       "Please select a socache provider with AuthnCacheSOCache "
-                      "(no default found on this platform)");
+                      "(no default found on this platform). Maybe you need to "
+                      "load mod_socache_shmcb or another socache module first");
         return 500; /* An HTTP status would be a misnomer! */
     }
 
     rv = ap_global_mutex_create(&authn_cache_mutex, NULL,
                                 authn_cache_id, NULL, s, pconf, 0);
     if (rv != APR_SUCCESS) {
-        ap_log_perror(APLOG_MARK, APLOG_CRIT, rv, plog,
+        ap_log_perror(APLOG_MARK, APLOG_CRIT, rv, plog, APLOGNO(01675)
                       "failed to create %s mutex", authn_cache_id);
         return 500; /* An HTTP status would be a misnomer! */
     }
     apr_pool_cleanup_register(pconf, NULL, remove_lock, apr_pool_cleanup_null);
 
     errmsg = socache_provider->create(&socache_instance, NULL, ptmp, pconf);
     if (errmsg) {
-        ap_log_perror(APLOG_MARK, APLOG_CRIT, rv, plog, "%s", errmsg);
+        ap_log_perror(APLOG_MARK, APLOG_CRIT, rv, plog, APLOGNO(01676) "%s", errmsg);
         return 500; /* An HTTP status would be a misnomer! */
     }
 
     rv = socache_provider->init(socache_instance, authn_cache_id,
                                 &authn_cache_hints, s, pconf);
     if (rv != APR_SUCCESS) {
-        ap_log_perror(APLOG_MARK, APLOG_CRIT, rv, plog,
+        ap_log_perror(APLOG_MARK, APLOG_CRIT, rv, plog, APLOGNO(01677)
                       "failed to initialise %s cache", authn_cache_id);
         return 500; /* An HTTP status would be a misnomer! */
     }
     apr_pool_cleanup_register(pconf, (void*)s, destroy_cache, apr_pool_cleanup_null);
     return OK;
 }
 static void authn_cache_child_init(apr_pool_t *p, server_rec *s)
 {
-    const char *lock = apr_global_mutex_lockfile(authn_cache_mutex);
+    const char *lock;
     apr_status_t rv;
     if (!configured) {
         return;       /* don't waste the overhead of creating mutex & cache */
     }
+    lock = apr_global_mutex_lockfile(authn_cache_mutex);
     rv = apr_global_mutex_child_init(&authn_cache_mutex, lock, p);
     if (rv != APR_SUCCESS) {
-        ap_log_error(APLOG_MARK, APLOG_CRIT, rv, s,
+        ap_log_error(APLOG_MARK, APLOG_CRIT, rv, s, APLOGNO(01678)
                      "failed to initialise mutex in child_init");
     }
 }
 
 static const char *authn_cache_socache(cmd_parms *cmd, void *CFG,
                                        const char *arg)
 {
     const char *errmsg = ap_check_cmd_context(cmd, GLOBAL_ONLY);
+    if (errmsg)
+        return errmsg;
     socache_provider = ap_lookup_provider(AP_SOCACHE_PROVIDER_GROUP, arg,
                                           AP_SOCACHE_PROVIDER_VERSION);
     if (socache_provider == NULL) {
-        errmsg = "Unknown socache provider";
+        errmsg = apr_psprintf(cmd->pool,
+                              "Unknown socache provider '%s'. Maybe you need "
+                              "to load the appropriate socache module "
+                              "(mod_socache_%s?)", arg, arg);
     }
     return errmsg;
 }
 
+static const char *authn_cache_enable(cmd_parms *cmd, void *CFG)
+{
+    const char *errmsg = ap_check_cmd_context(cmd, GLOBAL_ONLY);
+    configured = 1;
+    return errmsg;
+}
+
 static const char *const directory = "directory";
 static void* authn_cache_dircfg_create(apr_pool_t *pool, char *s)
 {
     authn_cache_dircfg *ret = apr_palloc(pool, sizeof(authn_cache_dircfg));
     ret->timeout = apr_time_from_sec(300);
     ret->providers = NULL;
