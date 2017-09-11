@@ -2537,7 +2537,7 @@ void sentinelCommand(redisClient *c) {
     return;
 
 numargserr:
-    addReplyErrorFormat(c,"Wrong number of commands for 'sentinel %s'",
+    addReplyErrorFormat(c,"Wrong number of arguments for 'sentinel %s'",
                           (char*)c->argv[1]->ptr);
 }
 