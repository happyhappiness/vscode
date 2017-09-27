     apr_pool_destroy(sp);
 
     *out = grps;
     return APR_SUCCESS;
 }
 
-/* Checking ID */
-
-static int check_user_access(request_rec *r)
+static authz_status group_check_authorization(request_rec *r,
+                                             const char *require_args)
 {
     authz_groupfile_config_rec *conf = ap_get_module_config(r->per_dir_config,
-                                                      &authz_groupfile_module);
+            &authz_groupfile_module);
     char *user = r->user;
-    int m = r->method_number;
-    int required_group = 0;
-    register int x;
     const char *t, *w;
     apr_table_t *grpstatus = NULL;
-    const apr_array_header_t *reqs_arr = ap_requires(r);
-    require_line *reqs;
-    const char *filegroup = NULL;
-    char *reason = NULL;
+    apr_status_t status;
+
+    if (!user) {
+        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
+            "access to %s failed, reason: no authenticated user", r->uri);
+        return AUTHZ_DENIED;
+    }
 
     /* If there is no group file - then we are not
      * configured. So decline.
      */
     if (!(conf->groupfile)) {
-        return DECLINED;
+        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
+                        "No group file was specified in the configuration");
+        return AUTHZ_DENIED;
     }
 
-    if (!reqs_arr) {
-        return DECLINED; /* XXX change from legacy */
+    status = groups_for_user(r->pool, user, conf->groupfile,
+                                &grpstatus);
+
+    if (status != APR_SUCCESS) {
+        ap_log_rerror(APLOG_MARK, APLOG_ERR, status, r,
+                        "Could not open group file: %s",
+                        conf->groupfile);
+        return AUTHZ_DENIED;
     }
 
-    /* If there's no user, it's a misconfiguration */
-    if (!user) {
-        return HTTP_INTERNAL_SERVER_ERROR;
+    if (apr_table_elts(grpstatus)->nelts == 0) {
+        /* no groups available, so exit immediately */
+        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
+                      "Authorization of user %s to access %s failed, reason: "
+                      "user doesn't appear in group file (%s).",
+                      r->user, r->uri, conf->groupfile);
+        return AUTHZ_DENIED;
     }
 
-    reqs = (require_line *)reqs_arr->elts;
+    t = require_args;
+    while ((w = ap_getword_conf(r->pool, &t)) && w[0]) {
+        if (apr_table_get(grpstatus, w)) {
+            return AUTHZ_GRANTED;
+        }
+    }
 
-    for (x = 0; x < reqs_arr->nelts; x++) {
+    ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
+                    "Authorization of user %s to access %s failed, reason: "
+                    "user is not part of the 'require'ed group(s).",
+                    r->user, r->uri);
 
-        if (!(reqs[x].method_mask & (AP_METHOD_BIT << m))) {
-            continue;
-        }
+    return AUTHZ_DENIED;
+}
 
-        t = reqs[x].requirement;
-        w = ap_getword_white(r->pool, &t);
+APR_OPTIONAL_FN_TYPE(authz_owner_get_file_group) *authz_owner_get_file_group;
 
-        /* needs mod_authz_owner to be present */
-        if (!strcasecmp(w, "file-group")) {
-            filegroup = apr_table_get(r->notes, AUTHZ_GROUP_NOTE);
-
-            if (!filegroup) {
-                /* mod_authz_owner is not present or not
-                 * authoritative. We are just a helper module for testing
-                 * group membership, so we don't care and decline.
-                 */
-                continue;
-            }
-        }
+static authz_status filegroup_check_authorization(request_rec *r,
+                                              const char *require_args)
+{
+    authz_groupfile_config_rec *conf = ap_get_module_config(r->per_dir_config,
+            &authz_groupfile_module);
+    char *user = r->user;
+    apr_table_t *grpstatus = NULL;
+    apr_status_t status;
+    const char *filegroup = NULL;
 
-        if (!strcasecmp(w, "group") || filegroup) {
-            required_group = 1; /* remember the requirement */
+    if (!user) {
+        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
+            "access to %s failed, reason: no authenticated user", r->uri);
+        return AUTHZ_DENIED;
+    }
 
-            /* create group table only if actually needed. */
-            if (!grpstatus) {
-                apr_status_t status;
-
-                status = groups_for_user(r->pool, user, conf->groupfile,
-                                         &grpstatus);
-
-                if (status != APR_SUCCESS) {
-                    ap_log_rerror(APLOG_MARK, APLOG_ERR, status, r,
-                                  "Could not open group file: %s",
-                                  conf->groupfile);
-                    return HTTP_INTERNAL_SERVER_ERROR;
-                }
-
-                if (apr_table_elts(grpstatus)->nelts == 0) {
-                    /* no groups available, so exit immediately */
-                    reason = apr_psprintf(r->pool,
-                                          "user doesn't appear in group file "
-                                          "(%s).", conf->groupfile);
-                    break;
-                }
-            }
+    /* If there is no group file - then we are not
+     * configured. So decline.
+     */
+    if (!(conf->groupfile)) {
+        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
+                        "No group file was specified in the configuration");
+        return AUTHZ_DENIED;
+    }
 
-            if (filegroup) {
-                if (apr_table_get(grpstatus, filegroup)) {
-                    return OK;
-                }
-
-                if (conf->authoritative) {
-                    reason = apr_psprintf(r->pool,
-                                          "file group '%s' does not match.",
-                                          filegroup);
-                    break;
-                }
-
-                /* now forget the filegroup, thus alternatively require'd
-                   groups get a real chance */
-                filegroup = NULL;
-            }
-            else {
-                while (t[0]) {
-                    w = ap_getword_conf(r->pool, &t);
-                    if (apr_table_get(grpstatus, w)) {
-                        return OK;
-                    }
-                }
-            }
-        }
+    status = groups_for_user(r->pool, user, conf->groupfile,
+                             &grpstatus);
+    if (status != APR_SUCCESS) {
+        ap_log_rerror(APLOG_MARK, APLOG_ERR, status, r,
+                      "Could not open group file: %s",
+                      conf->groupfile);
+        return AUTHZ_DENIED;
     }
 
-    /* No applicable "require group" for this method seen */
-    if (!required_group || !conf->authoritative) {
-        return DECLINED;
+    if (apr_table_elts(grpstatus)->nelts == 0) {
+        /* no groups available, so exit immediately */
+        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
+                        "Authorization of user %s to access %s failed, reason: "
+                        "user doesn't appear in group file (%s).",
+                        r->user, r->uri, conf->groupfile);
+        return AUTHZ_DENIED;
+    }
+
+    filegroup = authz_owner_get_file_group(r);
+
+    if (filegroup) {
+        if (apr_table_get(grpstatus, filegroup)) {
+            return AUTHZ_GRANTED;
+        }
+    }
+    else {
+        /* No need to emit a error log entry because the call
+        to authz_owner_get_file_group already did it
+        for us.
+        */
+        return AUTHZ_DENIED;
     }
 
     ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
-                  "Authorization of user %s to access %s failed, reason: %s",
-                  r->user, r->uri,
-                  reason ? reason : "user is not part of the "
-                                    "'require'ed group(s).");
+                  "Authorization of user %s to access %s failed, reason: "
+                  "user is not part of the 'require'ed file group.",
+                  r->user, r->uri);
 
-    ap_note_auth_failure(r);
-    return HTTP_UNAUTHORIZED;
+    return AUTHZ_DENIED;
 }
 
+static const authz_provider authz_group_provider =
+{
+    &group_check_authorization,
+};
+
+static const authz_provider authz_filegroup_provider =
+{
+    &filegroup_check_authorization,
+};
+
 static void register_hooks(apr_pool_t *p)
 {
-    static const char * const aszPre[]={ "mod_authz_owner.c", NULL };
+    authz_owner_get_file_group = APR_RETRIEVE_OPTIONAL_FN(authz_owner_get_file_group);
 
-    ap_hook_auth_checker(check_user_access, aszPre, NULL, APR_HOOK_MIDDLE);
+    ap_register_auth_provider(p, AUTHZ_PROVIDER_GROUP, "group",
+                              AUTHZ_PROVIDER_VERSION,
+                              &authz_group_provider,
+                              AP_AUTH_INTERNAL_PER_CONF);
+    ap_register_auth_provider(p, AUTHZ_PROVIDER_GROUP, "file-group",
+                              AUTHZ_PROVIDER_VERSION,
+                              &authz_filegroup_provider,
+                              AP_AUTH_INTERNAL_PER_CONF);
 }
 
-module AP_MODULE_DECLARE_DATA authz_groupfile_module =
+AP_DECLARE_MODULE(authz_groupfile) =
 {
     STANDARD20_MODULE_STUFF,
     create_authz_groupfile_dir_config,/* dir config creater */
     NULL,                             /* dir merger -- default is to override */
     NULL,                             /* server config */
     NULL,                             /* merge server config */
