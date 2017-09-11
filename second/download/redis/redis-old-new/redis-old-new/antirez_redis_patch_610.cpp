@@ -48,7 +48,7 @@
 
 void rdbCheckThenExit(char *reason, int where) {
     redisLog(REDIS_WARNING, "Corrupt RDB detected at rdb.c:%d (%s). "
-        "Running 'redis-check-rdb --dbfilename %s'",
+        "Running 'redis-check-rdb %s'",
         where, reason, server.rdb_filename);
     redis_check_rdb(server.rdb_filename);
     exit(1);
@@ -1375,7 +1375,7 @@ int rdbLoad(char *filename) {
             redisLog(REDIS_WARNING,"RDB file was saved with checksum disabled: no check performed.");
         } else if (cksum != expected) {
             redisLog(REDIS_WARNING,"Wrong RDB checksum. Aborting now.");
-            exit(1);
+            rdbExitReportCorruptRDB("RDB CRC error");
         }
     }
 
@@ -1385,7 +1385,7 @@ int rdbLoad(char *filename) {
 
 eoferr: /* unexpected end of file is handled here with a fatal exit */
     redisLog(REDIS_WARNING,"Short read or OOM loading DB. Unrecoverable error, aborting now.");
-    exit(1);
+    rdbExitReportCorruptRDB("Unexpected EOF reading RDB file");
     return REDIS_ERR; /* Just to avoid warning */
 }
 