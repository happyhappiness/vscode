                 }
             }
 
             zRC = deflate(&(ctx->stream), Z_NO_FLUSH);
 
             if (zRC != Z_OK) {
+                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01386)
+                              "Zlib error %d deflating data (%s)", zRC,
+                              ctx->stream.msg);
                 return APR_EGENERAL;
             }
         }
 
         apr_bucket_delete(e);
     }
