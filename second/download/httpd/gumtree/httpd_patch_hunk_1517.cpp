 
                     rv = apr_bucket_read(e, &buffer, &len, APR_BLOCK_READ);
 
                     if (rv == APR_SUCCESS) {
                         parsing = 1;
                         rv = parse_chunk_size(ctx, buffer, len,
-                                f->r->server->limit_req_fieldsize);
+                                f->r->server->limit_req_fieldsize, strict);
                     }
                     if (rv != APR_SUCCESS) {
                         ap_log_rerror(APLOG_MARK, APLOG_INFO, rv, f->r,
                                       "Error reading/parsing chunk %s ",
                                       (APR_ENOSPC == rv) ? "(overflow)" : "");
                         if (parsing) {
