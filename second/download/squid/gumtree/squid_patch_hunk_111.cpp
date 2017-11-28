 
 void
 clientOpenListenSockets(void)
 {
     clientHttpConnectionsOpen();
 #if USE_SSL
-
     clientHttpsConnectionsOpen();
 #endif
 
     if (NHttpSockets < 1)
-        fatal("Cannot open HTTP Port");
+        fatal("No HTTP or HTTPS ports configured");
 }
 
 void
 clientHttpConnectionsClose(void)
 {
-    int i;
+    for (AnyP::PortCfg *s = Config.Sockaddr.http; s; s = s->next) {
+        if (s->listenConn != NULL) {
+            debugs(1, 1, "Closing HTTP port " << s->listenConn->local);
+            s->listenConn->close();
+            s->listenConn = NULL;
+        }
+    }
 
-    for (i = 0; i < NHttpSockets; i++) {
-        if (HttpSockets[i] >= 0) {
-            debugs(1, 1, "FD " << HttpSockets[i] <<
-                   " Closing HTTP connection");
-            comm_close(HttpSockets[i]);
-            HttpSockets[i] = -1;
+#if USE_SSL
+    for (AnyP::PortCfg *s = Config.Sockaddr.https; s; s = s->next) {
+        if (s->listenConn != NULL) {
+            debugs(1, 1, "Closing HTTPS port " << s->listenConn->local);
+            s->listenConn->close();
+            s->listenConn = NULL;
         }
     }
+#endif
+
+    // TODO see if we can drop HttpSockets array entirely */
+    for (int i = 0; i < NHttpSockets; ++i) {
+        HttpSockets[i] = -1;
+    }
 
     NHttpSockets = 0;
 }
 
 int
 varyEvaluateMatch(StoreEntry * entry, HttpRequest * request)
