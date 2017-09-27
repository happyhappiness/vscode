         return ap_proxyerror(r, HTTP_BAD_GATEWAY,
                              apr_pstrcat(p, "DNS lookup failure for: ",
                                          conn->hostname, NULL));
     }
 
     /* Get the server port for the Via headers */
-    {
-        server_port = ap_get_server_port(r);
-        if (ap_is_default_port(server_port, r)) {
-            strcpy(server_portstr,"");
-        }
-        else {
-            apr_snprintf(server_portstr, server_portstr_size, ":%d",
-                         server_port);
-        }
+    server_port = ap_get_server_port(r);
+    AP_DEBUG_ASSERT(server_portstr_size > 0);
+    if (ap_is_default_port(server_port, r)) {
+        server_portstr[0] = '\0';
     }
+    else {
+        apr_snprintf(server_portstr, server_portstr_size, ":%d",
+                     server_port);
+    }
+
     /* check if ProxyBlock directive on this host */
     if (OK != ap_proxy_checkproxyblock2(r, conf, uri->hostname, 
                                        proxyname ? NULL : conn->addr)) {
         return ap_proxyerror(r, HTTP_FORBIDDEN,
                              "Connect to remote machine blocked");
     }
+    /*
+     * When SSL is configured, determine the hostname (SNI) for the request
+     * and save it in conn->ssl_hostname. Close any reused connection whose
+     * SNI differs.
+     */
+    if (conn->is_ssl) {
+        proxy_dir_conf *dconf;
+        const char *ssl_hostname;
+        /*
+         * In the case of ProxyPreserveHost on use the hostname of
+         * the request if present otherwise use the one from the
+         * backend request URI.
+         */
+        dconf = ap_get_module_config(r->per_dir_config, &proxy_module);
+        if (dconf->preserve_host) {
+            ssl_hostname = r->hostname;
+        }
+        else {
+            ssl_hostname = conn->hostname;
+        }
+        /*
+         * Close if a SNI is in use but this request requires no or
+         * a different one, or no SNI is in use but one is required.
+         */
+        if ((conn->ssl_hostname && (!ssl_hostname ||
+                                    strcasecmp(conn->ssl_hostname,
+                                               ssl_hostname) != 0)) ||
+                (!conn->ssl_hostname && ssl_hostname && conn->sock)) {
+            socket_cleanup(conn);
+        }
+        if (conn->ssl_hostname == NULL) {
+            conn->ssl_hostname = apr_pstrdup(conn->scpool, ssl_hostname);
+        }
+    }
     ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(00947)
                  "connected %s to %s:%d", *url, conn->hostname, conn->port);
     return OK;
 }
 
 #define USE_ALTERNATE_IS_CONNECTED 1
