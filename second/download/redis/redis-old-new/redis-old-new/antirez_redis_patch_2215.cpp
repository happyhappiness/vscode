@@ -7865,7 +7865,7 @@ static void debugCommand(redisClient *c) {
                 "+Key at:%p refcount:%d, value at:%p refcount:%d "
                 "encoding:%d serializedlength:%lld\r\n",
                 (void*)key, key->refcount, (void*)val, val->refcount,
-                val->encoding, rdbSavedObjectLen(val,NULL)));
+                val->encoding, (long long) rdbSavedObjectLen(val,NULL)));
         } else {
             addReplySds(c,sdscatprintf(sdsempty(),
                 "+Key at:%p refcount:%d, value swapped at: page %llu "