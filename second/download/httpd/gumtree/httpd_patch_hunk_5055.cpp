                     return APR_EGENERAL;
                 }
 
                 inflateEnd(&ctx->stream);
 
                 ctx->done = 1;
+
+                /* Did we have trailing data behind the closing 8 bytes? */
+                if (avail > 8) {
+                    ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(02485)
+                                  "Encountered extra data after compressed data");
+                    return APR_EGENERAL;
+                }
             }
 
         }
         apr_brigade_cleanup(ctx->bb);
     }
 
