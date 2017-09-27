             goto start_over;
         }
     }
 
     /* handle bind failure */
     if (result != LDAP_SUCCESS) {
-        ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r,
+        if (!sec->bind_authoritative) {
+           ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
+                      "[%" APR_PID_T_FMT "] auth_ldap authenticate: "
+                      "user %s authentication failed; URI %s [%s][%s] (not authoritative)",
+                      getpid(), user, r->uri, ldc->reason, ldap_err2string(result));
+           return AUTH_USER_NOT_FOUND;
+        }
+
+        ap_log_rerror(APLOG_MARK, APLOG_INFO, 0, r,
                       "[%" APR_PID_T_FMT "] auth_ldap authenticate: "
                       "user %s authentication failed; URI %s [%s][%s]",
                       getpid(), user, r->uri, ldc->reason, ldap_err2string(result));
 
         return (LDAP_NO_SUCH_OBJECT == result) ? AUTH_USER_NOT_FOUND
 #ifdef LDAP_SECURITY_ERROR
