@@ -3865,7 +3865,7 @@ static void zrangeCommand(redisClient *c) {
 
             addReplySds(c,sdscatprintf(sdsempty(),"*%d\r\n",rangelen));
             for (j = 0; j < rangelen; j++) {
-                ele = ln->forward[0]->obj;
+                ele = ln->obj;
                 addReplyBulkLen(c,ele);
                 addReply(c,ele);
                 addReply(c,shared.crlf);