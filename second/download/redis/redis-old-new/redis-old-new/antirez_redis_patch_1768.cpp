@@ -200,60 +200,28 @@ void debugCommand(redisClient *c) {
     } else if (!strcasecmp(c->argv[1]->ptr,"object") && c->argc == 3) {
         dictEntry *de = dictFind(c->db->dict,c->argv[2]->ptr);
         robj *val;
+        char *strenc;
+        char *storage;
 
         if (!de) {
             addReply(c,shared.nokeyerr);
             return;
         }
         val = dictGetEntryVal(de);
-        if (!server.vm_enabled || (val->storage == REDIS_VM_MEMORY ||
-                                   val->storage == REDIS_VM_SWAPPING)) {
-            char *strenc;
-
-            strenc = strEncoding(val->encoding);
-            addReplyStatusFormat(c,
-                "Value at:%p refcount:%d "
-                "encoding:%s serializedlength:%lld "
-                "lru:%d lru_seconds_idle:%lu",
-                (void*)val, val->refcount,
-                strenc, (long long) rdbSavedObjectLen(val),
-                val->lru, estimateObjectIdleTime(val));
-        } else {
-            vmpointer *vp = (vmpointer*) val;
-            addReplyStatusFormat(c,
-                "Value swapped at: page %llu "
-                "using %llu pages",
-                (unsigned long long) vp->page,
-                (unsigned long long) vp->usedpages);
-        }
-    } else if (!strcasecmp(c->argv[1]->ptr,"swapin") && c->argc == 3) {
-        lookupKeyRead(c->db,c->argv[2]);
-        addReply(c,shared.ok);
-    } else if (!strcasecmp(c->argv[1]->ptr,"swapout") && c->argc == 3) {
-        dictEntry *de = dictFind(c->db->dict,c->argv[2]->ptr);
-        robj *val;
-        vmpointer *vp;
-
-        if (!server.vm_enabled) {
-            addReplyError(c,"Virtual Memory is disabled");
-            return;
-        }
-        if (!de) {
-            addReply(c,shared.nokeyerr);
-            return;
-        }
-        val = dictGetEntryVal(de);
-        /* Swap it */
-        if (val->storage != REDIS_VM_MEMORY) {
-            addReplyError(c,"This key is not in memory");
-        } else if (val->refcount != 1) {
-            addReplyError(c,"Object is shared");
-        } else if ((vp = vmSwapObjectBlocking(val)) != NULL) {
-            dictGetEntryVal(de) = vp;
-            addReply(c,shared.ok);
-        } else {
-            addReply(c,shared.err);
+        strenc = strEncoding(val->encoding);
+        switch(val->storage) {
+        case REDIS_DS_MEMORY: storage = "memory"; break;
+        case REDIS_DS_DIRTY: storage = "dirty"; break;
+        case REDIS_DS_SAVING: storage = "saving"; break;
+        default: storage = "unknown"; break;
         }
+        addReplyStatusFormat(c,
+            "Value at:%p refcount:%d "
+            "encoding:%s serializedlength:%lld "
+            "lru:%d lru_seconds_idle:%lu storage:%s",
+            (void*)val, val->refcount,
+            strenc, (long long) rdbSavedObjectLen(val),
+            val->lru, estimateObjectIdleTime(val), storage);
     } else if (!strcasecmp(c->argv[1]->ptr,"populate") && c->argc == 3) {
         long keys, j;
         robj *key, *val;