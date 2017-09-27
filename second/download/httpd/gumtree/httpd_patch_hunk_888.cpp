 
     ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, ap_server_conf,
                  "Child %d: retrieved %d listeners from parent", my_pid, lcnt);
 }
 
 
-static int send_listeners_to_child(apr_pool_t *p, DWORD dwProcessId, 
+static int send_listeners_to_child(apr_pool_t *p, DWORD dwProcessId,
                                    apr_file_t *child_in)
 {
     apr_status_t rv;
     int lcnt = 0;
     ap_listen_rec *lr;
     LPWSAPROTOCOL_INFO  lpWSAProtocolInfo;
-    DWORD BytesWritten;
+    apr_size_t BytesWritten;
 
-    /* Run the chain of open sockets. For each socket, duplicate it 
-     * for the target process then send the WSAPROTOCOL_INFO 
+    /* Run the chain of open sockets. For each socket, duplicate it
+     * for the target process then send the WSAPROTOCOL_INFO
      * (returned by dup socket) to the child.
      */
     for (lr = ap_listeners; lr; lr = lr->next, ++lcnt) {
-        int nsd;
+        apr_os_sock_t nsd;
         lpWSAProtocolInfo = apr_pcalloc(p, sizeof(WSAPROTOCOL_INFO));
         apr_os_sock_get(&nsd,lr->sd);
         ap_log_error(APLOG_MARK, APLOG_INFO, APR_SUCCESS, ap_server_conf,
-                     "Parent: Duplicating socket %d and sending it to child process %d", 
+                     "Parent: Duplicating socket %d and sending it to child process %d",
                      nsd, dwProcessId);
         if (WSADuplicateSocket(nsd, dwProcessId,
                                lpWSAProtocolInfo) == SOCKET_ERROR) {
             ap_log_error(APLOG_MARK, APLOG_CRIT, apr_get_netos_error(), ap_server_conf,
                          "Parent: WSADuplicateSocket failed for socket %d. Check the FAQ.", lr->sd );
             return -1;
         }
 
-        if ((rv = apr_file_write_full(child_in, lpWSAProtocolInfo, 
+        if ((rv = apr_file_write_full(child_in, lpWSAProtocolInfo,
                                       sizeof(WSAPROTOCOL_INFO), &BytesWritten))
                 != APR_SUCCESS) {
             ap_log_error(APLOG_MARK, APLOG_CRIT, rv, ap_server_conf,
                          "Parent: Unable to write duplicated socket %d to the child.", lr->sd );
             return -1;
         }
