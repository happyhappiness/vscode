         rc = apr_ldap_set_option(ptemp, NULL, APR_LDAP_OPT_TLS_CERT,
                                  (void *)st->global_certs, &(result_err));
     }
 
     if (APR_SUCCESS == rc) {
         st->ssl_supported = 1;
-        ap_log_error(APLOG_MARK, APLOG_INFO, 0, s,
+        ap_log_error(APLOG_MARK, APLOG_INFO, 0, s, APLOGNO(01319)
                      "LDAP: SSL support available" );
     }
     else {
         st->ssl_supported = 0;
-        ap_log_error(APLOG_MARK, APLOG_INFO, 0, s,
+        ap_log_error(APLOG_MARK, APLOG_INFO, 0, s, APLOGNO(01320)
                      "LDAP: SSL support unavailable%s%s",
                      result_err ? ": " : "",
                      result_err ? result_err->reason : "");
     }
 
+    /* ssl_supported is really a global setting */
+    s_vhost = s->next;
+    while (s_vhost) {
+        st_vhost = (util_ldap_state_t *)
+                   ap_get_module_config(s_vhost->module_config,
+                                        &ldap_module);
+
+        st_vhost->ssl_supported = st->ssl_supported;
+        s_vhost = s_vhost->next;
+    }
+
     /* Initialize the rebind callback's cross reference list. */
     apr_ldap_rebind_init (p);
 
 #ifdef AP_LDAP_OPT_DEBUG
-    if (st->debug_level > 0) { 
+    if (st->debug_level > 0) {
         result = ldap_set_option(NULL, AP_LDAP_OPT_DEBUG, &st->debug_level);
         if (result != LDAP_SUCCESS) {
-            ap_log_error(APLOG_MARK, APLOG_ERR, 0, s,
-                    "LDAP: Could not set the LDAP library debug level to %d:(%d) %s", 
+            ap_log_error(APLOG_MARK, APLOG_ERR, 0, s, APLOGNO(01321)
+                    "LDAP: Could not set the LDAP library debug level to %d:(%d) %s",
                     st->debug_level, result, ldap_err2string(result));
         }
     }
 #endif
 
     return(OK);
