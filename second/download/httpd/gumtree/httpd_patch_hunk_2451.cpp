             if (!strcmp(v, w)) {
                 return AUTHZ_GRANTED;
             }
         }
     }
 
-    ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
+    ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01801)
                   "Authorization of user %s to access %s failed, reason: "
                   "user is not part of the 'require'ed group(s).",
                   r->user, r->uri);
 
     return AUTHZ_DENIED;
 }
 
 APR_OPTIONAL_FN_TYPE(authz_owner_get_file_group) *authz_owner_get_file_group;
 
 static authz_status dbmfilegroup_check_authorization(request_rec *r,
-                                              const char *require_args)
+                                                     const char *require_args,
+                                                     const void *parsed_require_args)
 {
     authz_dbm_config_rec *conf = ap_get_module_config(r->per_dir_config,
                                                       &authz_dbm_module);
     char *user = r->user;
     const char *realm = ap_auth_name(r);
     const char *filegroup = NULL;
