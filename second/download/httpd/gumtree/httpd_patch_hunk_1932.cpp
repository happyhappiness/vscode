         apr_pool_create(&c->ctx, cntxt);
 
     if ((rv = apr_socket_create(&c->aprsock, destsa->family,
                 SOCK_STREAM, 0, c->ctx)) != APR_SUCCESS) {
     apr_err("socket", rv);
     }
+
+    c->pollfd.desc_type = APR_POLL_SOCKET;
+    c->pollfd.desc.s = c->aprsock;
+    c->pollfd.reqevents = 0;
+    c->pollfd.client_data = c;
+
     if ((rv = apr_socket_opt_set(c->aprsock, APR_SO_NONBLOCK, 1))
          != APR_SUCCESS) {
         apr_err("socket nonblock", rv);
     }
 
     if (windowsize != 0) {
