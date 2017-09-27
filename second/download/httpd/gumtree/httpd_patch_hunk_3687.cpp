     while ((w = ap_getword_conf(r->pool, &t)) && w[0]) {
         if (apr_table_get(grpstatus, w)) {
             return AUTHZ_GRANTED;
         }
     }
 
-    ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01667)
+    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(01667)
                     "Authorization of user %s to access %s failed, reason: "
                     "user is not part of the 'require'ed group(s).",
                     r->user, r->uri);
 
     return AUTHZ_DENIED;
 }
 
-APR_OPTIONAL_FN_TYPE(authz_owner_get_file_group) *authz_owner_get_file_group;
+static APR_OPTIONAL_FN_TYPE(authz_owner_get_file_group) *authz_owner_get_file_group;
 
 static authz_status filegroup_check_authorization(request_rec *r,
                                                   const char *require_args,
                                                   const void *parsed_require_args)
 {
     authz_groupfile_config_rec *conf = ap_get_module_config(r->per_dir_config,
