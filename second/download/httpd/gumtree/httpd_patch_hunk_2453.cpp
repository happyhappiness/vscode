             if (!strcmp(v, filegroup)) {
                 return AUTHZ_GRANTED;
             }
         }
     }
 
-    ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
+    ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01805)
                   "Authorization of user %s to access %s failed, reason: "
                   "user is not part of the 'require'ed group(s).",
                   r->user, r->uri);
 
     return AUTHZ_DENIED;
 }
 
 static const authz_provider authz_dbmgroup_provider =
 {
     &dbmgroup_check_authorization,
+    NULL,
 };
 
 static const authz_provider authz_dbmfilegroup_provider =
 {
     &dbmfilegroup_check_authorization,
+    NULL,
 };
 
 
 static void register_hooks(apr_pool_t *p)
 {
     authz_owner_get_file_group = APR_RETRIEVE_OPTIONAL_FN(authz_owner_get_file_group);
