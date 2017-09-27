                                                 proxyport, server_portstr,
                                                 sizeof(server_portstr))) != OK)
             break;
 
         /* Step Two: Make the Connection */
         if (ap_proxy_connect_backend(proxy_function, backend, worker, r->server)) {
-            ap_log_error(APLOG_MARK, APLOG_ERR, 0, r->server,
-                         "proxy: HTTP: failed to make connection to backend: %s",
-                         backend->hostname);
+            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01114)
+                          "HTTP: failed to make connection to backend: %s",
+                          backend->hostname);
             status = HTTP_SERVICE_UNAVAILABLE;
             break;
         }
 
         /* Step Three: Create conn_rec */
         if (!backend->connection) {
