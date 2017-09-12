@@ -5407,14 +5407,37 @@ static void sortCommand(redisClient *c) {
     zfree(vector);
 }
 
+/* Convert an amount of bytes into a human readable string in the form
+ * of 100B, 2G, 100M, 4K, and so forth. */
+static void bytesToHuman(char *s, unsigned long long n) {
+    double d;
+
+    if (n < 1024) {
+        /* Bytes */
+        sprintf(s,"%lluB",n);
+        return;
+    } else if (n < (1024*1024)) {
+        d = (double)n/(1024);
+        sprintf(s,"%.2fK",d);
+    } else if (n < (1024LL*1024*1024)) {
+        d = (double)n/(1024*1024);
+        sprintf(s,"%.2fM",d);
+    } else if (n < (1024LL*1024*1024*1024)) {
+        d = (double)n/(1024LL*1024*1024);
+        sprintf(s,"%.2fM",d);
+    }
+}
+
 /* Create the string returned by the INFO command. This is decoupled
  * by the INFO command itself as we need to report the same information
  * on memory corruption problems. */
 static sds genRedisInfoString(void) {
     sds info;
     time_t uptime = time(NULL)-server.stat_starttime;
     int j;
-    
+    char hmem[64];
+  
+    bytesToHuman(hmem,server.usedmemory);
     info = sdscatprintf(sdsempty(),
         "redis_version:%s\r\n"
         "arch_bits:%s\r\n"
@@ -5426,6 +5449,7 @@ static sds genRedisInfoString(void) {
         "connected_slaves:%d\r\n"
         "blocked_clients:%d\r\n"
         "used_memory:%zu\r\n"
+        "used_memory_human:%s\r\n"
         "changes_since_last_save:%lld\r\n"
         "bgsave_in_progress:%d\r\n"
         "last_save_time:%ld\r\n"
@@ -5444,6 +5468,7 @@ static sds genRedisInfoString(void) {
         listLength(server.slaves),
         server.blockedclients,
         server.usedmemory,
+        hmem,
         server.dirty,
         server.bgsavechildpid != -1,
         server.lastsave,