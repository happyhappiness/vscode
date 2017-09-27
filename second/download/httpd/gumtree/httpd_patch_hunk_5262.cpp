 static apr_status_t uldap_connection_unbind(void *param)
 {
     util_ldap_connection_t *ldc = param;
 
     if (ldc) {
         if (ldc->ldap) {
+            if (ldc->r) { 
+                ap_log_rerror(APLOG_MARK, APLOG_TRACE5, 0, ldc->r, "LDC %pp unbind", ldc); 
+            }
             ldap_unbind_s(ldc->ldap);
             ldc->ldap = NULL;
         }
         ldc->bound = 0;
 
         /* forget the rebind info for this conn */
