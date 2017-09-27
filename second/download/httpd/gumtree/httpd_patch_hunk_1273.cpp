                     "winnt_accept: getsockname error on listening socket, is IPv6 available?");
         return 1;
    }
 #endif
 
     ap_log_error(APLOG_MARK, APLOG_NOTICE, 0, ap_server_conf,
-                 "Child %d: Starting thread to listen on port %d.", my_pid, lr->bind_addr->port);
+                 "Child %lu: Starting thread to listen on port %d.", my_pid, lr->bind_addr->port);
     while (!shutdown_in_progress) {
         if (!context) {
             context = mpm_get_completion_context();
             if (!context) {
                 /* Temporary resource constraint? */
                 Sleep(0);
