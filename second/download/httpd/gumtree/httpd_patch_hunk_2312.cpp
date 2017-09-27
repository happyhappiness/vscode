     {
         rc = uldap_simple_bind(ldc, (char *)ldc->binddn, (char *)ldc->bindpw,
                                st->opTimeout);
         if ((AP_LDAP_IS_SERVER_DOWN(rc) && failures == 5) ||
             (rc == LDAP_TIMEOUT && failures == 0))
         {
-           if (rc == LDAP_TIMEOUT && !new_connection) {
-               ap_log_rerror(APLOG_MARK, APLOG_INFO, 0, r,
-                             "ldap_simple_bind() timed out on reused "
-                             "connection, dropped by firewall?");
-           }
-           /* attempt to init the connection once again */
-           uldap_connection_unbind( ldc );
-           rc = uldap_connection_init( r, ldc );
-           if (LDAP_SUCCESS != rc)
-           {
-               break;
-           }
+            if (rc == LDAP_TIMEOUT && !new_connection) {
+                ap_log_rerror(APLOG_MARK, APLOG_INFO, 0, r,
+                              "ldap_simple_bind() timed out on reused "
+                              "connection, dropped by firewall?");
+            }
+            ap_log_rerror(APLOG_MARK, APLOG_TRACE2, 0, r,
+                          "attempt to re-init the connection");
+            uldap_connection_unbind( ldc );
+            rc = uldap_connection_init( r, ldc );
+            if (LDAP_SUCCESS != rc)
+            {
+                break;
+            }
         }
         else if (!AP_LDAP_IS_SERVER_DOWN(rc)) {
             break;
         }
+        ap_log_rerror(APLOG_MARK, APLOG_TRACE2, 0, r,
+                      "ldap_simple_bind() failed with server down "
+                      "(try %d)", failures + 1);
     }
 
     /* free the handle if there was an error
     */
     if (LDAP_SUCCESS != rc)
     {
-       uldap_connection_unbind(ldc);
+        uldap_connection_unbind(ldc);
         ldc->reason = "LDAP: ldap_simple_bind() failed";
     }
     else {
         ldc->bound = 1;
         ldc->reason = "LDAP: connection open successful";
     }
