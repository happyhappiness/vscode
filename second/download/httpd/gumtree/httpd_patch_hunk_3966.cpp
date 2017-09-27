     wd_server_conf->s = s;
     if ((wl = ap_list_provider_names(pconf, AP_WATCHDOG_PGROUP,
                                             AP_WATCHDOG_PVERSION))) {
         const ap_list_provider_names_t *wn;
         int i;
 
+        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, APLOGNO(02974)
+                "Watchdog: found parent providers.");
+
         wn = (ap_list_provider_names_t *)wl->elts;
         for (i = 0; i < wl->nelts; i++) {
             ap_watchdog_t *w = ap_lookup_provider(AP_WATCHDOG_PGROUP,
                                                   wn[i].provider_name,
                                                   AP_WATCHDOG_PVERSION);
+            ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, APLOGNO(02975)
+                    "Watchdog: Looking for parent (%s).", wn[i].provider_name);
             if (w) {
                 if (!w->active) {
                     int status = ap_run_watchdog_need(s, w->name, 1,
                                                       w->singleton);
                     if (status == OK) {
                         /* One of the modules returned OK to this watchog.
