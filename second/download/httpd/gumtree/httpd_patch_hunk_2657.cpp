             putLong((unsigned char *)&buf[0], ctx->crc);
             putLong((unsigned char *)&buf[4], ctx->stream.total_in);
 
             b = apr_bucket_pool_create(buf, VALIDATION_SIZE, r->pool,
                                        f->c->bucket_alloc);
             APR_BRIGADE_INSERT_TAIL(ctx->bb, b);
-            ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
+            ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(01384)
                           "Zlib: Compressed %ld to %ld : URL %s",
                           ctx->stream.total_in, ctx->stream.total_out, r->uri);
 
             /* leave notes for logging */
             if (c->note_input_name) {
                 apr_table_setn(r->notes, c->note_input_name,
