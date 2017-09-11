@@ -694,16 +694,17 @@ char *strEncoding(int encoding) {
 
 /* ========================== Objects introspection ========================= */
 
-/* Returns the size in bytes consumed by the key's value in RAM */
-size_t objectComputeSize(robj *o) {
+/* Returns the size in bytes consumed by the key's value in RAM.
+ * Note that the returned value is just an approximation, especially in the
+ * case of aggregated data types where only "sample_size" elements
+ * are checked and averaged to estimate the total size. */
+#define OBJ_COMPUTE_SIZE_DEF_SAMPLES 5 /* Default sample size. */
+size_t objectComputeSize(robj *o, size_t sample_size) {
     robj *ele;
-    list *l;
-    listNode *ln;
     dict *d;
     dictIterator *di;
-    listIter li;
     struct dictEntry *de;
-    size_t asize = 0, elesize;
+    size_t asize = 0, elesize = 0, samples = 0;
 
     if (o->type == OBJ_STRING) {
         if(o->encoding == OBJ_ENCODING_INT) {
@@ -722,20 +723,12 @@ size_t objectComputeSize(robj *o) {
             quicklistNode *node = ql->head;
             asize = sizeof(*o)+sizeof(quicklist);
             do {
-                asize += sizeof(quicklistNode)+ziplistBlobLen(node->zl);
-            } while ((node = node->next));
+                elesize += sizeof(quicklistNode)+ziplistBlobLen(node->zl);
+                samples++;
+            } while ((node = node->next) && samples < sample_size);
+            asize += (double)elesize/samples*listTypeLength(o);
         } else if (o->encoding == OBJ_ENCODING_ZIPLIST) {
             asize = sizeof(*o)+ziplistBlobLen(o->ptr);
-        } else if (o->encoding == OBJ_ENCODING_LINKEDLIST) {
-            l = o->ptr;
-            asize = sizeof(*o)+sizeof(list);
-            listRewind(l,&li);
-            while((ln = listNext(&li))) {
-                ele = ln->value;
-                elesize = (ele->encoding == OBJ_ENCODING_RAW) ?
-                                (sizeof(*o)+sdsAllocSize(ele->ptr)) : sizeof(*o);
-                asize += (sizeof(listNode)+elesize);
-            }
         } else {
             serverPanic("Unknown list encoding");
         }
@@ -744,13 +737,15 @@ size_t objectComputeSize(robj *o) {
             d = o->ptr;
             di = dictGetIterator(d);
             asize = sizeof(*o)+sizeof(dict)+(sizeof(struct dictEntry*)*dictSlots(d));
-            while((de = dictNext(di)) != NULL) {
+            while((de = dictNext(di)) != NULL && samples < sample_size) {
                 ele = dictGetKey(de);
-                elesize = (ele->encoding == OBJ_ENCODING_RAW) ?
+                elesize += (ele->encoding == OBJ_ENCODING_RAW) ?
                                 (sizeof(*o)+sdsAllocSize(ele->ptr)) : sizeof(*o);
-                asize += (sizeof(struct dictEntry)+elesize);
+                elesize += sizeof(struct dictEntry);
+                samples++;
             }
             dictReleaseIterator(di);
+            if (samples) asize += (double)elesize/samples*dictSize(d);
         } else if (o->encoding == OBJ_ENCODING_INTSET) {
             intset *is = o->ptr;
             asize = sizeof(*o)+sizeof(*is)+is->encoding*is->length;
@@ -764,14 +759,16 @@ size_t objectComputeSize(robj *o) {
             d = ((zset*)o->ptr)->dict;
             di = dictGetIterator(d);
             asize = sizeof(*o)+sizeof(zset)+(sizeof(struct dictEntry*)*dictSlots(d));
-            while((de = dictNext(di)) != NULL) {
+            while((de = dictNext(di)) != NULL && samples < sample_size) {
                 ele = dictGetKey(de);
-                elesize = (ele->encoding == OBJ_ENCODING_RAW) ?
+                elesize += (ele->encoding == OBJ_ENCODING_RAW) ?
                                 (sizeof(*o)+sdsAllocSize(ele->ptr)) : sizeof(*o);
-                asize += (sizeof(struct dictEntry)+elesize);
-                asize += sizeof(zskiplistNode)*dictSize(d);
+                elesize += sizeof(struct dictEntry);
+                elesize += sizeof(zskiplistNode)*dictSize(d);
+                samples++;
             }
             dictReleaseIterator(di);
+            if (samples) asize += (double)elesize/samples*dictSize(d);
         } else {
             serverPanic("Unknown sorted set encoding");
         }
@@ -782,16 +779,19 @@ size_t objectComputeSize(robj *o) {
             d = o->ptr;
             di = dictGetIterator(d);
             asize = sizeof(*o)+sizeof(dict)+(sizeof(struct dictEntry*)*dictSlots(d));
-            while((de = dictNext(di)) != NULL) {
+            while((de = dictNext(di)) != NULL && samples < sample_size) {
                 ele = dictGetKey(de);
-                elesize = (ele->encoding == OBJ_ENCODING_RAW) ?
+                elesize += (ele->encoding == OBJ_ENCODING_RAW) ?
                                 (sizeof(*o)+sdsAllocSize(ele->ptr)) : sizeof(*o);
                 ele = dictGetVal(de);
-                elesize = (ele->encoding == OBJ_ENCODING_RAW) ?
+                elesize += (ele->encoding == OBJ_ENCODING_RAW) ?
                                 (sizeof(*o)+sdsAllocSize(ele->ptr)) : sizeof(*o);
-                asize += (sizeof(struct dictEntry)+elesize);
+                elesize += sizeof(struct dictEntry);
+                samples++;
+                printf("%zu samples: %zu usage\n", samples, elesize);
             }
             dictReleaseIterator(di);
+            if (samples) asize += (double)elesize/samples*dictSize(d);
         } else {
             serverPanic("Unknown hash encoding");
         }
@@ -801,7 +801,7 @@ size_t objectComputeSize(robj *o) {
     return asize;
 }
 
-/* ============================ The OBJECT command ========================== */
+/* ======================= The OBJECT and MEMORY commands =================== */
 
 /* This is a helper function for the OBJECT command. We need to lookup keys
  * without any modification of LRU or other parameters. */
@@ -853,3 +853,21 @@ void objectCommand(client *c) {
     }
 }
 
+/* The memory command will eventually be a complete interface for the
+ * memory introspection capabilities of Redis.
+ *
+ * Usage: MEMORY usage <key> */
+void memoryCommand(client *c) {
+    robj *o;
+
+    if (!strcasecmp(c->argv[1]->ptr,"usage") && c->argc == 3) {
+        if ((o = objectCommandLookupOrReply(c,c->argv[2],shared.nullbulk))
+                == NULL) return;
+        size_t usage = objectComputeSize(o,OBJ_COMPUTE_SIZE_DEF_SAMPLES);
+        usage += sdsAllocSize(c->argv[1]->ptr);
+        usage += sizeof(dictEntry);
+        addReplyLongLong(c,usage);
+    } else {
+        addReplyError(c,"Syntax error. Try MEMORY usage <key>");
+    }
+}