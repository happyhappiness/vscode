@@ -492,7 +492,9 @@ static int handleClientsWaitingListPush(redisClient *c, robj *key, robj *ele);
 static void vmInit(void);
 static void vmMarkPagesFree(off_t page, off_t count);
 static robj *vmLoadObject(robj *key);
+static robj *vmPreviewObject(robj *key);
 static int vmSwapOneObject(void);
+static int vmCanSwapOut(void);
 
 static void authCommand(redisClient *c);
 static void pingCommand(redisClient *c);
@@ -1177,10 +1179,16 @@ static int serverCron(struct aeEventLoop *eventLoop, long long id, void *clientD
 
     /* Swap a few keys on disk if we are over the memory limit and VM
      * is enbled. */
-    while (server.vm_enabled && zmalloc_used_memory() > server.vm_max_memory) {
-        if (vmSwapOneObject() == REDIS_ERR) {
-            redisLog(REDIS_WARNING,"WARNING: vm-max-memory limit reached but unable to swap more objects out!");
-            break;
+    if (vmCanSwapOut()) {
+        while (server.vm_enabled && zmalloc_used_memory() >
+                server.vm_max_memory) {
+            if (vmSwapOneObject() == REDIS_ERR) {
+                if (zmalloc_used_memory() >
+                    (server.vm_max_memory+server.vm_max_memory/10)) {
+                    redisLog(REDIS_WARNING,"WARNING: vm-max-memory limit exceeded by more than 10%% but unable to swap more objects out!");
+                }
+                break;
+            }
         }
     }
 
@@ -2877,11 +2885,28 @@ static int rdbSave(char *filename) {
                 if (rdbSaveType(fp,REDIS_EXPIRETIME) == -1) goto werr;
                 if (rdbSaveTime(fp,expiretime) == -1) goto werr;
             }
-            /* Save the key and associated value */
-            if (rdbSaveType(fp,o->type) == -1) goto werr;
-            if (rdbSaveStringObject(fp,key) == -1) goto werr;
-            /* Save the actual value */
-            if (rdbSaveObject(fp,o) == -1) goto werr;
+            /* Save the key and associated value. This requires special
+             * handling if the value is swapped out. */
+            if (key->storage == REDIS_VM_MEMORY) {
+                /* Save type, key, value */
+                if (rdbSaveType(fp,o->type) == -1) goto werr;
+                if (rdbSaveStringObject(fp,key) == -1) goto werr;
+                if (rdbSaveObject(fp,o) == -1) goto werr;
+            } else {
+                robj *po, *newkey;
+                /* Get a preview of the object in memory */
+                po = vmPreviewObject(key);
+                /* Also duplicate the key object, to pass around a standard
+                 * string object. */
+                newkey = dupStringObject(key);
+                /* Save type, key, value */
+                if (rdbSaveType(fp,key->vtype) == -1) goto werr;
+                if (rdbSaveStringObject(fp,newkey) == -1) goto werr;
+                if (rdbSaveObject(fp,po) == -1) goto werr;
+                /* Remove the loaded object from memory */
+                decrRefCount(po);
+                decrRefCount(newkey);
+            }
         }
         dictReleaseIterator(di);
     }
@@ -6833,8 +6858,11 @@ static int vmSwapObject(robj *key, robj *val) {
 }
 
 /* Load the value object relative to the 'key' object from swap to memory.
- * The newly allocated object is returned. */
-static robj *vmLoadObject(robj *key) {
+ * The newly allocated object is returned.
+ *
+ * If preview is true the unserialized object is returned to the caller but
+ * no changes are made to the key object, nor the pages are marked as freed */
+static robj *vmGenericLoadObject(robj *key, int preview) {
     robj *val;
 
     assert(key->storage == REDIS_VM_SWAPPED);
@@ -6849,14 +6877,29 @@ static robj *vmLoadObject(robj *key) {
         redisLog(REDIS_WARNING, "Unrecoverable VM problem in vmLoadObject(): can't load object from swap file: %s", strerror(errno));
         exit(1);
     }
-    key->storage = REDIS_VM_MEMORY;
-    key->vm.atime = server.unixtime;
-    vmMarkPagesFree(key->vm.page,key->vm.usedpages);
-    redisLog(REDIS_DEBUG, "VM: object %s loaded from disk",
-        (unsigned char*) key->ptr);
+    if (!preview) {
+        key->storage = REDIS_VM_MEMORY;
+        key->vm.atime = server.unixtime;
+        vmMarkPagesFree(key->vm.page,key->vm.usedpages);
+        redisLog(REDIS_DEBUG, "VM: object %s loaded from disk",
+            (unsigned char*) key->ptr);
+    }
     return val;
 }
 
+/* Plain object loading, from swap to memory */
+static robj *vmLoadObject(robj *key) {
+    return vmGenericLoadObject(key,0);
+}
+
+/* Just load the value on disk, without to modify the key.
+ * This is useful when we want to perform some operation on the value
+ * without to really bring it from swap to memory, like while saving the
+ * dataset or rewriting the append only log. */
+static robj *vmPreviewObject(robj *key) {
+    return vmGenericLoadObject(key,1);
+}
+
 /* How a good candidate is this object for swapping?
  * The better candidate it is, the greater the returned value.
  *
@@ -6982,6 +7025,13 @@ static int vmSwapOneObject(void) {
     }
 }
 
+/* Return true if it's safe to swap out objects in a given moment.
+ * Basically we don't want to swap objects out while there is a BGSAVE
+ * or a BGAEOREWRITE running in backgroud. */
+static int vmCanSwapOut(void) {
+    return (server.bgsavechildpid == -1 && server.bgrewritechildpid == -1);
+}
+
 /* ================================= Debugging ============================== */
 
 static void debugCommand(redisClient *c) {