@@ -72,28 +72,28 @@ void queueMultiCommand(client *c) {
 void discardTransaction(client *c) {
     freeClientMultiState(c);
     initClientMultiState(c);
-    c->flags &= ~(REDIS_MULTI|REDIS_DIRTY_CAS|REDIS_DIRTY_EXEC);
+    c->flags &= ~(CLIENT_MULTI|CLIENT_DIRTY_CAS|CLIENT_DIRTY_EXEC);
     unwatchAllKeys(c);
 }
 
 /* Flag the transacation as DIRTY_EXEC so that EXEC will fail.
  * Should be called every time there is an error while queueing a command. */
 void flagTransaction(client *c) {
-    if (c->flags & REDIS_MULTI)
-        c->flags |= REDIS_DIRTY_EXEC;
+    if (c->flags & CLIENT_MULTI)
+        c->flags |= CLIENT_DIRTY_EXEC;
 }
 
 void multiCommand(client *c) {
-    if (c->flags & REDIS_MULTI) {
+    if (c->flags & CLIENT_MULTI) {
         addReplyError(c,"MULTI calls can not be nested");
         return;
     }
-    c->flags |= REDIS_MULTI;
+    c->flags |= CLIENT_MULTI;
     addReply(c,shared.ok);
 }
 
 void discardCommand(client *c) {
-    if (!(c->flags & REDIS_MULTI)) {
+    if (!(c->flags & CLIENT_MULTI)) {
         addReplyError(c,"DISCARD without MULTI");
         return;
     }
@@ -107,7 +107,7 @@ void execCommandPropagateMulti(client *c) {
     robj *multistring = createStringObject("MULTI",5);
 
     propagate(server.multiCommand,c->db->id,&multistring,1,
-              REDIS_PROPAGATE_AOF|REDIS_PROPAGATE_REPL);
+              PROPAGATE_AOF|PROPAGATE_REPL);
     decrRefCount(multistring);
 }
 
@@ -118,7 +118,7 @@ void execCommand(client *c) {
     struct redisCommand *orig_cmd;
     int must_propagate = 0; /* Need to propagate MULTI/EXEC to AOF / slaves? */
 
-    if (!(c->flags & REDIS_MULTI)) {
+    if (!(c->flags & CLIENT_MULTI)) {
         addReplyError(c,"EXEC without MULTI");
         return;
     }
@@ -129,8 +129,8 @@ void execCommand(client *c) {
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
@@ -151,12 +151,12 @@ void execCommand(client *c) {
          * This way we'll deliver the MULTI/..../EXEC block as a whole and
          * both the AOF and the replication link will have the same consistency
          * and atomicity guarantees. */
-        if (!must_propagate && !(c->cmd->flags & REDIS_CMD_READONLY)) {
+        if (!must_propagate && !(c->cmd->flags & CMD_READONLY)) {
             execCommandPropagateMulti(c);
             must_propagate = 1;
         }
 
-        call(c,REDIS_CALL_FULL);
+        call(c,CMD_CALL_FULL);
 
         /* Commands may alter argc/argv, restore mstate. */
         c->mstate.commands[j].argc = c->argc;
@@ -175,7 +175,7 @@ void execCommand(client *c) {
     /* Send EXEC to clients waiting data from MONITOR. We do it here
      * since the natural order of commands execution is actually:
      * MUTLI, EXEC, ... commands inside transaction ...
-     * Instead EXEC is flagged as REDIS_CMD_SKIP_MONITOR in the command
+     * Instead EXEC is flagged as CMD_SKIP_MONITOR in the command
      * table, and we do it here with correct ordering. */
     if (listLength(server.monitors) && !server.loading)
         replicationFeedMonitors(c,server.monitors,c->db->id,c->argv,c->argc);
@@ -267,13 +267,13 @@ void touchWatchedKey(redisDb *db, robj *key) {
     clients = dictFetchValue(db->watched_keys, key);
     if (!clients) return;
 
-    /* Mark all the clients watching this key as REDIS_DIRTY_CAS */
+    /* Mark all the clients watching this key as CLIENT_DIRTY_CAS */
     /* Check if we are already watching for this key */
     listRewind(clients,&li);
     while((ln = listNext(&li))) {
         client *c = listNodeValue(ln);
 
-        c->flags |= REDIS_DIRTY_CAS;
+        c->flags |= CLIENT_DIRTY_CAS;
     }
 }
 
@@ -298,7 +298,7 @@ void touchWatchedKeysOnFlush(int dbid) {
              * removed. */
             if (dbid == -1 || wk->db->id == dbid) {
                 if (dictFind(wk->db->dict, wk->key->ptr) != NULL)
-                    c->flags |= REDIS_DIRTY_CAS;
+                    c->flags |= CLIENT_DIRTY_CAS;
             }
         }
     }
@@ -307,7 +307,7 @@ void touchWatchedKeysOnFlush(int dbid) {
 void watchCommand(client *c) {
     int j;
 
-    if (c->flags & REDIS_MULTI) {
+    if (c->flags & CLIENT_MULTI) {
         addReplyError(c,"WATCH inside MULTI is not allowed");
         return;
     }
@@ -318,6 +318,6 @@ void watchCommand(client *c) {
 
 void unwatchCommand(client *c) {
     unwatchAllKeys(c);
-    c->flags &= (~REDIS_DIRTY_CAS);
+    c->flags &= (~CLIENT_DIRTY_CAS);
     addReply(c,shared.ok);
 }