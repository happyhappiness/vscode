                 if (error_fmt) {
                     ap_log_rerror(APLOG_MARK, loglevel,
                                   0, r, error_fmt, tag_val, r->filename);
                     CREATE_ERROR_BUCKET(ctx, tmp_buck, head_ptr, 
                                         *inserted_head);
                 }
-
-                /* destroy the sub request */
-                if (rr != NULL) {
-                    ap_destroy_sub_req(rr);
-                }
+                
+                /* Do *not* destroy the subrequest here; it may have allocated
+                 * variables in this r->subprocess_env in the subrequest's
+                 * r->pool, so that pool must survive as long as this request.
+                 * Yes, this is a memory leak. */
             }
             else {
                 ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                             "unknown parameter \"%s\" to tag include in %s",
                             tag, r->filename);
                 CREATE_ERROR_BUCKET(ctx, tmp_buck, head_ptr, *inserted_head);
