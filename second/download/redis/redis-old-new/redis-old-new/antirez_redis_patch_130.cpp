@@ -700,7 +700,7 @@ char *strEncoding(int encoding) {
  * are checked and averaged to estimate the total size. */
 #define OBJ_COMPUTE_SIZE_DEF_SAMPLES 5 /* Default sample size. */
 size_t objectComputeSize(robj *o, size_t sample_size) {
-    robj *ele;
+    sds ele, ele2;
     dict *d;
     dictIterator *di;
     struct dictEntry *de;
@@ -709,8 +709,7 @@ size_t objectComputeSize(robj *o, size_t sample_size) {
     if (o->type == OBJ_STRING) {
         if(o->encoding == OBJ_ENCODING_INT) {
             asize = sizeof(*o);
-        }
-        else if(o->encoding == OBJ_ENCODING_RAW) {
+        } else if(o->encoding == OBJ_ENCODING_RAW) {
             asize = sdsAllocSize(o->ptr)+sizeof(*o);
         } else if(o->encoding == OBJ_ENCODING_EMBSTR) {
             asize = sdslen(o->ptr)+2+sizeof(*o);
@@ -739,9 +738,7 @@ size_t objectComputeSize(robj *o, size_t sample_size) {
             asize = sizeof(*o)+sizeof(dict)+(sizeof(struct dictEntry*)*dictSlots(d));
             while((de = dictNext(di)) != NULL && samples < sample_size) {
                 ele = dictGetKey(de);
-                elesize += (ele->encoding == OBJ_ENCODING_RAW) ?
-                                (sizeof(*o)+sdsAllocSize(ele->ptr)) : sizeof(*o);
-                elesize += sizeof(struct dictEntry);
+                elesize += sizeof(struct dictEntry) + sdsAllocSize(ele);
                 samples++;
             }
             dictReleaseIterator(di);
@@ -761,10 +758,8 @@ size_t objectComputeSize(robj *o, size_t sample_size) {
             asize = sizeof(*o)+sizeof(zset)+(sizeof(struct dictEntry*)*dictSlots(d));
             while((de = dictNext(di)) != NULL && samples < sample_size) {
                 ele = dictGetKey(de);
-                elesize += (ele->encoding == OBJ_ENCODING_RAW) ?
-                                (sizeof(*o)+sdsAllocSize(ele->ptr)) : sizeof(*o);
-                elesize += sizeof(struct dictEntry);
-                elesize += sizeof(zskiplistNode)*dictSize(d);
+                elesize += sdsAllocSize(ele);
+                elesize += sizeof(struct dictEntry) + sizeof(zskiplistNode);
                 samples++;
             }
             dictReleaseIterator(di);
@@ -781,14 +776,10 @@ size_t objectComputeSize(robj *o, size_t sample_size) {
             asize = sizeof(*o)+sizeof(dict)+(sizeof(struct dictEntry*)*dictSlots(d));
             while((de = dictNext(di)) != NULL && samples < sample_size) {
                 ele = dictGetKey(de);
-                elesize += (ele->encoding == OBJ_ENCODING_RAW) ?
-                                (sizeof(*o)+sdsAllocSize(ele->ptr)) : sizeof(*o);
-                ele = dictGetVal(de);
-                elesize += (ele->encoding == OBJ_ENCODING_RAW) ?
-                                (sizeof(*o)+sdsAllocSize(ele->ptr)) : sizeof(*o);
+                ele2 = dictGetVal(de);
+                elesize += sdsAllocSize(ele) + sdsAllocSize(ele2);
                 elesize += sizeof(struct dictEntry);
                 samples++;
-                printf("%zu samples: %zu usage\n", samples, elesize);
             }
             dictReleaseIterator(di);
             if (samples) asize += (double)elesize/samples*dictSize(d);
@@ -955,10 +946,28 @@ struct redisMemOverhead *getMemoryOverheadData(void) {
 void memoryCommand(client *c) {
     robj *o;
 
-    if (!strcasecmp(c->argv[1]->ptr,"usage") && c->argc == 3) {
+    if (!strcasecmp(c->argv[1]->ptr,"usage") && c->argc >= 3) {
+        long long samples = OBJ_COMPUTE_SIZE_DEF_SAMPLES;
+        for (int j = 3; j < c->argc; j++) {
+            if (!strcasecmp(c->argv[j]->ptr,"samples") &&
+                j+1 < c->argc)
+            {
+                if (getLongLongFromObjectOrReply(c,c->argv[j+1],&samples,NULL)
+                     == C_ERR) return;
+                if (samples < 0) {
+                    addReply(c,shared.syntaxerr);
+                    return;
+                }
+                if (samples == 0) samples = LLONG_MAX;;
+                j++; /* skip option argument. */
+            } else {
+                addReply(c,shared.syntaxerr);
+                return;
+            }
+        }
         if ((o = objectCommandLookupOrReply(c,c->argv[2],shared.nullbulk))
                 == NULL) return;
-        size_t usage = objectComputeSize(o,OBJ_COMPUTE_SIZE_DEF_SAMPLES);
+        size_t usage = objectComputeSize(o,samples);
         usage += sdsAllocSize(c->argv[1]->ptr);
         usage += sizeof(dictEntry);
         addReplyLongLong(c,usage);