@@ -80,7 +80,8 @@ typedef struct _client {
     redisContext *context;
     int state;
     sds obuf;
-    char *randptr;
+    char *randptr[10]; /* needed for MSET against 10 keys */
+    size_t randlen;
     unsigned int written; /* bytes of 'obuf' already written */
     long long start; /* start time of a request */
     long long latency; /* request latency */
@@ -145,29 +146,14 @@ static void resetClient(client c) {
 }
 
 static void randomizeClientKey(client c) {
-    char *p, *newline;
     char buf[32];
-    long r;
+    size_t i, r;
 
-    if (c->randptr == NULL) return;
-
-    /* Check if we have to randomize (only once per connection) */
-    if (c->randptr == (void*)-1) {
-        p = strstr(c->obuf,":rand:");
-        if (!p) {
-            c->randptr = NULL;
-            return;
-        } else {
-            newline = strstr(p,"\r\n");
-            assert(newline-(p+6) == 12); /* 12 chars for randomness */
-            c->randptr = p+6;
-        }
+    for (i = 0; i < c->randlen; i++) {
+        r = random() % config.randomkeys_keyspacelen;
+        snprintf(buf,sizeof(buf),"%012lu",r);
+        memcpy(c->randptr[i],buf,12);
     }
-
-    /* Set random number in output buffer */
-    r = random() % config.randomkeys_keyspacelen;
-    snprintf(buf,sizeof(buf),"%012ld",r);
-    memcpy(c->randptr,buf,12);
 }
 
 static void clientDone(client c) {
@@ -249,7 +235,7 @@ static void writeHandler(aeEventLoop *el, int fd, void *privdata, int mask) {
     }
 }
 
-static client createClient() {
+static client createClient(char *cmd, int len) {
     client c = zmalloc(sizeof(struct _client));
     if (config.hostsocket == NULL) {
         c->context = redisConnectNonBlock(config.hostip,config.hostport);
@@ -265,9 +251,22 @@ static client createClient() {
         exit(1);
     }
     c->state = CLIENT_CONNECTING;
-    c->obuf = NULL;
-    c->randptr = (void*)-1;
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
@@ -279,9 +278,8 @@ static void createMissingClients(client c) {
     int n = 0;
 
     while(config.liveclients < config.numclients) {
-        client new = createClient();
-        new->obuf = sdsdup(c->obuf);
-        if (config.randomkeys) randomizeClientKey(c);
+        client new = createClient(c->obuf,sdslen(c->obuf));
+        if (config.randomkeys) randomizeClientKey(new);
 
         /* Listen backlog is quite limited on most systems */
         if (++n > 64) {
@@ -329,8 +327,7 @@ static void benchmark(char *title, char *cmd, int len) {
     config.title = title;
     config.donerequests = 0;
 
-    c = createClient();
-    c->obuf = sdsnewlen(cmd,len);
+    c = createClient(cmd,len);
     createMissingClients(c);
 
     config.start = mstime();
@@ -458,8 +455,7 @@ int main(int argc, char **argv) {
 
     if (config.idlemode) {
         printf("Creating %d idle connections and waiting forever (Ctrl+C when done)\n", config.numclients);
-        c = createClient(0); /* will never receive a reply */
-        c->obuf = sdsempty();
+        c = createClient("",0); /* will never receive a reply */
         createMissingClients(c);
         aeMain(config.el);
         /* and will wait for every */