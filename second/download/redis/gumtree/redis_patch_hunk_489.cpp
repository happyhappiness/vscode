 cleanup:
     listSetFreeMethod(keys,decrRefCountVoid);
     listRelease(keys);
 }
 
 /* The SCAN command completely relies on scanGenericCommand. */
-void scanCommand(redisClient *c) {
+void scanCommand(client *c) {
     unsigned long cursor;
-    if (parseScanCursorOrReply(c,c->argv[1],&cursor) == REDIS_ERR) return;
+    if (parseScanCursorOrReply(c,c->argv[1],&cursor) == C_ERR) return;
     scanGenericCommand(c,NULL,cursor);
 }
 
-void dbsizeCommand(redisClient *c) {
+void dbsizeCommand(client *c) {
     addReplyLongLong(c,dictSize(c->db->dict));
 }
 
-void lastsaveCommand(redisClient *c) {
+void lastsaveCommand(client *c) {
     addReplyLongLong(c,server.lastsave);
 }
 
-void typeCommand(redisClient *c) {
+void typeCommand(client *c) {
     robj *o;
     char *type;
 
     o = lookupKeyRead(c->db,c->argv[1]);
     if (o == NULL) {
         type = "none";
     } else {
         switch(o->type) {
-        case REDIS_STRING: type = "string"; break;
-        case REDIS_LIST: type = "list"; break;
-        case REDIS_SET: type = "set"; break;
-        case REDIS_ZSET: type = "zset"; break;
-        case REDIS_HASH: type = "hash"; break;
+        case OBJ_STRING: type = "string"; break;
+        case OBJ_LIST: type = "list"; break;
+        case OBJ_SET: type = "set"; break;
+        case OBJ_ZSET: type = "zset"; break;
+        case OBJ_HASH: type = "hash"; break;
         default: type = "unknown"; break;
         }
     }
     addReplyStatus(c,type);
 }
 
-void shutdownCommand(redisClient *c) {
+void shutdownCommand(client *c) {
     int flags = 0;
 
     if (c->argc > 2) {
         addReply(c,shared.syntaxerr);
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
         }
     }
     /* When SHUTDOWN is called while the server is loading a dataset in
      * memory we need to make sure no attempt is performed to save
      * the dataset on shutdown (otherwise it could overwrite the current DB
      * with half-read data).
      *
      * Also when in Sentinel mode clear the SAVE flag and force NOSAVE. */
     if (server.loading || server.sentinel_mode)
-        flags = (flags & ~REDIS_SHUTDOWN_SAVE) | REDIS_SHUTDOWN_NOSAVE;
-    if (prepareForShutdown(flags) == REDIS_OK) exit(0);
+        flags = (flags & ~SHUTDOWN_SAVE) | SHUTDOWN_NOSAVE;
+    if (prepareForShutdown(flags) == C_OK) exit(0);
     addReplyError(c,"Errors trying to SHUTDOWN. Check logs.");
 }
 
-void renameGenericCommand(redisClient *c, int nx) {
+void renameGenericCommand(client *c, int nx) {
     robj *o;
     long long expire;
+    int samekey = 0;
 
-    /* To use the same key as src and dst is probably an error */
-    if (sdscmp(c->argv[1]->ptr,c->argv[2]->ptr) == 0) {
-        addReply(c,shared.sameobjecterr);
-        return;
-    }
+    /* When source and dest key is the same, no operation is performed,
+     * if the key exists, however we still return an error on unexisting key. */
+    if (sdscmp(c->argv[1]->ptr,c->argv[2]->ptr) == 0) samekey = 1;
 
     if ((o = lookupKeyWriteOrReply(c,c->argv[1],shared.nokeyerr)) == NULL)
         return;
 
+    if (samekey) {
+        addReply(c,nx ? shared.czero : shared.ok);
+        return;
+    }
+
     incrRefCount(o);
     expire = getExpire(c->db,c->argv[1]);
     if (lookupKeyWrite(c->db,c->argv[2]) != NULL) {
         if (nx) {
             decrRefCount(o);
             addReply(c,shared.czero);
