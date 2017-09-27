 
         ap_log_rerror(APLOG_MARK, APLOG_INFO, 0, r, APLOGNO(01695)
                       "auth_ldap authenticate: "
                       "user %s authentication failed; URI %s [%s][%s]",
                       user, r->uri, ldc->reason, ldap_err2string(result));
 
+        /* talking to a primitive LDAP server (like RACF-over-LDAP) that doesn't return specific errors */
+        if (!strcasecmp(sec->filter, "none") && LDAP_OTHER == result) { 
+            return AUTH_USER_NOT_FOUND;
+        }
+
         return (LDAP_NO_SUCH_OBJECT == result) ? AUTH_USER_NOT_FOUND
 #ifdef LDAP_SECURITY_ERROR
                  : (LDAP_SECURITY_ERROR(result)) ? AUTH_DENIED
 #else
                  : (LDAP_INAPPROPRIATE_AUTH == result) ? AUTH_DENIED
                  : (LDAP_INVALID_CREDENTIALS == result) ? AUTH_DENIED
