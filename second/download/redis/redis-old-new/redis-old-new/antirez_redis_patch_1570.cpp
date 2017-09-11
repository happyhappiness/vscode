@@ -901,6 +901,7 @@ void initServerConfig() {
     server.replstate = REDIS_REPL_NONE;
     server.repl_syncio_timeout = REDIS_REPL_SYNCIO_TIMEOUT;
     server.repl_serve_stale_data = 1;
+    server.repl_down_since = -1;
 
     /* Double constants initialization */
     R_Zero = 0.0;
@@ -1522,6 +1523,12 @@ sds genRedisInfoString(char *section) {
                     (int)(time(NULL)-server.repl_transfer_lastio)
                 );
             }
+
+            if (server.replstate != REDIS_REPL_CONNECTED) {
+                info = sdscatprintf(info,
+                    "master_link_down_since_seconds:%ld\r\n",
+                    (long)time(NULL)-server.repl_down_since);
+            }
         }
         info = sdscatprintf(info,
             "connected_slaves:%d\r\n",