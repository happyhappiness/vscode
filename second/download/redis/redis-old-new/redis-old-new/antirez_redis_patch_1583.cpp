@@ -48,7 +48,10 @@
 #define REDIS_NOTUSED(V) ((void) V)
 
 static struct config {
-    int debug;
+    aeEventLoop *el;
+    const char *hostip;
+    int hostport;
+    const char *hostsocket;
     int numclients;
     int requests;
     int liveclients;
@@ -57,15 +60,11 @@ static struct config {
     int datasize;
     int randomkeys;
     int randomkeys_keyspacelen;
-    aeEventLoop *el;
-    char *hostip;
-    int hostport;
-    char *hostsocket;
     int keepalive;
     long long start;
     long long totlatency;
     long long *latency;
-    char *title;
+    const char *title;
     list *clients;
     int quiet;
     int loop;
@@ -227,7 +226,7 @@ static void writeHandler(aeEventLoop *el, int fd, void *privdata, int mask) {
     }
 }
 
-static client createClient(char *cmd, int len) {
+static client createClient(const char *cmd, size_t len) {
     client c = zmalloc(sizeof(struct _client));
     if (config.hostsocket == NULL) {
         c->context = redisConnectNonBlock(config.hostip,config.hostport);
@@ -311,7 +310,7 @@ static void showLatencyReport(void) {
     }
 }
 
-static void benchmark(char *title, char *cmd, int len) {
+static void benchmark(const char *title, const char *cmd, int len) {
     client c;
 
     config.title = title;
@@ -328,73 +327,87 @@ static void benchmark(char *title, char *cmd, int len) {
     freeAllClients();
 }
 
-void parseOptions(int argc, char **argv) {
+/* Returns number of consumed options. */
+int parseOptions(int argc, const char **argv) {
     int i;
+    int lastarg;
+    int exit_status = 1;
 
     for (i = 1; i < argc; i++) {
-        int lastarg = i==argc-1;
-        
-        if (!strcmp(argv[i],"-c") && !lastarg) {
-            config.numclients = atoi(argv[i+1]);
-            i++;
-        } else if (!strcmp(argv[i],"-n") && !lastarg) {
-            config.requests = atoi(argv[i+1]);
-            i++;
-        } else if (!strcmp(argv[i],"-k") && !lastarg) {
-            config.keepalive = atoi(argv[i+1]);
-            i++;
-        } else if (!strcmp(argv[i],"-h") && !lastarg) {
-            config.hostip = argv[i+1];
-            i++;
-        } else if (!strcmp(argv[i],"-p") && !lastarg) {
-            config.hostport = atoi(argv[i+1]);
-            i++;
-        } else if (!strcmp(argv[i],"-s") && !lastarg) {
-            config.hostsocket = argv[i+1];
-            i++;
-        } else if (!strcmp(argv[i],"-d") && !lastarg) {
-            config.datasize = atoi(argv[i+1]);
-            i++;
+        lastarg = (i == (argc-1));
+
+        if (!strcmp(argv[i],"-c")) {
+            if (lastarg) goto invalid;
+            config.numclients = atoi(argv[++i]);
+        } else if (!strcmp(argv[i],"-n")) {
+            if (lastarg) goto invalid;
+            config.requests = atoi(argv[++i]);
+        } else if (!strcmp(argv[i],"-k")) {
+            if (lastarg) goto invalid;
+            config.keepalive = atoi(argv[++i]);
+        } else if (!strcmp(argv[i],"-h")) {
+            if (lastarg) goto invalid;
+            config.hostip = strdup(argv[++i]);
+        } else if (!strcmp(argv[i],"-p")) {
+            if (lastarg) goto invalid;
+            config.hostport = atoi(argv[++i]);
+        } else if (!strcmp(argv[i],"-s")) {
+            if (lastarg) goto invalid;
+            config.hostsocket = strdup(argv[++i]);
+        } else if (!strcmp(argv[i],"-d")) {
+            if (lastarg) goto invalid;
+            config.datasize = atoi(argv[++i]);
             if (config.datasize < 1) config.datasize=1;
             if (config.datasize > 1024*1024) config.datasize = 1024*1024;
-        } else if (!strcmp(argv[i],"-r") && !lastarg) {
+        } else if (!strcmp(argv[i],"-r")) {
+            if (lastarg) goto invalid;
             config.randomkeys = 1;
-            config.randomkeys_keyspacelen = atoi(argv[i+1]);
+            config.randomkeys_keyspacelen = atoi(argv[++i]);
             if (config.randomkeys_keyspacelen < 0)
                 config.randomkeys_keyspacelen = 0;
-            i++;
         } else if (!strcmp(argv[i],"-q")) {
             config.quiet = 1;
         } else if (!strcmp(argv[i],"-l")) {
             config.loop = 1;
-        } else if (!strcmp(argv[i],"-D")) {
-            config.debug = 1;
         } else if (!strcmp(argv[i],"-I")) {
             config.idlemode = 1;
+        } else if (!strcmp(argv[i],"--help")) {
+            exit_status = 0;
+            goto usage;
         } else {
-            printf("Wrong option '%s' or option argument missing\n\n",argv[i]);
-            printf("Usage: redis-benchmark [-h <host>] [-p <port>] [-c <clients>] [-n <requests]> [-k <boolean>]\n\n");
-            printf(" -h <hostname>      Server hostname (default 127.0.0.1)\n");
-            printf(" -p <port>          Server port (default 6379)\n");
-            printf(" -s <socket>        Server socket (overrides host and port)\n");
-            printf(" -c <clients>       Number of parallel connections (default 50)\n");
-            printf(" -n <requests>      Total number of requests (default 10000)\n");
-            printf(" -d <size>          Data size of SET/GET value in bytes (default 2)\n");
-            printf(" -k <boolean>       1=keep alive 0=reconnect (default 1)\n");
-            printf(" -r <keyspacelen>   Use random keys for SET/GET/INCR, random values for SADD\n");
-            printf("  Using this option the benchmark will get/set keys\n");
-            printf("  in the form mykey_rand000000012456 instead of constant\n");
-            printf("  keys, the <keyspacelen> argument determines the max\n");
-            printf("  number of values for the random number. For instance\n");
-            printf("  if set to 10 only rand000000000000 - rand000000000009\n");
-            printf("  range will be allowed.\n");
-            printf(" -q                 Quiet. Just show query/sec values\n");
-            printf(" -l                 Loop. Run the tests forever\n");
-            printf(" -I                 Idle mode. Just open N idle connections and wait.\n");
-            printf(" -D                 Debug mode. more verbose.\n");
-            exit(1);
+            /* Assume the user meant to provide an option when the arg starts
+             * with a dash. We're done otherwise and should use the remainder
+             * as the command and arguments for running the benchmark. */
+            if (argv[i][0] == '-') goto invalid;
+            return i;
         }
     }
+
+    return i;
+
+invalid:
+    printf("Invalid option \"%s\" or option argument missing\n\n",argv[i]);
+
+usage:
+    printf("Usage: redis-benchmark [-h <host>] [-p <port>] [-c <clients>] [-n <requests]> [-k <boolean>]\n\n");
+    printf(" -h <hostname>      Server hostname (default 127.0.0.1)\n");
+    printf(" -p <port>          Server port (default 6379)\n");
+    printf(" -s <socket>        Server socket (overrides host and port)\n");
+    printf(" -c <clients>       Number of parallel connections (default 50)\n");
+    printf(" -n <requests>      Total number of requests (default 10000)\n");
+    printf(" -d <size>          Data size of SET/GET value in bytes (default 2)\n");
+    printf(" -k <boolean>       1=keep alive 0=reconnect (default 1)\n");
+    printf(" -r <keyspacelen>   Use random keys for SET/GET/INCR, random values for SADD\n");
+    printf("  Using this option the benchmark will get/set keys\n");
+    printf("  in the form mykey_rand000000012456 instead of constant\n");
+    printf("  keys, the <keyspacelen> argument determines the max\n");
+    printf("  number of values for the random number. For instance\n");
+    printf("  if set to 10 only rand000000000000 - rand000000000009\n");
+    printf("  range will be allowed.\n");
+    printf(" -q                 Quiet. Just show query/sec values\n");
+    printf(" -l                 Loop. Run the tests forever\n");
+    printf(" -I                 Idle mode. Just open N idle connections and wait.\n");
+    exit(exit_status);
 }
 
 int showThroughput(struct aeEventLoop *eventLoop, long long id, void *clientData) {
@@ -409,14 +422,16 @@ int showThroughput(struct aeEventLoop *eventLoop, long long id, void *clientData
     return 250; /* every 250ms */
 }
 
-int main(int argc, char **argv) {
+int main(int argc, const char **argv) {
     int i;
+    char *data, *cmd;
+    int len;
+
     client c;
 
     signal(SIGHUP, SIG_IGN);
     signal(SIGPIPE, SIG_IGN);
 
-    config.debug = 0;
     config.numclients = 50;
     config.requests = 10000;
     config.liveclients = 0;
@@ -436,7 +451,10 @@ int main(int argc, char **argv) {
     config.hostport = 6379;
     config.hostsocket = NULL;
 
-    parseOptions(argc,argv);
+    i = parseOptions(argc,argv);
+    argc -= i;
+    argv += i;
+
     config.latency = zmalloc(sizeof(long long)*config.requests);
 
     if (config.keepalive == 0) {
@@ -451,10 +469,25 @@ int main(int argc, char **argv) {
         /* and will wait for every */
     }
 
-    do {
-        char *data, *cmd;
-        int len;
+    /* Run benchmark with command in the remainder of the arguments. */
+    if (argc) {
+        sds title = sdsnew(argv[0]);
+        for (i = 1; i < argc; i++) {
+            title = sdscatlen(title, " ", 1);
+            title = sdscatlen(title, (char*)argv[i], strlen(argv[i]));
+        }
+
+        do {
+            len = redisFormatCommandArgv(&cmd,argc,argv,NULL);
+            benchmark(title,cmd,len);
+            free(cmd);
+        } while(config.loop);
 
+        return 0;
+    }
+
+    /* Run default benchmark suite. */
+    do {
         data = zmalloc(config.datasize+1);
         memset(data,'x',config.datasize);
         data[config.datasize] = '\0';