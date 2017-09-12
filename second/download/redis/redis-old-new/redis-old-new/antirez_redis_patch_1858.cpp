@@ -45,17 +45,10 @@
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
@@ -87,16 +80,27 @@ typedef struct _client {
     redisContext *context;
     int state;
     sds obuf;
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
@@ -136,7 +140,8 @@ static void resetClient(client c) {
     aeCreateFileEvent(config.el,c->context->fd,AE_WRITABLE,writeHandler,c);
     c->written = 0;
     c->state = CLIENT_SENDQUERY;
-    c->start = mstime();
+    c->start = ustime();
+    c->latency = -1;
 }
 
 static void randomizeClientKey(client c) {
@@ -153,12 +158,6 @@ static void randomizeClientKey(client c) {
 }
 
 static void clientDone(client c) {
-    long long latency;
-    config.donerequests ++;
-    latency = mstime() - c->start;
-    if (latency > MAX_LATENCY) latency = MAX_LATENCY;
-    config.latency[latency]++;
-
     if (config.donerequests == config.requests) {
         freeClient(c);
         aeStop(config.el);
@@ -182,6 +181,11 @@ static void readHandler(aeEventLoop *el, int fd, void *privdata, int mask) {
     REDIS_NOTUSED(fd);
     REDIS_NOTUSED(mask);
 
+    /* Calculate latency only for the first read event. This means that the
+     * server already sent the reply and we need to parse it. Parsing overhead
+     * is not part of the latency, so calculate it only once, here. */
+    if (c->latency < 0) c->latency = ustime()-(c->start);
+
     if (redisBufferRead(c->context) != REDIS_OK) {
         fprintf(stderr,"Error: %s\n",c->context->errstr);
         exit(1);
@@ -190,8 +194,11 @@ static void readHandler(aeEventLoop *el, int fd, void *privdata, int mask) {
             fprintf(stderr,"Error: %s\n",c->context->errstr);
             exit(1);
         }
-        if (reply != NULL)
+        if (reply != NULL) {
+            if (config.donerequests < config.requests)
+                config.latency[config.donerequests++] = c->latency;
             clientDone(c);
+        }
     }
 }
 
@@ -203,7 +210,8 @@ static void writeHandler(aeEventLoop *el, int fd, void *privdata, int mask) {
 
     if (c->state == CLIENT_CONNECTING) {
         c->state = CLIENT_SENDQUERY;
-        c->start = mstime();
+        c->start = ustime();
+        c->latency = -1;
     }
     if (sdslen(c->obuf) > c->written) {
         void *ptr = c->obuf+c->written;
@@ -258,8 +266,12 @@ static void createMissingClients(client c) {
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
@@ -271,11 +283,13 @@ static void showLatencyReport(void) {
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
@@ -285,7 +299,6 @@ static void showLatencyReport(void) {
 }
 
 static void prepareForBenchmark(char *title) {
-    memset(config.latency,0,sizeof(int)*(MAX_LATENCY+1));
     config.title = title;
     config.start = mstime();
     config.donerequests = 0;
@@ -400,13 +413,12 @@ int main(int argc, char **argv) {
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