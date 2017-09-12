@@ -782,8 +782,7 @@ void zrangeGenericCommand(redisClient *c, int reverse) {
     }
 
     /* Return the result in form of a multi-bulk reply */
-    addReplySds(c,sdscatprintf(sdsempty(),"*%d\r\n",
-        withscores ? (rangelen*2) : rangelen));
+    addReplyMultiBulkLen(c,withscores ? (rangelen*2) : rangelen);
     for (j = 0; j < rangelen; j++) {
         ele = ln->obj;
         addReplyBulk(c,ele);