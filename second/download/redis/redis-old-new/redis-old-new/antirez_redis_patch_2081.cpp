@@ -10906,7 +10906,8 @@ static void daemonize(void) {
 }
 
 static void version() {
-    printf("Redis server version %s\n", REDIS_VERSION);
+    printf("Redis server version %s (%s:%d)\n", REDIS_VERSION,
+        REDIS_GIT_SHA1, atoi(REDIS_GIT_DIRTY) > 0);
     exit(0);
 }
 