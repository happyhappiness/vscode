      * we're in better shape.
      */
     if (!ctx) {
         char *token;
         const char *encoding;
 
+        if (have_ssl_compression(r)) {
+            ap_log_rerror(APLOG_MARK, APLOG_TRACE1, 0, r,
+                          "Compression enabled at SSL level; not compressing "
+                          "at HTTP level.");
+            ap_remove_output_filter(f);
+            return ap_pass_brigade(f->next, bb);
+        }
+
         /* We have checked above that bb is not empty */
         e = APR_BRIGADE_LAST(bb);
         if (APR_BUCKET_IS_EOS(e)) {
             /*
              * If we already know the size of the response, we can skip
              * compression on responses smaller than the compression overhead.
