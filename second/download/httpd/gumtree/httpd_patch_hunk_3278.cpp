     apr_file_t *fd;
     apr_size_t file_length;
     apr_off_t file_offset;
     apr_size_t bytes_written = 0;
 
     if (!APR_BUCKET_IS_FILE(bucket)) {
-        ap_log_error(APLOG_MARK, APLOG_ERR, rv, c->base_server,
+        ap_log_error(APLOG_MARK, APLOG_ERR, rv, c->base_server, APLOGNO(00006)
                      "core_filter: sendfile_nonblocking: "
                      "this should never happen");
         return APR_EGENERAL;
     }
     file_bucket = (apr_bucket_file *)(bucket->data);
     fd = file_bucket->fd;
