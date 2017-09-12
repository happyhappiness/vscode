@@ -202,7 +202,7 @@ void sortCommand(redisClient *c) {
     /* Load the sorting vector with all the objects to sort */
     switch(sortval->type) {
     case REDIS_LIST: vectorlen = listTypeLength(sortval); break;
-    case REDIS_SET: vectorlen =  dictSize((dict*)sortval->ptr); break;
+    case REDIS_SET: vectorlen =  setTypeSize(sortval); break;
     case REDIS_ZSET: vectorlen = dictSize(((zset*)sortval->ptr)->dict); break;
     default: vectorlen = 0; redisPanic("Bad SORT type"); /* Avoid GCC warning */
     }
@@ -219,18 +219,20 @@ void sortCommand(redisClient *c) {
             j++;
         }
         listTypeReleaseIterator(li);
-    } else {
-        dict *set;
+    } else if (sortval->type == REDIS_SET) {
+        setTypeIterator *si = setTypeInitIterator(sortval);
+        robj *ele;
+        while((ele = setTypeNext(si)) != NULL) {
+            vector[j].obj = ele;
+            vector[j].u.score = 0;
+            vector[j].u.cmpobj = NULL;
+            j++;
+        }
+        setTypeReleaseIterator(si);
+    } else if (sortval->type == REDIS_ZSET) {
+        dict *set = ((zset*)sortval->ptr)->dict;
         dictIterator *di;
         dictEntry *setele;
-
-        if (sortval->type == REDIS_SET) {
-            set = sortval->ptr;
-        } else {
-            zset *zs = sortval->ptr;
-            set = zs->dict;
-        }
-
         di = dictGetIterator(set);
         while((setele = dictNext(di)) != NULL) {
             vector[j].obj = dictGetEntryKey(setele);
@@ -239,6 +241,8 @@ void sortCommand(redisClient *c) {
             j++;
         }
         dictReleaseIterator(di);
+    } else {
+        redisPanic("Unknown type");
     }
     redisAssert(j == vectorlen);
 
@@ -303,7 +307,7 @@ void sortCommand(redisClient *c) {
     outputlen = getop ? getop*(end-start+1) : end-start+1;
     if (storekey == NULL) {
         /* STORE option not specified, sent the sorting result to client */
-        addReplySds(c,sdscatprintf(sdsempty(),"*%d\r\n",outputlen));
+        addReplyMultiBulkLen(c,outputlen);
         for (j = start; j <= end; j++) {
             listNode *ln;
             listIter li;
@@ -365,11 +369,11 @@ void sortCommand(redisClient *c) {
          * replaced. */
         server.dirty += 1+outputlen;
         touchWatchedKey(c->db,storekey);
-        addReplySds(c,sdscatprintf(sdsempty(),":%d\r\n",outputlen));
+        addReplyLongLong(c,outputlen);
     }
 
     /* Cleanup */
-    if (sortval->type == REDIS_LIST)
+    if (sortval->type == REDIS_LIST || sortval->type == REDIS_SET)
         for (j = 0; j < vectorlen; j++)
             decrRefCount(vector[j].obj);
     decrRefCount(sortval);