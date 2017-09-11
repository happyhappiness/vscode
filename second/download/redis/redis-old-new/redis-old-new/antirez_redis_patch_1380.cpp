@@ -2236,8 +2236,8 @@ void daemonize(void) {
 }
 
 void version() {
-    printf("Redis server version %s (%s:%d)\n", REDIS_VERSION,
-        redisGitSHA1(), atoi(redisGitDirty()) > 0);
+    printf("Redis server v=%s sha=%s:%d malloc=%s\n", REDIS_VERSION,
+        redisGitSHA1(), atoi(redisGitDirty()) > 0, ZMALLOC_LIB);
     exit(0);
 }
 