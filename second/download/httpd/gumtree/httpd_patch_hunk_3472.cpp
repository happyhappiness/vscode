     if (!lp) {
         lp = ap_listeners;
     }
 
     rv = apr_socket_create(&sock, lp->bind_addr->family, SOCK_STREAM, 0, p);
     if (rv != APR_SUCCESS) {
-        ap_log_error(APLOG_MARK, APLOG_WARNING, rv, ap_server_conf,
+        ap_log_error(APLOG_MARK, APLOG_WARNING, rv, ap_server_conf, APLOGNO(00054)
                      "get socket to connect to listener");
         apr_pool_destroy(p);
         return rv;
     }
 
     /* on some platforms (e.g., FreeBSD), the kernel won't accept many
