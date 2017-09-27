          * back end since they would in part be interpreted
          * as another request!  If nothing is sent, then
          * just send nothing.
          *
          * Prevents HTTP Response Splitting.
          */
-        if (bytes_streamed > cl_val)
-             continue;
+        if (bytes_streamed > cl_val) {
+            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
+                          "proxy: read more bytes of request body than expected "
+                          "(got %" APR_OFF_T_FMT ", expected %" APR_OFF_T_FMT ")",
+                          bytes_streamed, cl_val);
+            return HTTP_INTERNAL_SERVER_ERROR;
+        }
 
         if (header_brigade) {
             /* we never sent the header brigade, so go ahead and
              * take care of that now
              */
             bb = header_brigade;
