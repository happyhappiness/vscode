                     return rv;
                 }
             }
 
             zRC = inflate(&ctx->stream, Z_NO_FLUSH);
 
+            if (zRC != Z_OK && zRC != Z_STREAM_END) {
+                ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r, APLOGNO(01409)
+                              "Zlib error %d inflating data (%s)", zRC,
+                              ctx->stream.msg);
+                return APR_EGENERAL;
+            }
+
+            if (!check_ratio(r, ctx, dc)) {
+                ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r, APLOGNO(02650)
+                              "Inflated content ratio is larger than the "
+                              "configured limit %i by %i time(s)",
+                              dc->ratio_limit, dc->ratio_burst);
+                return APR_EINVAL;
+            }
+
             if (zRC == Z_STREAM_END) {
                 /*
                  * We have inflated all data. Now try to capture the
                  * validation bytes. We may not have them all available
                  * right now, but capture what is there.
                  */
