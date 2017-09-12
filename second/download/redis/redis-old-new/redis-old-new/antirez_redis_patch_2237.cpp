@@ -231,8 +231,10 @@ typedef struct redisObject {
     void *ptr;
     unsigned char type;
     unsigned char encoding;
-    unsigned char storage;  /* where? REDIS_VM_MEMORY, REDIS_VM_SWAPPED, ... */
-    unsigned char notused;
+    unsigned char storage;  /* If this object is a key, where is the value?
+                             * REDIS_VM_MEMORY, REDIS_VM_SWAPPED, ... */
+    unsigned char vtype; /* If this object is a key, and value is swapped out,
+                          * this is the type of the swapped out object. */
     int refcount;
     /* VM fields, this are only allocated if VM is active, otherwise the
      * object allocation function will just allocate
@@ -6791,6 +6793,7 @@ static int vmSwapObject(robj *key, robj *val) {
     key->vm.page = page;
     key->vm.usedpages = pages;
     key->storage = REDIS_VM_SWAPPED;
+    key->vtype = val->type;
     decrRefCount(val); /* Deallocate the object from memory. */
     vmMarkPagesUsed(page,pages);
     redisLog(REDIS_DEBUG,"VM: object %s swapped out at %lld (%lld pages)",
@@ -6811,7 +6814,7 @@ static robj *vmLoadObject(robj *key) {
             strerror(errno));
         exit(1);
     }
-    val = rdbLoadObject(key->type,server.vm_fp);
+    val = rdbLoadObject(key->vtype,server.vm_fp);
     if (val == NULL) {
         redisLog(REDIS_WARNING, "Unrecoverable VM problem in vmLoadObject(): can't load object from swap file: %s", strerror(errno));
         exit(1);