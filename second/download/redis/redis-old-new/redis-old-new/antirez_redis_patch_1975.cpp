@@ -107,7 +107,7 @@ void execCommand(redisClient *c) {
     unwatchAllKeys(c); /* Unwatch ASAP otherwise we'll waste CPU cycles */
     orig_argv = c->argv;
     orig_argc = c->argc;
-    addReplySds(c,sdscatprintf(sdsempty(),"*%d\r\n",c->mstate.count));
+    addReplyMultiBulkLen(c,c->mstate.count);
     for (j = 0; j < c->mstate.count; j++) {
         c->argc = c->mstate.commands[j].argc;
         c->argv = c->mstate.commands[j].argv;