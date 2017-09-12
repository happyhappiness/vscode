@@ -6653,8 +6653,8 @@ static void vmInit(void) {
     } else {
         redisLog(REDIS_NOTICE,"Swap file allocated with success");
     }
-    server.vm_bitmap = zmalloc((server.vm_near_pages+7)/8);
-    memset(server.vm_bitmap,0,(server.vm_near_pages+7)/8);
+    server.vm_bitmap = zmalloc((server.vm_pages+7)/8);
+    memset(server.vm_bitmap,0,(server.vm_pages+7)/8);
     /* Try to remove the swap file, so the OS will really delete it from the
      * file system when Redis exists. */
     unlink("/tmp/redisvm");
@@ -6665,14 +6665,15 @@ static void vmMarkPageUsed(off_t page) {
     off_t byte = page/8;
     int bit = page&7;
     server.vm_bitmap[byte] |= 1<<bit;
+    printf("Mark used: %lld (byte:%d bit:%d)\n", (long long)page, byte, bit);
 }
 
 /* Mark N contiguous pages as used, with 'page' being the first. */
 static void vmMarkPagesUsed(off_t page, off_t count) {
     off_t j;
 
     for (j = 0; j < count; j++)
-        vmMarkPageUsed(page+count);
+        vmMarkPageUsed(page+j);
 }
 
 /* Mark the page as free */
@@ -6687,14 +6688,14 @@ static void vmMarkPagesFree(off_t page, off_t count) {
     off_t j;
 
     for (j = 0; j < count; j++)
-        vmMarkPageFree(page+count);
+        vmMarkPageFree(page+j);
 }
 
 /* Test if the page is free */
 static int vmFreePage(off_t page) {
     off_t byte = page/8;
     int bit = page&7;
-    return server.vm_bitmap[byte] & bit;
+    return (server.vm_bitmap[byte] & (1<<bit)) == 0;
 }
 
 /* Find N contiguous free pages storing the first page of the cluster in *first.
@@ -6729,6 +6730,7 @@ static int vmFindContiguousPages(off_t *first, int n) {
     while(offset < server.vm_pages) {
         off_t this = base+offset;
 
+        printf("THIS: %lld (%c)\n", (long long) this, vmFreePage(this) ? 'F' : 'X');
         /* If we overflow, restart from page zero */
         if (this >= server.vm_pages) {
             this -= server.vm_pages;
@@ -6743,7 +6745,8 @@ static int vmFindContiguousPages(off_t *first, int n) {
             numfree++;
             /* Already got N free pages? Return to the caller, with success */
             if (numfree == n) {
-                *first = this;
+                *first = this-(n-1);
+                server.vm_next_page = this+1;
                 return REDIS_OK;
             }
         } else {
@@ -6790,6 +6793,9 @@ static int vmSwapObject(robj *key, robj *val) {
     key->storage = REDIS_VM_SWAPPED;
     decrRefCount(val); /* Deallocate the object from memory. */
     vmMarkPagesUsed(page,pages);
+    redisLog(REDIS_DEBUG,"VM: object %s swapped out at %lld (%lld pages)",
+        (unsigned char*) key->ptr,
+        (unsigned long long) page, (unsigned long long) pages);
     return REDIS_OK;
 }
 
@@ -6813,6 +6819,8 @@ static robj *vmLoadObject(robj *key) {
     key->storage = REDIS_VM_MEMORY;
     key->vm.atime = server.unixtime;
     vmMarkPagesFree(key->vm.page,key->vm.usedpages);
+    redisLog(REDIS_DEBUG, "VM: object %s loaded from disk",
+        (unsigned char*) key->ptr);
     return val;
 }
 
@@ -6855,9 +6863,31 @@ static void debugCommand(redisClient *c) {
             "+Key at:%p refcount:%d, value at:%p refcount:%d encoding:%d serializedlength:%lld\r\n",
                 (void*)key, key->refcount, (void*)val, val->refcount,
                 val->encoding, rdbSavedObjectLen(val)));
+    } else if (!strcasecmp(c->argv[1]->ptr,"swapout") && c->argc == 3) {
+        dictEntry *de = dictFind(c->db->dict,c->argv[2]);
+        robj *key, *val;
+
+        if (!server.vm_enabled) {
+            addReplySds(c,sdsnew("-ERR Virtual Memory is disabled\r\n"));
+            return;
+        }
+        if (!de) {
+            addReply(c,shared.nokeyerr);
+            return;
+        }
+        key = dictGetEntryKey(de);
+        val = dictGetEntryVal(de);
+        if (key->storage != REDIS_VM_MEMORY) {
+            addReplySds(c,sdsnew("-ERR This key is not in memory\r\n"));
+        } else if (vmSwapObject(key,val) == REDIS_OK) {
+            dictGetEntryVal(de) = NULL;
+            addReply(c,shared.ok);
+        } else {
+            addReply(c,shared.err);
+        }
     } else {
         addReplySds(c,sdsnew(
-            "-ERR Syntax error, try DEBUG [SEGFAULT|OBJECT <key>|RELOAD]\r\n"));
+            "-ERR Syntax error, try DEBUG [SEGFAULT|OBJECT <key>|SWAPOUT <key>|RELOAD]\r\n"));
     }
 }
 