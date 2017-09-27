     apr_file_t *fd = NULL;
     apr_status_t rc;
     const char *fspec;
 
     fspec = ap_server_root_relative(cmd->pool, filename);
     if (!fspec) {
-        ap_log_error(APLOG_MARK, APLOG_WARNING, APR_EBADPATH, cmd->server,
-                     "mod_file_cache: invalid file path "
+        ap_log_error(APLOG_MARK, APLOG_WARNING, APR_EBADPATH, cmd->server, APLOGNO(00794)
+                     "invalid file path "
                      "%s, skipping", filename);
         return;
     }
     if ((rc = apr_stat(&tmp.finfo, fspec, APR_FINFO_MIN,
                                  cmd->temp_pool)) != APR_SUCCESS) {
-        ap_log_error(APLOG_MARK, APLOG_WARNING, rc, cmd->server,
-            "mod_file_cache: unable to stat(%s), skipping", fspec);
+        ap_log_error(APLOG_MARK, APLOG_WARNING, rc, cmd->server, APLOGNO(00795)
+                     "unable to stat(%s), skipping", fspec);
         return;
     }
     if (tmp.finfo.filetype != APR_REG) {
-        ap_log_error(APLOG_MARK, APLOG_WARNING, 0, cmd->server,
-            "mod_file_cache: %s isn't a regular file, skipping", fspec);
+        ap_log_error(APLOG_MARK, APLOG_WARNING, 0, cmd->server, APLOGNO(00796)
+                     "%s isn't a regular file, skipping", fspec);
         return;
     }
     if (tmp.finfo.size > AP_MAX_SENDFILE) {
-        ap_log_error(APLOG_MARK, APLOG_WARNING, 0, cmd->server,
-            "mod_file_cache: %s is too large to cache, skipping", fspec);
+        ap_log_error(APLOG_MARK, APLOG_WARNING, 0, cmd->server, APLOGNO(00797)
+                     "%s is too large to cache, skipping", fspec);
         return;
     }
 
     rc = apr_file_open(&fd, fspec, APR_READ | APR_BINARY | APR_XTHREAD,
                        APR_OS_DEFAULT, cmd->pool);
     if (rc != APR_SUCCESS) {
-        ap_log_error(APLOG_MARK, APLOG_WARNING, rc, cmd->server,
-                     "mod_file_cache: unable to open(%s, O_RDONLY), skipping", fspec);
+        ap_log_error(APLOG_MARK, APLOG_WARNING, rc, cmd->server, APLOGNO(00798)
+                     "unable to open(%s, O_RDONLY), skipping", fspec);
         return;
     }
     apr_file_inherit_set(fd);
 
     /* WooHoo, we have a file to put in the cache */
     new_file = apr_pcalloc(cmd->pool, sizeof(a_file));
