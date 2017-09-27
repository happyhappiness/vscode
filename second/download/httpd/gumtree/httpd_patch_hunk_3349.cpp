                 last_poll_idx++;
             }
         }
 
         if (rv != APR_SUCCESS) {
             if (!APR_STATUS_IS_EINTR(rv)) {
-                ap_log_error(APLOG_MARK, APLOG_ERR, rv, ap_server_conf,
+                ap_log_error(APLOG_MARK, APLOG_ERR, rv, ap_server_conf, APLOGNO(00194)
                              "apr_socket_accept");
                 clean_child_exit(APEXIT_CHILDFATAL);
             }
         } else {
             DosWriteQueue(workq, WORKTYPE_CONN, sizeof(worker_args_t), worker_args, 0);
             requests_this_child++;
