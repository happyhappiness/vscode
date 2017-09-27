     backconn = ap_run_create_connection(c->pool, r->server, sock,
                                         c->id, c->sbh, c->bucket_alloc);
     if (!backconn) {
         /* peer reset */
         ap_log_rerror(APLOG_MARK, APLOG_INFO, 0, r, APLOGNO(01021)
                       "an error occurred creating a new connection "
-                      "to %pI (%s)", connect_addr, connectname);
+                      "to %pI (%s)", nexthop, connectname);
         apr_socket_close(sock);
         return HTTP_INTERNAL_SERVER_ERROR;
     }
     ap_proxy_ssl_disable(backconn);
     rc = ap_run_pre_connection(backconn, sock);
     if (rc != OK && rc != DONE) {
