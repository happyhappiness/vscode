 
         ap_log_rerror(APLOG_MARK, APLOG_TRACE2, 0, r,
                       "%s: fam %d socket created to connect to %s",
                       proxy_function, backend_addr->family, backend_name);
 
         if (conf->source_address) {
-            rv = apr_socket_bind(*newsock, conf->source_address);
+            apr_sockaddr_t *local_addr;
+            /* Make a copy since apr_socket_bind() could change
+             * conf->source_address, which we don't want.
+             */
+            local_addr = apr_pmemdup(r->pool, conf->source_address,
+                                     sizeof(apr_sockaddr_t));
+            local_addr->pool = r->pool;
+            rv = apr_socket_bind(*newsock, local_addr);
             if (rv != APR_SUCCESS) {
                 ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r, APLOGNO(00938)
                               "%s: failed to bind socket to local address",
                               proxy_function);
             }
         }
