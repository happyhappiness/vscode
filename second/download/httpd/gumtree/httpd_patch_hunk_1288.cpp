             exit(APEXIT_CHILDINIT);
         }
         nsd = WSASocket(FROM_PROTOCOL_INFO, FROM_PROTOCOL_INFO, FROM_PROTOCOL_INFO,
                         &WSAProtocolInfo, 0, 0);
         if (nsd == INVALID_SOCKET) {
             ap_log_error(APLOG_MARK, APLOG_CRIT, apr_get_netos_error(), ap_server_conf,
-                         "Child %d: setup_inherited_listeners(), WSASocket failed to open the inherited socket.", my_pid);
+                         "Child %lu: setup_inherited_listeners(), WSASocket failed to open the inherited socket.", my_pid);
             exit(APEXIT_CHILDINIT);
         }
 
         if (osver.dwPlatformId == VER_PLATFORM_WIN32_WINDOWS) {
             HANDLE hProcess = GetCurrentProcess();
             HANDLE dup;
