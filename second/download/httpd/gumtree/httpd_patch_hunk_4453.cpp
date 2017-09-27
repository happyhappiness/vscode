 
     ap_log_rerror(APLOG_MARK, APLOG_TRACE1, 0, r,
                   "connecting to remote proxy %s on port %d",
                   connectname, connectport);
 
     /* Check if it is an allowed port */
-    if(!allowed_port(c_conf, uri.port)) {
-              return ap_proxyerror(r, HTTP_FORBIDDEN,
-                                   "Connect to remote machine blocked");
+    if (!allowed_port(c_conf, uri.port)) {
+        return ap_proxyerror(r, HTTP_FORBIDDEN,
+                             "Connect to remote machine blocked");
     }
 
     /*
      * Step Two: Make the Connection
      *
      * We have determined who to connect to. Now make the connection.
