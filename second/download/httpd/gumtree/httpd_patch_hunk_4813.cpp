                      * and we still want to keep going
                      */
                     if (rc != APR_SUCCESS && !APR_STATUS_IS_NOTFOUND(rc)) {
                         ap_log_error(APLOG_MARK, APLOG_ERR, rc, ap_server_conf,
                                      "pollset remove failed");
                         apr_thread_mutex_unlock(timeout_mutex);
-                        start_lingering_close(cs);
+                        start_lingering_close_nonblocking(cs);
                         break;
                     }
 
                     apr_thread_mutex_unlock(timeout_mutex);
                     TO_QUEUE_ELEM_INIT(cs);
                     /* If we didn't get a worker immediately for a keep-alive
                      * request, we close the connection, so that the client can
                      * re-connect to a different process.
                      */
                     if (!have_idle_worker) {
-                        start_lingering_close(cs);
+                        start_lingering_close_nonblocking(cs);
                         break;
                     }
                     rc = push2worker(out_pfd, event_pollset);
                     if (rc != APR_SUCCESS) {
                         ap_log_error(APLOG_MARK, APLOG_CRIT, rc,
                                      ap_server_conf, "push2worker failed");
