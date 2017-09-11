@@ -452,7 +452,7 @@ void hashTypeConvertZiplist(robj *o, int enc) {
             value = tryObjectEncoding(value);
             ret = dictAdd(dict, field, value);
             if (ret != DICT_OK) {
-                redisLogHexDump(REDIS_WARNING,"ziplist with dup elements dump",
+                serverLogHexDump(REDIS_WARNING,"ziplist with dup elements dump",
                     o->ptr,ziplistBlobLen(o->ptr));
                 redisAssert(ret == DICT_OK);
             }