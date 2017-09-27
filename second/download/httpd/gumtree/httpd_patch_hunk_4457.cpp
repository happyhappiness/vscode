                                                 uri, &locurl, proxyname,
                                                 proxyport, server_portstr,
                                                 sizeof(server_portstr))) != OK)
             break;
 
         /* Step Two: Make the Connection */
-        if (ap_proxy_connect_backend(proxy_function, backend, worker, r->server)) {
+        if (ap_proxy_check_connection(proxy_function, backend, r->server, 1,
+                                      PROXY_CHECK_CONN_EMPTY)
+                && ap_proxy_connect_backend(proxy_function, backend, worker,
+                                            r->server)) {
             ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01114)
                           "HTTP: failed to make connection to backend: %s",
                           backend->hostname);
             status = HTTP_SERVICE_UNAVAILABLE;
             break;
         }
