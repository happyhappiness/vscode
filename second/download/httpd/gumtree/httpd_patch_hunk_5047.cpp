         to authz_owner_get_file_group already did it
         for us.
         */
         return AUTHZ_DENIED;
     }
 
-    ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01671)
+    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(01671)
                   "Authorization of user %s to access %s failed, reason: "
                   "user is not part of the 'require'ed file group.",
                   r->user, r->uri);
 
     return AUTHZ_DENIED;
 }
