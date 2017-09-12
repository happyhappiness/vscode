@@ -575,6 +575,8 @@ typedef struct iojob {
 } iojob;
 
 /*================================ Prototypes =============================== */
+char *redisGitSHA1(void);
+char *redisGitDirty(void);
 
 static void freeStringObject(robj *o);
 static void freeListObject(robj *o);
@@ -7760,8 +7762,8 @@ static sds genRedisInfoString(void) {
         "vm_enabled:%d\r\n"
         "role:%s\r\n"
         ,REDIS_VERSION,
-        REDIS_GIT_SHA1,
-        strtol(REDIS_GIT_DIRTY,NULL,10) > 0,
+        redisGitSHA1(),
+        strtol(redisGitDirty(),NULL,10) > 0,
         (sizeof(long) == 8) ? "64" : "32",
         aeGetApiName(),
         (long) getpid(),
@@ -11442,7 +11444,7 @@ static void daemonize(void) {
 
 static void version() {
     printf("Redis server version %s (%s:%d)\n", REDIS_VERSION,
-        REDIS_GIT_SHA1, atoi(REDIS_GIT_DIRTY) > 0);
+        redisGitSHA1(), atoi(redisGitDirty()) > 0);
     exit(0);
 }
 