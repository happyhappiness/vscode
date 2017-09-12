@@ -2721,7 +2721,7 @@ static void authCommand(redisClient *c) {
       addReply(c,shared.ok);
     } else {
       c->authenticated = 0;
-      addReply(c,shared.err);
+      addReplySds(c,sdscatprintf(sdsempty(),"-ERR invalid password\r\n"));
     }
 }
 