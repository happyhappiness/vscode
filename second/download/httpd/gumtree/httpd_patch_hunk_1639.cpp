         /* The AJP protocol does not want body data yet */
         ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                      "proxy: request is chunked");
     } else {
         status = ap_get_brigade(r->input_filters, input_brigade,
                                 AP_MODE_READBYTES, APR_BLOCK_READ,
-                                AJP13_MAX_SEND_BODY_SZ);
+                                maxsize - AJP_HEADER_SZ);
 
         if (status != APR_SUCCESS) {
             /* We had a failure: Close connection to backend */
             conn->close++;
             ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                          "proxy: ap_get_brigade failed");
