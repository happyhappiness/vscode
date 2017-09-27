                 }
                 if (w->active) {
                     /* We have active watchdog.
                      * Create the watchdog thread
                      */
                     if ((rv = wd_startup(w, wd_server_conf->pool)) != APR_SUCCESS) {
-                        ap_log_error(APLOG_MARK, APLOG_CRIT, rv, s,
+                        ap_log_error(APLOG_MARK, APLOG_CRIT, rv, s, APLOGNO(01571)
                                 "Watchdog: Failed to create parent worker thread.");
                         return rv;
                     }
                     wd_server_conf->parent_workers++;
                 }
             }
         }
     }
     if (wd_server_conf->parent_workers) {
-        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
+        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, APLOGNO(01572)
                      "Spawned %d parent worker threads.",
                      wd_server_conf->parent_workers);
     }
-    if ((wl = ap_list_provider_names(pconf, AP_WATCHODG_PGROUP,
-                                            AP_WATCHODG_CVERSION))) {
+    if ((wl = ap_list_provider_names(pconf, AP_WATCHDOG_PGROUP,
+                                            AP_WATCHDOG_CVERSION))) {
         const ap_list_provider_names_t *wn;
         int i;
 
         wn = (ap_list_provider_names_t *)wl->elts;
         for (i = 0; i < wl->nelts; i++) {
-            ap_watchdog_t *w = ap_lookup_provider(AP_WATCHODG_PGROUP,
+            ap_watchdog_t *w = ap_lookup_provider(AP_WATCHDOG_PGROUP,
                                                   wn[i].provider_name,
-                                                  AP_WATCHODG_CVERSION);
+                                                  AP_WATCHDOG_CVERSION);
             if (w) {
                 if (!w->active) {
                     int status = ap_run_watchdog_need(s, w->name, 0,
                                                       w->singleton);
                     if (status == OK) {
                         /* One of the modules returned OK to this watchog.
