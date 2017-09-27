     ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                   "[%" APR_PID_T_FMT "] auth_ldap authenticate: accepting %s", getpid(), user);
 
     return AUTH_GRANTED;
 }
 
-/*
- * Authorisation Phase
- * -------------------
- *
- * After checking whether the username and password are correct, we need
- * to check whether that user is authorised to view this resource. The
- * require directive is used to do this:
- *
- *  require valid-user          Any authenticated is allowed in.
- *  require user <username>     This particular user is allowed in.
- *  require group <groupname>   The user must be a member of this group
- *                              in order to be allowed in.
- *  require dn <dn>             The user must have the following DN in the
- *                              LDAP tree to be let in.
- *
- */
-static int authz_ldap_check_user_access(request_rec *r)
+static authz_status ldapuser_check_authorization(request_rec *r,
+                                             const char *require_args)
 {
     int result = 0;
     authn_ldap_request_t *req =
         (authn_ldap_request_t *)ap_get_module_config(r->request_config, &authnz_ldap_module);
     authn_ldap_config_t *sec =
         (authn_ldap_config_t *)ap_get_module_config(r->per_dir_config, &authnz_ldap_module);
 
     util_ldap_connection_t *ldc = NULL;
-    int m = r->method_number;
 
-    const apr_array_header_t *reqs_arr = ap_requires(r);
-    require_line *reqs = reqs_arr ? (require_line *)reqs_arr->elts : NULL;
-
-    register int x;
     const char *t;
-    char *w, *value;
-    int method_restricted = 0;
-    int required_ldap = 0;
+    char *w;
 
     char filtbuf[FILTER_LENGTH];
     const char *dn = NULL;
-    const char **vals = NULL;
 
-/*
-    if (!sec->enabled) {
-        return DECLINED;
+    if (!sec->have_ldap_url) {
+        return AUTHZ_DENIED;
     }
-*/
 
-    if (!sec->have_ldap_url) {
-        return DECLINED;
+    if (sec->host) {
+        ldc = get_connection_for_authz(r, LDAP_COMPARE);
+        apr_pool_cleanup_register(r->pool, ldc,
+                                  authnz_ldap_cleanup_connection_close,
+                                  apr_pool_cleanup_null);
+    }
+    else {
+        ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r,
+                      "[%" APR_PID_T_FMT "] auth_ldap authorize: no sec->host - weird...?", getpid());
+        return AUTHZ_DENIED;
     }
 
-    /* pre-scan for ldap-* requirements so we can get out of the way early */
-    for(x=0; x < reqs_arr->nelts; x++) {
-        if (! (reqs[x].method_mask & (AP_METHOD_BIT << m))) {
-            continue;
-        }
+    /*
+     * If we have been authenticated by some other module than mod_authnz_ldap,
+     * the req structure needed for authorization needs to be created
+     * and populated with the userid and DN of the account in LDAP
+     */
+
+    /* Check that we have a userid to start with */
+    if (!r->user) {
+        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
+            "access to %s failed, reason: no authenticated user", r->uri);
+        return AUTHZ_DENIED;
+    }
+
+    if (!strlen(r->user)) {
+        ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r,
+            "ldap authorize: Userid is blank, AuthType=%s",
+            r->ap_auth_type);
+    }
+
+    if(!req) {
+        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
+            "ldap authorize: Creating LDAP req structure");
 
-        t = reqs[x].requirement;
-        w = ap_getword_white(r->pool, &t);
+        req = (authn_ldap_request_t *)apr_pcalloc(r->pool,
+            sizeof(authn_ldap_request_t));
+
+        /* Build the username filter */
+        authn_ldap_build_filter(filtbuf, r, r->user, NULL, sec);
+
+        /* Search for the user DN */
+        result = util_ldap_cache_getuserdn(r, ldc, sec->url, sec->basedn,
+             sec->scope, sec->attributes, filtbuf, &dn, &(req->vals));
 
-        if (strncmp(w, "ldap-",5) == 0) {
-            required_ldap = 1;
-            break;
+        /* Search failed, log error and return failure */
+        if(result != LDAP_SUCCESS) {
+            ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
+                "auth_ldap authorise: User DN not found, %s", ldc->reason);
+            return AUTHZ_DENIED;
         }
+
+        ap_set_module_config(r->request_config, &authnz_ldap_module, req);
+        req->dn = apr_pstrdup(r->pool, dn);
+        req->user = r->user;
+
     }
 
-    if (!required_ldap) {
+    if (req->dn == NULL || strlen(req->dn) == 0) {
         ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
-                      "[%" APR_PID_T_FMT "] auth_ldap authorise: declining to authorise (no ldap requirements)", getpid());
-        return DECLINED;
+                      "[%" APR_PID_T_FMT "] auth_ldap authorize: "
+                      "require user: user's DN has not been defined; failing authorization",
+                      getpid());
+        return AUTHZ_DENIED;
+    }
+
+    /*
+     * First do a whole-line compare, in case it's something like
+     *   require user Babs Jensen
+     */
+    result = util_ldap_cache_compare(r, ldc, sec->url, req->dn, sec->attribute, require_args);
+    switch(result) {
+        case LDAP_COMPARE_TRUE: {
+            ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
+                          "[%" APR_PID_T_FMT "] auth_ldap authorize: "
+                          "require user: authorization successful", getpid());
+            set_request_vars(r, LDAP_AUTHZ);
+            return AUTHZ_GRANTED;
+        }
+        default: {
+            ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
+                          "[%" APR_PID_T_FMT "] auth_ldap authorize: require user: "
+                          "authorization failed [%s][%s]", getpid(),
+                          ldc->reason, ldap_err2string(result));
+        }
+    }
+
+    /*
+     * Now break apart the line and compare each word on it
+     */
+    t = require_args;
+    while ((w = ap_getword_conf(r->pool, &t)) && w[0]) {
+        result = util_ldap_cache_compare(r, ldc, sec->url, req->dn, sec->attribute, w);
+        switch(result) {
+            case LDAP_COMPARE_TRUE: {
+                ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
+                              "[%" APR_PID_T_FMT "] auth_ldap authorize: "
+                              "require user: authorization successful", getpid());
+                set_request_vars(r, LDAP_AUTHZ);
+                return AUTHZ_GRANTED;
+            }
+            default: {
+                ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
+                              "[%" APR_PID_T_FMT "] auth_ldap authorize: "
+                              "require user: authorization failed [%s][%s]",
+                              getpid(), ldc->reason, ldap_err2string(result));
+            }
+        }
     }
 
+    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
+                  "[%" APR_PID_T_FMT "] auth_ldap authorize user: authorization denied for user %s to %s",
+                  getpid(), r->user, r->uri);
+
+    return AUTHZ_DENIED;
+}
+
+static authz_status ldapgroup_check_authorization(request_rec *r,
+                                             const char *require_args)
+{
+    int result = 0;
+    authn_ldap_request_t *req =
+        (authn_ldap_request_t *)ap_get_module_config(r->request_config, &authnz_ldap_module);
+    authn_ldap_config_t *sec =
+        (authn_ldap_config_t *)ap_get_module_config(r->per_dir_config, &authnz_ldap_module);
+
+    util_ldap_connection_t *ldc = NULL;
+
+    const char *t;
+
+    char filtbuf[FILTER_LENGTH];
+    const char *dn = NULL;
+    struct mod_auth_ldap_groupattr_entry_t *ent;
+    int i;
 
+    if (!sec->have_ldap_url) {
+        return AUTHZ_DENIED;
+    }
 
     if (sec->host) {
-        ldc = util_ldap_connection_find(r, sec->host, sec->port,
-                                       sec->binddn, sec->bindpw, sec->deref,
-                                       sec->secure);
+        ldc = get_connection_for_authz(r, LDAP_COMPARE); /* for the top-level group only */
         apr_pool_cleanup_register(r->pool, ldc,
                                   authnz_ldap_cleanup_connection_close,
                                   apr_pool_cleanup_null);
     }
     else {
         ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r,
-                      "[%" APR_PID_T_FMT "] auth_ldap authorise: no sec->host - weird...?", getpid());
-        return sec->auth_authoritative? HTTP_UNAUTHORIZED : DECLINED;
+                      "[%" APR_PID_T_FMT "] auth_ldap authorize: no sec->host - weird...?", getpid());
+        return AUTHZ_DENIED;
     }
 
     /*
      * If there are no elements in the group attribute array, the default should be
      * member and uniquemember; populate the array now.
      */
