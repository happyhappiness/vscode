         lenp = apr_table_get(f->r->headers_in, "Content-Length");
 
         if (tenc) {
             if (!strcasecmp(tenc, "chunked")) {
                 ctx->state = BODY_CHUNK;
             }
+            /* test lenp, because it gives another case we can handle */
+            else if (!lenp) {
+                /* Something that isn't in HTTP, unless some future
+                 * edition defines new transfer ecodings, is unsupported.
+                 */
+                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, f->r,
+                              "Unknown Transfer-Encoding: %s", tenc);
+                return bail_out_on_error(ctx, f, HTTP_NOT_IMPLEMENTED);
+            }
+            else {
+                ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, f->r,
+                  "Unknown Transfer-Encoding: %s; using Content-Length", tenc);
+                tenc = NULL;
+            }
         }
-        else if (lenp) {
+        if (lenp && !tenc) {
             char *endstr;
 
             ctx->state = BODY_LENGTH;
             errno = 0;
 
             /* Protects against over/underflow, non-digit chars in the
              * string (excluding leading space) (the endstr checks)
              * and a negative number. */
             if (apr_strtoff(&ctx->remaining, lenp, &endstr, 10)
                 || endstr == lenp || *endstr || ctx->remaining < 0) {
-                apr_bucket_brigade *bb;
 
                 ctx->remaining = 0;
                 ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, f->r,
                               "Invalid Content-Length");
 
-                bb = apr_brigade_create(f->r->pool, f->c->bucket_alloc);
-                e = ap_bucket_error_create(HTTP_REQUEST_ENTITY_TOO_LARGE, NULL,
-                                           f->r->pool, f->c->bucket_alloc);
-                APR_BRIGADE_INSERT_TAIL(bb, e);
-                e = apr_bucket_eos_create(f->c->bucket_alloc);
-                APR_BRIGADE_INSERT_TAIL(bb, e);
-                ctx->eos_sent = 1;
-                return ap_pass_brigade(f->r->output_filters, bb);
+                return bail_out_on_error(ctx, f, HTTP_REQUEST_ENTITY_TOO_LARGE);
             }
 
             /* If we have a limit in effect and we know the C-L ahead of
              * time, stop it here if it is invalid.
              */
             if (ctx->limit && ctx->limit < ctx->remaining) {
-                apr_bucket_brigade *bb;
                 ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, f->r,
                           "Requested content-length of %" APR_OFF_T_FMT
                           " is larger than the configured limit"
                           " of %" APR_OFF_T_FMT, ctx->remaining, ctx->limit);
-                bb = apr_brigade_create(f->r->pool, f->c->bucket_alloc);
-                e = ap_bucket_error_create(HTTP_REQUEST_ENTITY_TOO_LARGE, NULL,
-                                           f->r->pool, f->c->bucket_alloc);
-                APR_BRIGADE_INSERT_TAIL(bb, e);
-                e = apr_bucket_eos_create(f->c->bucket_alloc);
-                APR_BRIGADE_INSERT_TAIL(bb, e);
-                ctx->eos_sent = 1;
-                return ap_pass_brigade(f->r->output_filters, bb);
+                return bail_out_on_error(ctx, f, HTTP_REQUEST_ENTITY_TOO_LARGE);
             }
         }
 
         /* If we don't have a request entity indicated by the headers, EOS.
          * (BODY_NONE is a valid intermediate state due to trailers,
          *  but it isn't a valid starting state.)
