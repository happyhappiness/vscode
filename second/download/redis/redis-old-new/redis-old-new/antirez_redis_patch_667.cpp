@@ -2908,10 +2908,7 @@ void sentinelInfoCommand(redisClient *c) {
         dictReleaseIterator(di);
     }
 
-    addReplySds(c,sdscatprintf(sdsempty(),"$%lu\r\n",
-        (unsigned long)sdslen(info)));
-    addReplySds(c,info);
-    addReply(c,shared.crlf);
+    addReplyBulkSds(c, info);
 }
 
 /* Implements Sentinel verison of the ROLE command. The output is