                                NULL, NULL, st->opTimeout, APR_LDAP_SIZELIMIT, &res);
     if (AP_LDAP_IS_SERVER_DOWN(result))
     {
         ldc->reason = "ldap_search_ext_s() for user failed with server down";
         uldap_connection_unbind(ldc);
         failures++;
+        ap_log_rerror(APLOG_MARK, APLOG_TRACE5, 0, r, "%s (attempt %d)", ldc->reason, failures);
+        goto start_over;
+    }
+
+    if (result == LDAP_TIMEOUT) {
+        ldc->reason = "ldap_search_ext_s() for user failed with timeout";
+        uldap_connection_unbind(ldc);
+        failures++;
+        ap_log_rerror(APLOG_MARK, APLOG_TRACE5, 0, r, "%s (attempt %d)", ldc->reason, failures);
         goto start_over;
     }
 
+
     /* if there is an error (including LDAP_NO_SUCH_OBJECT) return now */
     if (result != LDAP_SUCCESS) {
         ldc->reason = "ldap_search_ext_s() for user failed";
         return result;
     }
 
