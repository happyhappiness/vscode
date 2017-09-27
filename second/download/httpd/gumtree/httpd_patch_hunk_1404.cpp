             }
         }
 
         do {
             clen = sizeof(sa_client);
             csd = accept(nsd, (struct sockaddr *) &sa_client, &clen);
-        } while (csd < 0 && APR_STATUS_IS_EINTR(apr_get_netos_error()));
+        } while (csd == INVALID_SOCKET && APR_STATUS_IS_EINTR(apr_get_netos_error()));
 
-        if (csd < 0) {
+        if (csd == INVALID_SOCKET) {
             if (APR_STATUS_IS_ECONNABORTED(apr_get_netos_error())) {
                 ap_log_error(APLOG_MARK, APLOG_ERR, apr_get_netos_error(), ap_server_conf,
                             "accept: (client socket)");
             }
         }
         else {
