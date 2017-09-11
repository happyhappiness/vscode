@@ -692,7 +692,7 @@ char *strEncoding(int encoding) {
     }
 }
 
-/* ========================== Objects introspection ========================= */
+/* =========================== Memory introspection ========================== */
 
 /* Returns the size in bytes consumed by the key's value in RAM.
  * Note that the returned value is just an approximation, especially in the
@@ -792,58 +792,6 @@ size_t objectComputeSize(robj *o, size_t sample_size) {
     return asize;
 }
 
-/* ======================= The OBJECT and MEMORY commands =================== */
-
-/* This is a helper function for the OBJECT command. We need to lookup keys
- * without any modification of LRU or other parameters. */
-robj *objectCommandLookup(client *c, robj *key) {
-    dictEntry *de;
-
-    if ((de = dictFind(c->db->dict,key->ptr)) == NULL) return NULL;
-    return (robj*) dictGetVal(de);
-}
-
-robj *objectCommandLookupOrReply(client *c, robj *key, robj *reply) {
-    robj *o = objectCommandLookup(c,key);
-
-    if (!o) addReply(c, reply);
-    return o;
-}
-
-/* Object command allows to inspect the internals of an Redis Object.
- * Usage: OBJECT <refcount|encoding|idletime> <key> */
-void objectCommand(client *c) {
-    robj *o;
-
-    if (!strcasecmp(c->argv[1]->ptr,"refcount") && c->argc == 3) {
-        if ((o = objectCommandLookupOrReply(c,c->argv[2],shared.nullbulk))
-                == NULL) return;
-        addReplyLongLong(c,o->refcount);
-    } else if (!strcasecmp(c->argv[1]->ptr,"encoding") && c->argc == 3) {
-        if ((o = objectCommandLookupOrReply(c,c->argv[2],shared.nullbulk))
-                == NULL) return;
-        addReplyBulkCString(c,strEncoding(o->encoding));
-    } else if (!strcasecmp(c->argv[1]->ptr,"idletime") && c->argc == 3) {
-        if ((o = objectCommandLookupOrReply(c,c->argv[2],shared.nullbulk))
-                == NULL) return;
-        if (server.maxmemory_policy & MAXMEMORY_FLAG_LFU) {
-            addReplyError(c,"An LFU maxmemory policy is selected, idle time not tracked. Please note that when switching between policies at runtime LRU and LFU data will take some time to adjust.");
-            return;
-        }
-        addReplyLongLong(c,estimateObjectIdleTime(o)/1000);
-    } else if (!strcasecmp(c->argv[1]->ptr,"freq") && c->argc == 3) {
-        if ((o = objectCommandLookupOrReply(c,c->argv[2],shared.nullbulk))
-                == NULL) return;
-        if (server.maxmemory_policy & MAXMEMORY_FLAG_LRU) {
-            addReplyError(c,"An LRU maxmemory policy is selected, access frequency not tracked. Please note that when switching between policies at runtime LRU and LFU data will take some time to adjust.");
-            return;
-        }
-        addReplyLongLong(c,o->lru&255);
-    } else {
-        addReplyError(c,"Syntax error. Try OBJECT (refcount|encoding|idletime|freq)");
-    }
-}
-
 /* Release data obtained with getMemoryOverheadData(). */
 void freeMemoryOverheadData(struct redisMemOverhead *mh) {
     zfree(mh->db);
@@ -945,6 +893,58 @@ struct redisMemOverhead *getMemoryOverheadData(void) {
     return mh;
 }
 
+/* ======================= The OBJECT and MEMORY commands =================== */
+
+/* This is a helper function for the OBJECT command. We need to lookup keys
+ * without any modification of LRU or other parameters. */
+robj *objectCommandLookup(client *c, robj *key) {
+    dictEntry *de;
+
+    if ((de = dictFind(c->db->dict,key->ptr)) == NULL) return NULL;
+    return (robj*) dictGetVal(de);
+}
+
+robj *objectCommandLookupOrReply(client *c, robj *key, robj *reply) {
+    robj *o = objectCommandLookup(c,key);
+
+    if (!o) addReply(c, reply);
+    return o;
+}
+
+/* Object command allows to inspect the internals of an Redis Object.
+ * Usage: OBJECT <refcount|encoding|idletime> <key> */
+void objectCommand(client *c) {
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
+        if (server.maxmemory_policy & MAXMEMORY_FLAG_LFU) {
+            addReplyError(c,"An LFU maxmemory policy is selected, idle time not tracked. Please note that when switching between policies at runtime LRU and LFU data will take some time to adjust.");
+            return;
+        }
+        addReplyLongLong(c,estimateObjectIdleTime(o)/1000);
+    } else if (!strcasecmp(c->argv[1]->ptr,"freq") && c->argc == 3) {
+        if ((o = objectCommandLookupOrReply(c,c->argv[2],shared.nullbulk))
+                == NULL) return;
+        if (server.maxmemory_policy & MAXMEMORY_FLAG_LRU) {
+            addReplyError(c,"An LRU maxmemory policy is selected, access frequency not tracked. Please note that when switching between policies at runtime LRU and LFU data will take some time to adjust.");
+            return;
+        }
+        addReplyLongLong(c,o->lru&255);
+    } else {
+        addReplyError(c,"Syntax error. Try OBJECT (refcount|encoding|idletime|freq)");
+    }
+}
+
 /* The memory command will eventually be a complete interface for the
  * memory introspection capabilities of Redis.
  *