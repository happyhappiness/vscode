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
 
