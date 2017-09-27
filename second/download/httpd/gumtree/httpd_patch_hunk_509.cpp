          * hence the debug level
          */
         ap_log_cerror(APLOG_MARK, APLOG_DEBUG, rv, c,
                       "apr_socket_opt_set(APR_TCP_NODELAY)");
     }
 #endif
+
+    /* The core filter requires the timeout mode to be set, which
+     * incidentally sets the socket to be nonblocking.  If this
+     * is not initialized correctly, Linux - for example - will
+     * be initially blocking, while Solaris will be non blocking
+     * and any initial read will fail.
+     */
+    rv = apr_socket_timeout_set(csd, c->base_server->timeout);
+    if (rv != APR_SUCCESS) {
+        /* expected cause is that the client disconnected already */
+        ap_log_cerror(APLOG_MARK, APLOG_DEBUG, rv, c,
+                     "apr_socket_timeout_set");
+    }
+
     net->c = c;
     net->in_ctx = NULL;
     net->out_ctx = NULL;
     net->client_socket = csd;
 
     ap_set_module_config(net->c->conn_config, &core_module, csd);
