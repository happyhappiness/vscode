         ldc = get_connection_for_authz(r, LDAP_SEARCH);
         apr_pool_cleanup_register(r->pool, ldc,
                                   authnz_ldap_cleanup_connection_close,
                                   apr_pool_cleanup_null);
     }
     else {
-        ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r,
+        ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r, APLOGNO(01738)
                       "auth_ldap authorize: no sec->host - weird...?");
         return AUTHZ_DENIED;
     }
 
     /*
      * If we have been authenticated by some other module than mod_auth_ldap,
      * the req structure needed for authorization needs to be created
      * and populated with the userid and DN of the account in LDAP
      */
 
     if (!strlen(r->user)) {
-        ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r,
+        ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r, APLOGNO(01739)
             "ldap authorize: Userid is blank, AuthType=%s",
             r->ap_auth_type);
     }
 
     if(!req) {
-        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
+        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(01740)
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
-                "auth_ldap authorise: User DN not found, %s", ldc->reason);
+            ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(01741)
+                "auth_ldap authorise: User DN not found with filter %s: %s", filtbuf, ldc->reason);
             return AUTHZ_DENIED;
         }
 
-        req = (authn_ldap_request_t *)apr_pcalloc(r->pool,
-            sizeof(authn_ldap_request_t));
         ap_set_module_config(r->request_config, &authnz_ldap_module, req);
         req->dn = apr_pstrdup(r->pool, dn);
         req->user = r->user;
     }
 
     if (req->dn == NULL || strlen(req->dn) == 0) {
-        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
+        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(01742)
                       "auth_ldap authorize: require ldap-filter: user's DN "
                       "has not been defined; failing authorization");
         return AUTHZ_DENIED;
     }
 
     t = require_args;
 
     if (t[0]) {
-        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
+        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(01743)
                       "auth_ldap authorize: checking filter %s", t);
 
         /* Build the username filter */
         authn_ldap_build_filter(filtbuf, r, req->user, t, sec);
 
         /* Search for the user DN */
         result = util_ldap_cache_getuserdn(r, ldc, sec->url, sec->basedn,
              sec->scope, sec->attributes, filtbuf, &dn, &(req->vals));
 
         /* Make sure that the filtered search returned the correct user dn */
         if (result == LDAP_SUCCESS) {
-            ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
+            ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(01744)
                           "auth_ldap authorize: checking dn match %s", dn);
             if (sec->compare_as_user) {
                 /* ldap-filter is the only authz that requires a search and a compare */
                 apr_pool_cleanup_kill(r->pool, ldc, authnz_ldap_cleanup_connection_close);
                 authnz_ldap_cleanup_connection_close(ldc);
                 ldc = get_connection_for_authz(r, LDAP_COMPARE);
