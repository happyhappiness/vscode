 }
 
 static apr_status_t pass_data_to_filter(ap_filter_t *f, const char *data,
                                         apr_size_t len, apr_bucket_brigade *bb)
 {
     ef_ctx_t *ctx = f->ctx;
-    ef_dir_t *dc = ctx->dc;
     apr_status_t rv;
     apr_size_t bytes_written = 0;
     apr_size_t tmplen;
 
     do {
         tmplen = len - bytes_written;
         rv = apr_file_write(ctx->proc->in,
                        (const char *)data + bytes_written,
                        &tmplen);
         bytes_written += tmplen;
         if (rv != APR_SUCCESS && !APR_STATUS_IS_EAGAIN(rv)) {
-            ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, f->r,
+            ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, f->r, APLOGNO(01461)
                           "apr_file_write(child input), len %" APR_SIZE_T_FMT,
                           tmplen);
             return rv;
         }
         if (APR_STATUS_IS_EAGAIN(rv)) {
             /* XXX handle blocking conditions here...  if we block, we need
