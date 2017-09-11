@@ -43,8 +43,13 @@ robj *createObject(int type, void *ptr) {
     o->ptr = ptr;
     o->refcount = 1;
 
-    /* Set the LRU to the current lruclock (minutes resolution). */
-    o->lru = LRU_CLOCK();
+    /* Set the LRU to the current lruclock (minutes resolution), or
+     * alternatively the LFU counter. */
+    if (server.maxmemory_policy & MAXMEMORY_FLAG_LFU) {
+        o->lru = (LFUGetTimeInMinutes()<<8) | LFU_INIT_VAL;
+    } else {
+        o->lru = LRU_CLOCK();
+    }
     return o;
 }
 
@@ -82,7 +87,11 @@ robj *createEmbeddedStringObject(const char *ptr, size_t len) {
     o->encoding = OBJ_ENCODING_EMBSTR;
     o->ptr = sh+1;
     o->refcount = 1;
-    o->lru = LRU_CLOCK();
+    if (server.maxmemory_policy & MAXMEMORY_FLAG_LFU) {
+        o->lru = (LFUGetTimeInMinutes()<<8) | LFU_INIT_VAL;
+    } else {
+        o->lru = LRU_CLOCK();
+    }
 
     sh->len = len;
     sh->alloc = len;
@@ -394,8 +403,7 @@ robj *tryObjectEncoding(robj *o) {
          * because every object needs to have a private LRU field for the LRU
          * algorithm to work well. */
         if ((server.maxmemory == 0 ||
-             (server.maxmemory_policy != MAXMEMORY_VOLATILE_LRU &&
-              server.maxmemory_policy != MAXMEMORY_ALLKEYS_LRU)) &&
+            !(server.maxmemory & MAXMEMORY_FLAG_NO_SHARED_INTEGERS)) &&
             value >= 0 &&
             value < OBJ_SHARED_INTEGERS)
         {
@@ -715,8 +723,12 @@ void objectCommand(client *c) {
         if ((o = objectCommandLookupOrReply(c,c->argv[2],shared.nullbulk))
                 == NULL) return;
         addReplyLongLong(c,estimateObjectIdleTime(o)/1000);
+    } else if (!strcasecmp(c->argv[1]->ptr,"freq") && c->argc == 3) {
+        if ((o = objectCommandLookupOrReply(c,c->argv[2],shared.nullbulk))
+                == NULL) return;
+        addReplyLongLong(c,o->lru&255);
     } else {
-        addReplyError(c,"Syntax error. Try OBJECT (refcount|encoding|idletime)");
+        addReplyError(c,"Syntax error. Try OBJECT (refcount|encoding|idletime|freq)");
     }
 }
 