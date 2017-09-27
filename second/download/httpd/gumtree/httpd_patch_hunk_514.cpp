     else
     {
        ap_log_error(APLOG_MARK, APLOG_NOTICE, 0, s, 
                          "LDAP: SSL support unavailable" );
     }
     
-#ifdef LDAP_OPT_NETWORK_TIMEOUT
-    if (st->connectionTimeout > 0) {
-        timeOut.tv_sec = st->connectionTimeout;
-    }
-
-    if (st->connectionTimeout >= 0) {
-        rc = ldap_set_option(NULL, LDAP_OPT_NETWORK_TIMEOUT, (void *)&timeOut);
-        if (APR_SUCCESS != rc) {
-            ap_log_error(APLOG_MARK, APLOG_ERR, 0, s,
-                             "LDAP: Could not set the connection timeout" );
-        }
-    }
-#endif
-
     return(OK);
 }
 
 static void util_ldap_child_init(apr_pool_t *p, server_rec *s)
 {
     apr_status_t sts;
-    util_ldap_state_t *st =
-        (util_ldap_state_t *)ap_get_module_config(s->module_config, &ldap_module);
+    util_ldap_state_t *st = ap_get_module_config(s->module_config, &ldap_module);
+
+    if (!st->util_ldap_cache_lock) return;
 
     sts = apr_global_mutex_child_init(&st->util_ldap_cache_lock, st->lock_file, p);
     if (sts != APR_SUCCESS) {
         ap_log_error(APLOG_MARK, APLOG_CRIT, sts, s,
                      "Failed to initialise global mutex %s in child process %"
                      APR_PID_T_FMT
