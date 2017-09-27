             const char *data;
             apr_size_t len;
 
             /* If we actually see the EOS, that means we screwed up! */
             if (APR_BUCKET_IS_EOS(bkt)) {
                 inflateEnd(&ctx->stream);
+                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01390)
+                              "Encountered EOS bucket in inflate filter (bug?)");
                 return APR_EGENERAL;
             }
 
             if (APR_BUCKET_IS_FLUSH(bkt)) {
                 apr_bucket *tmp_heap;
                 zRC = inflate(&(ctx->stream), Z_SYNC_FLUSH);
                 if (zRC != Z_OK) {
                     inflateEnd(&ctx->stream);
+                    ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r, APLOGNO(01391)
+                                  "Zlib error %d inflating data (%s)", zRC,
+                                  ctx->stream.msg);
                     return APR_EGENERAL;
                 }
 
                 ctx->stream.next_out = ctx->buffer;
                 len = c->bufferSize - ctx->stream.avail_out;
 
