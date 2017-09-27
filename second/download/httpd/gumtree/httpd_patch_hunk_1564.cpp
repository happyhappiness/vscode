         }
 
         /* pass through zlib inflate. */
         ctx->stream.next_in = (unsigned char *)data;
         ctx->stream.avail_in = len;
 
+        if (ctx->validation_buffer) {
+            if (ctx->validation_buffer_length < VALIDATION_SIZE) {
+                apr_size_t copy_size;
+
+                copy_size = VALIDATION_SIZE - ctx->validation_buffer_length;
+                if (copy_size > ctx->stream.avail_in)
+                    copy_size = ctx->stream.avail_in;
+                memcpy(ctx->validation_buffer + ctx->validation_buffer_length,
+                       ctx->stream.next_in, copy_size);
+                /* Saved copy_size bytes */
+                ctx->stream.avail_in -= copy_size;
+                ctx->validation_buffer_length += copy_size;
+            }
+            if (ctx->stream.avail_in) {
+                ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
+                              "Zlib: %d bytes of garbage at the end of "
+                              "compressed stream.", ctx->stream.avail_in);
+                /*
+                 * There is nothing worth consuming for zlib left, because it is
+                 * either garbage data or the data has been copied to the
+                 * validation buffer (processing validation data is no business
+                 * for zlib). So set ctx->stream.avail_in to zero to indicate
+                 * this to the following while loop.
+                 */
+                ctx->stream.avail_in = 0;
+            }
+        }
+
         zRC = Z_OK;
 
         while (ctx->stream.avail_in != 0) {
             if (ctx->stream.avail_out == 0) {
-                apr_bucket *tmp_heap;
+
                 ctx->stream.next_out = ctx->buffer;
                 len = c->bufferSize - ctx->stream.avail_out;
 
                 ctx->crc = crc32(ctx->crc, (const Bytef *)ctx->buffer, len);
-                tmp_heap = apr_bucket_heap_create((char *)ctx->buffer, len,
-                                                  NULL, f->c->bucket_alloc);
-                APR_BRIGADE_INSERT_TAIL(ctx->proc_bb, tmp_heap);
+                b = apr_bucket_heap_create((char *)ctx->buffer, len,
+                                           NULL, f->c->bucket_alloc);
+                APR_BRIGADE_INSERT_TAIL(ctx->bb, b);
                 ctx->stream.avail_out = c->bufferSize;
+                /* Send what we have right now to the next filter. */
+                rv = ap_pass_brigade(f->next, ctx->bb);
+                if (rv != APR_SUCCESS) {
+                    return rv;
+                }
             }
 
             zRC = inflate(&ctx->stream, Z_NO_FLUSH);
 
             if (zRC == Z_STREAM_END) {
+                /*
+                 * We have inflated all data. Now try to capture the
+                 * validation bytes. We may not have them all available
+                 * right now, but capture what is there.
+                 */
+                ctx->validation_buffer = apr_pcalloc(f->r->pool,
+                                                     VALIDATION_SIZE);
+                if (ctx->stream.avail_in > VALIDATION_SIZE) {
+                    ctx->validation_buffer_length = VALIDATION_SIZE;
+                    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
+                                  "Zlib: %d bytes of garbage at the end of "
+                                  "compressed stream.",
+                                  ctx->stream.avail_in - VALIDATION_SIZE);
+                } else if (ctx->stream.avail_in > 0) {
+                           ctx->validation_buffer_length = ctx->stream.avail_in;
+                }
+                if (ctx->validation_buffer_length)
+                    memcpy(ctx->validation_buffer, ctx->stream.next_in,
+                           ctx->validation_buffer_length);
                 break;
             }
 
             if (zRC != Z_OK) {
-                    inflateEnd(&ctx->stream);
-                    return APR_EGENERAL;
-            }
-        }
-        if (zRC == Z_STREAM_END) {
-            apr_bucket *tmp_heap, *eos;
-
-            ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
-                          "Zlib: Inflated %ld to %ld : URL %s",
-                          ctx->stream.total_in, ctx->stream.total_out,
-                          r->uri);
-
-            len = c->bufferSize - ctx->stream.avail_out;
-
-            ctx->crc = crc32(ctx->crc, (const Bytef *)ctx->buffer, len);
-            tmp_heap = apr_bucket_heap_create((char *)ctx->buffer, len,
-                                              NULL, f->c->bucket_alloc);
-            APR_BRIGADE_INSERT_TAIL(ctx->proc_bb, tmp_heap);
-            ctx->stream.avail_out = c->bufferSize;
-
-            /* Is the remaining 8 bytes already in the avail stream? */
-            if (ctx->stream.avail_in >= 8) {
-                unsigned long compCRC, compLen;
-                compCRC = getLong(ctx->stream.next_in);
-                if (ctx->crc != compCRC) {
-                    inflateEnd(&ctx->stream);
-                    return APR_EGENERAL;
-                }
-                ctx->stream.next_in += 4;
-                compLen = getLong(ctx->stream.next_in);
-                if (ctx->stream.total_out != compLen) {
-                    inflateEnd(&ctx->stream);
-                    return APR_EGENERAL;
-                }
-            }
-            else {
-                /* FIXME: We need to grab the 8 verification bytes
-                 * from the wire! */
-                inflateEnd(&ctx->stream);
                 return APR_EGENERAL;
             }
-
-            inflateEnd(&ctx->stream);
-
-            eos = apr_bucket_eos_create(f->c->bucket_alloc);
-            APR_BRIGADE_INSERT_TAIL(ctx->proc_bb, eos);
-            break;
         }
 
+        apr_bucket_delete(e);
     }
 
-    rv = ap_pass_brigade(f->next, ctx->proc_bb);
-    apr_brigade_cleanup(ctx->proc_bb);
-    return rv ;
+    apr_brigade_cleanup(bb);
+    return APR_SUCCESS;
 }
 
+#define PROTO_FLAGS AP_FILTER_PROTO_CHANGE|AP_FILTER_PROTO_CHANGE_LENGTH
 static void register_hooks(apr_pool_t *p)
 {
     ap_register_output_filter(deflateFilterName, deflate_out_filter, NULL,
                               AP_FTYPE_CONTENT_SET);
     ap_register_output_filter("INFLATE", inflate_out_filter, NULL,
                               AP_FTYPE_RESOURCE-1);
