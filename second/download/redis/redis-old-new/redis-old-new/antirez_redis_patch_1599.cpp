@@ -10,46 +10,18 @@
 void replicationFeedSlaves(list *slaves, int dictid, robj **argv, int argc) {
     listNode *ln;
     listIter li;
-    int outc = 0, j;
-    robj **outv;
-    /* We need 1+(ARGS*3) objects since commands are using the new protocol
-     * and we one 1 object for the first "*<count>\r\n" multibulk count, then
-     * for every additional object we have "$<count>\r\n" + object + "\r\n". */
-    robj *static_outv[REDIS_STATIC_ARGS*3+1];
-    robj *lenobj;
-
-    if (argc <= REDIS_STATIC_ARGS) {
-        outv = static_outv;
-    } else {
-        outv = zmalloc(sizeof(robj*)*(argc*3+1));
-    }
-
-    lenobj = createObject(REDIS_STRING,
-            sdscatprintf(sdsempty(), "*%d\r\n", argc));
-    lenobj->refcount = 0;
-    outv[outc++] = lenobj;
-    for (j = 0; j < argc; j++) {
-        lenobj = createObject(REDIS_STRING,
-            sdscatprintf(sdsempty(),"$%lu\r\n",
-                (unsigned long) stringObjectLen(argv[j])));
-        lenobj->refcount = 0;
-        outv[outc++] = lenobj;
-        outv[outc++] = argv[j];
-        outv[outc++] = shared.crlf;
-    }
+    int j;
 
-    /* Increment all the refcounts at start and decrement at end in order to
-     * be sure to free objects if there is no slave in a replication state
-     * able to be feed with commands */
-    for (j = 0; j < outc; j++) incrRefCount(outv[j]);
     listRewind(slaves,&li);
     while((ln = listNext(&li))) {
         redisClient *slave = ln->value;
 
         /* Don't feed slaves that are still waiting for BGSAVE to start */
         if (slave->replstate == REDIS_REPL_WAIT_BGSAVE_START) continue;
 
-        /* Feed all the other slaves, MONITORs and so on */
+        /* Feed slaves that are waiting for the initial SYNC (so these commands
+         * are queued in the output buffer until the intial SYNC completes),
+         * or are already in sync with the master. */
         if (slave->slaveseldb != dictid) {
             robj *selectcmd;
 
@@ -73,10 +45,9 @@ void replicationFeedSlaves(list *slaves, int dictid, robj **argv, int argc) {
             addReply(slave,selectcmd);
             slave->slaveseldb = dictid;
         }
-        for (j = 0; j < outc; j++) addReply(slave,outv[j]);
+        addReplyMultiBulkLen(slave,argc);
+        for (j = 0; j < argc; j++) addReplyBulk(slave,argv[j]);
     }
-    for (j = 0; j < outc; j++) decrRefCount(outv[j]);
-    if (outv != static_outv) zfree(outv);
 }
 
 void replicationFeedMonitors(list *monitors, int dictid, robj **argv, int argc) {