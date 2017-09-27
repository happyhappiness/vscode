     i = 0;
     while (i < buflen) {
         apr_size_t j = strlen(buffer + i);
         apr_status_t status;
         status  = apr_socket_send(sock, buffer+i, &j);
         if (status != APR_SUCCESS) {
-            ap_log_error(APLOG_MARK, APLOG_CRIT, status, srv,
+            ap_log_error(APLOG_MARK, APLOG_CRIT, status, srv, APLOGNO(01497)
                          "write: rfc1413: error sending request");
             return status;
         }
         else if (j > 0) {
             i+=j;
         }
