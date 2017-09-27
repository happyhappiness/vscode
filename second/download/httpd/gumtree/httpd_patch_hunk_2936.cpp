         r->headers_out = save_table;
     } else {
         r->headers_out = NULL;
         num_headers = 0;
     }
 
-    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
+    ap_log_rerror(APLOG_MARK, APLOG_TRACE4, 0, r,
            "ajp_unmarshal_response: Number of headers is = %d",
            num_headers);
 
     for(i = 0 ; i < (int) num_headers ; i++) {
         apr_uint16_t name;
         const char *stringname;
