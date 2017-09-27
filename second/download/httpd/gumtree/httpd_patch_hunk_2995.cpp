     }
     else {
         connectname = uri.hostname;
         connectport = uri.port;
         connect_addr = uri_addr;
     }
-    ap_log_error(APLOG_MARK, APLOG_TRACE1, 0, r->server,
-                 "proxy: CONNECT: connecting to remote proxy %s on port %d",
-                 connectname, connectport);
+    ap_log_rerror(APLOG_MARK, APLOG_TRACE1, 0, r,
+                  "connecting to remote proxy %s on port %d",
+                  connectname, connectport);
 
     /* check if ProxyBlock directive on this host */
     if (OK != ap_proxy_checkproxyblock(r, conf, uri_addr)) {
         return ap_proxyerror(r, HTTP_FORBIDDEN,
                              "Connect to remote machine blocked");
     }
