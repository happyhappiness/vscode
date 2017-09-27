                 ctx->crc = crc32(ctx->crc, (const Bytef *)ctx->buffer, len);
                 tmp_heap = apr_bucket_heap_create((char *)ctx->buffer, len,
                                                   NULL, f->c->bucket_alloc);
                 APR_BRIGADE_INSERT_TAIL(ctx->proc_bb, tmp_heap);
                 ctx->stream.avail_out = c->bufferSize;
 
-                /* Is the remaining 8 bytes already in the avail stream? */
-                if (ctx->stream.avail_in >= 8) {
+                {
                     unsigned long compCRC, compLen;
-                    compCRC = getLong(ctx->stream.next_in);
+                    compCRC = getLong(buf);
                     if (ctx->crc != compCRC) {
                         inflateEnd(&ctx->stream);
+                        ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r,
+                                      "Zlib: CRC error inflating data");
                         return APR_EGENERAL;
                     }
-                    ctx->stream.next_in += 4;
-                    compLen = getLong(ctx->stream.next_in);
-                    if (ctx->stream.total_out != compLen) {
+                    compLen = getLong(buf + VALIDATION_SIZE / 2);
+                    /* gzip stores original size only as 4 byte value */
+                    if ((ctx->stream.total_out & 0xFFFFFFFF) != compLen) {
                         inflateEnd(&ctx->stream);
+                        ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r,
+                                      "Zlib: Length %ld of inflated data does "
+                                      "not match expected value %ld",
+                                      ctx->stream.total_out, compLen);
                         return APR_EGENERAL;
                     }
                 }
-                else {
-                    /* FIXME: We need to grab the 8 verification bytes
-                     * from the wire! */
-                    inflateEnd(&ctx->stream);
-                    return APR_EGENERAL;
-                }
 
                 inflateEnd(&ctx->stream);
 
-                eos = apr_bucket_eos_create(f->c->bucket_alloc);
-                APR_BRIGADE_INSERT_TAIL(ctx->proc_bb, eos);
-                break;
+                ctx->done = 1;
+
+                /* Did we have trailing data behind the closing 8 bytes? */
+                if (avail > valid) {
+                    ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
+                                  "Encountered extra data after compressed data");
+                    return APR_EGENERAL;
+                }
             }
 
         }
         apr_brigade_cleanup(ctx->bb);
     }
 
     /* If we are about to return nothing for a 'blocking' read and we have
      * some data in our zlib buffer, flush it out so we can return something.
      */
     if (block == APR_BLOCK_READ &&
-        APR_BRIGADE_EMPTY(ctx->proc_bb) &&
-        ctx->stream.avail_out < c->bufferSize) {
+            APR_BRIGADE_EMPTY(ctx->proc_bb) &&
+            ctx->stream.avail_out < c->bufferSize) {
         apr_bucket *tmp_heap;
         apr_size_t len;
         ctx->stream.next_out = ctx->buffer;
         len = c->bufferSize - ctx->stream.avail_out;
 
         ctx->crc = crc32(ctx->crc, (const Bytef *)ctx->buffer, len);
