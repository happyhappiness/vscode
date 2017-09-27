     const char *t;
     char *w, *value;
 
     char filtbuf[FILTER_LENGTH];
     const char *dn = NULL;
 
+    if (!r->user) {
+        return AUTHZ_DENIED_NO_USER;
+    }
+
     if (!sec->have_ldap_url) {
         return AUTHZ_DENIED;
     }
 
     if (sec->host) {
         ldc = get_connection_for_authz(r, LDAP_COMPARE);
         apr_pool_cleanup_register(r->pool, ldc,
                                   authnz_ldap_cleanup_connection_close,
                                   apr_pool_cleanup_null);
     }
     else {
         ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r,
-                      "[%" APR_PID_T_FMT "] auth_ldap authorize: no sec->host - weird...?", getpid());
+                      "auth_ldap authorize: no sec->host - weird...?");
         return AUTHZ_DENIED;
     }
 
     /*
      * If we have been authenticated by some other module than mod_auth_ldap,
      * the req structure needed for authorization needs to be created
      * and populated with the userid and DN of the account in LDAP
      */
 
-    /* Check that we have a userid to start with */
-    if (!r->user) {
-        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
-            "access to %s failed, reason: no authenticated user", r->uri);
-        return AUTHZ_DENIED;
-    }
-
     if (!strlen(r->user)) {
         ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r,
             "ldap authorize: Userid is blank, AuthType=%s",
             r->ap_auth_type);
     }
 
