@@ -46,7 +46,7 @@
 #include "adlist.h"
 #include "zmalloc.h"
 
-#define REDIS_NOTUSED(V) ((void) V)
+#define UNUSED(V) ((void) V)
 #define RANDPTR_INITIAL_SIZE 8
 
 static struct config {
@@ -188,9 +188,9 @@ static void clientDone(client c) {
 static void readHandler(aeEventLoop *el, int fd, void *privdata, int mask) {
     client c = privdata;
     void *reply = NULL;
-    REDIS_NOTUSED(el);
-    REDIS_NOTUSED(fd);
-    REDIS_NOTUSED(mask);
+    UNUSED(el);
+    UNUSED(fd);
+    UNUSED(mask);
 
     /* Calculate latency only for the first read event. This means that the
      * server already sent the reply and we need to parse it. Parsing overhead
@@ -246,9 +246,9 @@ static void readHandler(aeEventLoop *el, int fd, void *privdata, int mask) {
 
 static void writeHandler(aeEventLoop *el, int fd, void *privdata, int mask) {
     client c = privdata;
-    REDIS_NOTUSED(el);
-    REDIS_NOTUSED(fd);
-    REDIS_NOTUSED(mask);
+    UNUSED(el);
+    UNUSED(fd);
+    UNUSED(mask);
 
     /* Initialize request when nothing was written. */
     if (c->written == 0) {
@@ -595,9 +595,9 @@ int parseOptions(int argc, const char **argv) {
 }
 
 int showThroughput(struct aeEventLoop *eventLoop, long long id, void *clientData) {
-    REDIS_NOTUSED(eventLoop);
-    REDIS_NOTUSED(id);
-    REDIS_NOTUSED(clientData);
+    UNUSED(eventLoop);
+    UNUSED(id);
+    UNUSED(clientData);
 
     if (config.liveclients == 0) {
         fprintf(stderr,"All clients disconnected... aborting.\n");