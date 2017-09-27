 
 static const char *set_cookie_log(cmd_parms *cmd, void *dummy, const char *fn)
 {
     return add_custom_log(cmd, dummy, fn, "%{Cookie}n \"%r\" %t", NULL);
 }
 
+static const char *set_buffered_logs_on(cmd_parms *parms, void *dummy, int flag)
+{
+    buffered_logs = flag;
+    ap_log_set_writer_init(ap_buffered_log_writer_init);
+    ap_log_set_writer(ap_buffered_log_writer);
+    return NULL;
+}
 static const command_rec config_log_cmds[] =
 {
 AP_INIT_TAKE23("CustomLog", add_custom_log, NULL, RSRC_CONF,
      "a file name, a custom log format string or format name, "
      "and an optional \"env=\" clause (see docs)"),
 AP_INIT_TAKE1("TransferLog", set_transfer_log, NULL, RSRC_CONF,
      "the filename of the access log"),
 AP_INIT_TAKE12("LogFormat", log_format, NULL, RSRC_CONF,
      "a log format string (see docs) and an optional format name"),
 AP_INIT_TAKE1("CookieLog", set_cookie_log, NULL, RSRC_CONF,
      "the filename of the cookie log"),
+AP_INIT_FLAG("BufferedLogs", set_buffered_logs_on, NULL, RSRC_CONF,
+                 "Enable Buffered Logging (experimental)"),
     {NULL}
 };
 
 static config_log_state *open_config_log(server_rec *s, apr_pool_t *p,
                                          config_log_state *cls,
                                          apr_array_header_t *default_format)
 {
-    apr_status_t status;
-    void *data;
-    const char *userdata_key = "open_config_log";
-
-    /* Skip opening the log the first time through. It's really
-     * good to avoid starting the piped log process during preflight.
-     */
-    apr_pool_userdata_get(&data, userdata_key, s->process->pool);
-    if (!data) {
-        apr_pool_userdata_set((const void *)1, userdata_key,
-                              NULL, s->process->pool);
-        /* If logging for the first time after a restart, keep going. */
-        if (!ap_my_generation) {
-            return cls;
-        }
-    }
-
-    if (cls->log_fd != NULL) {
+    if (cls->log_writer != NULL) {
         return cls;             /* virtual config shared w/main server */
     }
 
     if (cls->fname == NULL) {
         return cls;             /* Leave it NULL to decline.  */
     }
-
-    if (*cls->fname == '|') {
-        piped_log *pl;
-
-        pl = ap_open_piped_log(p, cls->fname + 1);
-        if (pl == NULL) {
-            exit(1);
-        }
-        cls->log_fd = ap_piped_log_write_fd(pl);
-    }
-    else {
-        const char *fname = ap_server_root_relative(p, cls->fname);
-        if (!fname) {
-            ap_log_error(APLOG_MARK, APLOG_ERR, APR_EBADPATH, s,
-                         "invalid transfer log path %s.", cls->fname);
-            exit(1);
-        }
-        if ((status = apr_file_open(&cls->log_fd, fname, xfer_flags,
-                                    xfer_perms, p)) != APR_SUCCESS) {
-            ap_log_error(APLOG_MARK, APLOG_ERR, status, s,
-                         "could not open transfer log file %s.", fname);
-            exit(1);
-        }
-        apr_file_inherit_set(cls->log_fd);
-    }
-#ifdef BUFFERED_LOGS
-    cls->outcnt = 0;
-#endif
+    
+    cls->log_writer = log_writer_init(p, s, cls->fname);
+    if (cls->log_writer == NULL)
+        return NULL; 
 
     return cls;
 }
 
-static config_log_state *open_multi_logs(server_rec *s, apr_pool_t *p)
+static int open_multi_logs(server_rec *s, apr_pool_t *p)
 {
     int i;
     multi_log_state *mls = ap_get_module_config(s->module_config,
                                              &log_config_module);
     config_log_state *clsarray;
     const char *dummy;
