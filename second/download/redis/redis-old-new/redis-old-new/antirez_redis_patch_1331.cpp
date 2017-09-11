@@ -2302,8 +2302,12 @@ void daemonize(void) {
 }
 
 void version() {
-    printf("Redis server v=%s sha=%s:%d malloc=%s\n", REDIS_VERSION,
-        redisGitSHA1(), atoi(redisGitDirty()) > 0, ZMALLOC_LIB);
+    printf("Redis server v=%s sha=%s:%d malloc=%s bits=%d\n",
+        REDIS_VERSION,
+        redisGitSHA1(),
+        atoi(redisGitDirty()) > 0,
+        ZMALLOC_LIB,
+        sizeof(long) == 4 ? 32 : 64);
     exit(0);
 }
 