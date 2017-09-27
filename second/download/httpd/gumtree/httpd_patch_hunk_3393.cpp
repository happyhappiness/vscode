                 if (rv == WAIT_OBJECT_0) {
                     if ((context->accept_socket != INVALID_SOCKET) &&
                         !GetOverlappedResult((HANDLE)context->accept_socket,
                                              &context->overlapped,
                                              &BytesRead, FALSE)) {
                         ap_log_error(APLOG_MARK, APLOG_WARNING,
-                                     apr_get_os_error(), ap_server_conf,
+                                     apr_get_os_error(), ap_server_conf, APLOGNO(00341)
                              "winnt_accept: Asynchronous AcceptEx failed.");
                         closesocket(context->accept_socket);
                         context->accept_socket = INVALID_SOCKET;
                     }
                 }
                 else {
