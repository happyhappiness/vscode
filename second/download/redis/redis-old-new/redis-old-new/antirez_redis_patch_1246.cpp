@@ -1228,7 +1228,7 @@ void clientCommand(redisClient *c) {
         else
             addReply(c,shared.nullbulk);
     } else {
-        addReplyError(c, "Syntax error, try CLIENT (LIST | KILL ip:port)");
+        addReplyError(c, "Syntax error, try CLIENT (LIST | KILL ip:port | GETNAME | SETNAME connection-name)");
     }
 }
 