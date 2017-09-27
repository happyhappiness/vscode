         ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                       "[%" APR_PID_T_FMT "] auth_ldap authorise: agreeing because non-restricted",
                       getpid());
         return OK;
     }
 
-    if (!required_ldap || !sec->auth_authoritative) {
+    if (!sec->auth_authoritative) {
         ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
-                      "[%" APR_PID_T_FMT "] auth_ldap authorise: declining to authorise", getpid());
+                      "[%" APR_PID_T_FMT "] auth_ldap authorise: declining to authorise (not authoritative)", getpid());
         return DECLINED;
     }
 
     ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                   "[%" APR_PID_T_FMT "] auth_ldap authorise: authorisation denied", getpid());
     ap_note_basic_auth_failure (r);
