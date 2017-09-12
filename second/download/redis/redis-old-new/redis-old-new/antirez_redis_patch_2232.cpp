@@ -7175,10 +7175,19 @@ static void debugCommand(redisClient *c) {
         }
         key = dictGetEntryKey(de);
         val = dictGetEntryVal(de);
-        addReplySds(c,sdscatprintf(sdsempty(),
-            "+Key at:%p refcount:%d, value at:%p refcount:%d encoding:%d serializedlength:%lld\r\n",
+        if (server.vm_enabled && key->storage == REDIS_VM_MEMORY) {
+            addReplySds(c,sdscatprintf(sdsempty(),
+                "+Key at:%p refcount:%d, value at:%p refcount:%d "
+                "encoding:%d serializedlength:%lld\r\n",
                 (void*)key, key->refcount, (void*)val, val->refcount,
                 val->encoding, rdbSavedObjectLen(val)));
+        } else {
+            addReplySds(c,sdscatprintf(sdsempty(),
+                "+Key at:%p refcount:%d, value swapped at: page %llu "
+                "using %llu pages\r\n",
+                (void*)key, key->refcount, (unsigned long long) key->vm.page,
+                (unsigned long long) key->vm.usedpages));
+        }
     } else if (!strcasecmp(c->argv[1]->ptr,"swapout") && c->argc == 3) {
         dictEntry *de = dictFind(c->db->dict,c->argv[2]);
         robj *key, *val;