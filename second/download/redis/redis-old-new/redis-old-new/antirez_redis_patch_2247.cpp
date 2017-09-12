@@ -1714,7 +1714,9 @@ static int processCommand(redisClient *c) {
     }
     cmd = lookupCommand(c->argv[0]->ptr);
     if (!cmd) {
-        addReplySds(c,sdsnew("-ERR unknown command\r\n"));
+        addReplySds(c,
+            sdscatprintf(sdsempty(), "-ERR unknown command '%s'\r\n",
+                (char*)c->argv[0]->ptr));
         resetClient(c);
         return 1;
     } else if ((cmd->arity > 0 && cmd->arity != c->argc) ||