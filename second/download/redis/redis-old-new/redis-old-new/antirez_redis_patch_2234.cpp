@@ -197,8 +197,9 @@
 
 /* Log levels */
 #define REDIS_DEBUG 0
-#define REDIS_NOTICE 1
-#define REDIS_WARNING 2
+#define REDIS_VERBOSE 1
+#define REDIS_NOTICE 2
+#define REDIS_WARNING 3
 
 /* Anti-warning macro... */
 #define REDIS_NOTUSED(V) ((void) V)
@@ -496,6 +497,7 @@ static robj *vmLoadObject(robj *key);
 static robj *vmPreviewObject(robj *key);
 static int vmSwapOneObject(void);
 static int vmCanSwapOut(void);
+static void freeOneObjectFromFreelist(void);
 
 static void authCommand(redisClient *c);
 static void pingCommand(redisClient *c);
@@ -949,7 +951,7 @@ static void closeTimedoutClients(void) {
             !(c->flags & REDIS_MASTER) &&   /* no timeout for masters */
              (now - c->lastinteraction > server.maxidletime))
         {
-            redisLog(REDIS_DEBUG,"Closing idle client");
+            redisLog(REDIS_VERBOSE,"Closing idle client");
             freeClient(c);
         } else if (c->flags & REDIS_BLOCKED) {
             if (c->blockingto != 0 && c->blockingto < now) {
@@ -976,9 +978,9 @@ static void tryResizeHashTables(void) {
 
     for (j = 0; j < server.dbnum; j++) {
         if (htNeedsResize(server.db[j].dict)) {
-            redisLog(REDIS_DEBUG,"The hash table %d is too sparse, resize it...",j);
+            redisLog(REDIS_VERBOSE,"The hash table %d is too sparse, resize it...",j);
             dictResize(server.db[j].dict);
-            redisLog(REDIS_DEBUG,"Hash table %d resized.",j);
+            redisLog(REDIS_VERBOSE,"Hash table %d resized.",j);
         }
         if (htNeedsResize(server.db[j].expires))
             dictResize(server.db[j].expires);
@@ -1092,7 +1094,7 @@ static int serverCron(struct aeEventLoop *eventLoop, long long id, void *clientD
         used = dictSize(server.db[j].dict);
         vkeys = dictSize(server.db[j].expires);
         if (!(loops % 5) && (used || vkeys)) {
-            redisLog(REDIS_DEBUG,"DB %d: %lld keys (%lld volatile) in %lld slots HT.",j,used,vkeys,size);
+            redisLog(REDIS_VERBOSE,"DB %d: %lld keys (%lld volatile) in %lld slots HT.",j,used,vkeys,size);
             /* dictPrintStats(server.dict); */
         }
     }
@@ -1107,7 +1109,7 @@ static int serverCron(struct aeEventLoop *eventLoop, long long id, void *clientD
 
     /* Show information about connected clients */
     if (!(loops % 5)) {
-        redisLog(REDIS_DEBUG,"%d clients connected (%d slaves), %zu bytes in use, %d shared objects",
+        redisLog(REDIS_VERBOSE,"%d clients connected (%d slaves), %zu bytes in use, %d shared objects",
             listLength(server.clients)-listLength(server.slaves),
             listLength(server.slaves),
             server.usedmemory,
@@ -1179,12 +1181,15 @@ static int serverCron(struct aeEventLoop *eventLoop, long long id, void *clientD
     }
 
     /* Swap a few keys on disk if we are over the memory limit and VM
-     * is enbled. */
+     * is enbled. Try to free objects from the free list first. */
     if (vmCanSwapOut()) {
         while (server.vm_enabled && zmalloc_used_memory() >
-                server.vm_max_memory) {
-            if (vmSwapOneObject() == REDIS_ERR) {
-                if (zmalloc_used_memory() >
+                server.vm_max_memory)
+        {
+            if (listLength(server.objfreelist)) {
+                freeOneObjectFromFreelist();
+            } else if (vmSwapOneObject() == REDIS_ERR) {
+                if ((loops % 30) == 0 && zmalloc_used_memory() >
                     (server.vm_max_memory+server.vm_max_memory/10)) {
                     redisLog(REDIS_WARNING,"WARNING: vm-max-memory limit exceeded by more than 10%% but unable to swap more objects out!");
                 }
@@ -1256,7 +1261,7 @@ static void resetServerSaveParams() {
 static void initServerConfig() {
     server.dbnum = REDIS_DEFAULT_DBNUM;
     server.port = REDIS_SERVERPORT;
-    server.verbosity = REDIS_DEBUG;
+    server.verbosity = REDIS_VERBOSE;
     server.maxidletime = REDIS_MAXIDLETIME;
     server.saveparams = NULL;
     server.logfile = NULL; /* NULL = log on standard output */
@@ -1436,6 +1441,7 @@ static void loadServerConfig(char *filename) {
             }
         } else if (!strcasecmp(argv[0],"loglevel") && argc == 2) {
             if (!strcasecmp(argv[1],"debug")) server.verbosity = REDIS_DEBUG;
+            else if (!strcasecmp(argv[1],"verbose")) server.verbosity = REDIS_VERBOSE;
             else if (!strcasecmp(argv[1],"notice")) server.verbosity = REDIS_NOTICE;
             else if (!strcasecmp(argv[1],"warning")) server.verbosity = REDIS_WARNING;
             else {
@@ -1677,7 +1683,7 @@ static void sendReplyToClient(aeEventLoop *el, int fd, void *privdata, int mask)
         if (errno == EAGAIN) {
             nwritten = 0;
         } else {
-            redisLog(REDIS_DEBUG,
+            redisLog(REDIS_VERBOSE,
                 "Error writing to client: %s", strerror(errno));
             freeClient(c);
             return;
@@ -1730,7 +1736,7 @@ static void sendReplyToClientWritev(aeEventLoop *el, int fd, void *privdata, int
         /* write all collected blocks at once */
         if((nwritten = writev(fd, iov, ion)) < 0) {
             if (errno != EAGAIN) {
-                redisLog(REDIS_DEBUG,
+                redisLog(REDIS_VERBOSE,
                          "Error writing to client: %s", strerror(errno));
                 freeClient(c);
                 return;
@@ -2091,7 +2097,7 @@ static void processInputBuffer(redisClient *c) {
             }
             return;
         } else if (sdslen(c->querybuf) >= REDIS_REQUEST_MAX_SIZE) {
-            redisLog(REDIS_DEBUG, "Client protocol error");
+            redisLog(REDIS_VERBOSE, "Client protocol error");
             freeClient(c);
             return;
         }
@@ -2128,12 +2134,12 @@ static void readQueryFromClient(aeEventLoop *el, int fd, void *privdata, int mas
         if (errno == EAGAIN) {
             nread = 0;
         } else {
-            redisLog(REDIS_DEBUG, "Reading from client: %s",strerror(errno));
+            redisLog(REDIS_VERBOSE, "Reading from client: %s",strerror(errno));
             freeClient(c);
             return;
         }
     } else if (nread == 0) {
-        redisLog(REDIS_DEBUG, "Client closed connection");
+        redisLog(REDIS_VERBOSE, "Client closed connection");
         freeClient(c);
         return;
     }
@@ -2252,10 +2258,10 @@ static void acceptHandler(aeEventLoop *el, int fd, void *privdata, int mask) {
 
     cfd = anetAccept(server.neterr, fd, cip, &cport);
     if (cfd == AE_ERR) {
-        redisLog(REDIS_DEBUG,"Accepting client connection: %s", server.neterr);
+        redisLog(REDIS_VERBOSE,"Accepting client connection: %s", server.neterr);
         return;
     }
-    redisLog(REDIS_DEBUG,"Accepted %s:%d", cip, cport);
+    redisLog(REDIS_VERBOSE,"Accepted %s:%d", cip, cport);
     if ((c = createClient(cfd)) == NULL) {
         redisLog(REDIS_WARNING,"Error allocating resoures for the client");
         close(cfd); /* May be already closed, just ingore errors */
@@ -6002,7 +6008,7 @@ static void sendBulkToSlave(aeEventLoop *el, int fd, void *privdata, int mask) {
         return;
     }
     if ((nwritten = write(fd,buf,buflen)) == -1) {
-        redisLog(REDIS_DEBUG,"Write error sending DB to slave: %s",
+        redisLog(REDIS_VERBOSE,"Write error sending DB to slave: %s",
             strerror(errno));
         freeClient(slave);
         return;
@@ -6206,6 +6212,18 @@ static void slaveofCommand(redisClient *c) {
 
 /* ============================ Maxmemory directive  ======================== */
 
+/* Free one object form the pre-allocated objects free list. This is useful
+ * under low mem conditions as by default we take 1 million free objects
+ * allocated. */
+static void freeOneObjectFromFreelist(void) {
+    robj *o;
+
+    listNode *head = listFirst(server.objfreelist);
+    o = listNodeValue(head);
+    listDelNode(server.objfreelist,head);
+    zfree(o);
+}
+
 /* This function gets called when 'maxmemory' is set on the config file to limit
  * the max memory used by the server, and we are out of memory.
  * This function will try to, in order:
@@ -6220,12 +6238,7 @@ static void slaveofCommand(redisClient *c) {
 static void freeMemoryIfNeeded(void) {
     while (server.maxmemory && zmalloc_used_memory() > server.maxmemory) {
         if (listLength(server.objfreelist)) {
-            robj *o;
-
-            listNode *head = listFirst(server.objfreelist);
-            o = listNodeValue(head);
-            listDelNode(server.objfreelist,head);
-            zfree(o);
+            freeOneObjectFromFreelist();
         } else {
             int j, k, freed = 0;
 
@@ -6731,7 +6744,7 @@ static void vmInit(void) {
         redisLog(REDIS_NOTICE,"Swap file allocated with success");
     }
     server.vm_bitmap = zmalloc((server.vm_pages+7)/8);
-    redisLog(REDIS_DEBUG,"Allocated %lld bytes page table for %lld pages",
+    redisLog(REDIS_VERBOSE,"Allocated %lld bytes page table for %lld pages",
         (long long) (server.vm_pages+7)/8, server.vm_pages);
     memset(server.vm_bitmap,0,(server.vm_pages+7)/8);
     /* Try to remove the swap file, so the OS will really delete it from the
@@ -6744,8 +6757,8 @@ static void vmMarkPageUsed(off_t page) {
     off_t byte = page/8;
     int bit = page&7;
     server.vm_bitmap[byte] |= 1<<bit;
-    printf("Mark used: %lld (byte:%lld bit:%d)\n", (long long)page,
-        (long long)byte, bit);
+    redisLog(REDIS_DEBUG,"Mark used: %lld (byte:%lld bit:%d)\n",
+        (long long)page, (long long)byte, bit);
 }
 
 /* Mark N contiguous pages as used, with 'page' being the first. */
@@ -6810,7 +6823,7 @@ static int vmFindContiguousPages(off_t *first, int n) {
     while(offset < server.vm_pages) {
         off_t this = base+offset;
 
-        printf("THIS: %lld (%c)\n", (long long) this, vmFreePage(this) ? 'F' : 'X');
+        redisLog(REDIS_DEBUG, "THIS: %lld (%c)\n", (long long) this, vmFreePage(this) ? 'F' : 'X');
         /* If we overflow, restart from page zero */
         if (this >= server.vm_pages) {
             this -= server.vm_pages;