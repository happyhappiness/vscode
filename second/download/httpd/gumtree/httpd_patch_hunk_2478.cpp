     /* cleanup should happen even if something fails part-way through here */
     apr_pool_cleanup_register(r->pool, r, privileges_end_req,
                               apr_pool_cleanup_null);
     /* set user and group if configured */
     if (cfg->uid || cfg->gid) {
         if (setppriv(PRIV_ON, PRIV_EFFECTIVE, priv_setid) == -1) {
-            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
+            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(02144)
                           "No privilege to set user/group");
         }
         /* if we should be able to set these but can't, it could be
          * a serious security issue.  Bail out rather than risk it!
          */
         if (cfg->uid && (setuid(cfg->uid) == -1)) {
-            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
+            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(02145)
                           "Error setting userid");
             return HTTP_INTERNAL_SERVER_ERROR;
         }
         if (cfg->gid && (setgid(cfg->gid) == -1)) {
-            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
+            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(02146)
                           "Error setting group");
             return HTTP_INTERNAL_SERVER_ERROR;
         }
     }
     /* set vhost's privileges */
     if (setppriv(PRIV_SET, PRIV_EFFECTIVE, cfg->priv) == -1) {
-        ap_log_rerror(APLOG_MARK, APLOG_ERR, errno, r,
+        ap_log_rerror(APLOG_MARK, APLOG_ERR, errno, r, APLOGNO(02147)
                       "Error setting effective privileges");
         return HTTP_INTERNAL_SERVER_ERROR;
     }
 
     /* ... including those of any subprocesses */
     if (setppriv(PRIV_SET, PRIV_INHERITABLE, cfg->child_priv) == -1) {
-        ap_log_rerror(APLOG_MARK, APLOG_ERR, errno, r,
+        ap_log_rerror(APLOG_MARK, APLOG_ERR, errno, r, APLOGNO(02148)
                       "Error setting inheritable privileges");
         return HTTP_INTERNAL_SERVER_ERROR;
     }
     if (setppriv(PRIV_SET, PRIV_LIMIT, cfg->child_priv) == -1) {
-        ap_log_rerror(APLOG_MARK, APLOG_ERR, errno, r,
+        ap_log_rerror(APLOG_MARK, APLOG_ERR, errno, r, APLOGNO(02149)
                       "Error setting limit privileges");
         return HTTP_INTERNAL_SERVER_ERROR;
     }
 
     /* If we're in a child process, drop down PPERM too */
     if (fork_req) {
         if (setppriv(PRIV_SET, PRIV_PERMITTED, cfg->priv) == -1) {
-            ap_log_rerror(APLOG_MARK, APLOG_ERR, errno, r,
+            ap_log_rerror(APLOG_MARK, APLOG_ERR, errno, r, APLOGNO(02150)
                           "Error setting permitted privileges");
             return HTTP_INTERNAL_SERVER_ERROR;
         }
     }
 
     return OK;
 }
 #define PDROP_CHECK(x) if (x == -1) { \
-        ap_log_error(APLOG_MARK, APLOG_CRIT, errno, s, \
+        ap_log_error(APLOG_MARK, APLOG_CRIT, errno, s, APLOGNO(02151) \
                      "Error dropping privileges"); \
         return !OK; \
     }
 
 static int privileges_drop_first(apr_pool_t *pool, server_rec *s)
 {
