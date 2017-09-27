                 conf->provider->socache_instance, s);
         conf->provider->socache_instance = NULL;
     }
     return APR_SUCCESS;
 }
 
+static int socache_status_hook(request_rec *r, int flags)
+{
+    apr_status_t status = APR_SUCCESS;
+    cache_socache_conf *conf = ap_get_module_config(r->server->module_config,
+                                                    &cache_socache_module);
+    if (!conf->provider || !conf->provider->socache_provider ||
+        !conf->provider->socache_instance) {
+        return DECLINED;
+    }
+
+    ap_rputs("<hr>\n"
+             "<table cellspacing=0 cellpadding=0>\n"
+             "<tr><td bgcolor=\"#000000\">\n"
+             "<b><font color=\"#ffffff\" face=\"Arial,Helvetica\">"
+             "mod_cache_socache Status:</font></b>\n"
+             "</td></tr>\n"
+             "<tr><td bgcolor=\"#ffffff\">\n", r);
+
+    if (socache_mutex) {
+        status = apr_global_mutex_lock(socache_mutex);
+        if (status != APR_SUCCESS) {
+            ap_log_rerror(APLOG_MARK, APLOG_ERR, status, r, APLOGNO(02816)
+                    "could not acquire lock for cache status");
+        }
+    }
+
+    if (status != APR_SUCCESS) {
+        ap_rputs("No cache status data available\n", r);
+    } else {
+        conf->provider->socache_provider->status(conf->provider->socache_instance,
+                                                 r, flags);
+    }
+
+    if (socache_mutex && status == APR_SUCCESS) {
+        status = apr_global_mutex_unlock(socache_mutex);
+        if (status != APR_SUCCESS) {
+            ap_log_rerror(APLOG_MARK, APLOG_ERR, status, r, APLOGNO(02817)
+                    "could not release lock for cache status");
+        }
+    }
+
+    ap_rputs("</td></tr>\n</table>\n", r);
+    return OK;
+}
+
+static void socache_status_register(apr_pool_t *p)
+{
+    APR_OPTIONAL_HOOK(ap, status_hook, socache_status_hook, NULL, NULL, APR_HOOK_MIDDLE);
+}
+
 static int socache_precfg(apr_pool_t *pconf, apr_pool_t *plog, apr_pool_t *ptmp)
 {
     apr_status_t rv = ap_mutex_register(pconf, cache_socache_id, NULL,
             APR_LOCK_DEFAULT, 0);
     if (rv != APR_SUCCESS) {
         ap_log_perror(APLOG_MARK, APLOG_CRIT, rv, plog, APLOGNO(02390)
         "failed to register %s mutex", cache_socache_id);
         return 500; /* An HTTP status would be a misnomer! */
     }
+
+    /* Register to handle mod_status status page generation */
+    socache_status_register(pconf);
+
     return OK;
 }
 
 static int socache_post_config(apr_pool_t *pconf, apr_pool_t *plog,
         apr_pool_t *ptmp, server_rec *base_server)
 {
     server_rec *s;
     apr_status_t rv;
     const char *errmsg;
     static struct ap_socache_hints socache_hints =
-    { 64, 32, 60000000 };
+    { 64, 2048, 60000000 };
 
     for (s = base_server; s; s = s->next) {
         cache_socache_conf *conf =
                 ap_get_module_config(s->module_config, &cache_socache_module);
 
         if (!conf->provider) {
