     }
 
     /* create the ldap session handle
     */
     if (NULL == ldc->ldap)
     {
+       new_connection = 1;
        rc = uldap_connection_init( r, ldc );
        if (LDAP_SUCCESS != rc)
        {
            return rc;
        }
     }
 
 
+    st = (util_ldap_state_t *)ap_get_module_config(r->server->module_config,
+                                                   &ldap_module);
+
     /* loop trying to bind up to 10 times if LDAP_SERVER_DOWN error is
-     * returned.  Break out of the loop on Success or any other error.
+     * returned. If LDAP_TIMEOUT is returned on the first try, maybe the
+     * connection was idle for a long time and has been dropped by a firewall.
+     * In this case close the connection immediately and try again.
+     *
+     * On Success or any other error, break out of the loop.
      *
      * NOTE: Looping is probably not a great idea. If the server isn't
      * responding the chances it will respond after a few tries are poor.
      * However, the original code looped and it only happens on
      * the error condition.
-      */
+     */
     for (failures=0; failures<10; failures++)
     {
-        rc = ldap_simple_bind_s(ldc->ldap,
-                                (char *)ldc->binddn,
-                                (char *)ldc->bindpw);
-        if (!AP_LDAP_IS_SERVER_DOWN(rc)) {
-            break;
-        } else if (failures == 5) {
+        rc = uldap_simple_bind(ldc, (char *)ldc->binddn, (char *)ldc->bindpw,
+                               st->opTimeout);
+        if ((AP_LDAP_IS_SERVER_DOWN(rc) && failures == 5) ||
+            (rc == LDAP_TIMEOUT && failures == 0))
+        {
+           if (rc == LDAP_TIMEOUT && !new_connection) {
+               ap_log_rerror(APLOG_MARK, APLOG_INFO, 0, r,
+                             "ldap_simple_bind() timed out on reused "
+                             "connection, dropped by firewall?");
+           }
            /* attempt to init the connection once again */
            uldap_connection_unbind( ldc );
            rc = uldap_connection_init( r, ldc );
            if (LDAP_SUCCESS != rc)
            {
                break;
            }
-       }
+        }
+        else if (!AP_LDAP_IS_SERVER_DOWN(rc)) {
+            break;
+        }
     }
 
     /* free the handle if there was an error
     */
     if (LDAP_SUCCESS != rc)
     {
        uldap_connection_unbind(ldc);
-        ldc->reason = "LDAP: ldap_simple_bind_s() failed";
+        ldc->reason = "LDAP: ldap_simple_bind() failed";
     }
     else {
         ldc->bound = 1;
         ldc->reason = "LDAP: connection open successful";
     }
 
