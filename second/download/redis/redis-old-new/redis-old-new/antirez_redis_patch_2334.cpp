@@ -3052,7 +3052,8 @@ static void sinterGenericCommand(redisClient *c, robj **setskeys, int setsnum, r
     if (!dstkey) {
         lenobj->ptr = sdscatprintf(sdsempty(),"*%d\r\n",cardinality);
     } else {
-        addReply(c,shared.ok);
+        addReplySds(c,sdscatprintf(sdsempty(),":%d\r\n",
+            dictSize((dict*)dstset->ptr)));
         server.dirty++;
     }
     zfree(dv);
@@ -3157,7 +3158,8 @@ static void sunionDiffGenericCommand(redisClient *c, robj **setskeys, int setsnu
     if (!dstkey) {
         decrRefCount(dstset);
     } else {
-        addReply(c,shared.ok);
+        addReplySds(c,sdscatprintf(sdsempty(),":%d\r\n",
+            dictSize((dict*)dstset->ptr)));
         server.dirty++;
     }
     zfree(dv);