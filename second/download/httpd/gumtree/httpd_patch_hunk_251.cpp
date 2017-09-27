 ** |              rewriting logfile support
 ** |                                                       |
 ** +-------------------------------------------------------+
 */
 
 
-static void open_rewritelog(server_rec *s, apr_pool_t *p)
+static int open_rewritelog(server_rec *s, apr_pool_t *p)
 {
     rewrite_server_conf *conf;
     const char *fname;
     apr_status_t rc;
     piped_log *pl;
     int rewritelog_flags = ( APR_WRITE | APR_APPEND | APR_CREATE );
     apr_fileperms_t rewritelog_mode = ( APR_UREAD | APR_UWRITE |
                                         APR_GREAD | APR_WREAD );
 
     conf = ap_get_module_config(s->module_config, &rewrite_module);
 
-    if (conf->rewritelogfile == NULL) {
-        return;
-    }
-    if (*(conf->rewritelogfile) == '\0') {
-        return;
-    }
-    if (conf->rewritelogfp != NULL) {
-        return; /* virtual log shared w/ main server */
+    /* - no logfile configured
+     * - logfilename empty
+     * - virtual log shared w/ main server
+     */
+    if (!conf->rewritelogfile || !*conf->rewritelogfile || conf->rewritelogfp) {
+        return 1;
     }
 
     if (*conf->rewritelogfile == '|') {
         if ((pl = ap_open_piped_log(p, conf->rewritelogfile+1)) == NULL) {
             ap_log_error(APLOG_MARK, APLOG_ERR, 0, s,
                          "mod_rewrite: could not open reliable pipe "
                          "to RewriteLog filter %s", conf->rewritelogfile+1);
-            exit(1);
+            return 0;
         }
         conf->rewritelogfp = ap_piped_log_write_fd(pl);
     }
     else if (*conf->rewritelogfile != '\0') {
         fname = ap_server_root_relative(p, conf->rewritelogfile);
         if (!fname) {
             ap_log_error(APLOG_MARK, APLOG_ERR, APR_EBADPATH, s,
                          "mod_rewrite: Invalid RewriteLog "
                          "path %s", conf->rewritelogfile);
-            exit(1);
+            return 0;
         }
         if ((rc = apr_file_open(&conf->rewritelogfp, fname,
                                 rewritelog_flags, rewritelog_mode, p))
                 != APR_SUCCESS) {
             ap_log_error(APLOG_MARK, APLOG_ERR, rc, s,
                          "mod_rewrite: could not open RewriteLog "
                          "file %s", fname);
-            exit(1);
+            return 0;
         }
     }
-    return;
+
+    return 1;
 }
 
 static void rewritelog(request_rec *r, int level, const char *text, ...)
 {
     rewrite_server_conf *conf;
     conn_rec *conn;
