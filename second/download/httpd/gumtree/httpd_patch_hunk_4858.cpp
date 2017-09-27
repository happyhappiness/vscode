     apr_status_t rv;
     apr_size_t bytes_written = 0;
     apr_size_t tmplen;
 
     do {
         tmplen = len - bytes_written;
-        rv = apr_file_write(ctx->proc->in,
+        rv = apr_file_write_full(ctx->proc->in,
                        (const char *)data + bytes_written,
-                       &tmplen);
+                       tmplen, &tmplen);
         bytes_written += tmplen;
         if (rv != APR_SUCCESS && !APR_STATUS_IS_EAGAIN(rv)) {
             ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, f->r, APLOGNO(01461)
                           "apr_file_write(child input), len %" APR_SIZE_T_FMT,
                           tmplen);
             return rv;
