 
     char filtbuf[FILTER_LENGTH];
     const char *dn = NULL;
     struct mod_auth_ldap_groupattr_entry_t *ent;
     int i;
 
+    if (!r->user) {
+        return AUTHZ_DENIED_NO_USER;
+    }
+
     if (!sec->have_ldap_url) {
         return AUTHZ_DENIED;
     }
 
     if (sec->host) {
         ldc = get_connection_for_authz(r, LDAP_COMPARE); /* for the top-level group only */
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
      * If there are no elements in the group attribute array, the default should be
      * member and uniquemember; populate the array now.
