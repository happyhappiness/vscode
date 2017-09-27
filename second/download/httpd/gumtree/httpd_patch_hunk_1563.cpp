 
         zRC = Z_OK;
 
         while (ctx->stream.avail_in != 0) {
             if (ctx->stream.avail_out == 0) {
 
-                if (!check_ratio(r, ctx, dc)) {
-                    ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r, 
-                            "Inflated content ratio is larger than the "
-                            "configured limit %i by %i time(s)",
-                            dc->ratio_limit, dc->ratio_burst);
-                    return APR_EINVAL;
-                }
-
                 ctx->stream.next_out = ctx->buffer;
                 len = c->bufferSize - ctx->stream.avail_out;
 
                 ctx->crc = crc32(ctx->crc, (const Bytef *)ctx->buffer, len);
                 b = apr_bucket_heap_create((char *)ctx->buffer, len,
                                            NULL, f->c->bucket_alloc);
