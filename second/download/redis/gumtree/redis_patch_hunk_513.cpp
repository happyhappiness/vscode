     memcpy(mc->argv,c->argv,sizeof(robj*)*c->argc);
     for (j = 0; j < c->argc; j++)
         incrRefCount(mc->argv[j]);
     c->mstate.count++;
 }
 
-void discardTransaction(redisClient *c) {
+void discardTransaction(client *c) {
     freeClientMultiState(c);
     initClientMultiState(c);
-    c->flags &= ~(REDIS_MULTI|REDIS_DIRTY_CAS|REDIS_DIRTY_EXEC);
+    c->flags &= ~(CLIENT_MULTI|CLIENT_DIRTY_CAS|CLIENT_DIRTY_EXEC);
     unwatchAllKeys(c);
 }
 
 /* Flag the transacation as DIRTY_EXEC so that EXEC will fail.
  * Should be called every time there is an error while queueing a command. */
-void flagTransaction(redisClient *c) {
-    if (c->flags & REDIS_MULTI)
-        c->flags |= REDIS_DIRTY_EXEC;
+void flagTransaction(client *c) {
+    if (c->flags & CLIENT_MULTI)
+        c->flags |= CLIENT_DIRTY_EXEC;
 }
 
-void multiCommand(redisClient *c) {
-    if (c->flags & REDIS_MULTI) {
+void multiCommand(client *c) {
+    if (c->flags & CLIENT_MULTI) {
         addReplyError(c,"MULTI calls can not be nested");
         return;
     }
-    c->flags |= REDIS_MULTI;
+    c->flags |= CLIENT_MULTI;
     addReply(c,shared.ok);
 }
 
-void discardCommand(redisClient *c) {
-    if (!(c->flags & REDIS_MULTI)) {
+void discardCommand(client *c) {
+    if (!(c->flags & CLIENT_MULTI)) {
         addReplyError(c,"DISCARD without MULTI");
         return;
     }
     discardTransaction(c);
     addReply(c,shared.ok);
 }
 
 /* Send a MULTI command to all the slaves and AOF file. Check the execCommand
  * implementation for more information. */
-void execCommandPropagateMulti(redisClient *c) {
+void execCommandPropagateMulti(client *c) {
     robj *multistring = createStringObject("MULTI",5);
 
     propagate(server.multiCommand,c->db->id,&multistring,1,
-              REDIS_PROPAGATE_AOF|REDIS_PROPAGATE_REPL);
+              PROPAGATE_AOF|PROPAGATE_REPL);
     decrRefCount(multistring);
 }
 
-void execCommand(redisClient *c) {
+void execCommand(client *c) {
     int j;
     robj **orig_argv;
     int orig_argc;
     struct redisCommand *orig_cmd;
     int must_propagate = 0; /* Need to propagate MULTI/EXEC to AOF / slaves? */
 
-    if (!(c->flags & REDIS_MULTI)) {
+    if (!(c->flags & CLIENT_MULTI)) {
         addReplyError(c,"EXEC without MULTI");
         return;
     }
 
     /* Check if we need to abort the EXEC because:
      * 1) Some WATCHed key was touched.
      * 2) There was a previous error while queueing commands.
      * A failed EXEC in the first case returns a multi bulk nil object
      * (technically it is not an error but a special behavior), while
      * in the second an EXECABORT error is returned. */
-    if (c->flags & (REDIS_DIRTY_CAS|REDIS_DIRTY_EXEC)) {
-        addReply(c, c->flags & REDIS_DIRTY_EXEC ? shared.execaborterr :
+    if (c->flags & (CLIENT_DIRTY_CAS|CLIENT_DIRTY_EXEC)) {
+        addReply(c, c->flags & CLIENT_DIRTY_EXEC ? shared.execaborterr :
                                                   shared.nullmultibulk);
         discardTransaction(c);
         goto handle_monitor;
     }
 
     /* Exec all the queued commands */
