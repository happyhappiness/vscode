 
 #ifdef LDAP_OPT_NETWORK_TIMEOUT
     if (st->connectionTimeout > 0) {
         connectionTimeout.tv_sec = st->connectionTimeout;
     }
 
-    if (st->connectionTimeout >= 0) {
+    if (connectionTimeout.tv_sec > 0) {
         rc = apr_ldap_set_option(r->pool, ldc->ldap, LDAP_OPT_NETWORK_TIMEOUT,
                                  (void *)&connectionTimeout, &(result));
         if (APR_SUCCESS != rc) {
-            ap_log_error(APLOG_MARK, APLOG_ERR, 0, r->server,
+            ap_log_error(APLOG_MARK, APLOG_ERR, 0, r->server, APLOGNO(01282)
                              "LDAP: Could not set the connection timeout");
         }
     }
 #endif
 
 #ifdef LDAP_OPT_TIMEOUT
