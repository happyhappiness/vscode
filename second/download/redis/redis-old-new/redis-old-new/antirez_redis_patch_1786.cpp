@@ -82,7 +82,6 @@ typedef struct _client {
     sds obuf;
     char *randptr;
     unsigned int written; /* bytes of 'obuf' already written */
-    int replytype;
     long long start; /* start time of a request */
     long long latency; /* request latency */
 } *client;
@@ -250,7 +249,7 @@ static void writeHandler(aeEventLoop *el, int fd, void *privdata, int mask) {
     }
 }
 
-static client createClient(int replytype) {
+static client createClient() {
     client c = zmalloc(sizeof(struct _client));
     if (config.hostsocket == NULL) {
         c->context = redisConnectNonBlock(config.hostip,config.hostport);
@@ -265,7 +264,6 @@ static client createClient(int replytype) {
             fprintf(stderr,"%s: %s\n",config.hostsocket,c->context->errstr);
         exit(1);
     }
-    c->replytype = replytype;
     c->state = CLIENT_CONNECTING;
     c->obuf = NULL;
     c->randptr = (void*)-1;
@@ -281,7 +279,7 @@ static void createMissingClients(client c) {
     int n = 0;
 
     while(config.liveclients < config.numclients) {
-        client new = createClient(c->replytype);
+        client new = createClient();
         new->obuf = sdsdup(c->obuf);
         if (config.randomkeys) randomizeClientKey(c);
 
@@ -291,9 +289,6 @@ static void createMissingClients(client c) {
             n = 0;
         }
     }
-
-    /* Start the timer once the connection are established */
-    config.start = mstime();
 }
 
 static int compareLatency(const void *a, const void *b) {
@@ -328,14 +323,20 @@ static void showLatencyReport(void) {
     }
 }
 
-static void prepareForBenchmark(char *title) {
+static void benchmark(char *title, char *cmd, int len) {
+    client c;
+
     config.title = title;
-    config.start = mstime();
     config.donerequests = 0;
-}
 
-static void endBenchmark(void) {
+    c = createClient();
+    c->obuf = sdsnewlen(cmd,len);
+    createMissingClients(c);
+
+    config.start = mstime();
+    aeMain(config.el);
     config.totlatency = mstime()-config.start;
+
     showLatencyReport();
     freeAllClients();
 }
@@ -457,7 +458,6 @@ int main(int argc, char **argv) {
 
     if (config.idlemode) {
         printf("Creating %d idle connections and waiting forever (Ctrl+C when done)\n", config.numclients);
-        prepareForBenchmark("IDLE");
         c = createClient(0); /* will never receive a reply */
         c->obuf = sdsempty();
         createMissingClients(c);
@@ -473,144 +473,67 @@ int main(int argc, char **argv) {
         memset(data,'x',config.datasize);
         data[config.datasize] = '\0';
 
-        prepareForBenchmark("PING (inline)");
-        c = createClient(REDIS_REPLY_STATUS);
-        c->obuf = sdscat(sdsempty(),"PING\r\n");
-        createMissingClients(c);
-        aeMain(config.el);
-        endBenchmark();
+        benchmark("PING (inline)","PING\r\n",6);
 
-        prepareForBenchmark("PING");
-        c = createClient(REDIS_REPLY_STATUS);
         len = redisFormatCommand(&cmd,"PING");
-        c->obuf = sdsnewlen(cmd,len);
+        benchmark("PING",cmd,len);
+        free(cmd);
+
+        const char *argv[11];
+        argv[0] = "MSET";
+        for (i = 1; i < 11; i++)
+            argv[i] = data;
+        len = redisFormatCommandArgv(&cmd,11,argv,NULL);
+        benchmark("MSET (10 keys)",cmd,len);
         free(cmd);
-        createMissingClients(c);
-        aeMain(config.el);
-        endBenchmark();
-
-        prepareForBenchmark("MSET (10 keys)");
-        c = createClient(REDIS_REPLY_ARRAY);
-        {
-            const char *argv[11];
-            argv[0] = "MSET";
-            for (i = 1; i < 11; i++)
-                argv[i] = data;
-            len = redisFormatCommandArgv(&cmd,11,argv,NULL);
-            c->obuf = sdsnewlen(cmd,len);
-            free(cmd);
-        }
-        createMissingClients(c);
-        aeMain(config.el);
-        endBenchmark();
 
-        prepareForBenchmark("SET");
-        c = createClient(REDIS_REPLY_STATUS);
         len = redisFormatCommand(&cmd,"SET foo:rand:000000000000 %s",data);
-        c->obuf = sdsnewlen(cmd,len);
+        benchmark("SET",cmd,len);
         free(cmd);
-        createMissingClients(c);
-        aeMain(config.el);
-        endBenchmark();
 
-        prepareForBenchmark("GET");
-        c = createClient(REDIS_REPLY_STRING);
         len = redisFormatCommand(&cmd,"GET foo:rand:000000000000");
-        c->obuf = sdsnewlen(cmd,len);
+        benchmark("GET",cmd,len);
         free(cmd);
-        createMissingClients(c);
-        aeMain(config.el);
-        endBenchmark();
 
-        prepareForBenchmark("INCR");
-        c = createClient(REDIS_REPLY_INTEGER);
         len = redisFormatCommand(&cmd,"INCR counter:rand:000000000000");
-        c->obuf = sdsnewlen(cmd,len);
+        benchmark("INCR",cmd,len);
         free(cmd);
-        createMissingClients(c);
-        aeMain(config.el);
-        endBenchmark();
 
-        prepareForBenchmark("LPUSH");
-        c = createClient(REDIS_REPLY_INTEGER);
         len = redisFormatCommand(&cmd,"LPUSH mylist %s",data);
-        c->obuf = sdsnewlen(cmd,len);
+        benchmark("LPUSH",cmd,len);
         free(cmd);
-        createMissingClients(c);
-        aeMain(config.el);
-        endBenchmark();
 
-        prepareForBenchmark("LPOP");
-        c = createClient(REDIS_REPLY_STRING);
         len = redisFormatCommand(&cmd,"LPOP mylist");
-        c->obuf = sdsnewlen(cmd,len);
+        benchmark("LPOP",cmd,len);
         free(cmd);
-        createMissingClients(c);
-        aeMain(config.el);
-        endBenchmark();
 
-        prepareForBenchmark("SADD");
-        c = createClient(REDIS_REPLY_STATUS);
         len = redisFormatCommand(&cmd,"SADD myset counter:rand:000000000000");
-        c->obuf = sdsnewlen(cmd,len);
+        benchmark("SADD",cmd,len);
         free(cmd);
-        createMissingClients(c);
-        aeMain(config.el);
-        endBenchmark();
 
-        prepareForBenchmark("SPOP");
-        c = createClient(REDIS_REPLY_STRING);
         len = redisFormatCommand(&cmd,"SPOP myset");
-        c->obuf = sdsnewlen(cmd,len);
+        benchmark("SPOP",cmd,len);
         free(cmd);
-        createMissingClients(c);
-        aeMain(config.el);
-        endBenchmark();
 
-        prepareForBenchmark("LPUSH (again, in order to bench LRANGE)");
-        c = createClient(REDIS_REPLY_STATUS);
         len = redisFormatCommand(&cmd,"LPUSH mylist %s",data);
-        c->obuf = sdsnewlen(cmd,len);
+        benchmark("LPUSH (again, in order to bench LRANGE)",cmd,len);
         free(cmd);
-        createMissingClients(c);
-        aeMain(config.el);
-        endBenchmark();
 
-        prepareForBenchmark("LRANGE (first 100 elements)");
-        c = createClient(REDIS_REPLY_ARRAY);
         len = redisFormatCommand(&cmd,"LRANGE mylist 0 99");
-        c->obuf = sdsnewlen(cmd,len);
+        benchmark("LRANGE (first 100 elements)",cmd,len);
         free(cmd);
-        createMissingClients(c);
-        aeMain(config.el);
-        endBenchmark();
 
-        prepareForBenchmark("LRANGE (first 300 elements)");
-        c = createClient(REDIS_REPLY_ARRAY);
         len = redisFormatCommand(&cmd,"LRANGE mylist 0 299");
-        c->obuf = sdsnewlen(cmd,len);
+        benchmark("LRANGE (first 300 elements)",cmd,len);
         free(cmd);
-        createMissingClients(c);
-        aeMain(config.el);
-        endBenchmark();
 
-        prepareForBenchmark("LRANGE (first 450 elements)");
-        c = createClient(REDIS_REPLY_ARRAY);
         len = redisFormatCommand(&cmd,"LRANGE mylist 0 449");
-        c->obuf = sdsnewlen(cmd,len);
+        benchmark("LRANGE (first 450 elements)",cmd,len);
         free(cmd);
-        createMissingClients(c);
-        aeMain(config.el);
-        endBenchmark();
 
-        prepareForBenchmark("LRANGE (first 600 elements)");
-        c = createClient(REDIS_REPLY_ARRAY);
         len = redisFormatCommand(&cmd,"LRANGE mylist 0 599");
-        c->obuf = sdsnewlen(cmd,len);
+        benchmark("LRANGE (first 600 elements)",cmd,len);
         free(cmd);
-        createMissingClients(c);
-        aeMain(config.el);
-        endBenchmark();
 
         printf("\n");
     } while(config.loop);