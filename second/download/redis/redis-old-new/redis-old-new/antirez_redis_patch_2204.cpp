@@ -8171,8 +8171,8 @@ static void debugCommand(redisClient *c) {
         }
         key = dictGetEntryKey(de);
         val = dictGetEntryVal(de);
-        if (server.vm_enabled && (key->storage == REDIS_VM_MEMORY ||
-                                  key->storage == REDIS_VM_SWAPPING)) {
+        if (!server.vm_enabled || (key->storage == REDIS_VM_MEMORY ||
+                                   key->storage == REDIS_VM_SWAPPING)) {
             addReplySds(c,sdscatprintf(sdsempty(),
                 "+Key at:%p refcount:%d, value at:%p refcount:%d "
                 "encoding:%d serializedlength:%lld\r\n",