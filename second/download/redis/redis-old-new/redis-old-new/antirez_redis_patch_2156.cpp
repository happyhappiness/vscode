@@ -86,7 +86,7 @@
 #define REDIS_MAXIDLETIME       (60*5)  /* default client timeout */
 #define REDIS_IOBUF_LEN         1024
 #define REDIS_LOADBUF_LEN       1024
-#define REDIS_STATIC_ARGS       4
+#define REDIS_STATIC_ARGS       8
 #define REDIS_DEFAULT_DBNUM     16
 #define REDIS_CONFIGLINE_MAX    1024
 #define REDIS_OBJFREELIST_MAX   1000000 /* Max number of objects to cache */
@@ -521,7 +521,7 @@ typedef struct iojob {
     robj *val;  /* the value to swap for REDIS_IOREQ_*_SWAP, otherwise this
                  * field is populated by the I/O thread for REDIS_IOREQ_LOAD. */
     off_t page; /* Swap page where to read/write the object */
-    off_t pages; /* Swap pages needed to safe object. PREPARE_SWAP return val */
+    off_t pages; /* Swap pages needed to save object. PREPARE_SWAP return val */
     int canceled; /* True if this command was canceled by blocking side of VM */
     pthread_t thread; /* ID of the thread processing this entry */
 } iojob;
@@ -541,7 +541,7 @@ static void incrRefCount(robj *o);
 static int rdbSaveBackground(char *filename);
 static robj *createStringObject(char *ptr, size_t len);
 static robj *dupStringObject(robj *o);
-static void replicationFeedSlaves(list *slaves, struct redisCommand *cmd, int dictid, robj **argv, int argc);
+static void replicationFeedSlaves(list *slaves, int dictid, robj **argv, int argc);
 static void feedAppendOnlyFile(struct redisCommand *cmd, int dictid, robj **argv, int argc);
 static int syncWithMaster(void);
 static robj *tryObjectSharing(robj *o);
@@ -2075,9 +2075,9 @@ static void call(redisClient *c, struct redisCommand *cmd) {
     if (server.appendonly && server.dirty-dirty)
         feedAppendOnlyFile(cmd,c->db->id,c->argv,c->argc);
     if (server.dirty-dirty && listLength(server.slaves))
-        replicationFeedSlaves(server.slaves,cmd,c->db->id,c->argv,c->argc);
+        replicationFeedSlaves(server.slaves,c->db->id,c->argv,c->argc);
     if (listLength(server.monitors))
-        replicationFeedSlaves(server.monitors,cmd,c->db->id,c->argv,c->argc);
+        replicationFeedSlaves(server.monitors,c->db->id,c->argv,c->argc);
     server.stat_numcommands++;
 }
 
@@ -2256,34 +2256,36 @@ static int processCommand(redisClient *c) {
     return 1;
 }
 
-static void replicationFeedSlaves(list *slaves, struct redisCommand *cmd, int dictid, robj **argv, int argc) {
+static void replicationFeedSlaves(list *slaves, int dictid, robj **argv, int argc) {
     listNode *ln;
     listIter li;
     int outc = 0, j;
     robj **outv;
-    /* (args*2)+1 is enough room for args, spaces, newlines */
-    robj *static_outv[REDIS_STATIC_ARGS*2+1];
+    /* We need 1+(ARGS*3) objects since commands are using the new protocol
+     * and we one 1 object for the first "*<count>\r\n" multibulk count, then
+     * for every additional object we have "$<count>\r\n" + object + "\r\n". */
+    robj *static_outv[REDIS_STATIC_ARGS*3+1];
+    robj *lenobj;
 
     if (argc <= REDIS_STATIC_ARGS) {
         outv = static_outv;
     } else {
-        outv = zmalloc(sizeof(robj*)*(argc*2+1));
+        outv = zmalloc(sizeof(robj*)*(argc*3+1));
     }
-    
-    for (j = 0; j < argc; j++) {
-        if (j != 0) outv[outc++] = shared.space;
-        if ((cmd->flags & REDIS_CMD_BULK) && j == argc-1) {
-            robj *lenobj;
 
-            lenobj = createObject(REDIS_STRING,
-                sdscatprintf(sdsempty(),"%lu\r\n",
-                    (unsigned long) stringObjectLen(argv[j])));
-            lenobj->refcount = 0;
-            outv[outc++] = lenobj;
-        }
+    lenobj = createObject(REDIS_STRING,
+            sdscatprintf(sdsempty(), "*%d\r\n", argc));
+    lenobj->refcount = 0;
+    outv[outc++] = lenobj;
+    for (j = 0; j < argc; j++) {
+        lenobj = createObject(REDIS_STRING,
+            sdscatprintf(sdsempty(),"$%lu\r\n",
+                (unsigned long) stringObjectLen(argv[j])));
+        lenobj->refcount = 0;
+        outv[outc++] = lenobj;
         outv[outc++] = argv[j];
+        outv[outc++] = shared.crlf;
     }
-    outv[outc++] = shared.crlf;
 
     /* Increment all the refcounts at start and decrement at end in order to
      * be sure to free objects if there is no slave in a replication state