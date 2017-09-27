      * If we have been authenticated by some other module than mod_auth_ldap,
      * the req structure needed for authorization needs to be created
      * and populated with the userid and DN of the account in LDAP
      */
 
     if (!strlen(r->user)) {
-        ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r,
+        ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r, APLOGNO(01709)
             "ldap authorize: Userid is blank, AuthType=%s",
             r->ap_auth_type);
     }
 
     if(!req) {
-        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
+        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(01710)
             "ldap authorize: Creating LDAP req structure");
 
+        req = (authn_ldap_request_t *)apr_pcalloc(r->pool,
+            sizeof(authn_ldap_request_t));
         /* Build the username filter */
         authn_ldap_build_filter(filtbuf, r, r->user, NULL, sec);
 
         /* Search for the user DN */
         result = util_ldap_cache_getuserdn(r, ldc, sec->url, sec->basedn,
              sec->scope, sec->attributes, filtbuf, &dn, &(req->vals));
 
         /* Search failed, log error and return failure */
         if(result != LDAP_SUCCESS) {
-            ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
+            ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(01711)
                 "auth_ldap authorise: User DN not found, %s", ldc->reason);
             return AUTHZ_DENIED;
         }
 
-        req = (authn_ldap_request_t *)apr_pcalloc(r->pool,
-            sizeof(authn_ldap_request_t));
         ap_set_module_config(r->request_config, &authnz_ldap_module, req);
         req->dn = apr_pstrdup(r->pool, dn);
         req->user = r->user;
     }
 
     ent = (struct mod_auth_ldap_groupattr_entry_t *) sec->groupattr->elts;
 
     if (sec->group_attrib_is_dn) {
         if (req->dn == NULL || strlen(req->dn) == 0) {
-            ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
+            ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(01712)
                           "auth_ldap authorize: require group: user's DN has "
                           "not been defined; failing authorization for user %s",
                           r->user);
             return AUTHZ_DENIED;
         }
     }
