                  : (LDAP_INSUFFICIENT_ACCESS == result) ? AUTH_DENIED
 #endif
 #ifdef LDAP_INSUFFICIENT_RIGHTS
                  : (LDAP_INSUFFICIENT_RIGHTS == result) ? AUTH_DENIED
 #endif
 #endif
-#ifdef LDAP_CONSTRAINT_VIOLATION
-    /* At least Sun Directory Server sends this if a user is
-     * locked. This is not covered by LDAP_SECURITY_ERROR.
-     */
-                 : (LDAP_CONSTRAINT_VIOLATION == result) ? AUTH_DENIED
-#endif
                  : AUTH_GENERAL_ERROR;
     }
 
     /* mark the user and DN */
     req->dn = apr_pstrdup(r->pool, dn);
     req->user = apr_pstrdup(r->pool, user);
+    req->password = apr_pstrdup(r->pool, password);
     if (sec->user_is_dn) {
         r->user = req->dn;
     }
 
     /* add environment variables */
-    if (sec->attributes && vals) {
-        apr_table_t *e = r->subprocess_env;
-        int i = 0;
-        while (sec->attributes[i]) {
-            char *str = apr_pstrcat(r->pool, AUTHN_PREFIX, sec->attributes[i], NULL);
-            int j = sizeof(AUTHN_PREFIX)-1; /* string length of "AUTHENTICATE_", excluding the trailing NIL */
-            while (str[j]) {
-                str[j] = apr_toupper(str[j]);
-                j++;
-            }
-            apr_table_setn(e, str, vals[i]);
-
-            /* handle remote_user_attribute, if set */
-            if (sec->remote_user_attribute && 
-                !strcmp(sec->remote_user_attribute, sec->attributes[i])) {
-                r->user = (char *)apr_pstrdup(r->pool, vals[i]);
-                remote_user_attribute_set = 1;
-            }
-            i++;
-        }
-    }
+    remote_user_attribute_set = set_request_vars(r, LDAP_AUTHN);
 
     /* sanity check */
     if (sec->remote_user_attribute && !remote_user_attribute_set) {
         ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r,
                   "[%" APR_PID_T_FMT "] auth_ldap authenticate: "
                   "REMOTE_USER was to be set with attribute '%s', "
