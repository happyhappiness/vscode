 
 static apr_status_t ef_close_file(void *vfile)
 {
     return apr_file_close(vfile);
 }
 
+static void child_errfn(apr_pool_t *pool, apr_status_t err, const char *description)
+{
+    request_rec *r;
+    void *vr;
+    apr_file_t *stderr_log;
+    char errbuf[200];
+    char time_str[APR_CTIME_LEN];
+
+    apr_pool_userdata_get(&vr, ERRFN_USERDATA_KEY, pool);
+    r = vr;
+    apr_file_open_stderr(&stderr_log, pool);
+    ap_recent_ctime(time_str, apr_time_now());
+    apr_file_printf(stderr_log,
+                    "[%s] [client %s] mod_ext_filter (%d)%s: %s\n",
+                    time_str,
+                    r->connection->remote_ip,
+                    err,
+                    apr_strerror(err, errbuf, sizeof(errbuf)),
+                    description);
+}
+
 /* init_ext_filter_process: get the external filter process going
  * This is per-filter-instance (i.e., per-request) initialization.
  */
 static apr_status_t init_ext_filter_process(ap_filter_t *f)
 {
     ef_ctx_t *ctx = f->ctx;
