      * data. The sockets have been set to listening in the parent process.
      *
      * *** We now do this was back in winnt_rewrite_args
      * pipe = GetStdHandle(STD_INPUT_HANDLE);
      */
     for (lr = ap_listeners; lr; lr = lr->next, ++lcnt) {
+        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, ap_server_conf, APLOGNO(00403)
+                     "Child: Waiting for data for listening socket %pI",
+                     lr->bind_addr);
         if (!ReadFile(pipe, &WSAProtocolInfo, sizeof(WSAPROTOCOL_INFO),
                       &BytesRead, (LPOVERLAPPED) NULL)) {
-            ap_log_error(APLOG_MARK, APLOG_CRIT, apr_get_os_error(), ap_server_conf,
-                         "setup_inherited_listeners: Unable to read socket data from parent");
+            ap_log_error(APLOG_MARK, APLOG_CRIT, apr_get_os_error(), ap_server_conf, APLOGNO(00404)
+                         "Child: Unable to read socket data from parent");
             exit(APEXIT_CHILDINIT);
         }
 
         nsd = WSASocket(FROM_PROTOCOL_INFO, FROM_PROTOCOL_INFO, FROM_PROTOCOL_INFO,
                         &WSAProtocolInfo, 0, 0);
         if (nsd == INVALID_SOCKET) {
-            ap_log_error(APLOG_MARK, APLOG_CRIT, apr_get_netos_error(), ap_server_conf,
-                         "Child %d: setup_inherited_listeners(), WSASocket failed to open the inherited socket.", my_pid);
+            ap_log_error(APLOG_MARK, APLOG_CRIT, apr_get_netos_error(), ap_server_conf, APLOGNO(00405)
+                         "Child: WSASocket failed to open the inherited socket");
             exit(APEXIT_CHILDINIT);
         }
 
         if (!SetHandleInformation((HANDLE)nsd, HANDLE_FLAG_INHERIT, 0)) {
-            ap_log_error(APLOG_MARK, APLOG_ERR, apr_get_os_error(), ap_server_conf,
-                         "set_listeners_noninheritable: SetHandleInformation failed.");
+            ap_log_error(APLOG_MARK, APLOG_ERR, apr_get_os_error(), ap_server_conf, APLOGNO(00406)
+                         "Child: SetHandleInformation failed");
         }
         apr_os_sock_put(&lr->sd, &nsd, s->process->pool);
     }
 
-    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, ap_server_conf,
-                 "Child %d: retrieved %d listeners from parent", my_pid, lcnt);
+    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, ap_server_conf, APLOGNO(00407)
+                 "Child: retrieved %d listeners from parent", lcnt);
 }
 
 
 static int send_listeners_to_child(apr_pool_t *p, DWORD dwProcessId,
                                    apr_file_t *child_in)
 {
