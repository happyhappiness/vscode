              *   with mod_include to provide processing of the exec directive.
              */
             cgid_pfn_reg_with_ssi("exec", handle_exec);
         }
     }
     return ret;
-} 
+}
 
-static void *create_cgid_config(apr_pool_t *p, server_rec *s) 
-{ 
-    cgid_server_conf *c = 
-    (cgid_server_conf *) apr_pcalloc(p, sizeof(cgid_server_conf)); 
-
-    c->logname = NULL; 
-    c->logbytes = DEFAULT_LOGBYTES; 
-    c->bufbytes = DEFAULT_BUFBYTES; 
-    c->sockname = ap_server_root_relative(p, DEFAULT_SOCKET); 
-    return c; 
-} 
-
-static void *merge_cgid_config(apr_pool_t *p, void *basev, void *overridesv) 
-{ 
-    cgid_server_conf *base = (cgid_server_conf *) basev, *overrides = (cgid_server_conf *) overridesv; 
-
-    return overrides->logname ? overrides : base; 
-} 
-
-static const char *set_scriptlog(cmd_parms *cmd, void *dummy, const char *arg) 
-{ 
-    server_rec *s = cmd->server; 
+static void *create_cgid_config(apr_pool_t *p, server_rec *s)
+{
+    cgid_server_conf *c =
+    (cgid_server_conf *) apr_pcalloc(p, sizeof(cgid_server_conf));
+
+    c->logname = NULL;
+    c->logbytes = DEFAULT_LOGBYTES;
+    c->bufbytes = DEFAULT_BUFBYTES;
+    return c;
+}
+
+static void *merge_cgid_config(apr_pool_t *p, void *basev, void *overridesv)
+{
+    cgid_server_conf *base = (cgid_server_conf *) basev, *overrides = (cgid_server_conf *) overridesv;
+
+    return overrides->logname ? overrides : base;
+}
+
+static const char *set_scriptlog(cmd_parms *cmd, void *dummy, const char *arg)
+{
+    server_rec *s = cmd->server;
     cgid_server_conf *conf = ap_get_module_config(s->module_config,
-                                                  &cgid_module); 
+                                                  &cgid_module);
 
     conf->logname = ap_server_root_relative(cmd->pool, arg);
 
     if (!conf->logname) {
         return apr_pstrcat(cmd->pool, "Invalid ScriptLog path ",
                            arg, NULL);
     }
-    return NULL; 
-} 
+    return NULL;
+}
 
-static const char *set_scriptlog_length(cmd_parms *cmd, void *dummy, const char *arg) 
-{ 
-    server_rec *s = cmd->server; 
+static const char *set_scriptlog_length(cmd_parms *cmd, void *dummy, const char *arg)
+{
+    server_rec *s = cmd->server;
     cgid_server_conf *conf = ap_get_module_config(s->module_config,
-                                                  &cgid_module); 
+                                                  &cgid_module);
 
-    conf->logbytes = atol(arg); 
-    return NULL; 
-} 
-
-static const char *set_scriptlog_buffer(cmd_parms *cmd, void *dummy, const char *arg) 
-{ 
-    server_rec *s = cmd->server; 
-    cgid_server_conf *conf = ap_get_module_config(s->module_config,
-                                                  &cgid_module); 
+    conf->logbytes = atol(arg);
+    return NULL;
+}
 
-    conf->bufbytes = atoi(arg); 
-    return NULL; 
-} 
-
-static const char *set_script_socket(cmd_parms *cmd, void *dummy, const char *arg) 
-{ 
-    server_rec *s = cmd->server; 
+static const char *set_scriptlog_buffer(cmd_parms *cmd, void *dummy, const char *arg)
+{
+    server_rec *s = cmd->server;
     cgid_server_conf *conf = ap_get_module_config(s->module_config,
-                                                  &cgid_module); 
+                                                  &cgid_module);
 
-    conf->sockname = ap_server_root_relative(cmd->pool, arg); 
+    conf->bufbytes = atoi(arg);
+    return NULL;
+}
 
-    if (!conf->sockname) {
-        return apr_pstrcat(cmd->pool, "Invalid Scriptsock path ",
+static const char *set_script_socket(cmd_parms *cmd, void *dummy, const char *arg)
+{
+    const char *err = ap_check_cmd_context(cmd, GLOBAL_ONLY);
+    if (err != NULL) {
+        return err;
+    }
+
+    /* Make sure the pid is appended to the sockname */
+    sockname = ap_append_pid(cmd->pool, arg, ".");
+    sockname = ap_server_root_relative(cmd->pool, sockname);
+
+    if (!sockname) {
+        return apr_pstrcat(cmd->pool, "Invalid ScriptSock path",
                            arg, NULL);
     }
 
-    return NULL; 
-} 
+    return NULL;
+}
 
-static const command_rec cgid_cmds[] = 
-{ 
+static const command_rec cgid_cmds[] =
+{
     AP_INIT_TAKE1("ScriptLog", set_scriptlog, NULL, RSRC_CONF,
-                  "the name of a log for script debugging info"), 
+                  "the name of a log for script debugging info"),
     AP_INIT_TAKE1("ScriptLogLength", set_scriptlog_length, NULL, RSRC_CONF,
-                  "the maximum length (in bytes) of the script debug log"), 
+                  "the maximum length (in bytes) of the script debug log"),
     AP_INIT_TAKE1("ScriptLogBuffer", set_scriptlog_buffer, NULL, RSRC_CONF,
-                  "the maximum size (in bytes) to record of a POST request"), 
-    AP_INIT_TAKE1("Scriptsock", set_script_socket, NULL, RSRC_CONF,
+                  "the maximum size (in bytes) to record of a POST request"),
+    AP_INIT_TAKE1("ScriptSock", set_script_socket, NULL, RSRC_CONF,
                   "the name of the socket to use for communication with "
-                  "the cgi daemon."), 
-    {NULL} 
-}; 
-
-static int log_scripterror(request_rec *r, cgid_server_conf * conf, int ret, 
-                           apr_status_t rv, char *error) 
-{ 
-    apr_file_t *f = NULL; 
-    struct stat finfo; 
+                  "the cgi daemon."),
+    {NULL}
+};
+
+static int log_scripterror(request_rec *r, cgid_server_conf * conf, int ret,
+                           apr_status_t rv, char *error)
+{
+    apr_file_t *f = NULL;
+    struct stat finfo;
     char time_str[APR_CTIME_LEN];
     int log_flags = rv ? APLOG_ERR : APLOG_ERR;
 
-    ap_log_rerror(APLOG_MARK, log_flags, rv, r, 
-                "%s: %s", error, r->filename); 
+    ap_log_rerror(APLOG_MARK, log_flags, rv, r,
+                "%s: %s", error, r->filename);
 
     /* XXX Very expensive mainline case! Open, then getfileinfo! */
-    if (!conf->logname || 
-        ((stat(conf->logname, &finfo) == 0) 
-         && (finfo.st_size > conf->logbytes)) || 
+    if (!conf->logname ||
+        ((stat(conf->logname, &finfo) == 0)
+         && (finfo.st_size > conf->logbytes)) ||
          (apr_file_open(&f, conf->logname,
-                  APR_APPEND|APR_WRITE|APR_CREATE, APR_OS_DEFAULT, r->pool) != APR_SUCCESS)) { 
-        return ret; 
-    } 
+                  APR_APPEND|APR_WRITE|APR_CREATE, APR_OS_DEFAULT, r->pool) != APR_SUCCESS)) {
+        return ret;
+    }
 
-    /* "%% [Wed Jun 19 10:53:21 1996] GET /cgid-bin/printenv HTTP/1.0" */ 
+    /* "%% [Wed Jun 19 10:53:21 1996] GET /cgid-bin/printenv HTTP/1.0" */
     apr_ctime(time_str, apr_time_now());
-    apr_file_printf(f, "%%%% [%s] %s %s%s%s %s\n", time_str, r->method, r->uri, 
-            r->args ? "?" : "", r->args ? r->args : "", r->protocol); 
-    /* "%% 500 /usr/local/apache/cgid-bin */ 
-    apr_file_printf(f, "%%%% %d %s\n", ret, r->filename); 
-
-    apr_file_printf(f, "%%error\n%s\n", error); 
-
-    apr_file_close(f); 
-    return ret; 
-} 
+    apr_file_printf(f, "%%%% [%s] %s %s%s%s %s\n", time_str, r->method, r->uri,
+            r->args ? "?" : "", r->args ? r->args : "", r->protocol);
+    /* "%% 500 /usr/local/apache/cgid-bin */
+    apr_file_printf(f, "%%%% %d %s\n", ret, r->filename);
+
+    apr_file_printf(f, "%%error\n%s\n", error);
 
-static int log_script(request_rec *r, cgid_server_conf * conf, int ret, 
+    apr_file_close(f);
+    return ret;
+}
+
+static int log_script(request_rec *r, cgid_server_conf * conf, int ret,
                       char *dbuf, const char *sbuf, apr_bucket_brigade *bb,
-                      apr_file_t *script_err) 
-{ 
-    const apr_array_header_t *hdrs_arr = apr_table_elts(r->headers_in); 
-    const apr_table_entry_t *hdrs = (apr_table_entry_t *) hdrs_arr->elts; 
-    char argsbuffer[HUGE_STRING_LEN]; 
-    apr_file_t *f = NULL; 
+                      apr_file_t *script_err)
+{
+    const apr_array_header_t *hdrs_arr = apr_table_elts(r->headers_in);
+    const apr_table_entry_t *hdrs = (apr_table_entry_t *) hdrs_arr->elts;
+    char argsbuffer[HUGE_STRING_LEN];
+    apr_file_t *f = NULL;
     apr_bucket *e;
     const char *buf;
     apr_size_t len;
     apr_status_t rv;
     int first;
-    int i; 
-    struct stat finfo; 
+    int i;
+    struct stat finfo;
     char time_str[APR_CTIME_LEN];
 
     /* XXX Very expensive mainline case! Open, then getfileinfo! */
-    if (!conf->logname || 
-        ((stat(conf->logname, &finfo) == 0) 
-         && (finfo.st_size > conf->logbytes)) || 
-         (apr_file_open(&f, conf->logname, 
-                  APR_APPEND|APR_WRITE|APR_CREATE, APR_OS_DEFAULT, r->pool) != APR_SUCCESS)) { 
-        /* Soak up script output */ 
+    if (!conf->logname ||
+        ((stat(conf->logname, &finfo) == 0)
+         && (finfo.st_size > conf->logbytes)) ||
+         (apr_file_open(&f, conf->logname,
+                  APR_APPEND|APR_WRITE|APR_CREATE, APR_OS_DEFAULT, r->pool) != APR_SUCCESS)) {
+        /* Soak up script output */
         discard_script_output(bb);
         if (script_err) {
-            while (apr_file_gets(argsbuffer, HUGE_STRING_LEN, 
-                                 script_err) == APR_SUCCESS) 
-                continue; 
+            while (apr_file_gets(argsbuffer, HUGE_STRING_LEN,
+                                 script_err) == APR_SUCCESS)
+                continue;
         }
-        return ret; 
-    } 
+        return ret;
+    }
 
-    /* "%% [Wed Jun 19 10:53:21 1996] GET /cgid-bin/printenv HTTP/1.0" */ 
+    /* "%% [Wed Jun 19 10:53:21 1996] GET /cgid-bin/printenv HTTP/1.0" */
     apr_ctime(time_str, apr_time_now());
-    apr_file_printf(f, "%%%% [%s] %s %s%s%s %s\n", time_str, r->method, r->uri, 
-            r->args ? "?" : "", r->args ? r->args : "", r->protocol); 
-    /* "%% 500 /usr/local/apache/cgid-bin" */ 
-    apr_file_printf(f, "%%%% %d %s\n", ret, r->filename); 
-
-    apr_file_puts("%request\n", f); 
-    for (i = 0; i < hdrs_arr->nelts; ++i) { 
-        if (!hdrs[i].key) 
-            continue; 
-        apr_file_printf(f, "%s: %s\n", hdrs[i].key, hdrs[i].val); 
-    } 
-    if ((r->method_number == M_POST || r->method_number == M_PUT) 
-        && *dbuf) { 
-        apr_file_printf(f, "\n%s\n", dbuf); 
-    } 
-
-    apr_file_puts("%response\n", f); 
-    hdrs_arr = apr_table_elts(r->err_headers_out); 
-    hdrs = (const apr_table_entry_t *) hdrs_arr->elts; 
-
-    for (i = 0; i < hdrs_arr->nelts; ++i) { 
-        if (!hdrs[i].key) 
-            continue; 
-        apr_file_printf(f, "%s: %s\n", hdrs[i].key, hdrs[i].val); 
-    } 
+    apr_file_printf(f, "%%%% [%s] %s %s%s%s %s\n", time_str, r->method, r->uri,
+            r->args ? "?" : "", r->args ? r->args : "", r->protocol);
+    /* "%% 500 /usr/local/apache/cgid-bin" */
+    apr_file_printf(f, "%%%% %d %s\n", ret, r->filename);
+
+    apr_file_puts("%request\n", f);
+    for (i = 0; i < hdrs_arr->nelts; ++i) {
+        if (!hdrs[i].key)
+            continue;
+        apr_file_printf(f, "%s: %s\n", hdrs[i].key, hdrs[i].val);
+    }
+    if ((r->method_number == M_POST || r->method_number == M_PUT)
+        && *dbuf) {
+        apr_file_printf(f, "\n%s\n", dbuf);
+    }
 
-    if (sbuf && *sbuf) 
-        apr_file_printf(f, "%s\n", sbuf); 
+    apr_file_puts("%response\n", f);
+    hdrs_arr = apr_table_elts(r->err_headers_out);
+    hdrs = (const apr_table_entry_t *) hdrs_arr->elts;
+
+    for (i = 0; i < hdrs_arr->nelts; ++i) {
+        if (!hdrs[i].key)
+            continue;
+        apr_file_printf(f, "%s: %s\n", hdrs[i].key, hdrs[i].val);
+    }
+
+    if (sbuf && *sbuf)
+        apr_file_printf(f, "%s\n", sbuf);
 
     first = 1;
-    APR_BRIGADE_FOREACH(e, bb) {
+
+    for (e = APR_BRIGADE_FIRST(bb);
+         e != APR_BRIGADE_SENTINEL(bb);
+         e = APR_BUCKET_NEXT(e))
+    {
         if (APR_BUCKET_IS_EOS(e)) {
             break;
         }
         rv = apr_bucket_read(e, &buf, &len, APR_BLOCK_READ);
-        if (!APR_STATUS_IS_SUCCESS(rv) || (len == 0)) {
+        if (rv != APR_SUCCESS || (len == 0)) {
             break;
         }
         if (first) {
             apr_file_puts("%stdout\n", f);
             first = 0;
         }
         apr_file_write(f, buf, &len);
         apr_file_puts("\n", f);
     }
 
     if (script_err) {
-        if (apr_file_gets(argsbuffer, HUGE_STRING_LEN, 
-                          script_err) == APR_SUCCESS) { 
-            apr_file_puts("%stderr\n", f); 
-            apr_file_puts(argsbuffer, f); 
-            while (apr_file_gets(argsbuffer, HUGE_STRING_LEN, 
-                                 script_err) == APR_SUCCESS) 
-                apr_file_puts(argsbuffer, f); 
-            apr_file_puts("\n", f); 
-        } 
+        if (apr_file_gets(argsbuffer, HUGE_STRING_LEN,
+                          script_err) == APR_SUCCESS) {
+            apr_file_puts("%stderr\n", f);
+            apr_file_puts(argsbuffer, f);
+            while (apr_file_gets(argsbuffer, HUGE_STRING_LEN,
+                                 script_err) == APR_SUCCESS)
+                apr_file_puts(argsbuffer, f);
+            apr_file_puts("\n", f);
+        }
     }
 
     if (script_err) {
-        apr_file_close(script_err); 
+        apr_file_close(script_err);
     }
 
-    apr_file_close(f); 
-    return ret; 
-} 
+    apr_file_close(f);
+    return ret;
+}
 
 static apr_status_t close_unix_socket(void *thefd)
 {
-    int fd = (int)thefd;
-    
+    int fd = (int)((long)thefd);
+
     return close(fd);
 }
 
 static int connect_to_daemon(int *sdptr, request_rec *r,
                              cgid_server_conf *conf)
 {
