@@ -696,3 +696,15 @@ int redis_check_rdb(char *rdbfilename) {
     close(fd);
     return 0;
 }
+
+/* RDB check main: called form redis.c when Redis is executed with the
+ * redis-check-rdb alias. */
+int redis_check_rdb_main(char **argv, int argc) {
+    if (argc != 2) {
+        fprintf(stderr, "Usage: %s <rdb-file-name>\n", argv[0]);
+        exit(1);
+    }
+    redisLog(REDIS_WARNING, "Checking RDB file %s", argv[1]);
+    exit(redis_check_rdb(argv[1]));
+    return 0;
+}