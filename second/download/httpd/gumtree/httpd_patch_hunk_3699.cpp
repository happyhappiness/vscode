                     if (ctx->stream.avail_out == 0) {
                         apr_bucket *tmp_heap;
 
                         ctx->stream.next_out = ctx->buffer;
                         len = c->bufferSize - ctx->stream.avail_out;
 
-                        ctx->inflate_total += len;
-                        if (inflate_limit && ctx->inflate_total > inflate_limit) { 
-                            inflateEnd(&ctx->stream);
-                            ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r, APLOGNO(02648)
-                                    "Inflated content length of %" APR_OFF_T_FMT
-                                    " is larger than the configured limit"
-                                    " of %" APR_OFF_T_FMT, 
-                                    ctx->inflate_total, inflate_limit);
-                            return APR_ENOSPC;
-                        }
-
-                        if (!check_ratio(r, ctx, dc)) {
-                            inflateEnd(&ctx->stream);
-                            ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r, APLOGNO(02649)
-                                    "Inflated content ratio is larger than the "
-                                    "configured limit %i by %i time(s)",
-                                    dc->ratio_limit, dc->ratio_burst);
-                            return APR_EINVAL;
-                        }
-
                         ctx->crc = crc32(ctx->crc, (const Bytef *)ctx->buffer, len);
                         tmp_heap = apr_bucket_heap_create((char *)ctx->buffer, len,
                                                           NULL, f->c->bucket_alloc);
                         APR_BRIGADE_INSERT_TAIL(ctx->proc_bb, tmp_heap);
                         ctx->stream.avail_out = c->bufferSize;
                     }
 
+                    len = ctx->stream.avail_out;
                     zRC = inflate(&ctx->stream, Z_NO_FLUSH);
 
-                    if (zRC == Z_STREAM_END) {
-                        ctx->validation_buffer = apr_pcalloc(r->pool,
-                                                             VALIDATION_SIZE);
-                        ctx->validation_buffer_length = 0;
-                        break;
-                    }
-
-                    if (zRC != Z_OK) {
+                    if (zRC != Z_OK && zRC != Z_STREAM_END) {
                         inflateEnd(&ctx->stream);
                         ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r, APLOGNO(01392)
                                       "Zlib error %d inflating data (%s)", zRC,
                                       ctx->stream.msg);
                         return APR_EGENERAL;
                     }
+
+                    ctx->inflate_total += len - ctx->stream.avail_out;
+                    if (inflate_limit && ctx->inflate_total > inflate_limit) { 
+                        inflateEnd(&ctx->stream);
+                        ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r, APLOGNO(02648)
+                                "Inflated content length of %" APR_OFF_T_FMT
+                                " is larger than the configured limit"
+                                " of %" APR_OFF_T_FMT, 
+                                ctx->inflate_total, inflate_limit);
+                        return APR_ENOSPC;
+                    }
+
+                    if (!check_ratio(r, ctx, dc)) {
+                        inflateEnd(&ctx->stream);
+                        ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r, APLOGNO(02649)
+                                "Inflated content ratio is larger than the "
+                                "configured limit %i by %i time(s)",
+                                dc->ratio_limit, dc->ratio_burst);
+                        return APR_EINVAL;
+                    }
+
+                    if (zRC == Z_STREAM_END) {
+                        ctx->validation_buffer = apr_pcalloc(r->pool,
+                                                             VALIDATION_SIZE);
+                        ctx->validation_buffer_length = 0;
+                        break;
+                    }
                 }
             }
 
             if (ctx->validation_buffer) {
                 apr_bucket *tmp_heap;
                 apr_size_t avail, valid;
