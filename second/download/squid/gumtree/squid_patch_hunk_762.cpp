 }
 
 void
 clientOpenListenSockets(void)
 {
     clientHttpConnectionsOpen();
-#if USE_SSL
+#if USE_OPENSSL
     clientHttpsConnectionsOpen();
 #endif
+    Ftp::StartListening();
 
     if (NHttpSockets < 1)
-        fatal("No HTTP or HTTPS ports configured");
+        fatal("No HTTP, HTTPS, or FTP ports configured");
 }
 
 void
-clientHttpConnectionsClose(void)
+clientConnectionsClose()
 {
-    for (AnyP::PortCfg *s = Config.Sockaddr.http; s; s = s->next) {
+    for (AnyP::PortCfgPointer s = HttpPortList; s != NULL; s = s->next) {
         if (s->listenConn != NULL) {
             debugs(1, DBG_IMPORTANT, "Closing HTTP port " << s->listenConn->local);
             s->listenConn->close();
             s->listenConn = NULL;
         }
     }
 
-#if USE_SSL
-    for (AnyP::PortCfg *s = Config.Sockaddr.https; s; s = s->next) {
+#if USE_OPENSSL
+    for (AnyP::PortCfgPointer s = HttpsPortList; s != NULL; s = s->next) {
         if (s->listenConn != NULL) {
             debugs(1, DBG_IMPORTANT, "Closing HTTPS port " << s->listenConn->local);
             s->listenConn->close();
             s->listenConn = NULL;
         }
     }
 #endif
 
+    Ftp::StopListening();
+
     // TODO see if we can drop HttpSockets array entirely */
     for (int i = 0; i < NHttpSockets; ++i) {
         HttpSockets[i] = -1;
     }
 
     NHttpSockets = 0;
 }
 
 int
 varyEvaluateMatch(StoreEntry * entry, HttpRequest * request)
 {
-    const char *vary = request->vary_headers;
+    SBuf vary(request->vary_headers);
     int has_vary = entry->getReply()->header.has(HDR_VARY);
 #if X_ACCELERATOR_VARY
-
     has_vary |=
         entry->getReply()->header.has(HDR_X_ACCELERATOR_VARY);
 #endif
 
-    if (!has_vary || !entry->mem_obj->vary_headers) {
-        if (vary) {
+    if (!has_vary || entry->mem_obj->vary_headers.isEmpty()) {
+        if (!vary.isEmpty()) {
             /* Oops... something odd is going on here.. */
             debugs(33, DBG_IMPORTANT, "varyEvaluateMatch: Oops. Not a Vary object on second attempt, '" <<
-                   entry->mem_obj->url << "' '" << vary << "'");
-            safe_free(request->vary_headers);
+                   entry->mem_obj->urlXXX() << "' '" << vary << "'");
+            request->vary_headers.clear();
             return VARY_CANCEL;
         }
 
         if (!has_vary) {
             /* This is not a varying object */
             return VARY_NONE;
