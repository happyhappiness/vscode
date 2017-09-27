      * that the can and have done so unless they they remove
      * their decoding from the headers_in T-E list.
      * XXX: Make this extensible, but in doing so, presume the
      * encoding has been done by the extensions' handler, and
      * do not modify add_te_chunked's logic
      */
-    if (old_te_val && strcmp(old_te_val, "chunked") != 0) {
+    if (old_te_val && strcasecmp(old_te_val, "chunked") != 0) {
         ap_log_error(APLOG_MARK, APLOG_ERR, 0, r->server,
                      "proxy: %s Transfer-Encoding is not supported",
                      old_te_val);
         return HTTP_INTERNAL_SERVER_ERROR;
     }
 
