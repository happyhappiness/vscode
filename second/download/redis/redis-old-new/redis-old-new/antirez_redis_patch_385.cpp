@@ -179,9 +179,27 @@ int hashTypeExists(robj *o, sds field) {
 }
 
 /* Add a new field, overwrite the old with the new value if it already exists.
- * Return 0 on insert and 1 on update. The key and value SDS strings are copied
- * if needed, so the caller retains ownership of the strings passed. */
-int hashTypeSet(robj *o, sds field, sds value) {
+ * Return 0 on insert and 1 on update.
+ *
+ * By default, the key and value SDS strings are copied if needed, so the
+ * caller retains ownership of the strings passed. However this behavior
+ * can be effected by passing appropriate flags (possibly bitwise OR-ed):
+ *
+ * HASH_SET_TAKE_FIELD -- The SDS field ownership passes to the function.
+ * HASH_SET_TAKE_VALUE -- The SDS value ownership passes to the function.
+ *
+ * When the flags are used the caller does not need to release the passed
+ * SDS string(s). It's up to the function to use the string to create a new
+ * entry or to free the SDS string before returning to the caller.
+ *
+ * HASH_SET_COPY corresponds to no flags passed, and means the default
+ * semantics of copying the values if needed.
+ *
+ */
+#define HASH_SET_TAKE_FIELD (1<<0)
+#define HASH_SET_TAKE_VALUE (1<<1)
+#define HASH_SET_COPY 0
+int hashTypeSet(robj *o, sds field, sds value, int flags) {
     int update = 0;
 
     if (o->encoding == OBJ_ENCODING_ZIPLIST) {
@@ -222,14 +240,37 @@ int hashTypeSet(robj *o, sds field, sds value) {
         dictEntry *de = dictFind(o->ptr,field);
         if (de) {
             sdsfree(dictGetVal(de));
-            dictGetVal(de) = sdsdup(value);
+            if (flags & HASH_SET_TAKE_VALUE) {
+                dictGetVal(de) = value;
+                value = NULL;
+            } else {
+                dictGetVal(de) = sdsdup(value);
+            }
             update = 1;
         } else {
-            dictAdd(o->ptr,sdsdup(field),sdsdup(value));
+            sds f,v;
+            if (flags & HASH_SET_TAKE_FIELD) {
+                f = field;
+                field = NULL;
+            } else {
+                f = sdsdup(field);
+            }
+            if (flags & HASH_SET_TAKE_VALUE) {
+                v = value;
+                value = NULL;
+            } else {
+                v = sdsdup(value);
+            }
+            dictAdd(o->ptr,f,v);
         }
     } else {
         serverPanic("Unknown hash encoding");
     }
+
+    /* Free SDS strings we did not referenced elsewhere if the flags
+     * want this function to be responsible. */
+    if (flags & HASH_SET_TAKE_FIELD && field) sdsfree(field);
+    if (flags & HASH_SET_TAKE_VALUE && value) sdsfree(value);
     return update;
 }
 
@@ -476,7 +517,7 @@ void hsetCommand(client *c) {
 
     if ((o = hashTypeLookupWriteOrCreate(c,c->argv[1])) == NULL) return;
     hashTypeTryConversion(o,c->argv,2,3);
-    update = hashTypeSet(o,c->argv[2]->ptr,c->argv[3]->ptr);
+    update = hashTypeSet(o,c->argv[2]->ptr,c->argv[3]->ptr,HASH_SET_COPY);
     addReply(c, update ? shared.czero : shared.cone);
     signalModifiedKey(c->db,c->argv[1]);
     notifyKeyspaceEvent(NOTIFY_HASH,"hset",c->argv[1],c->db->id);
@@ -491,7 +532,7 @@ void hsetnxCommand(client *c) {
     if (hashTypeExists(o, c->argv[2]->ptr)) {
         addReply(c, shared.czero);
     } else {
-        hashTypeSet(o,c->argv[2]->ptr,c->argv[3]->ptr);
+        hashTypeSet(o,c->argv[2]->ptr,c->argv[3]->ptr,HASH_SET_COPY);
         addReply(c, shared.cone);
         signalModifiedKey(c->db,c->argv[1]);
         notifyKeyspaceEvent(NOTIFY_HASH,"hset",c->argv[1],c->db->id);
@@ -511,7 +552,7 @@ void hmsetCommand(client *c) {
     if ((o = hashTypeLookupWriteOrCreate(c,c->argv[1])) == NULL) return;
     hashTypeTryConversion(o,c->argv,2,c->argc-1);
     for (i = 2; i < c->argc; i += 2) {
-        hashTypeSet(o,c->argv[i]->ptr,c->argv[i+1]->ptr);
+        hashTypeSet(o,c->argv[i]->ptr,c->argv[i+1]->ptr,HASH_SET_COPY);
     }
     addReply(c, shared.ok);
     signalModifiedKey(c->db,c->argv[1]);
@@ -547,7 +588,7 @@ void hincrbyCommand(client *c) {
     }
     value += incr;
     new = sdsfromlonglong(value);
-    hashTypeSet(o,c->argv[2]->ptr,new);
+    hashTypeSet(o,c->argv[2]->ptr,new,HASH_SET_TAKE_VALUE);
     addReplyLongLong(c,value);
     signalModifiedKey(c->db,c->argv[1]);
     notifyKeyspaceEvent(NOTIFY_HASH,"hincrby",c->argv[1],c->db->id);
@@ -582,8 +623,8 @@ void hincrbyfloatCommand(client *c) {
     char buf[256];
     int len = ld2string(buf,sizeof(buf),value,1);
     new = sdsnewlen(buf,len);
-    hashTypeSet(o,c->argv[2]->ptr,new);
-    addReplyBulkSds(c,new);
+    hashTypeSet(o,c->argv[2]->ptr,new,HASH_SET_TAKE_VALUE);
+    addReplyBulkCBuffer(c,buf,len);
     signalModifiedKey(c->db,c->argv[1]);
     notifyKeyspaceEvent(NOTIFY_HASH,"hincrbyfloat",c->argv[1],c->db->id);
     server.dirty++;