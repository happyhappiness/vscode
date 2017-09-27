     char *user = r->user;
     const char *t, *w;
     apr_table_t *grpstatus = NULL;
     apr_status_t status;
 
     if (!user) {
-        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
-            "access to %s failed, reason: no authenticated user", r->uri);
-        return AUTHZ_DENIED;
+        return AUTHZ_DENIED_NO_USER;
     }
 
     /* If there is no group file - then we are not
      * configured. So decline.
      */
     if (!(conf->groupfile)) {
