@@ -361,7 +361,7 @@ struct redisServer {
     redisClient *master;    /* client that is master for this slave */
     int replstate;
     unsigned int maxclients;
-    unsigned long maxmemory;
+    unsigned long long maxmemory;
     unsigned int blockedclients;
     /* Sort parameters - qsort_r() is only available under BSD so we
      * have to take this state global, in order to pass it to sortCompare() */
@@ -372,7 +372,7 @@ struct redisServer {
     int vm_enabled;
     off_t vm_page_size;
     off_t vm_pages;
-    long vm_max_memory;
+    unsigned long long vm_max_memory;
     /* Virtual memory state */
     FILE *vm_fp;
     int vm_fd;
@@ -459,6 +459,7 @@ static void addReplySds(redisClient *c, sds s);
 static void incrRefCount(robj *o);
 static int rdbSaveBackground(char *filename);
 static robj *createStringObject(char *ptr, size_t len);
+static robj *dupStringObject(robj *o);
 static void replicationFeedSlaves(list *slaves, struct redisCommand *cmd, int dictid, robj **argv, int argc);
 static void feedAppendOnlyFile(struct redisCommand *cmd, int dictid, robj **argv, int argc);
 static int syncWithMaster(void);
@@ -491,6 +492,7 @@ static int handleClientsWaitingListPush(redisClient *c, robj *key, robj *ele);
 static void vmInit(void);
 static void vmMarkPagesFree(off_t page, off_t count);
 static robj *vmLoadObject(robj *key);
+static int vmSwapOneObject(void);
 
 static void authCommand(redisClient *c);
 static void pingCommand(redisClient *c);
@@ -1153,7 +1155,7 @@ static int serverCron(struct aeEventLoop *eventLoop, long long id, void *clientD
         /* Continue to expire if at the end of the cycle more than 25%
          * of the keys were expired. */
         do {
-            int num = dictSize(db->expires);
+            long num = dictSize(db->expires);
             time_t now = time(NULL);
 
             expired = 0;
@@ -1173,6 +1175,15 @@ static int serverCron(struct aeEventLoop *eventLoop, long long id, void *clientD
         } while (expired > REDIS_EXPIRELOOKUPS_PER_CRON/4);
     }
 
+    /* Swap a few keys on disk if we are over the memory limit and VM
+     * is enbled. */
+    while (server.vm_enabled && zmalloc_used_memory() > server.vm_max_memory) {
+        if (vmSwapOneObject() == REDIS_ERR) {
+            redisLog(REDIS_WARNING,"WARNING: vm-max-memory limit reached but unable to swap more objects out!");
+            break;
+        }
+    }
+
     /* Check if we should connect to a MASTER */
     if (server.replstate == REDIS_REPL_CONNECT) {
         redisLog(REDIS_NOTICE,"Connecting to MASTER...");
@@ -1502,6 +1513,12 @@ static void loadServerConfig(char *filename) {
             if ((server.vm_enabled = yesnotoi(argv[1])) == -1) {
                 err = "argument must be 'yes' or 'no'"; goto loaderr;
             }
+        } else if (!strcasecmp(argv[0],"vm-max-memory") && argc == 2) {
+            server.vm_max_memory = strtoll(argv[1], NULL, 10);
+        } else if (!strcasecmp(argv[0],"vm-page-size") && argc == 2) {
+            server.vm_page_size = strtoll(argv[1], NULL, 10);
+        } else if (!strcasecmp(argv[0],"vm-pages") && argc == 2) {
+            server.vm_pages = strtoll(argv[1], NULL, 10);
         } else {
             err = "Bad directive or wrong number of arguments"; goto loaderr;
         }
@@ -2278,6 +2295,10 @@ static robj *createStringObject(char *ptr, size_t len) {
     return createObject(REDIS_STRING,sdsnewlen(ptr,len));
 }
 
+static robj *dupStringObject(robj *o) {
+    return createStringObject(o->ptr,sdslen(o->ptr));
+}
+
 static robj *createListObject(void) {
     list *l = listCreate();
 
@@ -6656,6 +6677,8 @@ static void vmInit(void) {
         redisLog(REDIS_NOTICE,"Swap file allocated with success");
     }
     server.vm_bitmap = zmalloc((server.vm_pages+7)/8);
+    redisLog(REDIS_DEBUG,"Allocated %lld bytes page table for %lld pages",
+        (long long) (server.vm_pages+7)/8, server.vm_pages);
     memset(server.vm_bitmap,0,(server.vm_pages+7)/8);
     /* Try to remove the swap file, so the OS will really delete it from the
      * file system when Redis exists. */
@@ -6667,7 +6690,8 @@ static void vmMarkPageUsed(off_t page) {
     off_t byte = page/8;
     int bit = page&7;
     server.vm_bitmap[byte] |= 1<<bit;
-    printf("Mark used: %lld (byte:%d bit:%d)\n", (long long)page, byte, bit);
+    printf("Mark used: %lld (byte:%lld bit:%d)\n", (long long)page,
+        (long long)byte, bit);
 }
 
 /* Mark N contiguous pages as used, with 'page' being the first. */
@@ -6782,6 +6806,7 @@ static int vmSwapObject(robj *key, robj *val) {
     off_t page;
 
     assert(key->storage == REDIS_VM_MEMORY);
+    assert(key->refcount == 1);
     if (vmFindContiguousPages(&page,pages) == REDIS_ERR) return REDIS_ERR;
     if (fseeko(server.vm_fp,page*server.vm_page_size,SEEK_SET) == -1) {
         redisLog(REDIS_WARNING,
@@ -6827,6 +6852,123 @@ static robj *vmLoadObject(robj *key) {
     return val;
 }
 
+/* How a good candidate is this object for swapping?
+ * The better candidate it is, the greater the returned value.
+ *
+ * Currently we try to perform a fast estimation of the object size in
+ * memory, and combine it with aging informations.
+ *
+ * Basically swappability = idle-time * log(estimated size)
+ *
+ * Bigger objects are preferred over smaller objects, but not
+ * proportionally, this is why we use the logarithm. This algorithm is
+ * just a first try and will probably be tuned later. */
+static double computeObjectSwappability(robj *o) {
+    time_t age = server.unixtime - o->vm.atime;
+    long asize = 0;
+    list *l;
+    dict *d;
+    struct dictEntry *de;
+    int z;
+
+    if (age <= 0) return 0;
+    switch(o->type) {
+    case REDIS_STRING:
+        if (o->encoding != REDIS_ENCODING_RAW) {
+            asize = sizeof(*o);
+        } else {
+            asize = sdslen(o->ptr)+sizeof(*o)+sizeof(long)*2;
+        }
+        break;
+    case REDIS_LIST:
+        l = o->ptr;
+        listNode *ln = listFirst(l);
+
+        asize = sizeof(list);
+        if (ln) {
+            robj *ele = ln->value;
+            long elesize;
+
+            elesize = (ele->encoding == REDIS_ENCODING_RAW) ?
+                            (sizeof(*o)+sdslen(ele->ptr)) :
+                            sizeof(*o);
+            asize += (sizeof(listNode)+elesize)*listLength(l);
+        }
+        break;
+    case REDIS_SET:
+    case REDIS_ZSET:
+        z = (o->type == REDIS_ZSET);
+        d = z ? ((zset*)o->ptr)->dict : o->ptr;
+
+        asize = sizeof(dict)+(sizeof(struct dictEntry*)*dictSlots(d));
+        if (z) asize += sizeof(zset)-sizeof(dict);
+        if (dictSize(d)) {
+            long elesize;
+            robj *ele;
+
+            de = dictGetRandomKey(d);
+            ele = dictGetEntryKey(de);
+            elesize = (ele->encoding == REDIS_ENCODING_RAW) ?
+                            (sizeof(*o)+sdslen(ele->ptr)) :
+                            sizeof(*o);
+            asize += (sizeof(struct dictEntry)+elesize)*dictSize(d);
+            if (z) asize += sizeof(zskiplistNode)*dictSize(d);
+        }
+        break;
+    }
+    return (double)asize*log(1+asize);
+}
+
+/* Try to swap an object that's a good candidate for swapping.
+ * Returns REDIS_OK if the object was swapped, REDIS_ERR if it's not possible
+ * to swap any object at all. */
+static int vmSwapOneObject(void) {
+    int j, i;
+    struct dictEntry *best = NULL;
+    double best_swappability = 0;
+    robj *key, *val;
+
+    for (j = 0; j < server.dbnum; j++) {
+        redisDb *db = server.db+j;
+
+        if (dictSize(db->dict) == 0) continue;
+        for (i = 0; i < 5; i++) {
+            dictEntry *de;
+            double swappability;
+
+            de = dictGetRandomKey(db->dict);
+            key = dictGetEntryKey(de);
+            val = dictGetEntryVal(de);
+            if (key->storage != REDIS_VM_MEMORY) continue;
+            swappability = computeObjectSwappability(val);
+            if (!best || swappability > best_swappability) {
+                best = de;
+                best_swappability = swappability;
+            }
+        }
+    }
+    if (best == NULL) return REDIS_ERR;
+    key = dictGetEntryKey(best);
+    val = dictGetEntryVal(best);
+
+    redisLog(REDIS_DEBUG,"Key with best swappability: %s, %f\n",
+        key->ptr, best_swappability);
+
+    /* Unshare the key if needed */
+    if (key->refcount > 1) {
+        robj *newkey = dupStringObject(key);
+        decrRefCount(key);
+        key = dictGetEntryKey(best) = newkey;
+    }
+    /* Swap it */
+    if (vmSwapObject(key,val) == REDIS_OK) {
+        dictGetEntryVal(best) = NULL;
+        return REDIS_OK;
+    } else {
+        return REDIS_ERR;
+    }
+}
+
 /* ================================= Debugging ============================== */
 
 static void debugCommand(redisClient *c) {
@@ -6880,6 +7022,13 @@ static void debugCommand(redisClient *c) {
         }
         key = dictGetEntryKey(de);
         val = dictGetEntryVal(de);
+        /* If the key is shared we want to create a copy */
+        if (key->refcount > 1) {
+            robj *newkey = dupStringObject(key);
+            decrRefCount(key);
+            key = dictGetEntryKey(de) = newkey;
+        }
+        /* Swap it */
         if (key->storage != REDIS_VM_MEMORY) {
             addReplySds(c,sdsnew("-ERR This key is not in memory\r\n"));
         } else if (vmSwapObject(key,val) == REDIS_OK) {