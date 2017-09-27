                             " is larger than the configured limit"
                             " of %" APR_OFF_T_FMT, 
                             ctx->inflate_total, inflate_limit);
                     return APR_ENOSPC;
                 }
 
+                if (!check_ratio(r, ctx, dc)) {
+                    inflateEnd(&ctx->stream);
+                    ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r, APLOGNO(02805)
+                            "Inflated content ratio is larger than the "
+                            "configured limit %i by %i time(s)",
+                            dc->ratio_limit, dc->ratio_burst);
+                    return APR_EINVAL;
+                }
+
                 ctx->crc = crc32(ctx->crc, (const Bytef *)ctx->buffer, len);
                 tmp_b = apr_bucket_heap_create((char *)ctx->buffer, len,
                                                 NULL, f->c->bucket_alloc);
                 APR_BRIGADE_INSERT_TAIL(ctx->proc_bb, tmp_b);
                 ctx->stream.avail_out = c->bufferSize;
 
