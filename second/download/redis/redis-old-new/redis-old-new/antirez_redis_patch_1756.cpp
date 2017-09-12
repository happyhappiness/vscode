@@ -45,10 +45,6 @@
 #include "adlist.h"
 #include "zmalloc.h"
 
-#define CLIENT_CONNECTING 0
-#define CLIENT_SENDQUERY 1
-#define CLIENT_READREPLY 2
-
 #define REDIS_NOTUSED(V) ((void) V)
 
 static struct config {
@@ -78,10 +74,10 @@ static struct config {
 
 typedef struct _client {
     redisContext *context;
-    int state;
     sds obuf;
+    char *randptr[10]; /* needed for MSET against 10 keys */
+    size_t randlen;
     unsigned int written; /* bytes of 'obuf' already written */
-    int replytype;
     long long start; /* start time of a request */
     long long latency; /* request latency */
 } *client;
@@ -139,22 +135,17 @@ static void resetClient(client c) {
     aeDeleteFileEvent(config.el,c->context->fd,AE_READABLE);
     aeCreateFileEvent(config.el,c->context->fd,AE_WRITABLE,writeHandler,c);
     c->written = 0;
-    c->state = CLIENT_SENDQUERY;
-    c->start = ustime();
-    c->latency = -1;
 }
 
 static void randomizeClientKey(client c) {
-    char *p;
     char buf[32];
-    long r;
-
-    p = strstr(c->obuf, "_rand");
-    if (!p) return;
-    p += 5;
-    r = random() % config.randomkeys_keyspacelen;
-    sprintf(buf,"%ld",r);
-    memcpy(p,buf,strlen(buf));
+    size_t i, r;
+
+    for (i = 0; i < c->randlen; i++) {
+        r = random() % config.randomkeys_keyspacelen;
+        snprintf(buf,sizeof(buf),"%012lu",r);
+        memcpy(c->randptr[i],buf,12);
+    }
 }
 
 static void clientDone(client c) {
@@ -165,7 +156,6 @@ static void clientDone(client c) {
     }
     if (config.keepalive) {
         resetClient(c);
-        if (config.randomkeys) randomizeClientKey(c);
     } else {
         config.liveclients--;
         createMissingClients(c);
@@ -195,6 +185,11 @@ static void readHandler(aeEventLoop *el, int fd, void *privdata, int mask) {
             exit(1);
         }
         if (reply != NULL) {
+            if (reply == (void*)REDIS_REPLY_ERROR) {
+                fprintf(stderr,"Unexpected error reply, exiting...\n");
+                exit(1);
+            }
+
             if (config.donerequests < config.requests)
                 config.latency[config.donerequests++] = c->latency;
             clientDone(c);
@@ -208,11 +203,13 @@ static void writeHandler(aeEventLoop *el, int fd, void *privdata, int mask) {
     REDIS_NOTUSED(fd);
     REDIS_NOTUSED(mask);
 
-    if (c->state == CLIENT_CONNECTING) {
-        c->state = CLIENT_SENDQUERY;
+    /* When nothing was written yet, randomize keys and set start time. */
+    if (c->written == 0) {
+        if (config.randomkeys) randomizeClientKey(c);
         c->start = ustime();
         c->latency = -1;
     }
+
     if (sdslen(c->obuf) > c->written) {
         void *ptr = c->obuf+c->written;
         int nwritten = write(c->context->fd,ptr,sdslen(c->obuf)-c->written);
@@ -226,12 +223,11 @@ static void writeHandler(aeEventLoop *el, int fd, void *privdata, int mask) {
         if (sdslen(c->obuf) == c->written) {
             aeDeleteFileEvent(config.el,c->context->fd,AE_WRITABLE);
             aeCreateFileEvent(config.el,c->context->fd,AE_READABLE,readHandler,c);
-            c->state = CLIENT_READREPLY;
         }
     }
 }
 
-static client createClient(int replytype) {
+static client createClient(char *cmd, int len) {
     client c = zmalloc(sizeof(struct _client));
     if (config.hostsocket == NULL) {
         c->context = redisConnectNonBlock(config.hostip,config.hostport);
@@ -246,10 +242,22 @@ static client createClient(int replytype) {
             fprintf(stderr,"%s: %s\n",config.hostsocket,c->context->errstr);
         exit(1);
     }
-    c->replytype = replytype;
-    c->state = CLIENT_CONNECTING;
-    c->obuf = sdsempty();
+    c->obuf = sdsnewlen(cmd,len);
+    c->randlen = 0;
     c->written = 0;
+
+    /* Find substrings in the output buffer that need to be randomized. */
+    if (config.randomkeys) {
+        char *p = c->obuf, *newline;
+        while ((p = strstr(p,":rand:")) != NULL) {
+            newline = strstr(p,"\r\n");
+            assert(newline-(p+6) == 12); /* 12 chars for randomness */
+            assert(c->randlen < (signed)(sizeof(c->randptr)/sizeof(char*)));
+            c->randptr[c->randlen++] = p+6;
+            p = newline+2;
+        }
+    }
+
     redisSetReplyObjectFunctions(c->context,NULL);
     aeCreateFileEvent(config.el,c->context->fd,AE_WRITABLE,writeHandler,c);
     listAddNodeTail(config.clients,c);
@@ -258,11 +266,16 @@ static client createClient(int replytype) {
 }
 
 static void createMissingClients(client c) {
+    int n = 0;
+
     while(config.liveclients < config.numclients) {
-        client new = createClient(c->replytype);
-        sdsfree(new->obuf);
-        new->obuf = sdsdup(c->obuf);
-        if (config.randomkeys) randomizeClientKey(c);
+        createClient(c->obuf,sdslen(c->obuf));
+
+        /* Listen backlog is quite limited on most systems */
+        if (++n > 64) {
+            usleep(50000);
+            n = 0;
+        }
     }
 }
 
@@ -298,14 +311,19 @@ static void showLatencyReport(void) {
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
+    c = createClient(cmd,len);
+    createMissingClients(c);
+
+    config.start = mstime();
+    aeMain(config.el);
     config.totlatency = mstime()-config.start;
+
     showLatencyReport();
     freeAllClients();
 }
@@ -392,6 +410,7 @@ int showThroughput(struct aeEventLoop *eventLoop, long long id, void *clientData
 }
 
 int main(int argc, char **argv) {
+    int i;
     client c;
 
     signal(SIGHUP, SIG_IGN);
@@ -426,136 +445,83 @@ int main(int argc, char **argv) {
 
     if (config.idlemode) {
         printf("Creating %d idle connections and waiting forever (Ctrl+C when done)\n", config.numclients);
-        prepareForBenchmark("IDLE");
-        c = createClient(0); /* will never receive a reply */
-        c->obuf = sdsempty();
+        c = createClient("",0); /* will never receive a reply */
         createMissingClients(c);
         aeMain(config.el);
         /* and will wait for every */
     }
 
     do {
-        prepareForBenchmark("PING");
-        c = createClient(REDIS_REPLY_STATUS);
-        c->obuf = sdscat(c->obuf,"PING\r\n");
-        createMissingClients(c);
-        aeMain(config.el);
-        endBenchmark();
+        char *data, *cmd;
+        int len;
 
-        prepareForBenchmark("PING (multi bulk)");
-        c = createClient(REDIS_REPLY_STATUS);
-        c->obuf = sdscat(c->obuf,"*1\r\n$4\r\nPING\r\n");
-        createMissingClients(c);
-        aeMain(config.el);
-        endBenchmark();
-
-        prepareForBenchmark("MSET (10 keys, multi bulk)");
-        c = createClient(REDIS_REPLY_ARRAY);
-        c->obuf = sdscatprintf(c->obuf,"*%d\r\n$4\r\nMSET\r\n", 11);
-        {
-            int i;
-            char *data = zmalloc(config.datasize+2);
-            memset(data,'x',config.datasize);
-            for (i = 0; i < 10; i++) {
-                c->obuf = sdscatprintf(c->obuf,"$%d\r\n%s\r\n",config.datasize,data);
-            }
-            zfree(data);
-        }
-        createMissingClients(c);
-        aeMain(config.el);
-        endBenchmark();
-
-        prepareForBenchmark("SET");
-        c = createClient(REDIS_REPLY_STATUS);
-        c->obuf = sdscat(c->obuf,"*3\r\n$3\r\nSET\r\n$20\r\nfoo_rand000000000000\r\n");
-        {
-            char *data = zmalloc(config.datasize+2);
-            memset(data,'x',config.datasize);
-            data[config.datasize] = '\r';
-            data[config.datasize+1] = '\n';
-            c->obuf = sdscatprintf(c->obuf,"$%d\r\n",config.datasize);
-            c->obuf = sdscatlen(c->obuf,data,config.datasize+2);
+        data = zmalloc(config.datasize+1);
+        memset(data,'x',config.datasize);
+        data[config.datasize] = '\0';
+
+        benchmark("PING (inline)","PING\r\n",6);
+
+        len = redisFormatCommand(&cmd,"PING");
+        benchmark("PING",cmd,len);
+        free(cmd);
+
+        const char *argv[21];
+        argv[0] = "MSET";
+        for (i = 1; i < 21; i += 2) {
+            argv[i] = "foo:rand:000000000000";
+            argv[i+1] = data;
         }
-        createMissingClients(c);
-        aeMain(config.el);
-        endBenchmark();
+        len = redisFormatCommandArgv(&cmd,21,argv,NULL);
+        benchmark("MSET (10 keys)",cmd,len);
+        free(cmd);
 
-        prepareForBenchmark("GET");
-        c = createClient(REDIS_REPLY_STRING);
-        c->obuf = sdscat(c->obuf,"GET foo_rand000000000000\r\n");
-        createMissingClients(c);
-        aeMain(config.el);
-        endBenchmark();
+        len = redisFormatCommand(&cmd,"SET foo:rand:000000000000 %s",data);
+        benchmark("SET",cmd,len);
+        free(cmd);
 
-        prepareForBenchmark("INCR");
-        c = createClient(REDIS_REPLY_INTEGER);
-        c->obuf = sdscat(c->obuf,"INCR counter_rand000000000000\r\n");
-        createMissingClients(c);
-        aeMain(config.el);
-        endBenchmark();
+        len = redisFormatCommand(&cmd,"GET foo:rand:000000000000");
+        benchmark("GET",cmd,len);
+        free(cmd);
 
-        prepareForBenchmark("LPUSH");
-        c = createClient(REDIS_REPLY_INTEGER);
-        c->obuf = sdscat(c->obuf,"LPUSH mylist bar\r\n");
-        createMissingClients(c);
-        aeMain(config.el);
-        endBenchmark();
+        len = redisFormatCommand(&cmd,"INCR counter:rand:000000000000");
+        benchmark("INCR",cmd,len);
+        free(cmd);
 
-        prepareForBenchmark("LPOP");
-        c = createClient(REDIS_REPLY_STRING);
-        c->obuf = sdscat(c->obuf,"LPOP mylist\r\n");
-        createMissingClients(c);
-        aeMain(config.el);
-        endBenchmark();
+        len = redisFormatCommand(&cmd,"LPUSH mylist %s",data);
+        benchmark("LPUSH",cmd,len);
+        free(cmd);
 
-        prepareForBenchmark("SADD");
-        c = createClient(REDIS_REPLY_STATUS);
-        c->obuf = sdscat(c->obuf,"SADD myset counter_rand000000000000\r\n");
-        createMissingClients(c);
-        aeMain(config.el);
-        endBenchmark();
+        len = redisFormatCommand(&cmd,"LPOP mylist");
+        benchmark("LPOP",cmd,len);
+        free(cmd);
 
-        prepareForBenchmark("SPOP");
-        c = createClient(REDIS_REPLY_STRING);
-        c->obuf = sdscat(c->obuf,"SPOP myset\r\n");
-        createMissingClients(c);
-        aeMain(config.el);
-        endBenchmark();
+        len = redisFormatCommand(&cmd,"SADD myset counter:rand:000000000000");
+        benchmark("SADD",cmd,len);
+        free(cmd);
 
-        prepareForBenchmark("LPUSH (again, in order to bench LRANGE)");
-        c = createClient(REDIS_REPLY_STATUS);
-        c->obuf = sdscat(c->obuf,"LPUSH mylist bar\r\n");
-        createMissingClients(c);
-        aeMain(config.el);
-        endBenchmark();
+        len = redisFormatCommand(&cmd,"SPOP myset");
+        benchmark("SPOP",cmd,len);
+        free(cmd);
 
-        prepareForBenchmark("LRANGE (first 100 elements)");
-        c = createClient(REDIS_REPLY_ARRAY);
-        c->obuf = sdscat(c->obuf,"LRANGE mylist 0 99\r\n");
-        createMissingClients(c);
-        aeMain(config.el);
-        endBenchmark();
+        len = redisFormatCommand(&cmd,"LPUSH mylist %s",data);
+        benchmark("LPUSH (again, in order to bench LRANGE)",cmd,len);
+        free(cmd);
 
-        prepareForBenchmark("LRANGE (first 300 elements)");
-        c = createClient(REDIS_REPLY_ARRAY);
-        c->obuf = sdscat(c->obuf,"LRANGE mylist 0 299\r\n");
-        createMissingClients(c);
-        aeMain(config.el);
-        endBenchmark();
+        len = redisFormatCommand(&cmd,"LRANGE mylist 0 99");
+        benchmark("LRANGE (first 100 elements)",cmd,len);
+        free(cmd);
 
-        prepareForBenchmark("LRANGE (first 450 elements)");
-        c = createClient(REDIS_REPLY_ARRAY);
-        c->obuf = sdscat(c->obuf,"LRANGE mylist 0 449\r\n");
-        createMissingClients(c);
-        aeMain(config.el);
-        endBenchmark();
+        len = redisFormatCommand(&cmd,"LRANGE mylist 0 299");
+        benchmark("LRANGE (first 300 elements)",cmd,len);
+        free(cmd);
 
-        prepareForBenchmark("LRANGE (first 600 elements)");
-        c = createClient(REDIS_REPLY_ARRAY);
-        c->obuf = sdscat(c->obuf,"LRANGE mylist 0 599\r\n");
-        createMissingClients(c);
-        aeMain(config.el);
-        endBenchmark();
+        len = redisFormatCommand(&cmd,"LRANGE mylist 0 449");
+        benchmark("LRANGE (first 450 elements)",cmd,len);
+        free(cmd);
+
+        len = redisFormatCommand(&cmd,"LRANGE mylist 0 599");
+        benchmark("LRANGE (first 600 elements)",cmd,len);
+        free(cmd);
 
         printf("\n");
     } while(config.loop);