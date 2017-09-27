             if (token == NULL || token[0] == '\0') {
                 ap_remove_output_filter(f);
                 return ap_pass_brigade(f->next, bb);
             }
         }
 
-        /* For a 304 or 204 response there is no entity included in
-         * the response and hence nothing to deflate. */
-        if (r->status == HTTP_NOT_MODIFIED || r->status == HTTP_NO_CONTENT) {
-            ap_remove_output_filter(f);
-            return ap_pass_brigade(f->next, bb);
-        }
+        /* At this point we have decided to filter the content. Let's try to
+         * to initialize zlib (except for 304 responses, where we will only
+         * send out the headers).
+         */
 
-        /* We're cool with filtering this. */
-        ctx = f->ctx = apr_pcalloc(r->pool, sizeof(*ctx));
-        ctx->bb = apr_brigade_create(r->pool, f->c->bucket_alloc);
-        ctx->buffer = apr_palloc(r->pool, c->bufferSize);
-        ctx->libz_end_func = deflateEnd;
+        if (r->status != HTTP_NOT_MODIFIED) {
+            ctx = f->ctx = apr_pcalloc(r->pool, sizeof(*ctx));
+            ctx->bb = apr_brigade_create(r->pool, f->c->bucket_alloc);
+            ctx->buffer = apr_palloc(r->pool, c->bufferSize);
+            ctx->libz_end_func = deflateEnd;
 
-        zRC = deflateInit2(&ctx->stream, c->compressionlevel, Z_DEFLATED,
-                           c->windowSize, c->memlevel,
-                           Z_DEFAULT_STRATEGY);
+            zRC = deflateInit2(&ctx->stream, c->compressionlevel, Z_DEFLATED,
+                               c->windowSize, c->memlevel,
+                               Z_DEFAULT_STRATEGY);
 
-        if (zRC != Z_OK) {
-            deflateEnd(&ctx->stream);
-            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
-                          "unable to init Zlib: "
-                          "deflateInit2 returned %d: URL %s",
-                          zRC, r->uri);
+            if (zRC != Z_OK) {
+                deflateEnd(&ctx->stream);
+                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
+                              "unable to init Zlib: "
+                              "deflateInit2 returned %d: URL %s",
+                              zRC, r->uri);
+                /*
+                 * Remove ourselves as it does not make sense to return:
+                 * We are not able to init libz and pass data down the chain
+                 * uncompressed.
+                 */
+                ap_remove_output_filter(f);
+                return ap_pass_brigade(f->next, bb);
+            }
             /*
-             * Remove ourselves as it does not make sense to return:
-             * We are not able to init libz and pass data down the chain
-             * uncompressed.
+             * Register a cleanup function to ensure that we cleanup the internal
+             * libz resources.
              */
-            ap_remove_output_filter(f);
-            return ap_pass_brigade(f->next, bb);
+            apr_pool_cleanup_register(r->pool, ctx, deflate_ctx_cleanup,
+                                      apr_pool_cleanup_null);
         }
+
         /*
-         * Register a cleanup function to ensure that we cleanup the internal
-         * libz resources.
+         * Zlib initialization worked, so we can now change the important
+         * content metadata before sending the response out.
          */
-        apr_pool_cleanup_register(r->pool, ctx, deflate_ctx_cleanup,
-                                  apr_pool_cleanup_null);
-
-        /* add immortal gzip header */
-        e = apr_bucket_immortal_create(gzip_header, sizeof gzip_header,
-                                       f->c->bucket_alloc);
-        APR_BRIGADE_INSERT_TAIL(ctx->bb, e);
 
         /* If the entire Content-Encoding is "identity", we can replace it. */
         if (!encoding || !strcasecmp(encoding, "identity")) {
             apr_table_setn(r->headers_out, "Content-Encoding", "gzip");
         }
         else {
             apr_table_mergen(r->headers_out, "Content-Encoding", "gzip");
         }
+        /* Fix r->content_encoding if it was set before */
+        if (r->content_encoding) {
+            r->content_encoding = apr_table_get(r->headers_out,
+                                                "Content-Encoding");
+        }
         apr_table_unset(r->headers_out, "Content-Length");
         apr_table_unset(r->headers_out, "Content-MD5");
+        deflate_check_etag(r, "gzip");
+
+        /* For a 304 response, only change the headers */
+        if (r->status == HTTP_NOT_MODIFIED) {
+            ap_remove_output_filter(f);
+            return ap_pass_brigade(f->next, bb);
+        }
+
+        /* add immortal gzip header */
+        e = apr_bucket_immortal_create(gzip_header, sizeof gzip_header,
+                                       f->c->bucket_alloc);
+        APR_BRIGADE_INSERT_TAIL(ctx->bb, e);
 
         /* initialize deflate output buffer */
         ctx->stream.next_out = ctx->buffer;
         ctx->stream.avail_out = c->bufferSize;
     }
 
     while (!APR_BRIGADE_EMPTY(bb))
     {
         const char *data;
         apr_bucket *b;
         apr_size_t len;
 
-        /*
-         * Optimization: If we are a HEAD request and bytes_sent is not zero
-         * it means that we have passed the content-length filter once and
-         * have more data to sent. This means that the content-length filter
-         * could not determine our content-length for the response to the
-         * HEAD request anyway (the associated GET request would deliver the
-         * body in chunked encoding) and we can stop compressing.
-         */
-        if (r->header_only && r->bytes_sent) {
-            ap_remove_output_filter(f);
-            return ap_pass_brigade(f->next, bb);
-        }
-
         e = APR_BRIGADE_FIRST(bb);
 
         if (APR_BUCKET_IS_EOS(e)) {
             char *buf;
 
             ctx->stream.avail_in = 0; /* should be zero already anyway */
