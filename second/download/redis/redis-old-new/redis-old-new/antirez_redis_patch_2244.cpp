@@ -3524,7 +3524,10 @@ static void pushGenericCommand(redisClient *c, int where) {
 
     lobj = lookupKeyWrite(c->db,c->argv[1]);
     if (lobj == NULL) {
-        if (handleClientsWaitingListPush(c,c->argv[1],c->argv[2])) return;
+        if (handleClientsWaitingListPush(c,c->argv[1],c->argv[2])) {
+            addReply(c,shared.ok);
+            return;
+        }
         lobj = createListObject();
         list = lobj->ptr;
         if (where == REDIS_HEAD) {
@@ -3540,7 +3543,10 @@ static void pushGenericCommand(redisClient *c, int where) {
             addReply(c,shared.wrongtypeerr);
             return;
         }
-        if (handleClientsWaitingListPush(c,c->argv[1],c->argv[2])) return;
+        if (handleClientsWaitingListPush(c,c->argv[1],c->argv[2])) {
+            addReply(c,shared.ok);
+            return;
+        }
         list = lobj->ptr;
         if (where == REDIS_HEAD) {
             listAddNodeHead(list,c->argv[2]);
@@ -5462,7 +5468,7 @@ static void execCommand(redisClient *c) {
  *   empty we need to block. In order to do so we remove the notification for
  *   new data to read in the client socket (so that we'll not serve new
  *   requests if the blocking request is not served). Also we put the client
- *   in a dictionary (server.blockingkeys) mapping keys to a list of clients
+ *   in a dictionary (db->blockingkeys) mapping keys to a list of clients
  *   blocking for this keys.
  * - If a PUSH operation against a key with blocked clients waiting is
  *   performed, we serve the first in the list: basically instead to push
@@ -5479,7 +5485,6 @@ static void blockForKey(redisClient *c, robj *key, time_t timeout) {
     dictEntry *de;
     list *l;
 
-    printf("blockForKey %p %s\n", c, key->ptr);
     c->blockingkey = key;
     incrRefCount(key);
     c->blockingto = timeout;
@@ -5504,7 +5509,6 @@ static void unblockClient(redisClient *c) {
     dictEntry *de;
     list *l;
 
-    printf("unblockClient %p %s\n", c, c->blockingkey->ptr);
     /* Remove this client from the list of clients waiting for this key. */
     assert(c->blockingkey != NULL);
     de = dictFind(c->db->blockingkeys,c->blockingkey);
@@ -5554,9 +5558,6 @@ static int handleClientsWaitingListPush(redisClient *c, robj *key, robj *ele) {
     ln = listFirst(l);
     assert(ln != NULL);
     receiver = ln->value;
-    listDelNode(l,ln);
-    if (listLength(l) == 0)
-        dictDelete(c->db->blockingkeys,key);
 
     addReplyBulkLen(receiver,ele);
     addReply(receiver,ele);