             apr_brigade_cleanup(bb);
 
             /* Detect chunksize error (such as overflow) */
             if (rv != APR_SUCCESS || ctx->remaining < 0) {
                 ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, f->r, "Error reading first chunk %s ", 
                               (ctx->remaining < 0) ? "(overflow)" : "");
-                ctx->remaining = 0; /* Reset it in case we have to
-                                     * come back here later */
-                if (APR_STATUS_IS_TIMEUP(rv)) { 
+                if (APR_STATUS_IS_TIMEUP(rv) || ctx->remaining > 0) {
                     http_error = HTTP_REQUEST_TIME_OUT;
                 }
+                ctx->remaining = 0; /* Reset it in case we have to
+                                     * come back here later */
                 return bail_out_on_error(ctx, f, http_error);
             }
 
             if (!ctx->remaining) {
-                /* Handle trailers by calling ap_get_mime_headers again! */
-                ctx->state = BODY_NONE;
-                ap_get_mime_headers(f->r);
-                e = apr_bucket_eos_create(f->c->bucket_alloc);
-                APR_BRIGADE_INSERT_TAIL(b, e);
-                ctx->eos_sent = 1;
-                return APR_SUCCESS;
+                return read_chunked_trailers(ctx, f, b,
+                        conf->merge_trailers == AP_MERGE_TRAILERS_ENABLE);
             }
         }
     }
     else {
         bb = ctx->bb;
     }
