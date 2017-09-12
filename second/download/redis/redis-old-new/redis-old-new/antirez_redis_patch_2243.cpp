@@ -2468,7 +2468,7 @@ static size_t stringObjectLen(robj *o) {
     }
 }
 
-/*============================ DB saving/loading ============================ */
+/*============================ RDB saving/loading =========================== */
 
 static int rdbSaveType(FILE *fp, unsigned char type) {
     if (fwrite(&type,1,1,fp) == 0) return -1;
@@ -2641,6 +2641,72 @@ static int rdbSaveDoubleValue(FILE *fp, double val) {
     return 0;
 }
 
+/* Save a Redis object. */
+static int rdbSaveObject(FILE *fp, robj *o) {
+    if (o->type == REDIS_STRING) {
+        /* Save a string value */
+        if (rdbSaveStringObject(fp,o) == -1) return -1;
+    } else if (o->type == REDIS_LIST) {
+        /* Save a list value */
+        list *list = o->ptr;
+        listNode *ln;
+
+        listRewind(list);
+        if (rdbSaveLen(fp,listLength(list)) == -1) return -1;
+        while((ln = listYield(list))) {
+            robj *eleobj = listNodeValue(ln);
+
+            if (rdbSaveStringObject(fp,eleobj) == -1) return -1;
+        }
+    } else if (o->type == REDIS_SET) {
+        /* Save a set value */
+        dict *set = o->ptr;
+        dictIterator *di = dictGetIterator(set);
+        dictEntry *de;
+
+        if (rdbSaveLen(fp,dictSize(set)) == -1) return -1;
+        while((de = dictNext(di)) != NULL) {
+            robj *eleobj = dictGetEntryKey(de);
+
+            if (rdbSaveStringObject(fp,eleobj) == -1) return -1;
+        }
+        dictReleaseIterator(di);
+    } else if (o->type == REDIS_ZSET) {
+        /* Save a set value */
+        zset *zs = o->ptr;
+        dictIterator *di = dictGetIterator(zs->dict);
+        dictEntry *de;
+
+        if (rdbSaveLen(fp,dictSize(zs->dict)) == -1) return -1;
+        while((de = dictNext(di)) != NULL) {
+            robj *eleobj = dictGetEntryKey(de);
+            double *score = dictGetEntryVal(de);
+
+            if (rdbSaveStringObject(fp,eleobj) == -1) return -1;
+            if (rdbSaveDoubleValue(fp,*score) == -1) return -1;
+        }
+        dictReleaseIterator(di);
+    } else {
+        redisAssert(0 != 0);
+    }
+    return 0;
+}
+
+/* Return the length the object will have on disk if saved with
+ * the rdbSaveObject() function. Currently we use a trick to get
+ * this length with very little changes to the code. In the future
+ * we could switch to a faster solution. */
+static off_t rdbSavedObjectLen(robj *o) {
+    static FILE *fp = NULL;
+
+    if (fp == NULL) fp = fopen("/dev/null","w");
+    assert(fp != NULL);
+
+    rewind(fp);
+    assert(rdbSaveObject(fp,o) != 1);
+    return ftello(fp);
+}
+
 /* Save the DB on disk. Return REDIS_ERR on error, REDIS_OK on success */
 static int rdbSave(char *filename) {
     dictIterator *di = NULL;
@@ -2687,52 +2753,8 @@ static int rdbSave(char *filename) {
             /* Save the key and associated value */
             if (rdbSaveType(fp,o->type) == -1) goto werr;
             if (rdbSaveStringObject(fp,key) == -1) goto werr;
-            if (o->type == REDIS_STRING) {
-                /* Save a string value */
-                if (rdbSaveStringObject(fp,o) == -1) goto werr;
-            } else if (o->type == REDIS_LIST) {
-                /* Save a list value */
-                list *list = o->ptr;
-                listNode *ln;
-
-                listRewind(list);
-                if (rdbSaveLen(fp,listLength(list)) == -1) goto werr;
-                while((ln = listYield(list))) {
-                    robj *eleobj = listNodeValue(ln);
-
-                    if (rdbSaveStringObject(fp,eleobj) == -1) goto werr;
-                }
-            } else if (o->type == REDIS_SET) {
-                /* Save a set value */
-                dict *set = o->ptr;
-                dictIterator *di = dictGetIterator(set);
-                dictEntry *de;
-
-                if (rdbSaveLen(fp,dictSize(set)) == -1) goto werr;
-                while((de = dictNext(di)) != NULL) {
-                    robj *eleobj = dictGetEntryKey(de);
-
-                    if (rdbSaveStringObject(fp,eleobj) == -1) goto werr;
-                }
-                dictReleaseIterator(di);
-            } else if (o->type == REDIS_ZSET) {
-                /* Save a set value */
-                zset *zs = o->ptr;
-                dictIterator *di = dictGetIterator(zs->dict);
-                dictEntry *de;
-
-                if (rdbSaveLen(fp,dictSize(zs->dict)) == -1) goto werr;
-                while((de = dictNext(di)) != NULL) {
-                    robj *eleobj = dictGetEntryKey(de);
-                    double *score = dictGetEntryVal(de);
-
-                    if (rdbSaveStringObject(fp,eleobj) == -1) goto werr;
-                    if (rdbSaveDoubleValue(fp,*score) == -1) goto werr;
-                }
-                dictReleaseIterator(di);
-            } else {
-                redisAssert(0 != 0);
-            }
+            /* Save the actual value */
+            if (rdbSaveObject(fp,o) == -1) goto werr;
         }
         dictReleaseIterator(di);
     }
@@ -6546,9 +6568,9 @@ static void debugCommand(redisClient *c) {
         key = dictGetEntryKey(de);
         val = dictGetEntryVal(de);
         addReplySds(c,sdscatprintf(sdsempty(),
-            "+Key at:%p refcount:%d, value at:%p refcount:%d encoding:%d\r\n",
+            "+Key at:%p refcount:%d, value at:%p refcount:%d encoding:%d serializedlength:%lld\r\n",
                 (void*)key, key->refcount, (void*)val, val->refcount,
-                val->encoding));
+                val->encoding, rdbSavedObjectLen(val)));
     } else {
         addReplySds(c,sdsnew(
             "-ERR Syntax error, try DEBUG [SEGFAULT|OBJECT <key>|RELOAD]\r\n"));