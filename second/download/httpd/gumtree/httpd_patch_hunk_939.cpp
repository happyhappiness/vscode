     ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, ap_server_conf,
                  "Parent: Sent the scoreboard to the child");
     return 0;
 }
 
 
-/* 
+/*
  * get_listeners_from_parent()
  * The listen sockets are opened in the parent. This function, which runs
  * exclusively in the child process, receives them from the parent and
  * makes them availeble in the child.
  */
 void get_listeners_from_parent(server_rec *s)
 {
     WSAPROTOCOL_INFO WSAProtocolInfo;
+    HANDLE pipe;
     ap_listen_rec *lr;
     DWORD BytesRead;
     int lcnt = 0;
     SOCKET nsd;
 
     /* Set up a default listener if necessary */
