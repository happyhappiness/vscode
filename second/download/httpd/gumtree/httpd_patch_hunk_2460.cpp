     if (!r->user) {
         return AUTHZ_DENIED_NO_USER;
     }
 
     if (!r->filename) {
         reason = "no filename available";
-        ap_log_rerror(APLOG_MARK, APLOG_ERR, status, r,
+        ap_log_rerror(APLOG_MARK, APLOG_ERR, status, r, APLOGNO(01633)
                       "Authorization of user %s to access %s failed, reason: %s",
                       r->user, r->uri, reason ? reason : "unknown");
         return AUTHZ_DENIED;
     }
 
     status = apr_stat(&finfo, r->filename, APR_FINFO_USER, r->pool);
     if (status != APR_SUCCESS) {
         reason = apr_pstrcat(r->pool, "could not stat file ",
                                 r->filename, NULL);
-        ap_log_rerror(APLOG_MARK, APLOG_ERR, status, r,
+        ap_log_rerror(APLOG_MARK, APLOG_ERR, status, r, APLOGNO(01634)
                       "Authorization of user %s to access %s failed, reason: %s",
                       r->user, r->uri, reason ? reason : "unknown");
         return AUTHZ_DENIED;
     }
 
     if (!(finfo.valid & APR_FINFO_USER)) {
         reason = "no file owner information available";
-        ap_log_rerror(APLOG_MARK, APLOG_ERR, status, r,
+        ap_log_rerror(APLOG_MARK, APLOG_ERR, status, r, APLOGNO(01635)
                       "Authorization of user %s to access %s failed, reason: %s",
                       r->user, r->uri, reason ? reason : "unknown");
         return AUTHZ_DENIED;
     }
 
     status = apr_uid_name_get(&owner, finfo.user, r->pool);
     if (status != APR_SUCCESS || !owner) {
         reason = "could not get name of file owner";
-        ap_log_rerror(APLOG_MARK, APLOG_ERR, status, r,
+        ap_log_rerror(APLOG_MARK, APLOG_ERR, status, r, APLOGNO(01636)
                       "Authorization of user %s to access %s failed, reason: %s",
                       r->user, r->uri, reason ? reason : "unknown");
         return AUTHZ_DENIED;
     }
 
     if (strcmp(owner, r->user)) {
         reason = apr_psprintf(r->pool, "file owner %s does not match.",
                                 owner);
-        ap_log_rerror(APLOG_MARK, APLOG_ERR, status, r,
+        ap_log_rerror(APLOG_MARK, APLOG_ERR, status, r, APLOGNO(01637)
                       "Authorization of user %s to access %s failed, reason: %s",
                       r->user, r->uri, reason ? reason : "unknown");
         return AUTHZ_DENIED;
     }
 
     /* this user is authorized */
