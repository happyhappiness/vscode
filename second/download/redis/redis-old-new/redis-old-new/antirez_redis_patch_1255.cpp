@@ -1929,6 +1929,7 @@ sds genRedisInfoString(char *section) {
             "redis_version:%s\r\n"
             "redis_git_sha1:%s\r\n"
             "redis_git_dirty:%d\r\n"
+            "redis_build_id:%llx\r\n"
             "redis_mode:%s\r\n"
             "os:%s %s %s\r\n"
             "arch_bits:%d\r\n"
@@ -1943,6 +1944,7 @@ sds genRedisInfoString(char *section) {
             REDIS_VERSION,
             redisGitSHA1(),
             strtol(redisGitDirty(),NULL,10) > 0,
+            redisBuildId(),
             mode,
             name.sysname, name.release, name.machine,
             server.arch_bits,
@@ -2489,12 +2491,13 @@ void daemonize(void) {
 }
 
 void version() {
-    printf("Redis server v=%s sha=%s:%d malloc=%s bits=%d\n",
+    printf("Redis server v=%s sha=%s:%d malloc=%s bits=%d build=%llx\n",
         REDIS_VERSION,
         redisGitSHA1(),
         atoi(redisGitDirty()) > 0,
         ZMALLOC_LIB,
-        sizeof(long) == 4 ? 32 : 64);
+        sizeof(long) == 4 ? 32 : 64,
+        redisBuildId());
     exit(0);
 }
 