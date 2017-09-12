@@ -78,6 +78,7 @@ static struct config {
     list *clients;
     int quiet;
     int loop;
+    int idlemode;
 } config;
 
 typedef struct _client {
@@ -136,7 +137,7 @@ static void freeAllClients(void) {
 static void resetClient(client c) {
     aeDeleteFileEvent(config.el,c->fd,AE_WRITABLE);
     aeDeleteFileEvent(config.el,c->fd,AE_READABLE);
-    aeCreateFileEvent(config.el,c->fd, AE_WRITABLE,writeHandler,c,NULL);
+    aeCreateFileEvent(config.el,c->fd, AE_WRITABLE,writeHandler,c);
     sdsfree(c->ibuf);
     c->ibuf = sdsempty();
     c->readlen = (c->replytype == REPLY_BULK ||
@@ -328,7 +329,7 @@ static void writeHandler(aeEventLoop *el, int fd, void *privdata, int mask)
         c->written += nwritten;
         if (sdslen(c->obuf) == c->written) {
             aeDeleteFileEvent(config.el,c->fd,AE_WRITABLE);
-            aeCreateFileEvent(config.el,c->fd,AE_READABLE,readHandler,c,NULL);
+            aeCreateFileEvent(config.el,c->fd,AE_READABLE,readHandler,c);
             c->state = CLIENT_READREPLY;
         }
     }
@@ -352,7 +353,7 @@ static client createClient(void) {
     c->written = 0;
     c->totreceived = 0;
     c->state = CLIENT_CONNECTING;
-    aeCreateFileEvent(config.el, c->fd, AE_WRITABLE, writeHandler, c, NULL);
+    aeCreateFileEvent(config.el, c->fd, AE_WRITABLE, writeHandler, c);
     config.liveclients++;
     listAddNodeTail(config.clients,c);
     return c;
@@ -451,6 +452,8 @@ void parseOptions(int argc, char **argv) {
             config.loop = 1;
         } else if (!strcmp(argv[i],"-D")) {
             config.debug = 1;
+        } else if (!strcmp(argv[i],"-I")) {
+            config.idlemode = 1;
         } else {
             printf("Wrong option '%s' or option argument missing\n\n",argv[i]);
             printf("Usage: redis-benchmark [-h <host>] [-p <port>] [-c <clients>] [-n <requests]> [-k <boolean>]\n\n");
@@ -469,6 +472,7 @@ void parseOptions(int argc, char **argv) {
             printf("  range will be allowed.\n");
             printf(" -q                 Quiet. Just show query/sec values\n");
             printf(" -l                 Loop. Run the tests forever\n");
+            printf(" -I                 Idle mode. Just open N idle connections and wait.\n");
             printf(" -D                 Debug mode. more verbose.\n");
             exit(1);
         }
@@ -493,6 +497,7 @@ int main(int argc, char **argv) {
     config.randomkeys_keyspacelen = 0;
     config.quiet = 0;
     config.loop = 0;
+    config.idlemode = 0;
     config.latency = NULL;
     config.clients = listCreate();
     config.latency = zmalloc(sizeof(int)*(MAX_LATENCY+1));
@@ -506,6 +511,18 @@ int main(int argc, char **argv) {
         printf("WARNING: keepalive disabled, you probably need 'echo 1 > /proc/sys/net/ipv4/tcp_tw_reuse' for Linux and 'sudo sysctl -w net.inet.tcp.msl=1000' for Mac OS X in order to use a lot of clients/requests\n");
     }
 
+    if (config.idlemode) {
+        printf("Creating %d idle connections and waiting forever (Ctrl+C when done)\n", config.numclients);
+        prepareForBenchmark();
+        c = createClient();
+        if (!c) exit(1);
+        c->obuf = sdsempty();
+        prepareClientForReply(c,REPLY_RETCODE); /* will never receive it */
+        createMissingClients(c);
+        aeMain(config.el);
+        /* and will wait for every */
+    }
+
     do {
         prepareForBenchmark();
         c = createClient();