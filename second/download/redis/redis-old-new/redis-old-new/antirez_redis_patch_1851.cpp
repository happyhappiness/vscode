@@ -40,22 +40,15 @@
 #include <assert.h>
 
 #include "ae.h"
-#include "anet.h"
+#include "hiredis.h"
 #include "sds.h"
 #include "adlist.h"
 #include "zmalloc.h"
 
-#define REPLY_INT 0
-#define REPLY_RETCODE 1
-#define REPLY_BULK 2
-#define REPLY_MBULK 3
-
 #define CLIENT_CONNECTING 0
 #define CLIENT_SENDQUERY 1
 #define CLIENT_READREPLY 2
 
-#define MAX_LATENCY 5000
-
 #define REDIS_NOTUSED(V) ((void) V)
 
 static struct config {
@@ -75,7 +68,7 @@ static struct config {
     int keepalive;
     long long start;
     long long totlatency;
-    int *latency;
+    long long *latency;
     char *title;
     list *clients;
     int quiet;
@@ -84,23 +77,30 @@ static struct config {
 } config;
 
 typedef struct _client {
+    redisContext *context;
     int state;
-    int fd;
     sds obuf;
-    sds ibuf;
-    int mbulk;          /* Number of elements in an mbulk reply */
-    int readlen;        /* readlen == -1 means read a single line */
-    int totreceived;
-    unsigned int written;        /* bytes of 'obuf' already written */
+    unsigned int written; /* bytes of 'obuf' already written */
     int replytype;
-    long long start;    /* start time in milliseconds */
+    long long start; /* start time of a request */
+    long long latency; /* request latency */
 } *client;
 
 /* Prototypes */
 static void writeHandler(aeEventLoop *el, int fd, void *privdata, int mask);
 static void createMissingClients(client c);
 
 /* Implementation */
+static long long ustime(void) {
+    struct timeval tv;
+    long long ust;
+
+    gettimeofday(&tv, NULL);
+    ust = ((long)tv.tv_sec)*1000000;
+    ust += tv.tv_usec;
+    return ust;
+}
+
 static long long mstime(void) {
     struct timeval tv;
     long long mst;
@@ -113,12 +113,10 @@ static long long mstime(void) {
 
 static void freeClient(client c) {
     listNode *ln;
-
-    aeDeleteFileEvent(config.el,c->fd,AE_WRITABLE);
-    aeDeleteFileEvent(config.el,c->fd,AE_READABLE);
-    sdsfree(c->ibuf);
+    aeDeleteFileEvent(config.el,c->context->fd,AE_WRITABLE);
+    aeDeleteFileEvent(config.el,c->context->fd,AE_READABLE);
+    redisFree(c->context);
     sdsfree(c->obuf);
-    close(c->fd);
     zfree(c);
     config.liveclients--;
     ln = listSearchKey(config.clients,c);
@@ -137,19 +135,13 @@ static void freeAllClients(void) {
 }
 
 static void resetClient(client c) {
-    aeDeleteFileEvent(config.el,c->fd,AE_WRITABLE);
-    aeDeleteFileEvent(config.el,c->fd,AE_READABLE);
-    aeCreateFileEvent(config.el,c->fd, AE_WRITABLE,writeHandler,c);
-    sdsfree(c->ibuf);
-    c->ibuf = sdsempty();
-    c->readlen = (c->replytype == REPLY_BULK ||
-                  c->replytype == REPLY_MBULK) ? -1 : 0;
-    c->mbulk = -1;
+    aeDeleteFileEvent(config.el,c->context->fd,AE_WRITABLE);
+    aeDeleteFileEvent(config.el,c->context->fd,AE_READABLE);
+    aeCreateFileEvent(config.el,c->context->fd,AE_WRITABLE,writeHandler,c);
     c->written = 0;
-    c->totreceived = 0;
     c->state = CLIENT_SENDQUERY;
-    c->start = mstime();
-    createMissingClients(c);
+    c->start = ustime();
+    c->latency = -1;
 }
 
 static void randomizeClientKey(client c) {
@@ -165,33 +157,7 @@ static void randomizeClientKey(client c) {
     memcpy(p,buf,strlen(buf));
 }
 
-static void prepareClientForReply(client c, int type) {
-    if (type == REPLY_BULK) {
-        c->replytype = REPLY_BULK;
-        c->readlen = -1;
-    } else if (type == REPLY_MBULK) {
-        c->replytype = REPLY_MBULK;
-        c->readlen = -1;
-        c->mbulk = -1;
-    } else {
-        c->replytype = type;
-        c->readlen = 0;
-    }
-}
-
 static void clientDone(client c) {
-    static int last_tot_received = 1;
-
-    long long latency;
-    config.donerequests ++;
-    latency = mstime() - c->start;
-    if (latency > MAX_LATENCY) latency = MAX_LATENCY;
-    config.latency[latency]++;
-
-    if (config.debug && last_tot_received != c->totreceived) {
-        printf("Tot bytes received: %d\n", c->totreceived);
-        last_tot_received = c->totreceived;
-    }
     if (config.donerequests == config.requests) {
         freeClient(c);
         aeStop(config.el);
@@ -208,139 +174,48 @@ static void clientDone(client c) {
     }
 }
 
-/* Read a length from the buffer pointed to by *p, store the length in *len,
- * and return the number of bytes that the cursor advanced. */
-static int readLen(char *p, int *len) {
-    char *tail = strstr(p,"\r\n");
-    if (tail == NULL)
-        return 0;
-    *tail = '\0';
-    *len = atoi(p+1);
-    return tail+2-p;
-}
-
-static void readHandler(aeEventLoop *el, int fd, void *privdata, int mask)
-{
-    char buf[1024], *p;
-    int nread, pos=0, len=0;
+static void readHandler(aeEventLoop *el, int fd, void *privdata, int mask) {
     client c = privdata;
+    void *reply = NULL;
     REDIS_NOTUSED(el);
     REDIS_NOTUSED(fd);
     REDIS_NOTUSED(mask);
 
-    nread = read(c->fd,buf,sizeof(buf));
-    if (nread == -1) {
-        fprintf(stderr, "Reading from socket: %s\n", strerror(errno));
-        freeClient(c);
-        return;
-    }
-    if (nread == 0) {
-        fprintf(stderr, "EOF from client\n");
-        freeClient(c);
-        return;
-    }
-    c->totreceived += nread;
-    c->ibuf = sdscatlen(c->ibuf,buf,nread);
-    len = sdslen(c->ibuf);
-
-    if (c->replytype == REPLY_INT ||
-        c->replytype == REPLY_RETCODE)
-    {
-        /* Check if the first line is complete. This is everything we need
-         * when waiting for an integer or status code reply.*/
-        if ((p = strstr(c->ibuf,"\r\n")) != NULL)
-            goto done;
-    } else if (c->replytype == REPLY_BULK) {
-        int advance = 0;
-        if (c->readlen < 0) {
-            advance = readLen(c->ibuf+pos,&c->readlen);
-            if (advance) {
-                pos += advance;
-                if (c->readlen == -1) {
-                    goto done;
-                } else {
-                    /* include the trailing \r\n */
-                    c->readlen += 2;
-                }
-            } else {
-                goto skip;
-            }
-        }
-
-        int canconsume;
-        if (c->readlen > 0) {
-            canconsume = c->readlen > (len-pos) ? (len-pos) : c->readlen;
-            c->readlen -= canconsume;
-            pos += canconsume;
-        }
+    /* Calculate latency only for the first read event. This means that the
+     * server already sent the reply and we need to parse it. Parsing overhead
+     * is not part of the latency, so calculate it only once, here. */
+    if (c->latency < 0) c->latency = ustime()-(c->start);
 
-        if (c->readlen == 0)
-            goto done;
-    } else if (c->replytype == REPLY_MBULK) {
-        int advance = 0;
-        if (c->mbulk == -1) {
-            advance = readLen(c->ibuf+pos,&c->mbulk);
-            if (advance) {
-                pos += advance;
-                if (c->mbulk == -1)
-                    goto done;
-            } else {
-                goto skip;
-            }
+    if (redisBufferRead(c->context) != REDIS_OK) {
+        fprintf(stderr,"Error: %s\n",c->context->errstr);
+        exit(1);
+    } else {
+        if (redisGetReply(c->context,&reply) != REDIS_OK) {
+            fprintf(stderr,"Error: %s\n",c->context->errstr);
+            exit(1);
         }
-
-        int canconsume;
-        while(c->mbulk > 0 && pos < len) {
-            if (c->readlen > 0) {
-                canconsume = c->readlen > (len-pos) ? (len-pos) : c->readlen;
-                c->readlen -= canconsume;
-                pos += canconsume;
-                if (c->readlen == 0)
-                    c->mbulk--;
-            } else {
-                advance = readLen(c->ibuf+pos,&c->readlen);
-                if (advance) {
-                    pos += advance;
-                    if (c->readlen == -1) {
-                        c->mbulk--;
-                        continue;
-                    } else {
-                        /* include the trailing \r\n */
-                        c->readlen += 2;
-                    }
-                } else {
-                    goto skip;
-                }
-            }
+        if (reply != NULL) {
+            if (config.donerequests < config.requests)
+                config.latency[config.donerequests++] = c->latency;
+            clientDone(c);
         }
-
-        if (c->mbulk == 0)
-            goto done;
     }
-
-skip:
-    c->ibuf = sdsrange(c->ibuf,pos,-1);
-    return;
-done:
-    clientDone(c);
-    return;
 }
 
-static void writeHandler(aeEventLoop *el, int fd, void *privdata, int mask)
-{
+static void writeHandler(aeEventLoop *el, int fd, void *privdata, int mask) {
     client c = privdata;
     REDIS_NOTUSED(el);
     REDIS_NOTUSED(fd);
     REDIS_NOTUSED(mask);
 
     if (c->state == CLIENT_CONNECTING) {
         c->state = CLIENT_SENDQUERY;
-        c->start = mstime();
+        c->start = ustime();
+        c->latency = -1;
     }
     if (sdslen(c->obuf) > c->written) {
         void *ptr = c->obuf+c->written;
-        int len = sdslen(c->obuf) - c->written;
-        int nwritten = write(c->fd, ptr, len);
+        int nwritten = write(c->context->fd,ptr,sdslen(c->obuf)-c->written);
         if (nwritten == -1) {
             if (errno != EPIPE)
                 fprintf(stderr, "Writing to socket: %s\n", strerror(errno));
@@ -349,54 +224,54 @@ static void writeHandler(aeEventLoop *el, int fd, void *privdata, int mask)
         }
         c->written += nwritten;
         if (sdslen(c->obuf) == c->written) {
-            aeDeleteFileEvent(config.el,c->fd,AE_WRITABLE);
-            aeCreateFileEvent(config.el,c->fd,AE_READABLE,readHandler,c);
+            aeDeleteFileEvent(config.el,c->context->fd,AE_WRITABLE);
+            aeCreateFileEvent(config.el,c->context->fd,AE_READABLE,readHandler,c);
             c->state = CLIENT_READREPLY;
         }
     }
 }
 
-static client createClient(void) {
+static client createClient(int replytype) {
     client c = zmalloc(sizeof(struct _client));
-    char err[ANET_ERR_LEN];
-
-    if (config.hostsocket == NULL)
-        c->fd = anetTcpNonBlockConnect(err,config.hostip,config.hostport);
-    else
-        c->fd = anetUnixNonBlockConnect(err,config.hostsocket);
-
-    if (c->fd == ANET_ERR) {
-        zfree(c);
-        fprintf(stderr,"Connect: %s\n",err);
-        return NULL;
+    if (config.hostsocket == NULL) {
+        c->context = redisConnectNonBlock(config.hostip,config.hostport);
+    } else {
+        c->context = redisConnectUnixNonBlock(config.hostsocket);
+    }
+    if (c->context->err) {
+        fprintf(stderr,"Could not connect to Redis at ");
+        if (config.hostsocket == NULL)
+            fprintf(stderr,"%s:%d: %s\n",config.hostip,config.hostport,c->context->errstr);
+        else
+            fprintf(stderr,"%s: %s\n",config.hostsocket,c->context->errstr);
+        exit(1);
     }
-    anetTcpNoDelay(NULL,c->fd);
+    c->replytype = replytype;
+    c->state = CLIENT_CONNECTING;
     c->obuf = sdsempty();
-    c->ibuf = sdsempty();
-    c->mbulk = -1;
-    c->readlen = 0;
     c->written = 0;
-    c->totreceived = 0;
-    c->state = CLIENT_CONNECTING;
-    aeCreateFileEvent(config.el, c->fd, AE_WRITABLE, writeHandler, c);
-    config.liveclients++;
+    redisSetReplyObjectFunctions(c->context,NULL);
+    aeCreateFileEvent(config.el,c->context->fd,AE_WRITABLE,writeHandler,c);
     listAddNodeTail(config.clients,c);
+    config.liveclients++;
     return c;
 }
 
 static void createMissingClients(client c) {
     while(config.liveclients < config.numclients) {
-        client new = createClient();
-        if (!new) continue;
+        client new = createClient(c->replytype);
         sdsfree(new->obuf);
         new->obuf = sdsdup(c->obuf);
         if (config.randomkeys) randomizeClientKey(c);
-        prepareClientForReply(new,c->replytype);
     }
 }
 
+static int compareLatency(const void *a, const void *b) {
+    return (*(long long*)a)-(*(long long*)b);
+}
+
 static void showLatencyReport(void) {
-    int j, seen = 0;
+    int i, curlat = 0;
     float perc, reqpersec;
 
     reqpersec = (float)config.donerequests/((float)config.totlatency/1000);
@@ -408,11 +283,13 @@ static void showLatencyReport(void) {
         printf("  %d bytes payload\n", config.datasize);
         printf("  keep alive: %d\n", config.keepalive);
         printf("\n");
-        for (j = 0; j <= MAX_LATENCY; j++) {
-            if (config.latency[j]) {
-                seen += config.latency[j];
-                perc = ((float)seen*100)/config.donerequests;
-                printf("%.2f%% <= %d milliseconds\n", perc, j);
+
+        qsort(config.latency,config.requests,sizeof(long long),compareLatency);
+        for (i = 0; i < config.requests; i++) {
+            if (config.latency[i]/1000 != curlat || i == (config.requests-1)) {
+                curlat = config.latency[i]/1000;
+                perc = ((float)(i+1)*100)/config.requests;
+                printf("%.2f%% <= %d milliseconds\n", perc, curlat);
             }
         }
         printf("%.2f requests per second\n\n", reqpersec);
@@ -422,7 +299,6 @@ static void showLatencyReport(void) {
 }
 
 static void prepareForBenchmark(char *title) {
-    memset(config.latency,0,sizeof(int)*(MAX_LATENCY+1));
     config.title = title;
     config.start = mstime();
     config.donerequests = 0;
@@ -450,12 +326,7 @@ void parseOptions(int argc, char **argv) {
             config.keepalive = atoi(argv[i+1]);
             i++;
         } else if (!strcmp(argv[i],"-h") && !lastarg) {
-            char *ip = zmalloc(32);
-            if (anetResolve(NULL,argv[i+1],ip) == ANET_ERR) {
-                printf("Can't resolve %s\n", argv[i]);
-                exit(1);
-            }
-            config.hostip = ip;
+            config.hostip = argv[i+1];
             i++;
         } else if (!strcmp(argv[i],"-p") && !lastarg) {
             config.hostport = atoi(argv[i+1]);
@@ -542,13 +413,12 @@ int main(int argc, char **argv) {
     config.idlemode = 0;
     config.latency = NULL;
     config.clients = listCreate();
-    config.latency = zmalloc(sizeof(int)*(MAX_LATENCY+1));
-
     config.hostip = "127.0.0.1";
     config.hostport = 6379;
     config.hostsocket = NULL;
 
     parseOptions(argc,argv);
+    config.latency = zmalloc(sizeof(long long)*config.requests);
 
     if (config.keepalive == 0) {
         printf("WARNING: keepalive disabled, you probably need 'echo 1 > /proc/sys/net/ipv4/tcp_tw_reuse' for Linux and 'sudo sysctl -w net.inet.tcp.msl=1000' for Mac OS X in order to use a lot of clients/requests\n");
@@ -557,37 +427,30 @@ int main(int argc, char **argv) {
     if (config.idlemode) {
         printf("Creating %d idle connections and waiting forever (Ctrl+C when done)\n", config.numclients);
         prepareForBenchmark("IDLE");
-        c = createClient();
-        if (!c) exit(1);
+        c = createClient(0); /* will never receive a reply */
         c->obuf = sdsempty();
-        prepareClientForReply(c,REPLY_RETCODE); /* will never receive it */
         createMissingClients(c);
         aeMain(config.el);
         /* and will wait for every */
     }
 
     do {
         prepareForBenchmark("PING");
-        c = createClient();
-        if (!c) exit(1);
+        c = createClient(REDIS_REPLY_STATUS);
         c->obuf = sdscat(c->obuf,"PING\r\n");
-        prepareClientForReply(c,REPLY_RETCODE);
         createMissingClients(c);
         aeMain(config.el);
         endBenchmark();
 
         prepareForBenchmark("PING (multi bulk)");
-        c = createClient();
-        if (!c) exit(1);
+        c = createClient(REDIS_REPLY_STATUS);
         c->obuf = sdscat(c->obuf,"*1\r\n$4\r\nPING\r\n");
-        prepareClientForReply(c,REPLY_RETCODE);
         createMissingClients(c);
         aeMain(config.el);
         endBenchmark();
 
         prepareForBenchmark("MSET (10 keys, multi bulk)");
-        c = createClient();
-        if (!c) exit(1);
+        c = createClient(REDIS_REPLY_ARRAY);
         c->obuf = sdscatprintf(c->obuf,"*%d\r\n$4\r\nMSET\r\n", 11);
         {
             int i;
@@ -598,122 +461,98 @@ int main(int argc, char **argv) {
             }
             zfree(data);
         }
-        prepareClientForReply(c,REPLY_RETCODE);
         createMissingClients(c);
         aeMain(config.el);
         endBenchmark();
 
         prepareForBenchmark("SET");
-        c = createClient();
-        if (!c) exit(1);
-        c->obuf = sdscat(c->obuf,"SET foo_rand000000000000 ");
+        c = createClient(REDIS_REPLY_STATUS);
+        c->obuf = sdscat(c->obuf,"*3\r\n$3\r\nSET\r\n$20\r\nfoo_rand000000000000\r\n");
         {
             char *data = zmalloc(config.datasize+2);
             memset(data,'x',config.datasize);
             data[config.datasize] = '\r';
             data[config.datasize+1] = '\n';
+            c->obuf = sdscatprintf(c->obuf,"$%d\r\n",config.datasize);
             c->obuf = sdscatlen(c->obuf,data,config.datasize+2);
         }
-        prepareClientForReply(c,REPLY_RETCODE);
         createMissingClients(c);
         aeMain(config.el);
         endBenchmark();
 
         prepareForBenchmark("GET");
-        c = createClient();
-        if (!c) exit(1);
+        c = createClient(REDIS_REPLY_STRING);
         c->obuf = sdscat(c->obuf,"GET foo_rand000000000000\r\n");
-        prepareClientForReply(c,REPLY_BULK);
         createMissingClients(c);
         aeMain(config.el);
         endBenchmark();
 
         prepareForBenchmark("INCR");
-        c = createClient();
-        if (!c) exit(1);
+        c = createClient(REDIS_REPLY_INTEGER);
         c->obuf = sdscat(c->obuf,"INCR counter_rand000000000000\r\n");
-        prepareClientForReply(c,REPLY_INT);
         createMissingClients(c);
         aeMain(config.el);
         endBenchmark();
 
         prepareForBenchmark("LPUSH");
-        c = createClient();
-        if (!c) exit(1);
+        c = createClient(REDIS_REPLY_INTEGER);
         c->obuf = sdscat(c->obuf,"LPUSH mylist bar\r\n");
-        prepareClientForReply(c,REPLY_INT);
         createMissingClients(c);
         aeMain(config.el);
         endBenchmark();
 
         prepareForBenchmark("LPOP");
-        c = createClient();
-        if (!c) exit(1);
+        c = createClient(REDIS_REPLY_STRING);
         c->obuf = sdscat(c->obuf,"LPOP mylist\r\n");
-        prepareClientForReply(c,REPLY_BULK);
         createMissingClients(c);
         aeMain(config.el);
         endBenchmark();
 
         prepareForBenchmark("SADD");
-        c = createClient();
-        if (!c) exit(1);
+        c = createClient(REDIS_REPLY_STATUS);
         c->obuf = sdscat(c->obuf,"SADD myset counter_rand000000000000\r\n");
-        prepareClientForReply(c,REPLY_RETCODE);
         createMissingClients(c);
         aeMain(config.el);
         endBenchmark();
 
         prepareForBenchmark("SPOP");
-        c = createClient();
-        if (!c) exit(1);
+        c = createClient(REDIS_REPLY_STRING);
         c->obuf = sdscat(c->obuf,"SPOP myset\r\n");
-        prepareClientForReply(c,REPLY_BULK);
         createMissingClients(c);
         aeMain(config.el);
         endBenchmark();
 
         prepareForBenchmark("LPUSH (again, in order to bench LRANGE)");
-        c = createClient();
-        if (!c) exit(1);
+        c = createClient(REDIS_REPLY_STATUS);
         c->obuf = sdscat(c->obuf,"LPUSH mylist bar\r\n");
-        prepareClientForReply(c,REPLY_RETCODE);
         createMissingClients(c);
         aeMain(config.el);
         endBenchmark();
 
         prepareForBenchmark("LRANGE (first 100 elements)");
-        c = createClient();
-        if (!c) exit(1);
+        c = createClient(REDIS_REPLY_ARRAY);
         c->obuf = sdscat(c->obuf,"LRANGE mylist 0 99\r\n");
-        prepareClientForReply(c,REPLY_MBULK);
         createMissingClients(c);
         aeMain(config.el);
         endBenchmark();
 
         prepareForBenchmark("LRANGE (first 300 elements)");
-        c = createClient();
-        if (!c) exit(1);
+        c = createClient(REDIS_REPLY_ARRAY);
         c->obuf = sdscat(c->obuf,"LRANGE mylist 0 299\r\n");
-        prepareClientForReply(c,REPLY_MBULK);
         createMissingClients(c);
         aeMain(config.el);
         endBenchmark();
 
         prepareForBenchmark("LRANGE (first 450 elements)");
-        c = createClient();
-        if (!c) exit(1);
+        c = createClient(REDIS_REPLY_ARRAY);
         c->obuf = sdscat(c->obuf,"LRANGE mylist 0 449\r\n");
-        prepareClientForReply(c,REPLY_MBULK);
         createMissingClients(c);
         aeMain(config.el);
         endBenchmark();
 
         prepareForBenchmark("LRANGE (first 600 elements)");
-        c = createClient();
-        if (!c) exit(1);
+        c = createClient(REDIS_REPLY_ARRAY);
         c->obuf = sdscat(c->obuf,"LRANGE mylist 0 599\r\n");
-        prepareClientForReply(c,REPLY_MBULK);
         createMissingClients(c);
         aeMain(config.el);
         endBenchmark();