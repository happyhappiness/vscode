@@ -62,6 +62,7 @@ static struct config {
     int randomkeys;
     int randomkeys_keyspacelen;
     int keepalive;
+    int pipeline;
     long long start;
     long long totlatency;
     long long *latency;
@@ -82,6 +83,7 @@ typedef struct _client {
     unsigned int written; /* bytes of 'obuf' already written */
     long long start; /* start time of a request */
     long long latency; /* request latency */
+    int pending;    /* Number of pending requests (sent but no reply received) */
 } *client;
 
 /* Prototypes */
@@ -137,6 +139,7 @@ static void resetClient(client c) {
     aeDeleteFileEvent(config.el,c->context->fd,AE_READABLE);
     aeCreateFileEvent(config.el,c->context->fd,AE_WRITABLE,writeHandler,c);
     c->written = 0;
+    c->pending = config.pipeline;
 }
 
 static void randomizeClientKey(client c) {
@@ -182,19 +185,24 @@ static void readHandler(aeEventLoop *el, int fd, void *privdata, int mask) {
         fprintf(stderr,"Error: %s\n",c->context->errstr);
         exit(1);
     } else {
-        if (redisGetReply(c->context,&reply) != REDIS_OK) {
-            fprintf(stderr,"Error: %s\n",c->context->errstr);
-            exit(1);
-        }
-        if (reply != NULL) {
-            if (reply == (void*)REDIS_REPLY_ERROR) {
-                fprintf(stderr,"Unexpected error reply, exiting...\n");
+        while(c->pending) {
+            if (redisGetReply(c->context,&reply) != REDIS_OK) {
+                fprintf(stderr,"Error: %s\n",c->context->errstr);
                 exit(1);
             }
-
-            if (config.requests_finished < config.requests)
-                config.latency[config.requests_finished++] = c->latency;
-            clientDone(c);
+            if (reply != NULL) {
+                if (reply == (void*)REDIS_REPLY_ERROR) {
+                    fprintf(stderr,"Unexpected error reply, exiting...\n");
+                    exit(1);
+                }
+
+                if (config.requests_finished < config.requests)
+                    config.latency[config.requests_finished++] = c->latency;
+                c->pending--;
+                if (c->pending == 0) clientDone(c);
+            } else {
+                break;
+            }
         }
     }
 }
@@ -236,8 +244,10 @@ static void writeHandler(aeEventLoop *el, int fd, void *privdata, int mask) {
     }
 }
 
-static client createClient(const char *cmd, size_t len) {
+static client createClient(char *cmd, size_t len) {
+    int j;
     client c = zmalloc(sizeof(struct _client));
+
     if (config.hostsocket == NULL) {
         c->context = redisConnectNonBlock(config.hostip,config.hostport);
     } else {
@@ -251,9 +261,13 @@ static client createClient(const char *cmd, size_t len) {
             fprintf(stderr,"%s: %s\n",config.hostsocket,c->context->errstr);
         exit(1);
     }
-    c->obuf = sdsnewlen(cmd,len);
+    /* Queue N requests accordingly to the pipeline size. */
+    c->obuf = sdsempty();
+    for (j = 0; j < config.pipeline; j++)
+        c->obuf = sdscatlen(c->obuf,cmd,len);
     c->randlen = 0;
     c->written = 0;
+    c->pending = config.pipeline;
 
     /* Find substrings in the output buffer that need to be randomized. */
     if (config.randomkeys) {
@@ -322,7 +336,7 @@ static void showLatencyReport(void) {
     }
 }
 
-static void benchmark(const char *title, const char *cmd, int len) {
+static void benchmark(char *title, char *cmd, int len) {
     client c;
 
     config.title = title;
@@ -372,6 +386,10 @@ int parseOptions(int argc, const char **argv) {
             config.datasize = atoi(argv[++i]);
             if (config.datasize < 1) config.datasize=1;
             if (config.datasize > 1024*1024*1024) config.datasize = 1024*1024*1024;
+        } else if (!strcmp(argv[i],"-P")) {
+            if (lastarg) goto invalid;
+            config.pipeline = atoi(argv[++i]);
+            if (config.pipeline <= 0) config.pipeline=1;
         } else if (!strcmp(argv[i],"-r")) {
             if (lastarg) goto invalid;
             config.randomkeys = 1;
@@ -431,6 +449,7 @@ int parseOptions(int argc, const char **argv) {
 "  number of values for the random number. For instance\n"
 "  if set to 10 only rand:000000000000 - rand:000000000009\n"
 "  range will be allowed.\n"
+" -P <numreq>        Pipeline <numreq> requests. Default 1 (no pipeline).\n"
 " -q                 Quiet. Just show query/sec values\n"
 " --csv              Output in CSV format\n"
 " -l                 Loop. Run the tests forever\n"
@@ -496,6 +515,7 @@ int main(int argc, const char **argv) {
     aeCreateTimeEvent(config.el,1,showThroughput,NULL,NULL);
     config.keepalive = 1;
     config.datasize = 3;
+    config.pipeline = 1;
     config.randomkeys = 0;
     config.randomkeys_keyspacelen = 0;
     config.quiet = 0;