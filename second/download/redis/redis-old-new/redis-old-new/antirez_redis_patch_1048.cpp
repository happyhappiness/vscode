@@ -319,32 +319,76 @@ void keysCommand(redisClient *c) {
     setDeferredMultiBulkLength(c,replylen,numkeys);
 }
 
+/* This callback is used by scanGenericCommand in order to collect elements
+ * returned by the dictionary iterator into a list. */
 void scanCallback(void *privdata, const dictEntry *de) {
-    list *keys = (list *)privdata;
-    sds key = dictGetKey(de);
-    robj *kobj = createStringObject(key, sdslen(key));
-    listAddNodeTail(keys, kobj);
+    void **pd = (void**) privdata;
+    list *keys = pd[0];
+    robj *o = pd[1];
+    robj *key, *val = NULL;
+
+    if (o == NULL) {
+        sds sdskey = dictGetKey(de);
+        key = createStringObject(sdskey, sdslen(sdskey));
+    } else if (o->type == REDIS_SET) {
+        key = dictGetKey(de);
+        incrRefCount(key);
+    } else if (o->type == REDIS_HASH) {
+        key = dictGetKey(de);
+        incrRefCount(key);
+        val = dictGetVal(de);
+        incrRefCount(val);
+    } else if (o->type == REDIS_ZSET) {
+        key = dictGetKey(de);
+        incrRefCount(key);
+        val = createStringObjectFromLongDouble(*(double*)dictGetVal(de));
+    } else {
+        redisPanic("Type not handled in SCAN callback.");
+    }
+
+    listAddNodeTail(keys, key);
+    if (val) listAddNodeTail(keys, val);
 }
 
-void scanCommand(redisClient *c) {
+/* This command implements SCAN, HSCAN and SSCAN commands.
+ * If object 'o' is passed, then it must be an Hash or Set object, otherwise
+ * if 'o' is NULL the command will operate on the dictionary associated with
+ * the current database.
+ *
+ * When 'o' is not NULL the function assumes that the first argument in
+ * the client arguments vector is a key so it skips it before iterating
+ * in order to parse options.
+ *
+ * In the case of an Hash object the function returns both the field and value
+ * of every element on the Hash. */
+void scanGenericCommand(redisClient *c, robj *o) {
     int rv;
     int i, j;
     char buf[REDIS_LONGSTR_SIZE];
     list *keys = listCreate();
     listNode *node, *nextnode;
     unsigned long cursor = 0;
-    long count = 1;
+    long count = 10;
     sds pat;
     int patlen, patnoop = 1;
+    dict *ht;
+
+    /* Object must be NULL (to iterate keys names), or the type of the object
+     * must be Set, Sorted Set, or Hash. */
+    redisAssert(o == NULL || o->type == REDIS_SET || o->type == REDIS_HASH ||
+                o->type == REDIS_ZSET);
+
+    /* Set i to the first option argument. The previous one is the cursor. */
+    i = (o == NULL) ? 2 : 3; /* Skip the key argument if needed. */
 
     /* Use sscanf because we need an *unsigned* long */
-    rv = sscanf(c->argv[1]->ptr, "%lu", &cursor);
+    rv = sscanf(c->argv[i-1]->ptr, "%lu", &cursor);
     if (rv != 1) {
         addReplyError(c, "invalid cursor");
         goto cleanup;
     }
 
-    i = 2;
+    /* Step 1: Parse options. */
     while (i < c->argc) {
         j = c->argc - i;
         if (!strcasecmp(c->argv[i]->ptr, "count") && j >= 2) {
@@ -374,29 +418,92 @@ void scanCommand(redisClient *c) {
         }
     }
 
-    do {
-        cursor = dictScan(c->db->dict, cursor, scanCallback, keys);
-    } while (cursor && listLength(keys) < count);
+    /* Step 2: Iterate the collection.
+     *
+     * Note that if the object is encoded with a ziplist, intset, or any other
+     * representation that is not an hash table, we are sure that it is also
+     * composed of a small number of elements. So to avoid taking state we
+     * just return everything inside the object in a single call, setting the
+     * cursor to zero to signal the end of the iteration. */
+
+    /* Handle the case of an hash table. */
+    ht = NULL;
+    if (o == NULL) {
+        ht = c->db->dict;
+    } else if (o->type == REDIS_SET && o->encoding == REDIS_ENCODING_HT) {
+        ht = o->ptr;
+    } else if (o->type == REDIS_HASH && o->encoding == REDIS_ENCODING_HT) {
+        ht = o->ptr;
+        count *= 2; /* We return key / value for this type. */
+    } else if (o->type == REDIS_ZSET && o->encoding == REDIS_ENCODING_SKIPLIST) {
+        zset *zs = o->ptr;
+        ht = zs->dict;
+        count *= 2; /* We return key / value for this type. */
+    }
+
+    if (ht) {
+        void *privdata[2];
+
+        /* We pass two pointers to the callback: the list to which it will
+         * add new elements, and the object containing the dictionary so that
+         * it is possible to fetch more data in a type-dependent way. */
+        privdata[0] = keys;
+        privdata[1] = o;
+        do {
+            cursor = dictScan(ht, cursor, scanCallback, privdata);
+        } while (cursor && listLength(keys) < count);
+    } else if (o->type == REDIS_SET) {
+        int pos = 0;
+        long long ll;
+
+        while(intsetGet(o->ptr,pos++,&ll))
+            listAddNodeTail(keys,createStringObjectFromLongLong(ll));
+    } else if (o->type == REDIS_HASH || o->type == REDIS_ZSET) {
+        unsigned char *p = ziplistIndex(o->ptr,0);
+        unsigned char *vstr;
+        unsigned int vlen;
+        long long vll;
+
+        while(p) {
+            ziplistGet(p,&vstr,&vlen,&vll);
+            listAddNodeTail(keys,
+                (vstr != NULL) ? createStringObject((char*)vstr,vlen) :
+                                 createStringObjectFromLongLong(vll));
+            ziplistNext(o->ptr,p);
+        }
+    } else {
+        redisPanic("Not handled encoding in SCAN.");
+    }
 
-    /* Filter keys */
+    /* Step 3: Filter elements. */
     node = listFirst(keys);
     while (node) {
         robj *kobj = listNodeValue(node);
         nextnode = listNextNode(node);
 
-        /* Keep key iff pattern matches and it hasn't expired */
+        /* Keep key iff pattern matches and, if we are iterating the key
+         * space, check that the key hasn't expired. */
         if ((patnoop ||
              stringmatchlen(pat, patlen, kobj->ptr, sdslen(kobj->ptr), 0)) &&
-            (expireIfNeeded(c->db, kobj) == 0))
+            (o != NULL || expireIfNeeded(c->db, kobj) == 0))
         {
             /* Keep */
         } else {
             decrRefCount(kobj);
             listDelNode(keys, node);
+            /* Also remove the value for hashes and sorted sets. */
+            if (o && (o->type == REDIS_ZSET || o->type == REDIS_HASH)) {
+                node = nextnode;
+                kobj = listNodeValue(node);
+                nextnode = listNextNode(node);
+                decrRefCount(kobj);
+                listDelNode(keys, node);
+            }
         }
         node = nextnode;
     }
 
+    /* Step 4: Reply to the client. */
     addReplyMultiBulkLen(c, 2);
     rv = snprintf(buf, sizeof(buf), "%lu", cursor);
     redisAssert(rv < sizeof(buf));
@@ -415,6 +522,11 @@ void scanCommand(redisClient *c) {
     listRelease(keys);
 }
 
+/* The SCAN command completely relies on scanGenericCommand. */
+void scanCommand(redisClient *c) {
+    scanGenericCommand(c,NULL);
+}
+
 void dbsizeCommand(redisClient *c) {
     addReplyLongLong(c,dictSize(c->db->dict));
 }