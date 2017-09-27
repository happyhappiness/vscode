 
         if (status != OK)
             break;
 
         /* Step Two: Make the Connection */
         if (ap_proxy_connect_backend(scheme, backend, worker, r->server)) {
-            ap_log_error(APLOG_MARK, APLOG_ERR, 0, r->server,
-                         "proxy: AJP: failed to make connection to backend: %s",
-                         backend->hostname);
+            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(00896)
+                          "failed to make connection to backend: %s",
+                          backend->hostname);
             status = HTTP_SERVICE_UNAVAILABLE;
             break;
         }
 
         /* Handle CPING/CPONG */
-        if (worker->ping_timeout_set) {
+        if (worker->s->ping_timeout_set) {
             status = ajp_handle_cping_cpong(backend->sock, r,
-                                            worker->ping_timeout);
+                                            worker->s->ping_timeout);
             /*
              * In case the CPING / CPONG failed for the first time we might be
              * just out of luck and got a faulty backend connection, but the
              * backend might be healthy nevertheless. So ensure that the backend
              * TCP connection gets closed and try it once again.
              */
             if (status != APR_SUCCESS) {
                 backend->close++;
-                ap_log_error(APLOG_MARK, APLOG_ERR, status, r->server,
-                             "proxy: AJP: cping/cpong failed to %pI (%s)",
-                             worker->cp->addr,
-                             worker->hostname);
+                ap_log_rerror(APLOG_MARK, APLOG_ERR, status, r, APLOGNO(00897)
+                              "cping/cpong failed to %pI (%s)",
+                              worker->cp->addr, worker->s->hostname);
                 status = HTTP_SERVICE_UNAVAILABLE;
                 retry++;
                 continue;
             }
         }
         /* Step Three: Process the Request */
