 
             /* if we are done, leave */
             if (TRUE == finish) {
                 break;
             }
         }
-        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
+        ap_log_error(APLOG_MARK, APLOG_TRACE3, 0, r->server,
                      "proxy: FTP: end body send");
 
     }
     if (data_sock) {
         ap_flush_conn(data);
         apr_socket_close(data_sock);
