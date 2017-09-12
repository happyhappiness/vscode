@@ -59,6 +59,7 @@
 #define REDIS_NOTUSED(V) ((void) V)
 
 static struct config {
+    int debug;
     int numclients;
     int requests;
     int liveclients;
@@ -86,6 +87,7 @@ typedef struct _client {
     sds ibuf;
     int mbulk;          /* Number of elements in an mbulk reply */
     int readlen;        /* readlen == -1 means read a single line */
+    int totreceived;
     unsigned int written;        /* bytes of 'obuf' already written */
     int replytype;
     long long start;    /* start time in milliseconds */
@@ -141,6 +143,7 @@ static void resetClient(client c) {
                   c->replytype == REPLY_MBULK) ? -1 : 0;
     c->mbulk = -1;
     c->written = 0;
+    c->totreceived = 0;
     c->state = CLIENT_SENDQUERY;
     c->start = mstime();
     createMissingClients(c);
@@ -174,12 +177,18 @@ static void prepareClientForReply(client c, int type) {
 }
 
 static void clientDone(client c) {
+    static int last_tot_received = 1;
+
     long long latency;
     config.donerequests ++;
     latency = mstime() - c->start;
     if (latency > MAX_LATENCY) latency = MAX_LATENCY;
     config.latency[latency]++;
 
+    if (config.debug && last_tot_received != c->totreceived) {
+        printf("Tot bytes received: %d\n", c->totreceived);
+        last_tot_received = c->totreceived;
+    }
     if (config.donerequests == config.requests) {
         freeClient(c);
         aeStop(config.el);
@@ -216,6 +225,7 @@ static void readHandler(aeEventLoop *el, int fd, void *privdata, int mask)
         freeClient(c);
         return;
     }
+    c->totreceived += nread;
     c->ibuf = sdscatlen(c->ibuf,buf,nread);
 
 processdata:
@@ -340,6 +350,7 @@ static client createClient(void) {
     c->mbulk = -1;
     c->readlen = 0;
     c->written = 0;
+    c->totreceived = 0;
     c->state = CLIENT_CONNECTING;
     aeCreateFileEvent(config.el, c->fd, AE_WRITABLE, writeHandler, c, NULL);
     config.liveclients++;
@@ -440,6 +451,8 @@ void parseOptions(int argc, char **argv) {
             config.quiet = 1;
         } else if (!strcmp(argv[i],"-l")) {
             config.loop = 1;
+        } else if (!strcmp(argv[i],"-D")) {
+            config.debug = 1;
         } else {
             printf("Wrong option '%s' or option argument missing\n\n",argv[i]);
             printf("Usage: redis-benchmark [-h <host>] [-p <port>] [-c <clients>] [-n <requests]> [-k <boolean>]\n\n");
@@ -458,6 +471,7 @@ void parseOptions(int argc, char **argv) {
             printf("  range will be allowed.\n");
             printf(" -q                 Quiet. Just show query/sec values\n");
             printf(" -l                 Loop. Run the tests forever\n");
+            printf(" -D                 Debug mode. more verbose.\n");
             exit(1);
         }
     }
@@ -469,6 +483,7 @@ int main(int argc, char **argv) {
     signal(SIGHUP, SIG_IGN);
     signal(SIGPIPE, SIG_IGN);
 
+    config.debug = 0;
     config.numclients = 50;
     config.requests = 10000;
     config.liveclients = 0;