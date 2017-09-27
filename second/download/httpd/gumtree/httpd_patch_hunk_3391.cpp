                 }
                 else if ((rv == APR_FROM_OS_ERROR(WSAEINVAL)) ||
                          (rv == APR_FROM_OS_ERROR(WSAENOTSOCK))) {
                     /* We can get here when:
                      * 1) TransmitFile does not properly recycle the accept socket (typically
                      *    because the client disconnected)
-                     * 2) there is VPN or Firewall software installed with 
+                     * 2) there is VPN or Firewall software installed with
                      *    buggy WSAAccept or WSADuplicateSocket implementation
                      * 3) the dynamic address / adapter has changed
                      * Give five chances, then fall back on AcceptFilter 'none'
                      */
                     if (accf == 2)
                         apr_bucket_free(buf);
                     closesocket(context->accept_socket);
                     context->accept_socket = INVALID_SOCKET;
                     ++err_count;
                     if (err_count > MAX_ACCEPTEX_ERR_COUNT) {
-                        ap_log_error(APLOG_MARK, APLOG_ERR, rv, ap_server_conf,
-                                     "Child %d: Encountered too many AcceptEx "
+                        ap_log_error(APLOG_MARK, APLOG_ERR, rv, ap_server_conf, APLOGNO(00337)
+                                     "Child: Encountered too many AcceptEx "
                                      "faults accepting client connections. "
                                      "Possible causes: dynamic address renewal, "
-                                     "or incompatible VPN or firewall software. ",
-                                     my_pid);
-                        ap_log_error(APLOG_MARK, APLOG_NOTICE, rv, ap_server_conf,
+                                     "or incompatible VPN or firewall software. ");
+                        ap_log_error(APLOG_MARK, APLOG_NOTICE, rv, ap_server_conf, APLOGNO(00338)
                                      "winnt_mpm: falling back to "
                                      "'AcceptFilter none'.");
                         err_count = 0;
                         accf = 0;
                     }
                     continue;
