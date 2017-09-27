         to authz_owner_get_file_group already did it
         for us.
         */
         return AUTHZ_DENIED;
     }
 
-    ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
+    ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01671)
                   "Authorization of user %s to access %s failed, reason: "
                   "user is not part of the 'require'ed file group.",
                   r->user, r->uri);
 
     return AUTHZ_DENIED;
 }
 
 static const authz_provider authz_group_provider =
 {
     &group_check_authorization,
+    NULL,
 };
 
 static const authz_provider authz_filegroup_provider =
 {
     &filegroup_check_authorization,
+    NULL,
 };
 
 static void register_hooks(apr_pool_t *p)
 {
     authz_owner_get_file_group = APR_RETRIEVE_OPTIONAL_FN(authz_owner_get_file_group);
 
