 
     if ((rv = apr_sockaddr_info_get(&localsa, conn->local_ip, APR_UNSPEC,
                               0, /* ephemeral port */
                               0, conn->pool)) != APR_SUCCESS) {
         /* This should not fail since we have a numeric address string
          * as the host. */
-        ap_log_error(APLOG_MARK, APLOG_CRIT, rv, srv,
+        ap_log_error(APLOG_MARK, APLOG_CRIT, rv, srv, APLOGNO(01492)
                      "rfc1413: apr_sockaddr_info_get(%s) failed",
                      conn->local_ip);
         return rv;
     }
 
-    if ((rv = apr_sockaddr_info_get(&destsa, conn->remote_ip,
+    if ((rv = apr_sockaddr_info_get(&destsa, conn->client_ip,
                               localsa->family, /* has to match */
                               RFC1413_PORT, 0, conn->pool)) != APR_SUCCESS) {
         /* This should not fail since we have a numeric address string
          * as the host. */
-        ap_log_error(APLOG_MARK, APLOG_CRIT, rv, srv,
+        ap_log_error(APLOG_MARK, APLOG_CRIT, rv, srv, APLOGNO(01493)
                      "rfc1413: apr_sockaddr_info_get(%s) failed",
-                     conn->remote_ip);
+                     conn->client_ip);
         return rv;
     }
 
     if ((rv = apr_socket_create(newsock,
                                 localsa->family, /* has to match */
                                 SOCK_STREAM, 0, conn->pool)) != APR_SUCCESS) {
-        ap_log_error(APLOG_MARK, APLOG_CRIT, rv, srv,
+        ap_log_error(APLOG_MARK, APLOG_CRIT, rv, srv, APLOGNO(01494)
                      "rfc1413: error creating query socket");
         return rv;
     }
 
     if ((rv = apr_socket_timeout_set(*newsock, timeout)) != APR_SUCCESS) {
-        ap_log_error(APLOG_MARK, APLOG_CRIT, rv, srv,
+        ap_log_error(APLOG_MARK, APLOG_CRIT, rv, srv, APLOGNO(01495)
                      "rfc1413: error setting query socket timeout");
         apr_socket_close(*newsock);
         return rv;
     }
 
 /*
