     } else {
         status = ap_get_brigade(r->input_filters, input_brigade,
                                 AP_MODE_READBYTES, APR_BLOCK_READ,
                                 AJP13_MAX_SEND_BODY_SZ);
 
         if (status != APR_SUCCESS) {
+            /* We had a failure: Close connection to backend */
+            conn->close++;
             ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                          "proxy: ap_get_brigade failed");
             apr_brigade_destroy(input_brigade);
             return HTTP_INTERNAL_SERVER_ERROR;
         }
 
