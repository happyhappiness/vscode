@@ -72,10 +72,17 @@ void queueMultiCommand(redisClient *c) {
 void discardTransaction(redisClient *c) {
     freeClientMultiState(c);
     initClientMultiState(c);
-    c->flags &= ~(REDIS_MULTI|REDIS_DIRTY_CAS);;
+    c->flags &= ~(REDIS_MULTI|REDIS_DIRTY_CAS|REDIS_DIRTY_EXEC);;
     unwatchAllKeys(c);
 }
 
+/* Flag the transacation as DIRTY_EXEC so that EXEC will fail.
+ * Should be called every time there is an error while queueing a command. */
+void flagTransaction(redisClient *c) {
+    if (c->flags & REDIS_MULTI)
+        c->flags |= REDIS_DIRTY_EXEC;
+}
+
 void multiCommand(redisClient *c) {
     if (c->flags & REDIS_MULTI) {
         addReplyError(c,"MULTI calls can not be nested");
@@ -117,14 +124,19 @@ void execCommand(redisClient *c) {
         return;
     }
 
-    /* Check if we need to abort the EXEC if some WATCHed key was touched.
-     * A failed EXEC will return a multi bulk nil object. */
-    if (c->flags & REDIS_DIRTY_CAS) {
+    /* Check if we need to abort the EXEC because:
+     * 1) Some WATCHed key was touched.
+     * 2) There was a previous error while queueing commands.
+     * A failed EXEC in the first case returns a multi bulk nil object
+     * (technically it is not an error but a special behavior), while
+     * in the second an EXECABORT error is returned. */
+    if (c->flags & (REDIS_DIRTY_CAS|REDIS_DIRTY_EXEC)) {
+        addReply(c, c->flags & REDIS_DIRTY_EXEC ? shared.execaborterr :
+                                                  shared.nullmultibulk);
         freeClientMultiState(c);
         initClientMultiState(c);
-        c->flags &= ~(REDIS_MULTI|REDIS_DIRTY_CAS);
+        c->flags &= ~(REDIS_MULTI|REDIS_DIRTY_CAS|REDIS_DIRTY_EXEC);
         unwatchAllKeys(c);
-        addReply(c,shared.nullmultibulk);
         goto handle_monitor;
     }
 
@@ -156,7 +168,7 @@ void execCommand(redisClient *c) {
     c->cmd = orig_cmd;
     freeClientMultiState(c);
     initClientMultiState(c);
-    c->flags &= ~(REDIS_MULTI|REDIS_DIRTY_CAS);
+    c->flags &= ~(REDIS_MULTI|REDIS_DIRTY_CAS|REDIS_DIRTY_EXEC);
     /* Make sure the EXEC command is always replicated / AOF, since we
      * always send the MULTI command (we can't know beforehand if the
      * next operations will contain at least a modification to the DB). */