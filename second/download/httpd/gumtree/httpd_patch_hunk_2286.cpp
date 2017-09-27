     const char *orig_groups = NULL;
     apr_status_t status;
     const char *groups;
     char *v;
 
     if (!user) {
-        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
-            "access to %s failed, reason: no authenticated user", r->uri);
-        return AUTHZ_DENIED;
+        return AUTHZ_DENIED_NO_USER;
     }
 
     if (!conf->grpfile) {
         ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                         "No group file was specified in the configuration");
         return AUTHZ_DENIED;
