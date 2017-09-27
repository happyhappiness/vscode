     return AUTHZ_DENIED;
 #else  /* APR_HAS_USER */
     char *owner = NULL;
     apr_finfo_t finfo;
 
     if (!r->user) {
-        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
-            "access to %s failed, reason: no authenticated user", r->uri);
-        return AUTHZ_DENIED;
+        return AUTHZ_DENIED_NO_USER;
     }
 
     if (!r->filename) {
         reason = "no filename available";
         ap_log_rerror(APLOG_MARK, APLOG_ERR, status, r,
                       "Authorization of user %s to access %s failed, reason: %s",
