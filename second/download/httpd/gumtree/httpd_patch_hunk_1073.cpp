             proxy_function = "FTP";
     }
     ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
              "proxy: HTTP: serving URL %s", url);
 
 
-    /* only use stored info for top-level pages. Sub requests don't share
-     * in keepalives
-     */
-    if (!r->main) {
-        backend = (proxy_conn_rec *) ap_get_module_config(c->conn_config,
-                                                      &proxy_http_module);
-    }
     /* create space for state information */
-    if (!backend) {
-        if ((status = ap_proxy_acquire_connection(proxy_function, &backend,
-                                                  worker, r->server)) != OK)
-            goto cleanup;
+    if ((status = ap_proxy_acquire_connection(proxy_function, &backend,
+                                              worker, r->server)) != OK)
+        goto cleanup;
 
-        if (!r->main) {
-            ap_set_module_config(c->conn_config, &proxy_http_module, backend);
-        }
-    }
 
     backend->is_ssl = is_ssl;
-    backend->close_on_recycle = 1;
+    /*
+     * TODO: Currently we cannot handle persistent SSL backend connections,
+     * because we recreate backend->connection for each request and thus
+     * try to initialize an already existing SSL connection. This does
+     * not work.
+     */
+    if (is_ssl)
+        backend->close_on_recycle = 1;
 
     /* Step One: Determine Who To Connect To */
     if ((status = ap_proxy_determine_connection(p, r, conf, worker, backend,
                                                 uri, &url, proxyname,
                                                 proxyport, server_portstr,
                                                 sizeof(server_portstr))) != OK)
