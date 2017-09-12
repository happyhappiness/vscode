@@ -7563,6 +7563,7 @@ static void execCommand(redisClient *c) {
     execCommandReplicateMulti(c);
 
     /* Exec all the queued commands */
+    unwatchAllKeys(c); /* Unwatch ASAP otherwise we'll waste CPU cycles */
     orig_argv = c->argv;
     orig_argc = c->argc;
     addReplySds(c,sdscatprintf(sdsempty(),"*%d\r\n",c->mstate.count));
@@ -7575,8 +7576,7 @@ static void execCommand(redisClient *c) {
     c->argc = orig_argc;
     freeClientMultiState(c);
     initClientMultiState(c);
-    c->flags &= (~REDIS_MULTI);
-    unwatchAllKeys(c);
+    c->flags &= ~(REDIS_MULTI|REDIS_DIRTY_CAS);
     /* Make sure the EXEC command is always replicated / AOF, since we
      * always send the MULTI command (we can't know beforehand if the
      * next operations will contain at least a modification to the DB). */