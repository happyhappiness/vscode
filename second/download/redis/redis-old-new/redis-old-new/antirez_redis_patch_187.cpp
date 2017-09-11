@@ -43,11 +43,20 @@
 
 #define rdbExitReportCorruptRDB(reason) rdbCheckThenExit(reason, __LINE__);
 
+extern int rdbCheckMode;
+void rdbCheckError(const char *fmt, ...);
+
 void rdbCheckThenExit(char *reason, int where) {
-    serverLog(LL_WARNING, "Corrupt RDB detected at rdb.c:%d (%s). "
-        "Running 'redis-check-rdb %s'",
-        where, reason, server.rdb_filename);
-    redis_check_rdb(server.rdb_filename);
+     if (!rdbCheckMode) {
+        serverLog(LL_WARNING, "Corrupt RDB detected at rdb.c:%d (%s). "
+            "Running 'redis-check-rdb %s'",
+            where, reason, server.rdb_filename);
+        char *argv[2] = {"",server.rdb_filename};
+        redis_check_rdb_main(2,argv);
+    } else {
+        rdbCheckError("Internal error in RDB reading function at rdb.c:%d (%s)",
+            where, reason);
+    }
     exit(1);
 }
 