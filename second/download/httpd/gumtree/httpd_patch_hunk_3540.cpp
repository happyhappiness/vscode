 
     if ((rv = apr_socket_create(&c->aprsock, destsa->family,
                 SOCK_STREAM, 0, c->ctx)) != APR_SUCCESS) {
     apr_err("socket", rv);
     }
 
+    if ((rv = apr_socket_bind(c->aprsock, mysa)) != APR_SUCCESS) {
+        apr_err("bind", rv);
+    }
+
     c->pollfd.desc_type = APR_POLL_SOCKET;
     c->pollfd.desc.s = c->aprsock;
     c->pollfd.reqevents = 0;
     c->pollfd.client_data = c;
 
     if ((rv = apr_socket_opt_set(c->aprsock, APR_SO_NONBLOCK, 1))
          != APR_SUCCESS) {
         apr_err("socket nonblock", rv);
     }
 
     if (windowsize != 0) {
-        rv = apr_socket_opt_set(c->aprsock, APR_SO_SNDBUF, 
+        rv = apr_socket_opt_set(c->aprsock, APR_SO_SNDBUF,
                                 windowsize);
         if (rv != APR_SUCCESS && rv != APR_ENOTIMPL) {
             apr_err("socket send buffer", rv);
         }
-        rv = apr_socket_opt_set(c->aprsock, APR_SO_RCVBUF, 
+        rv = apr_socket_opt_set(c->aprsock, APR_SO_RCVBUF,
                                 windowsize);
         if (rv != APR_SUCCESS && rv != APR_ENOTIMPL) {
             apr_err("socket receive buffer", rv);
         }
     }
 
