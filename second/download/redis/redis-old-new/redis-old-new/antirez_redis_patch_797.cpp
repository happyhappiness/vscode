@@ -910,6 +910,9 @@ void evalGenericCommand(redisClient *c, int evalsha) {
     if (numkeys > (c->argc - 3)) {
         addReplyError(c,"Number of keys can't be greater than number of args");
         return;
+    } else if (numkeys < 0) {
+        addReplyError(c,"Number of keys can't be negative");
+        return;
     }
 
     /* We obtain the script SHA1, then check if this function is already