         else {
             apr_snprintf(server_portstr, server_portstr_size, ":%d",
                          server_port);
         }
     }
     /* check if ProxyBlock directive on this host */
-    if (OK != ap_proxy_checkproxyblock(r, conf, conn->addr)) {
+    if (OK != ap_proxy_checkproxyblock2(r, conf, uri->hostname, 
+                                       proxyname ? NULL : conn->addr)) {
         return ap_proxyerror(r, HTTP_FORBIDDEN,
                              "Connect to remote machine blocked");
     }
     ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(00947)
                  "connected %s to %s:%d", *url, conn->hostname, conn->port);
     return OK;
