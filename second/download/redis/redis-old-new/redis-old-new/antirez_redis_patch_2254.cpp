@@ -826,8 +826,7 @@ static dictType hashDictType = {
  * is based on heap allocation for send buffers, so we simply abort.
  * At least the code will be simpler to read... */
 static void oom(const char *msg) {
-    fprintf(stderr, "%s: Out of memory\n",msg);
-    fflush(stderr);
+    redisLog(REDIS_WARNING, "%s: Out of memory\n",msg);
     sleep(1);
     abort();
 }
@@ -6158,6 +6157,7 @@ static void daemonize(void) {
     FILE *fp;
 
     if (fork() != 0) exit(0); /* parent exits */
+    printf("New pid: %d\n", getpid());
     setsid(); /* create a new session */
 
     /* Every output goes to /dev/null. If Redis is daemonized but
@@ -6188,8 +6188,8 @@ int main(int argc, char **argv) {
     } else {
         redisLog(REDIS_WARNING,"Warning: no config file specified, using the default config. In order to specify a config file use 'redis-server /path/to/redis.conf'");
     }
-    initServer();
     if (server.daemonize) daemonize();
+    initServer();
     redisLog(REDIS_NOTICE,"Server started, Redis version " REDIS_VERSION);
 #ifdef __linux__
     linuxOvercommitMemoryWarning();