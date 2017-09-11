@@ -3058,11 +3058,7 @@ void infoCommand(redisClient *c) {
         addReply(c,shared.syntaxerr);
         return;
     }
-    sds info = genRedisInfoString(section);
-    addReplySds(c,sdscatprintf(sdsempty(),"$%lu\r\n",
-        (unsigned long)sdslen(info)));
-    addReplySds(c,info);
-    addReply(c,shared.crlf);
+    addReplyBulkSds(c, genRedisInfoString(section));
 }
 
 void monitorCommand(redisClient *c) {