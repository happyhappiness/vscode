@@ -45,10 +45,6 @@
 #include "adlist.h"
 #include "zmalloc.h"
 
-#define CLIENT_CONNECTING 0
-#define CLIENT_SENDQUERY 1
-#define CLIENT_READREPLY 2
-
 #define REDIS_NOTUSED(V) ((void) V)
 
 static struct config {
@@ -78,7 +74,6 @@ static struct config {
 
 typedef struct _client {
     redisContext *context;
-    int state;
     sds obuf;
     char *randptr[10]; /* needed for MSET against 10 keys */
     size_t randlen;
@@ -140,9 +135,6 @@ static void resetClient(client c) {
     aeDeleteFileEvent(config.el,c->context->fd,AE_READABLE);
     aeCreateFileEvent(config.el,c->context->fd,AE_WRITABLE,writeHandler,c);
     c->written = 0;
-    c->state = CLIENT_SENDQUERY;
-    c->start = ustime();
-    c->latency = -1;
 }
 
 static void randomizeClientKey(client c) {
@@ -164,7 +156,6 @@ static void clientDone(client c) {
     }
     if (config.keepalive) {
         resetClient(c);
-        if (config.randomkeys) randomizeClientKey(c);
     } else {
         config.liveclients--;
         createMissingClients(c);
@@ -212,11 +203,13 @@ static void writeHandler(aeEventLoop *el, int fd, void *privdata, int mask) {
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
@@ -230,7 +223,6 @@ static void writeHandler(aeEventLoop *el, int fd, void *privdata, int mask) {
         if (sdslen(c->obuf) == c->written) {
             aeDeleteFileEvent(config.el,c->context->fd,AE_WRITABLE);
             aeCreateFileEvent(config.el,c->context->fd,AE_READABLE,readHandler,c);
-            c->state = CLIENT_READREPLY;
         }
     }
 }
@@ -250,7 +242,6 @@ static client createClient(char *cmd, int len) {
             fprintf(stderr,"%s: %s\n",config.hostsocket,c->context->errstr);
         exit(1);
     }
-    c->state = CLIENT_CONNECTING;
     c->obuf = sdsnewlen(cmd,len);
     c->randlen = 0;
     c->written = 0;
@@ -278,8 +269,7 @@ static void createMissingClients(client c) {
     int n = 0;
 
     while(config.liveclients < config.numclients) {
-        client new = createClient(c->obuf,sdslen(c->obuf));
-        if (config.randomkeys) randomizeClientKey(new);
+        createClient(c->obuf,sdslen(c->obuf));
 
         /* Listen backlog is quite limited on most systems */
         if (++n > 64) {