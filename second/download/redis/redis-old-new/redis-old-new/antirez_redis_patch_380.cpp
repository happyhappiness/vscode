@@ -1111,7 +1111,10 @@ void readSyncBulkPayload(aeEventLoop *el, int fd, void *privdata, int mask) {
         }
         serverLog(LL_NOTICE, "MASTER <-> SLAVE sync: Flushing old data");
         signalFlushedDb(-1);
-        emptyDb(-1,EMPTYDB_NO_FLAGS,replicationEmptyDbCallback);
+        emptyDb(
+            -1,
+            server.repl_slave_lazy_flush ? EMPTYDB_ASYNC : EMPTYDB_NO_FLAGS,
+            replicationEmptyDbCallback);
         /* Before loading the DB into memory we need to delete the readable
          * handler, otherwise it will get called recursively since
          * rdbLoad() will call the event loop to process events from time to