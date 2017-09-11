@@ -490,11 +490,12 @@ int masterTryPartialResynchronization(client *c) {
  * Returns C_OK on success or C_ERR otherwise. */
 int startBgsaveForReplication(int mincapa) {
     int retval;
+    int socket_target = server.repl_diskless_sync && (mincapa & SLAVE_CAPA_EOF);
 
     serverLog(LL_NOTICE,"Starting BGSAVE for SYNC with target: %s",
-        server.repl_diskless_sync ? "slaves sockets" : "disk");
+        socket_target ? "slaves sockets" : "disk");
 
-    if (server.repl_diskless_sync && (mincapa & SLAVE_CAPA_EOF))
+    if (socket_target)
         retval = rdbSaveToSlavesSockets();
     else
         retval = rdbSaveBackground(server.rdb_filename);