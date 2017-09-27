         uldap_connection_unbind(ldc);
         failures++;
         ap_log_rerror(APLOG_MARK, APLOG_TRACE5, 0, r, "%s (attempt %d)", ldc->reason, failures);
         goto start_over;
     }
 
+    ldc->last_backend_conn = r->request_time;
     ldc->reason = "Comparison complete";
     if ((LDAP_COMPARE_TRUE == result) ||
         (LDAP_COMPARE_FALSE == result) ||
         (LDAP_NO_SUCH_ATTRIBUTE == result)) {
         if (curl) {
             /* compare completed; caching result */
