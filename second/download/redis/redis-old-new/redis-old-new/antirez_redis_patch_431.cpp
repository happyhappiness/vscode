@@ -81,7 +81,7 @@ robj *lookupKeyRead(redisDb *db, robj *key) {
         if (server.current_client &&
             server.current_client != server.master &&
             server.current_client->cmd &&
-            server.current_client->cmd->flags & REDIS_CMD_READONLY)
+            server.current_client->cmd->flags & CMD_READONLY)
         {
             return NULL;
         }
@@ -309,7 +309,7 @@ void delCommand(client *c) {
         expireIfNeeded(c->db,c->argv[j]);
         if (dbDelete(c->db,c->argv[j])) {
             signalModifiedKey(c->db,c->argv[j]);
-            notifyKeyspaceEvent(REDIS_NOTIFY_GENERIC,
+            notifyKeyspaceEvent(NOTIFY_GENERIC,
                 "del",c->argv[j],c->db->id);
             server.dirty++;
             deleted++;
@@ -412,7 +412,7 @@ void scanCallback(void *privdata, const dictEntry *de) {
         incrRefCount(key);
         val = createStringObjectFromLongDouble(*(double*)dictGetVal(de),0);
     } else {
-        redisPanic("Type not handled in SCAN callback.");
+        serverPanic("Type not handled in SCAN callback.");
     }
 
     listAddNodeTail(keys, key);
@@ -560,7 +560,7 @@ void scanGenericCommand(client *c, robj *o, unsigned long cursor) {
         }
         cursor = 0;
     } else {
-        redisPanic("Not handled encoding in SCAN.");
+        serverPanic("Not handled encoding in SCAN.");
     }
 
     /* Step 3: Filter elements. */
@@ -576,7 +576,7 @@ void scanGenericCommand(client *c, robj *o, unsigned long cursor) {
                 if (!stringmatchlen(pat, patlen, kobj->ptr, sdslen(kobj->ptr), 0))
                     filter = 1;
             } else {
-                char buf[REDIS_LONGSTR_SIZE];
+                char buf[LONG_STR_SIZE];
                 int len;
 
                 serverAssert(kobj->encoding == OBJ_ENCODING_INT);
@@ -669,9 +669,9 @@ void shutdownCommand(client *c) {
         return;
     } else if (c->argc == 2) {
         if (!strcasecmp(c->argv[1]->ptr,"nosave")) {
-            flags |= REDIS_SHUTDOWN_NOSAVE;
+            flags |= SHUTDOWN_NOSAVE;
         } else if (!strcasecmp(c->argv[1]->ptr,"save")) {
-            flags |= REDIS_SHUTDOWN_SAVE;
+            flags |= SHUTDOWN_SAVE;
         } else {
             addReply(c,shared.syntaxerr);
             return;
@@ -684,7 +684,7 @@ void shutdownCommand(client *c) {
      *
      * Also when in Sentinel mode clear the SAVE flag and force NOSAVE. */
     if (server.loading || server.sentinel_mode)
-        flags = (flags & ~REDIS_SHUTDOWN_SAVE) | REDIS_SHUTDOWN_NOSAVE;
+        flags = (flags & ~SHUTDOWN_SAVE) | SHUTDOWN_NOSAVE;
     if (prepareForShutdown(flags) == C_OK) exit(0);
     addReplyError(c,"Errors trying to SHUTDOWN. Check logs.");
 }
@@ -723,9 +723,9 @@ void renameGenericCommand(client *c, int nx) {
     dbDelete(c->db,c->argv[1]);
     signalModifiedKey(c->db,c->argv[1]);
     signalModifiedKey(c->db,c->argv[2]);
-    notifyKeyspaceEvent(REDIS_NOTIFY_GENERIC,"rename_from",
+    notifyKeyspaceEvent(NOTIFY_GENERIC,"rename_from",
         c->argv[1],c->db->id);
-    notifyKeyspaceEvent(REDIS_NOTIFY_GENERIC,"rename_to",
+    notifyKeyspaceEvent(NOTIFY_GENERIC,"rename_to",
         c->argv[2],c->db->id);
     server.dirty++;
     addReply(c,nx ? shared.cone : shared.ok);
@@ -844,7 +844,7 @@ void propagateExpire(redisDb *db, robj *key) {
     incrRefCount(argv[0]);
     incrRefCount(argv[1]);
 
-    if (server.aof_state != REDIS_AOF_OFF)
+    if (server.aof_state != AOF_OFF)
         feedAppendOnlyFile(server.delCommand,db->id,argv,2);
     replicationFeedSlaves(server.slaves,db->id,argv,2);
 
@@ -883,7 +883,7 @@ int expireIfNeeded(redisDb *db, robj *key) {
     /* Delete the key */
     server.stat_expiredkeys++;
     propagateExpire(db,key);
-    notifyKeyspaceEvent(REDIS_NOTIFY_EXPIRED,
+    notifyKeyspaceEvent(NOTIFY_EXPIRED,
         "expired",key,db->id);
     return dbDelete(db,key);
 }
@@ -932,14 +932,14 @@ void expireGenericCommand(client *c, long long basetime, int unit) {
         rewriteClientCommandVector(c,2,aux,key);
         decrRefCount(aux);
         signalModifiedKey(c->db,key);
-        notifyKeyspaceEvent(REDIS_NOTIFY_GENERIC,"del",key,c->db->id);
+        notifyKeyspaceEvent(NOTIFY_GENERIC,"del",key,c->db->id);
         addReply(c, shared.cone);
         return;
     } else {
         setExpire(c->db,key,when);
         addReply(c,shared.cone);
         signalModifiedKey(c->db,key);
-        notifyKeyspaceEvent(REDIS_NOTIFY_GENERIC,"expire",key,c->db->id);
+        notifyKeyspaceEvent(NOTIFY_GENERIC,"expire",key,c->db->id);
         server.dirty++;
         return;
     }
@@ -1015,7 +1015,7 @@ void persistCommand(client *c) {
  * (firstkey, lastkey, step). */
 int *getKeysUsingCommandTable(struct redisCommand *cmd,robj **argv, int argc, int *numkeys) {
     int j, i = 0, last, *keys;
-    REDIS_NOTUSED(argv);
+    UNUSED(argv);
 
     if (cmd->firstkey == 0) {
         *numkeys = 0;
@@ -1061,7 +1061,7 @@ void getKeysFreeResult(int *result) {
  * ZINTERSTORE <destkey> <num-keys> <key> <key> ... <key> <options> */
 int *zunionInterGetKeys(struct redisCommand *cmd, robj **argv, int argc, int *numkeys) {
     int i, num, *keys;
-    REDIS_NOTUSED(cmd);
+    UNUSED(cmd);
 
     num = atoi(argv[2]->ptr);
     /* Sanity check. Don't return any key if the command is going to
@@ -1090,7 +1090,7 @@ int *zunionInterGetKeys(struct redisCommand *cmd, robj **argv, int argc, int *nu
  * EVALSHA <script> <num-keys> <key> <key> ... <key> [more stuff] */
 int *evalGetKeys(struct redisCommand *cmd, robj **argv, int argc, int *numkeys) {
     int i, num, *keys;
-    REDIS_NOTUSED(cmd);
+    UNUSED(cmd);
 
     num = atoi(argv[2]->ptr);
     /* Sanity check. Don't return any key if the command is going to
@@ -1118,7 +1118,7 @@ int *evalGetKeys(struct redisCommand *cmd, robj **argv, int argc, int *numkeys)
  * correctly identify keys in the "STORE" option. */
 int *sortGetKeys(struct redisCommand *cmd, robj **argv, int argc, int *numkeys) {
     int i, j, num, *keys, found_store = 0;
-    REDIS_NOTUSED(cmd);
+    UNUSED(cmd);
 
     num = 0;
     keys = zmalloc(sizeof(int)*2); /* Alloc 2 places for the worst case. */