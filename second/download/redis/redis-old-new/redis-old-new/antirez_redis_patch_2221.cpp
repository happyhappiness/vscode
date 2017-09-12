@@ -1018,9 +1018,10 @@ static void closeTimedoutClients(void) {
     redisClient *c;
     listNode *ln;
     time_t now = time(NULL);
+    listIter li;
 
-    listRewind(server.clients);
-    while ((ln = listYield(server.clients)) != NULL) {
+    listRewind(server.clients,&li);
+    while ((ln = listNext(&li)) != NULL) {
         c = listNodeValue(ln);
         if (server.maxidletime &&
             !(c->flags & REDIS_SLAVE) &&    /* no timeout for slaves */
@@ -1711,10 +1712,11 @@ static void glueReplyBuffersIfNeeded(redisClient *c) {
     int copylen = 0;
     char buf[GLUEREPLY_UP_TO];
     listNode *ln;
+    listIter li;
     robj *o;
 
-    listRewind(c->reply);
-    while((ln = listYield(c->reply))) {
+    listRewind(c->reply,&li);
+    while((ln = listNext(&li))) {
         int objlen;
 
         o = ln->value;
@@ -2076,6 +2078,7 @@ static int processCommand(redisClient *c) {
 
 static void replicationFeedSlaves(list *slaves, struct redisCommand *cmd, int dictid, robj **argv, int argc) {
     listNode *ln;
+    listIter li;
     int outc = 0, j;
     robj **outv;
     /* (args*2)+1 is enough room for args, spaces, newlines */
@@ -2106,8 +2109,8 @@ static void replicationFeedSlaves(list *slaves, struct redisCommand *cmd, int di
      * be sure to free objects if there is no slave in a replication state
      * able to be feed with commands */
     for (j = 0; j < outc; j++) incrRefCount(outv[j]);
-    listRewind(slaves);
-    while((ln = listYield(slaves))) {
+    listRewind(slaves,&li);
+    while((ln = listNext(&li))) {
         redisClient *slave = ln->value;
 
         /* Don't feed slaves that are still waiting for BGSAVE to start */
@@ -2922,11 +2925,12 @@ static int rdbSaveObject(FILE *fp, robj *o) {
     } else if (o->type == REDIS_LIST) {
         /* Save a list value */
         list *list = o->ptr;
+        listIter li;
         listNode *ln;
 
-        listRewind(list);
         if (rdbSaveLen(fp,listLength(list)) == -1) return -1;
-        while((ln = listYield(list))) {
+        listRewind(list,&li);
+        while((ln = listNext(&li))) {
             robj *eleobj = listNodeValue(ln);
 
             if (rdbSaveStringObject(fp,eleobj) == -1) return -1;
@@ -5362,9 +5366,10 @@ static void sortCommand(redisClient *c) {
     if (sortval->type == REDIS_LIST) {
         list *list = sortval->ptr;
         listNode *ln;
+        listIter li;
 
-        listRewind(list);
-        while((ln = listYield(list))) {
+        listRewind(list,&li);
+        while((ln = listNext(&li))) {
             robj *ele = ln->value;
             vector[j].obj = ele;
             vector[j].u.score = 0;
@@ -5392,6 +5397,8 @@ static void sortCommand(redisClient *c) {
         }
         dictReleaseIterator(di);
     }
+    printf("**************************** %d == %d\n",
+        j, vectorlen);
     redisAssert(j == vectorlen);
 
     /* Now it's time to load the right scores in the sorting vector */
@@ -5460,13 +5467,15 @@ static void sortCommand(redisClient *c) {
         addReplySds(c,sdscatprintf(sdsempty(),"*%d\r\n",outputlen));
         for (j = start; j <= end; j++) {
             listNode *ln;
+            listIter li;
+
             if (!getop) {
                 addReplyBulkLen(c,vector[j].obj);
                 addReply(c,vector[j].obj);
                 addReply(c,shared.crlf);
             }
-            listRewind(operations);
-            while((ln = listYield(operations))) {
+            listRewind(operations,&li);
+            while((ln = listNext(&li))) {
                 redisSortOperation *sop = ln->value;
                 robj *val = lookupKeyByPattern(c->db,sop->pattern,
                     vector[j].obj);
@@ -5491,12 +5500,14 @@ static void sortCommand(redisClient *c) {
         /* STORE option specified, set the sorting result as a List object */
         for (j = start; j <= end; j++) {
             listNode *ln;
+            listIter li;
+
             if (!getop) {
                 listAddNodeTail(listPtr,vector[j].obj);
                 incrRefCount(vector[j].obj);
             }
-            listRewind(operations);
-            while((ln = listYield(operations))) {
+            listRewind(operations,&li);
+            while((ln = listNext(&li))) {
                 redisSortOperation *sop = ln->value;
                 robj *val = lookupKeyByPattern(c->db,sop->pattern,
                     vector[j].obj);
@@ -6136,9 +6147,10 @@ static void syncCommand(redisClient *c) {
          * registering differences since the server forked to save */
         redisClient *slave;
         listNode *ln;
+        listIter li;
 
-        listRewind(server.slaves);
-        while((ln = listYield(server.slaves))) {
+        listRewind(server.slaves,&li);
+        while((ln = listNext(&li))) {
             slave = ln->value;
             if (slave->replstate == REDIS_REPL_WAIT_BGSAVE_END) break;
         }
@@ -6235,9 +6247,10 @@ static void sendBulkToSlave(aeEventLoop *el, int fd, void *privdata, int mask) {
 static void updateSlavesWaitingBgsave(int bgsaveerr) {
     listNode *ln;
     int startbgsave = 0;
+    listIter li;
 
-    listRewind(server.slaves);
-    while((ln = listYield(server.slaves))) {
+    listRewind(server.slaves,&li);
+    while((ln = listNext(&li))) {
         redisClient *slave = ln->value;
 
         if (slave->replstate == REDIS_REPL_WAIT_BGSAVE_START) {
@@ -6269,9 +6282,11 @@ static void updateSlavesWaitingBgsave(int bgsaveerr) {
     }
     if (startbgsave) {
         if (rdbSaveBackground(server.dbfilename) != REDIS_OK) {
-            listRewind(server.slaves);
+            listIter li;
+
+            listRewind(server.slaves,&li);
             redisLog(REDIS_WARNING,"SYNC failed. BGSAVE failed");
-            while((ln = listYield(server.slaves))) {
+            while((ln = listNext(&li))) {
                 redisClient *slave = ln->value;
 
                 if (slave->replstate == REDIS_REPL_WAIT_BGSAVE_START)
@@ -6792,9 +6807,10 @@ static int rewriteAppendOnlyFile(char *filename) {
                 /* Emit the RPUSHes needed to rebuild the list */
                 list *list = o->ptr;
                 listNode *ln;
+                listIter li;
 
-                listRewind(list);
-                while((ln = listYield(list))) {
+                listRewind(list,&li);
+                while((ln = listNext(&li))) {
                     char cmd[]="*3\r\n$5\r\nRPUSH\r\n";
                     robj *eleobj = listNodeValue(ln);
 
@@ -7080,7 +7096,7 @@ static int vmFreePage(off_t page) {
  * note: I implemented this function just after watching an episode of
  * Battlestar Galactica, where the hybrid was continuing to say "JUMP!"
  */
-static int vmFindContiguousPages(off_t *first, int n) {
+static int vmFindContiguousPages(off_t *first, off_t n) {
     off_t base, offset = 0, since_jump = 0, numfree = 0;
 
     if (server.vm_near_pages == REDIS_VM_MAX_NEAR_PAGES) {
@@ -7469,6 +7485,10 @@ static void vmThreadedIOCompletedJob(aeEventLoop *el, int fd, void *privdata,
                 /* Ooops... no space! */
                 freeIOJob(j);
             } else {
+                /* Note that we need to mark this pages as used now,
+                 * if the job will be canceled, we'll mark them as freed
+                 * again. */
+                vmMarkPagesUsed(j->page,j->pages);
                 j->type = REDIS_IOJOB_DO_SWAP;
                 lockThreadedIO();
                 queueIOJob(j);
@@ -7494,7 +7514,6 @@ static void vmThreadedIOCompletedJob(aeEventLoop *el, int fd, void *privdata,
             key->vtype = j->val->type;
             decrRefCount(val); /* Deallocate the object from memory. */
             dictGetEntryVal(de) = NULL;
-            vmMarkPagesUsed(j->page,j->pages);
             redisLog(REDIS_DEBUG,
                 "VM: object %s swapped out at %lld (%lld pages) (threaded)",
                 (unsigned char*) key->ptr,
@@ -7549,9 +7568,10 @@ static void vmCancelThreadedIOJob(robj *o) {
     /* Search for a matching key in one of the queues */
     for (i = 0; i < 3; i++) {
         listNode *ln;
+        listIter li;
 
-        listRewind(lists[i]);
-        while ((ln = listYield(lists[i])) != NULL) {
+        listRewind(lists[i],&li);
+        while ((ln = listNext(&li)) != NULL) {
             iojob *job = ln->value;
 
             if (job->canceled) continue; /* Skip this, already canceled. */
@@ -7570,6 +7590,12 @@ static void vmCancelThreadedIOJob(robj *o) {
                     job->canceled = 1;
                     break;
                 }
+                /* Mark the pages as free since the swap didn't happened
+                 * or happened but is not discarded. */
+                if (job->type == REDIS_IOJOB_DO_SWAP)
+                    vmMarkPagesFree(job->page,job->pages);
+                /* Finally we have to adjust the storage type of the object
+                 * in order to "UNDO" the operaiton. */
                 if (o->storage == REDIS_VM_LOADING)
                     o->storage = REDIS_VM_SWAPPED;
                 else if (o->storage == REDIS_VM_SWAPPING)