@@ -4075,7 +4075,7 @@ static void pushGenericCommand(redisClient *c, int where) {
     lobj = lookupKeyWrite(c->db,c->argv[1]);
     if (lobj == NULL) {
         if (handleClientsWaitingListPush(c,c->argv[1],c->argv[2])) {
-            addReply(c,shared.ok);
+            addReply(c,shared.cone);
             return;
         }
         lobj = createListObject();
@@ -4094,7 +4094,7 @@ static void pushGenericCommand(redisClient *c, int where) {
             return;
         }
         if (handleClientsWaitingListPush(c,c->argv[1],c->argv[2])) {
-            addReply(c,shared.ok);
+            addReply(c,shared.cone);
             return;
         }
         list = lobj->ptr;
@@ -4106,7 +4106,7 @@ static void pushGenericCommand(redisClient *c, int where) {
         incrRefCount(c->argv[2]);
     }
     server.dirty++;
-    addReply(c,shared.ok);
+    addReplySds(c,sdscatprintf(sdsempty(),":%d\r\n",listLength(list)));
 }
 
 static void lpushCommand(redisClient *c) {