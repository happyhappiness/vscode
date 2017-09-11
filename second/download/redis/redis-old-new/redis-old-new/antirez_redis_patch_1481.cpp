@@ -1174,7 +1174,7 @@ int processCommand(redisClient *c) {
 
     /* Now lookup the command and check ASAP about trivial error conditions
      * such as wrong arity, bad command name and so forth. */
-    c->cmd = lookupCommand(c->argv[0]->ptr);
+    c->cmd = c->lastcmd = lookupCommand(c->argv[0]->ptr);
     if (!c->cmd) {
         addReplyErrorFormat(c,"unknown command '%s'",
             (char*)c->argv[0]->ptr);