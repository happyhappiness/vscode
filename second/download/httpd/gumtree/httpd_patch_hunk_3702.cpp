                 if (ctx->stream.avail_in > VALIDATION_SIZE) {
                     ctx->validation_buffer_length = VALIDATION_SIZE;
                     ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(01408)
                                   "Zlib: %d bytes of garbage at the end of "
                                   "compressed stream.",
                                   ctx->stream.avail_in - VALIDATION_SIZE);
-                } else if (ctx->stream.avail_in > 0) {
-                           ctx->validation_buffer_length = ctx->stream.avail_in;
+                }
+                else if (ctx->stream.avail_in > 0) {
+                    ctx->validation_buffer_length = ctx->stream.avail_in;
                 }
                 if (ctx->validation_buffer_length)
                     memcpy(ctx->validation_buffer, ctx->stream.next_in,
                            ctx->validation_buffer_length);
                 break;
             }
-
-            if (zRC != Z_OK) {
-                ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r, APLOGNO(01409)
-                              "Zlib error %d inflating data (%s)", zRC,
-                              ctx->stream.msg);
-                return APR_EGENERAL;
-            }
         }
 
         apr_bucket_delete(e);
     }
 
     apr_brigade_cleanup(bb);
