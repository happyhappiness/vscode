@@ -1376,7 +1376,7 @@ void createSharedObjects(void) {
     shared.maxstring = createStringObject("maxstring",9);
 }
 
-void initServerConfig() {
+void initServerConfig(void) {
     int j;
 
     getRandomHexChars(server.runid,REDIS_RUN_ID_SIZE);
@@ -1696,7 +1696,7 @@ void resetServerStats(void) {
     server.ops_sec_last_sample_ops = 0;
 }
 
-void initServer() {
+void initServer(void) {
     int j;
 
     signal(SIGHUP, SIG_IGN);
@@ -3349,7 +3349,7 @@ void daemonize(void) {
     }
 }
 
-void version() {
+void version(void) {
     printf("Redis server v=%s sha=%s:%d malloc=%s bits=%d build=%llx\n",
         REDIS_VERSION,
         redisGitSHA1(),
@@ -3360,7 +3360,7 @@ void version() {
     exit(0);
 }
 
-void usage() {
+void usage(void) {
     fprintf(stderr,"Usage: ./redis-server [/path/to/redis.conf] [options]\n");
     fprintf(stderr,"       ./redis-server - (read config from stdin)\n");
     fprintf(stderr,"       ./redis-server -v or --version\n");