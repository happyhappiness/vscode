                     return rv;
                 }
                 if (rv == APR_SUCCESS) {
                     ctx->remaining = get_chunk_size(ctx->chunk_ln);
                     if (ctx->remaining == INVALID_CHAR) {
                         rv = APR_EGENERAL;
-                        http_error = HTTP_SERVICE_UNAVAILABLE;
+                        http_error = HTTP_BAD_REQUEST;
                     }
                 }
             }
             apr_brigade_cleanup(bb);
 
             /* Detect chunksize error (such as overflow) */
             if (rv != APR_SUCCESS || ctx->remaining < 0) {
-                ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, f->r, "Error reading first chunk %s ", 
+                ap_log_rerror(APLOG_MARK, APLOG_INFO, rv, f->r, APLOGNO(01589) "Error reading first chunk %s ",
                               (ctx->remaining < 0) ? "(overflow)" : "");
                 ctx->remaining = 0; /* Reset it in case we have to
                                      * come back here later */
-                if (APR_STATUS_IS_TIMEUP(rv)) { 
+                if (APR_STATUS_IS_TIMEUP(rv)) {
                     http_error = HTTP_REQUEST_TIME_OUT;
                 }
                 return bail_out_on_error(ctx, f, http_error);
             }
 
             if (!ctx->remaining) {
