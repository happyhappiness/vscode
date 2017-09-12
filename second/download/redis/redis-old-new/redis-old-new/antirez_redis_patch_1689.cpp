@@ -93,9 +93,13 @@ robj *createHashObject(void) {
 
 robj *createZsetObject(void) {
     zset *zs = zmalloc(sizeof(*zs));
+    robj *o;
+
     zs->dict = dictCreate(&zsetDictType,NULL);
     zs->zsl = zslCreate();
-    return createObject(REDIS_ZSET,zs);
+    o = createObject(REDIS_ZSET,zs);
+    o->encoding = REDIS_ENCODING_SKIPLIST;
+    return o;
 }
 
 robj *createZsetZiplistObject(void) {
@@ -417,6 +421,7 @@ char *strEncoding(int encoding) {
     case REDIS_ENCODING_LINKEDLIST: return "linkedlist";
     case REDIS_ENCODING_ZIPLIST: return "ziplist";
     case REDIS_ENCODING_INTSET: return "intset";
+    case REDIS_ENCODING_SKIPLIST: return "skiplist";
     default: return "unknown";
     }
 }
@@ -431,3 +436,42 @@ unsigned long estimateObjectIdleTime(robj *o) {
                     REDIS_LRU_CLOCK_RESOLUTION;
     }
 }
+
+/* This is an helper function for the DEBUG command. We need to lookup keys
+ * without any modification of LRU or other parameters. */
+robj *objectCommandLookup(redisClient *c, robj *key) {
+    dictEntry *de;
+
+    if ((de = dictFind(c->db->dict,key->ptr)) == NULL) return NULL;
+    return (robj*) dictGetEntryVal(de);
+}
+
+robj *objectCommandLookupOrReply(redisClient *c, robj *key, robj *reply) {
+    robj *o = objectCommandLookup(c,key);
+
+    if (!o) addReply(c, reply);
+    return o;
+}
+
+/* Object command allows to inspect the internals of an Redis Object.
+ * Usage: OBJECT <verb> ... arguments ... */
+void objectCommand(redisClient *c) {
+    robj *o;
+
+    if (!strcasecmp(c->argv[1]->ptr,"refcount") && c->argc == 3) {
+        if ((o = objectCommandLookupOrReply(c,c->argv[2],shared.nullbulk))
+                == NULL) return;
+        addReplyLongLong(c,o->refcount);
+    } else if (!strcasecmp(c->argv[1]->ptr,"encoding") && c->argc == 3) {
+        if ((o = objectCommandLookupOrReply(c,c->argv[2],shared.nullbulk))
+                == NULL) return;
+        addReplyBulkCString(c,strEncoding(o->encoding));
+    } else if (!strcasecmp(c->argv[1]->ptr,"idletime") && c->argc == 3) {
+        if ((o = objectCommandLookupOrReply(c,c->argv[2],shared.nullbulk))
+                == NULL) return;
+        addReplyLongLong(c,estimateObjectIdleTime(o));
+    } else {
+        addReplyError(c,"Syntax error. Try OBJECT (refcount|encoding|idletime)");
+    }
+}
+