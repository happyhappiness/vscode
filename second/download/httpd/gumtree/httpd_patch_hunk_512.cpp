         /* Set the alias dereferencing option */
         ldap_set_option(ldc->ldap, LDAP_OPT_DEREF, &(ldc->deref));
 
         /* always default to LDAP V3 */
         ldap_set_option(ldc->ldap, LDAP_OPT_PROTOCOL_VERSION, &version);
 
+#ifdef LDAP_OPT_NETWORK_TIMEOUT
+        if (st->connectionTimeout > 0) {
+            timeOut.tv_sec = st->connectionTimeout;
+        }
+
+        if (st->connectionTimeout >= 0) {
+            rc = ldap_set_option(ldc->ldap, LDAP_OPT_NETWORK_TIMEOUT, (void *)&timeOut);
+            if (APR_SUCCESS != rc) {
+                ap_log_error(APLOG_MARK, APLOG_ERR, 0, r->server,
+                                 "LDAP: Could not set the connection timeout" );
+            }
+        }
+#endif
     }
 
 
     /* loop trying to bind up to 10 times if LDAP_SERVER_DOWN error is
      * returned.  Break out of the loop on Success or any other error.
      *
