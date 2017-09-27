     status = apr_socket_accept(&csd, lr->sd, ptrans);
     if (status == APR_SUCCESS) {
         *accepted = csd;
 #ifdef _OSD_POSIX
         apr_os_sock_get(&sockdes, csd);
         if (sockdes >= FD_SETSIZE) {
-            ap_log_error(APLOG_MARK, APLOG_WARNING, 0, NULL,
+            ap_log_error(APLOG_MARK, APLOG_WARNING, 0, ap_server_conf, APLOGNO(02176)
                          "new file descriptor %d is too large; you probably need "
                          "to rebuild Apache with a larger FD_SETSIZE "
                          "(currently %d)",
                          sockdes, FD_SETSIZE);
             apr_socket_close(csd);
             return APR_EINTR;
