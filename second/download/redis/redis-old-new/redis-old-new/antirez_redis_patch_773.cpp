@@ -66,7 +66,6 @@ double R_Zero, R_PosInf, R_NegInf, R_Nan;
 
 /* Global vars */
 struct redisServer server; /* server global state */
-struct redisCommand *commandTable;
 
 /* Our command table.
  *
@@ -267,7 +266,7 @@ struct redisCommand redisCommandTable[] = {
     {"readwrite",readwriteCommand,1,"rF",0,NULL,0,0,0,0,0},
     {"dump",dumpCommand,2,"ar",0,NULL,1,1,1,0,0},
     {"object",objectCommand,3,"r",0,NULL,2,2,2,0,0},
-    {"client",clientCommand,-2,"ar",0,NULL,0,0,0,0,0},
+    {"client",clientCommand,-2,"ars",0,NULL,0,0,0,0,0},
     {"eval",evalCommand,-3,"s",0,evalGetKeys,0,0,0,0,0},
     {"evalsha",evalShaCommand,-3,"s",0,evalGetKeys,0,0,0,0,0},
     {"slowlog",slowlogCommand,-2,"r",0,NULL,0,0,0,0,0},
@@ -760,8 +759,8 @@ void activeExpireCycle(int type) {
     static int timelimit_exit = 0;      /* Time limit hit in previous call? */
     static long long last_fast_cycle = 0; /* When last fast cycle ran. */
 
-    unsigned int j, iteration = 0;
-    unsigned int dbs_per_call = REDIS_DBCRON_DBS_PER_CALL;
+    int j, iteration = 0;
+    int dbs_per_call = REDIS_DBCRON_DBS_PER_CALL;
     long long start = ustime(), timelimit;
 
     if (type == ACTIVE_EXPIRE_CYCLE_FAST) {
@@ -1000,8 +999,8 @@ void databasesCron(void) {
          * cron loop iteration. */
         static unsigned int resize_db = 0;
         static unsigned int rehash_db = 0;
-        unsigned int dbs_per_call = REDIS_DBCRON_DBS_PER_CALL;
-        unsigned int j;
+        int dbs_per_call = REDIS_DBCRON_DBS_PER_CALL;
+        int j;
 
         /* Don't test more DBs than we have. */
         if (dbs_per_call > server.dbnum) dbs_per_call = server.dbnum;
@@ -1376,7 +1375,7 @@ void createSharedObjects(void) {
     shared.maxstring = createStringObject("maxstring",9);
 }
 
-void initServerConfig() {
+void initServerConfig(void) {
     int j;
 
     getRandomHexChars(server.runid,REDIS_RUN_ID_SIZE);
@@ -1557,7 +1556,7 @@ void adjustOpenFilesLimit(void) {
              * to the higher value supported less than maxfiles. */
             f = maxfiles;
             while(f > oldlimit) {
-                int decr_step = 16;
+                rlim_t decr_step = 16;
 
                 limit.rlim_cur = f;
                 limit.rlim_max = f;
@@ -1696,7 +1695,7 @@ void resetServerStats(void) {
     server.ops_sec_last_sample_ops = 0;
 }
 
-void initServer() {
+void initServer(void) {
     int j;
 
     signal(SIGHUP, SIG_IGN);
@@ -2359,9 +2358,9 @@ int time_independent_strcmp(char *a, char *b) {
      * a or b are fixed (our password) length, and the difference is only
      * relative to the length of the user provided string, so no information
      * leak is possible in the following two lines of code. */
-    int alen = strlen(a);
-    int blen = strlen(b);
-    int j;
+    unsigned int alen = strlen(a);
+    unsigned int blen = strlen(b);
+    unsigned int j;
     int diff = 0;
 
     /* We can't compare strings longer than our static buffers.
@@ -2547,6 +2546,15 @@ void bytesToHuman(char *s, unsigned long long n) {
     } else if (n < (1024LL*1024*1024*1024)) {
         d = (double)n/(1024LL*1024*1024);
         sprintf(s,"%.2fG",d);
+    } else if (n < (1024LL*1024*1024*1024*1024)) {
+        d = (double)n/(1024LL*1024*1024*1024);
+        sprintf(s,"%.2fT",d);
+    } else if (n < (1024LL*1024*1024*1024*1024*1024)) {
+        d = (double)n/(1024LL*1024*1024*1024*1024);
+        sprintf(s,"%.2fP",d);
+    } else {
+        /* Let's hope we never need this */
+        sprintf(s,"%lluB",n);
     }
 }
 
@@ -2562,10 +2570,9 @@ sds genRedisInfoString(char *section) {
     int allsections = 0, defsections = 0;
     int sections = 0;
 
-    if (section) {
-        allsections = strcasecmp(section,"all") == 0;
-        defsections = strcasecmp(section,"default") == 0;
-    }
+    if (section == NULL) section = "default";
+    allsections = strcasecmp(section,"all") == 0;
+    defsections = strcasecmp(section,"default") == 0;
 
     getrusage(RUSAGE_SELF, &self_ru);
     getrusage(RUSAGE_CHILDREN, &c_ru);
@@ -3350,7 +3357,7 @@ void daemonize(void) {
     }
 }
 
-void version() {
+void version(void) {
     printf("Redis server v=%s sha=%s:%d malloc=%s bits=%d build=%llx\n",
         REDIS_VERSION,
         redisGitSHA1(),
@@ -3361,7 +3368,7 @@ void version() {
     exit(0);
 }
 
-void usage() {
+void usage(void) {
     fprintf(stderr,"Usage: ./redis-server [/path/to/redis.conf] [options]\n");
     fprintf(stderr,"       ./redis-server - (read config from stdin)\n");
     fprintf(stderr,"       ./redis-server -v or --version\n");
@@ -3399,10 +3406,33 @@ void redisAsciiArt(void) {
     zfree(buf);
 }
 
-static void sigtermHandler(int sig) {
-    REDIS_NOTUSED(sig);
-
-    redisLogFromHandler(REDIS_WARNING,"Received SIGTERM, scheduling shutdown...");
+static void sigShutdownHandler(int sig) {
+    char *msg;
+
+    switch (sig) {
+    case SIGINT:
+        msg = "Received SIGINT scheduling shutdown...";
+        break;
+    case SIGTERM:
+        msg = "Received SIGTERM scheduling shutdown...";
+        break;
+    default:
+        msg = "Received shutdown signal, scheduling shutdown...";
+    };
+
+    /* SIGINT is often delivered via Ctrl+C in an interactive session.
+     * If we receive the signal the second time, we interpret this as
+     * the user really wanting to quit ASAP without waiting to persist
+     * on disk. */
+    if (server.shutdown_asap && sig == SIGINT) {
+        redisLogFromHandler(REDIS_WARNING, "You insist... exiting now.");
+        rdbRemoveTempFile(getpid());
+        exit(1); /* Exit with an error since this was not a clean shutdown. */
+    } else if (server.loading) {
+        exit(0);
+    }
+
+    redisLogFromHandler(REDIS_WARNING, msg);
     server.shutdown_asap = 1;
 }
 
@@ -3413,8 +3443,9 @@ void setupSignalHandlers(void) {
      * Otherwise, sa_handler is used. */
     sigemptyset(&act.sa_mask);
     act.sa_flags = 0;
-    act.sa_handler = sigtermHandler;
+    act.sa_handler = sigShutdownHandler;
     sigaction(SIGTERM, &act, NULL);
+    sigaction(SIGINT, &act, NULL);
 
 #ifdef HAVE_BACKTRACE
     sigemptyset(&act.sa_mask);
@@ -3545,6 +3576,13 @@ int main(int argc, char **argv) {
             }
             j++;
         }
+        if (server.sentinel_mode && configfile && *configfile == '-') {
+            redisLog(REDIS_WARNING,
+                "Sentinel config from STDIN not allowed.");
+            redisLog(REDIS_WARNING,
+                "Sentinel needs config file on disk to save state.  Exiting...");
+            exit(1);
+        }
         if (configfile) server.configfile = getAbsolutePath(configfile);
         resetServerSaveParams();
         loadServerConfig(configfile,options);