@@ -487,6 +487,7 @@ static void queueMultiCommand(redisClient *c, struct redisCommand *cmd);
 static void unblockClient(redisClient *c);
 static int handleClientsWaitingListPush(redisClient *c, robj *key, robj *ele);
 static void vmInit(void);
+static void vmMarkPagesFree(off_t page, off_t count);
 
 static void authCommand(redisClient *c);
 static void pingCommand(redisClient *c);
@@ -836,6 +837,7 @@ static void dictRedisObjectDestructor(void *privdata, void *val)
 {
     DICT_NOTUSED(privdata);
 
+    if (val == NULL) return; /* Values of swapped out keys as set to NULL */
     decrRefCount(val);
 }
 
@@ -2320,20 +2322,25 @@ static void freeHashObject(robj *o) {
 }
 
 static void incrRefCount(robj *o) {
+    assert(!server.vm_enabled || o->storage == REDIS_VM_MEMORY);
     o->refcount++;
-#ifdef DEBUG_REFCOUNT
-    if (o->type == REDIS_STRING)
-        printf("Increment '%s'(%p), now is: %d\n",o->ptr,o,o->refcount);
-#endif
 }
 
 static void decrRefCount(void *obj) {
     robj *o = obj;
 
-#ifdef DEBUG_REFCOUNT
-    if (o->type == REDIS_STRING)
-        printf("Decrement '%s'(%p), now is: %d\n",o->ptr,o,o->refcount-1);
-#endif
+    /* REDIS_VM_SWAPPED */
+    if (server.vm_enabled && o->storage == REDIS_VM_SWAPPED) {
+        assert(o->refcount == 1);
+        assert(o->type == REDIS_STRING);
+        freeStringObject(o);
+        vmMarkPagesFree(o->vm.page,o->vm.usedpages);
+        if (listLength(server.objfreelist) > REDIS_OBJFREELIST_MAX ||
+            !listAddNodeHead(server.objfreelist,o))
+            zfree(o);
+        return;
+    }
+    /* REDIS_VM_MEMORY */
     if (--(o->refcount) == 0) {
         switch(o->type) {
         case REDIS_STRING: freeStringObject(o); break;