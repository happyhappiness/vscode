         }
         else {
             conn->hostname = apr_pstrdup(conn->pool, uri->hostname);
             conn->port = uri->port;
         }
         socket_cleanup(conn);
-        err = apr_sockaddr_info_get(&(conn->addr),
-                                    conn->hostname, APR_UNSPEC,
-                                    conn->port, 0,
-                                    conn->pool);
-    }
-    else if (!worker->cp->addr) {
-        if ((err = PROXY_THREAD_LOCK(worker)) != APR_SUCCESS) {
-            ap_log_error(APLOG_MARK, APLOG_ERR, err, r->server,
-                         "proxy: lock");
-            return HTTP_INTERNAL_SERVER_ERROR;
+        if (!worker->is_address_reusable || worker->disablereuse) {
+            /*
+             * Only do a lookup if we should not reuse the backend address.
+             * Otherwise we will look it up once for the worker.
+             */
+            err = apr_sockaddr_info_get(&(conn->addr),
+                                        conn->hostname, APR_UNSPEC,
+                                        conn->port, 0,
+                                        conn->pool);
         }
-
+    }
+    if (worker->is_address_reusable && !worker->disablereuse) {
         /*
-         * Worker can have the single constant backend adress.
-         * The single DNS lookup is used once per worker.
-         * If dynamic change is needed then set the addr to NULL
-         * inside dynamic config to force the lookup.
+         * Looking up the backend address for the worker only makes sense if
+         * we can reuse the address.
          */
-        err = apr_sockaddr_info_get(&(worker->cp->addr),
-                                    conn->hostname, APR_UNSPEC,
-                                    conn->port, 0,
-                                    worker->cp->pool);
-        conn->addr = worker->cp->addr;
-        if ((uerr = PROXY_THREAD_UNLOCK(worker)) != APR_SUCCESS) {
-            ap_log_error(APLOG_MARK, APLOG_ERR, uerr, r->server,
-                         "proxy: unlock");
+        if (!worker->cp->addr) {
+            if ((err = PROXY_THREAD_LOCK(worker)) != APR_SUCCESS) {
+                ap_log_error(APLOG_MARK, APLOG_ERR, err, r->server,
+                             "proxy: lock");
+                return HTTP_INTERNAL_SERVER_ERROR;
+            }
+
+            /*
+             * Worker can have the single constant backend adress.
+             * The single DNS lookup is used once per worker.
+             * If dynamic change is needed then set the addr to NULL
+             * inside dynamic config to force the lookup.
+             */
+            err = apr_sockaddr_info_get(&(worker->cp->addr),
+                                        conn->hostname, APR_UNSPEC,
+                                        conn->port, 0,
+                                        worker->cp->pool);
+            conn->addr = worker->cp->addr;
+            if ((uerr = PROXY_THREAD_UNLOCK(worker)) != APR_SUCCESS) {
+                ap_log_error(APLOG_MARK, APLOG_ERR, uerr, r->server,
+                             "proxy: unlock");
+            }
+        }
+        else {
+            conn->addr = worker->cp->addr;
         }
-    }
-    else {
-        conn->addr = worker->cp->addr;
     }
     /* Close a possible existing socket if we are told to do so */
     if (conn->close) {
         socket_cleanup(conn);
         conn->close = 0;
     }
