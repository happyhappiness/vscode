@@ -821,13 +821,8 @@ void clientsCron(void) {
  * a macro is used: run_with_period(milliseconds) { .... }
  */
 
-/* Using the following macro you can run code inside serverCron() with the
- * specified period, specified in milliseconds.
- * The actual resolution depends on REDIS_HZ. */
-#define run_with_period(_ms_) if (!(loops % ((_ms_)/(1000/REDIS_HZ))))
-
 int serverCron(struct aeEventLoop *eventLoop, long long id, void *clientData) {
-    int j, loops = server.cronloops;
+    int j;
     REDIS_NOTUSED(eventLoop);
     REDIS_NOTUSED(id);
     REDIS_NOTUSED(clientData);
@@ -896,11 +891,14 @@ int serverCron(struct aeEventLoop *eventLoop, long long id, void *clientData) {
     }
 
     /* Show information about connected clients */
-    run_with_period(5000) {
-        redisLog(REDIS_VERBOSE,"%d clients connected (%d slaves), %zu bytes in use",
-            listLength(server.clients)-listLength(server.slaves),
-            listLength(server.slaves),
-            zmalloc_used_memory());
+    if (!server.sentinel_mode) {
+        run_with_period(5000) {
+            redisLog(REDIS_VERBOSE,
+                "%d clients connected (%d slaves), %zu bytes in use",
+                listLength(server.clients)-listLength(server.slaves),
+                listLength(server.slaves),
+                zmalloc_used_memory());
+        }
     }
 
     /* We need to do a few operations on clients asynchronously. */
@@ -985,6 +983,11 @@ int serverCron(struct aeEventLoop *eventLoop, long long id, void *clientData) {
         if (server.cluster_enabled) clusterCron();
     }
 
+    /* Run the sentinel timer if we are in sentinel mode. */
+    run_with_period(100) {
+        if (server.sentinel_mode) sentinelTimer();
+    }
+
     server.cronloops++;
     return 1000/REDIS_HZ;
 }
@@ -2444,21 +2447,26 @@ void usage() {
     fprintf(stderr,"       ./redis-server /etc/redis/6379.conf\n");
     fprintf(stderr,"       ./redis-server --port 7777\n");
     fprintf(stderr,"       ./redis-server --port 7777 --slaveof 127.0.0.1 8888\n");
-    fprintf(stderr,"       ./redis-server /etc/myredis.conf --loglevel verbose\n");
+    fprintf(stderr,"       ./redis-server /etc/myredis.conf --loglevel verbose\n\n");
+    fprintf(stderr,"Sentinel mode:\n");
+    fprintf(stderr,"       ./redis-server /etc/sentinel.conf --sentinel\n");
     exit(1);
 }
 
 void redisAsciiArt(void) {
 #include "asciilogo.h"
     char *buf = zmalloc(1024*16);
+    char *mode = "stand alone";
+
+    if (server.cluster_enabled) mode = "cluster";
+    else if (server.sentinel_mode) mode = "sentinel";
 
     snprintf(buf,1024*16,ascii_logo,
         REDIS_VERSION,
         redisGitSHA1(),
         strtol(redisGitDirty(),NULL,10) > 0,
         (sizeof(long) == 8) ? "64" : "32",
-        server.cluster_enabled ? "cluster" : "stand alone",
-        server.port,
+        mode, server.port,
         (long) getpid()
     );
     redisLogRaw(REDIS_NOTICE|REDIS_LOG_RAW,buf);
@@ -2496,17 +2504,53 @@ void setupSignalHandlers(void) {
 
 void memtest(size_t megabytes, int passes);
 
+/* Returns 1 if there is --sentinel among the arguments or if
+ * argv[0] is exactly "redis-sentinel". */
+int checkForSentinelMode(int argc, char **argv) {
+    int j;
+
+    if (strstr(argv[0],"redis-sentinel") != NULL) return 1;
+    for (j = 1; j < argc; j++)
+        if (!strcmp(argv[j],"--sentinel")) return 1;
+    return 0;
+}
+
+/* Function called at startup to load RDB or AOF file in memory. */
+void loadDataFromDisk(void) {
+    long long start = ustime();
+    if (server.aof_state == REDIS_AOF_ON) {
+        if (loadAppendOnlyFile(server.aof_filename) == REDIS_OK)
+            redisLog(REDIS_NOTICE,"DB loaded from append only file: %.3f seconds",(float)(ustime()-start)/1000000);
+    } else {
+        if (rdbLoad(server.rdb_filename) == REDIS_OK) {
+            redisLog(REDIS_NOTICE,"DB loaded from disk: %.3f seconds",
+                (float)(ustime()-start)/1000000);
+        } else if (errno != ENOENT) {
+            redisLog(REDIS_WARNING,"Fatal error loading the DB. Exiting.");
+            exit(1);
+        }
+    }
+}
+
 int main(int argc, char **argv) {
-    long long start;
     struct timeval tv;
 
     /* We need to initialize our libraries, and the server configuration. */
     zmalloc_enable_thread_safeness();
     srand(time(NULL)^getpid());
     gettimeofday(&tv,NULL);
     dictSetHashFunctionSeed(tv.tv_sec^tv.tv_usec^getpid());
+    server.sentinel_mode = checkForSentinelMode(argc,argv);
     initServerConfig();
 
+    /* We need to init sentinel right now as parsing the configuration file
+     * in sentinel mode will have the effect of populating the sentinel
+     * data structures with master nodes to monitor. */
+    if (server.sentinel_mode) {
+        initSentinelConfig();
+        initSentinel();
+    }
+
     if (argc >= 2) {
         int j = 1; /* First option to parse in argv[] */
         sds options = sdsempty();
@@ -2558,27 +2602,20 @@ int main(int argc, char **argv) {
     initServer();
     if (server.daemonize) createPidFile();
     redisAsciiArt();
-    redisLog(REDIS_WARNING,"Server started, Redis version " REDIS_VERSION);
-#ifdef __linux__
-    linuxOvercommitMemoryWarning();
-#endif
-    start = ustime();
-    if (server.aof_state == REDIS_AOF_ON) {
-        if (loadAppendOnlyFile(server.aof_filename) == REDIS_OK)
-            redisLog(REDIS_NOTICE,"DB loaded from append only file: %.3f seconds",(float)(ustime()-start)/1000000);
-    } else {
-        if (rdbLoad(server.rdb_filename) == REDIS_OK) {
-            redisLog(REDIS_NOTICE,"DB loaded from disk: %.3f seconds",
-                (float)(ustime()-start)/1000000);
-        } else if (errno != ENOENT) {
-            redisLog(REDIS_WARNING,"Fatal error loading the DB. Exiting.");
-            exit(1);
-        }
+
+    if (!server.sentinel_mode) {
+        /* Things only needed when not runnign in Sentinel mode. */
+        redisLog(REDIS_WARNING,"Server started, Redis version " REDIS_VERSION);
+    #ifdef __linux__
+        linuxOvercommitMemoryWarning();
+    #endif
+        loadDataFromDisk();
+        if (server.ipfd > 0)
+            redisLog(REDIS_NOTICE,"The server is now ready to accept connections on port %d", server.port);
+        if (server.sofd > 0)
+            redisLog(REDIS_NOTICE,"The server is now ready to accept connections at %s", server.unixsocket);
     }
-    if (server.ipfd > 0)
-        redisLog(REDIS_NOTICE,"The server is now ready to accept connections on port %d", server.port);
-    if (server.sofd > 0)
-        redisLog(REDIS_NOTICE,"The server is now ready to accept connections at %s", server.unixsocket);
+
     aeSetBeforeSleepProc(server.el,beforeSleep);
     aeMain(server.el);
     aeDeleteEventLoop(server.el);