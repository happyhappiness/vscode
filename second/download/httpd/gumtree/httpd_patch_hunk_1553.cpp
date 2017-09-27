                     ctx->is_sb = 0;
                 }
             }
         }
         else {
             ctx->noop = 1;
-            if (dc->debug >= DBGLVL_GORY) {
+            if (mime_type && dc->debug >= DBGLVL_GORY) {
                 ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, f->r,
                               "mime type is %s; no translation selected",
                               mime_type);
             }
         }
     }
