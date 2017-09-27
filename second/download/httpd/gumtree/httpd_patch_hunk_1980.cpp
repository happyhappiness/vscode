 
     while (!APR_BRIGADE_EMPTY(bb))
     {
         const char *data;
         apr_bucket *b;
         apr_size_t len;
-        int done = 0;
 
         e = APR_BRIGADE_FIRST(bb);
 
         if (APR_BUCKET_IS_EOS(e)) {
             char *buf;
-            unsigned int deflate_len;
 
             ctx->stream.avail_in = 0; /* should be zero already anyway */
-            for (;;) {
-                deflate_len = c->bufferSize - ctx->stream.avail_out;
+            /* flush the remaining data from the zlib buffers */
+            flush_libz_buffer(ctx, c, f->c->bucket_alloc, deflate, Z_FINISH,
+                              NO_UPDATE_CRC);
 
-                if (deflate_len != 0) {
-                    b = apr_bucket_heap_create((char *)ctx->buffer,
-                                               deflate_len, NULL,
-                                               f->c->bucket_alloc);
-                    APR_BRIGADE_INSERT_TAIL(ctx->bb, b);
-                    ctx->stream.next_out = ctx->buffer;
-                    ctx->stream.avail_out = c->bufferSize;
-                }
-
-                if (done) {
-                    break;
-                }
-
-                zRC = deflate(&ctx->stream, Z_FINISH);
-
-                if (deflate_len == 0 && zRC == Z_BUF_ERROR) {
-                    zRC = Z_OK;
-                }
-
-                done = (ctx->stream.avail_out != 0 || zRC == Z_STREAM_END);
-
-                if (zRC != Z_OK && zRC != Z_STREAM_END) {
-                    break;
-                }
-            }
-
-            buf = apr_palloc(r->pool, 8);
+            buf = apr_palloc(r->pool, VALIDATION_SIZE);
             putLong((unsigned char *)&buf[0], ctx->crc);
             putLong((unsigned char *)&buf[4], ctx->stream.total_in);
 
-            b = apr_bucket_pool_create(buf, 8, r->pool, f->c->bucket_alloc);
+            b = apr_bucket_pool_create(buf, VALIDATION_SIZE, r->pool,
+                                       f->c->bucket_alloc);
             APR_BRIGADE_INSERT_TAIL(ctx->bb, b);
             ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                           "Zlib: Compressed %ld to %ld : URL %s",
                           ctx->stream.total_in, ctx->stream.total_out, r->uri);
 
             /* leave notes for logging */
