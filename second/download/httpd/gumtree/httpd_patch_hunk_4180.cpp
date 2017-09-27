                     if (APR_STATUS_IS_EINTR(rv)) {
                         continue;
                     }
 
                     /* apr_pollset_poll() will only return errors in catastrophic
                      * circumstances. Let's try exiting gracefully, for now. */
-                    ap_log_error(APLOG_MARK, APLOG_ERR, rv, ap_server_conf,
+                    ap_log_error(APLOG_MARK, APLOG_ERR, rv, ap_server_conf, APLOGNO(03137)
                                  "apr_pollset_poll: (listen)");
                     signal_threads(ST_GRACEFUL);
                 }
 
                 if (listener_may_exit) break;
 
