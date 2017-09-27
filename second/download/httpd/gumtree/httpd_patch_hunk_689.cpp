             ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, f->r,
                           "apr_file_write(child input), len %" APR_SIZE_T_FMT,
                           tmplen);
             return rv;
         }
         if (APR_STATUS_IS_EAGAIN(rv)) {
-            /* XXX handle blocking conditions here...  if we block, we need 
+            /* XXX handle blocking conditions here...  if we block, we need
              * to read data from the child process and pass it down to the
              * next filter!
              */
-            rv = drain_available_output(f);
+            rv = drain_available_output(f, bb);
             if (APR_STATUS_IS_EAGAIN(rv)) {
 #if APR_FILES_AS_SOCKETS
                 int num_events;
-                
-                rv = apr_poll(ctx->pollset, 2,
-                              &num_events, f->r->server->timeout);
+                const apr_pollfd_t *pdesc;
+
+                rv = apr_pollset_poll(ctx->pollset, f->r->server->timeout,
+                                      &num_events, &pdesc);
                 if (rv || dc->debug >= DBGLVL_GORY) {
                     ap_log_rerror(APLOG_MARK, APLOG_DEBUG,
-                                  rv, f->r, "apr_poll()");
+                                  rv, f->r, "apr_pollset_poll()");
                 }
-                if (rv != APR_SUCCESS && !APR_STATUS_IS_EINTR(rv)) { 
+                if (rv != APR_SUCCESS && !APR_STATUS_IS_EINTR(rv)) {
                     /* some error such as APR_TIMEUP */
                     return rv;
                 }
 #else /* APR_FILES_AS_SOCKETS */
                 /* Yuck... I'd really like to wait until I can read
-                 * or write, but instead I have to sleep and try again 
+                 * or write, but instead I have to sleep and try again
                  */
                 apr_sleep(100000); /* 100 milliseconds */
                 if (dc->debug >= DBGLVL_GORY) {
-                    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 
+                    ap_log_rerror(APLOG_MARK, APLOG_DEBUG,
                                   0, f->r, "apr_sleep()");
                 }
 #endif /* APR_FILES_AS_SOCKETS */
             }
             else if (rv != APR_SUCCESS) {
                 return rv;
             }
         }
     } while (bytes_written < len);
     return rv;
 }
 
-static apr_status_t ef_output_filter(ap_filter_t *f, apr_bucket_brigade *bb)
+/* ef_unified_filter:
+ *
+ * runs the bucket brigade bb through the filter and puts the result into
+ * bb, dropping the previous content of bb (the input)
+ */
+
+static int ef_unified_filter(ap_filter_t *f, apr_bucket_brigade *bb)
 {
     request_rec *r = f->r;
     conn_rec *c = r->connection;
     ef_ctx_t *ctx = f->ctx;
     apr_bucket *b;
     ef_dir_t *dc;
     apr_size_t len;
     const char *data;
     apr_status_t rv;
     char buf[4096];
     apr_bucket *eos = NULL;
+    apr_bucket_brigade *bb_tmp;
 
-    if (!ctx) {
-        if ((rv = init_filter_instance(f)) != APR_SUCCESS) {
-            return rv;
-        }
-        ctx = f->ctx;
-    }
-    if (ctx->noop) {
-        ap_remove_output_filter(f);
-        return ap_pass_brigade(f->next, bb);
-    }
     dc = ctx->dc;
+    bb_tmp = apr_brigade_create(r->pool, c->bucket_alloc);
 
-    APR_BRIGADE_FOREACH(b, bb) {
-
+    for (b = APR_BRIGADE_FIRST(bb);
+         b != APR_BRIGADE_SENTINEL(bb);
+         b = APR_BUCKET_NEXT(b))
+    {
         if (APR_BUCKET_IS_EOS(b)) {
             eos = b;
             break;
         }
 
         rv = apr_bucket_read(b, &data, &len, APR_BLOCK_READ);
