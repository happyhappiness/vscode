@@ -119,7 +119,7 @@ void dbAdd(redisDb *db, robj *key, robj *val) {
     sds copy = sdsdup(key->ptr);
     int retval = dictAdd(db->dict, copy, val);
 
-    serverAssertWithInfo(NULL,key,retval == REDIS_OK);
+    serverAssertWithInfo(NULL,key,retval == C_OK);
     if (val->type == OBJ_LIST) signalListAsReady(db, key);
     if (server.cluster_enabled) slotToKeyAdd(key);
  }
@@ -249,9 +249,9 @@ long long emptyDb(void(callback)(void*)) {
 
 int selectDb(client *c, int id) {
     if (id < 0 || id >= server.dbnum)
-        return REDIS_ERR;
+        return C_ERR;
     c->db = &server.db[id];
-    return REDIS_OK;
+    return C_OK;
 }
 
 /*-----------------------------------------------------------------------------
@@ -335,14 +335,14 @@ void selectCommand(client *c) {
     long id;
 
     if (getLongFromObjectOrReply(c, c->argv[1], &id,
-        "invalid DB index") != REDIS_OK)
+        "invalid DB index") != C_OK)
         return;
 
     if (server.cluster_enabled && id != 0) {
         addReplyError(c,"SELECT is not allowed in cluster mode");
         return;
     }
-    if (selectDb(c,id) == REDIS_ERR) {
+    if (selectDb(c,id) == C_ERR) {
         addReplyError(c,"invalid DB index");
     } else {
         addReply(c,shared.ok);
@@ -421,7 +421,7 @@ void scanCallback(void *privdata, const dictEntry *de) {
 
 /* Try to parse a SCAN cursor stored at object 'o':
  * if the cursor is valid, store it as unsigned integer into *cursor and
- * returns REDIS_OK. Otherwise return REDIS_ERR and send an error to the
+ * returns C_OK. Otherwise return C_ERR and send an error to the
  * client. */
 int parseScanCursorOrReply(client *c, robj *o, unsigned long *cursor) {
     char *eptr;
@@ -433,9 +433,9 @@ int parseScanCursorOrReply(client *c, robj *o, unsigned long *cursor) {
     if (isspace(((char*)o->ptr)[0]) || eptr[0] != '\0' || errno == ERANGE)
     {
         addReplyError(c, "invalid cursor");
-        return REDIS_ERR;
+        return C_ERR;
     }
-    return REDIS_OK;
+    return C_OK;
 }
 
 /* This command implements SCAN, HSCAN and SSCAN commands.
@@ -471,7 +471,7 @@ void scanGenericCommand(client *c, robj *o, unsigned long cursor) {
         j = c->argc - i;
         if (!strcasecmp(c->argv[i]->ptr, "count") && j >= 2) {
             if (getLongFromObjectOrReply(c, c->argv[i+1], &count, NULL)
-                != REDIS_OK)
+                != C_OK)
             {
                 goto cleanup;
             }
@@ -629,7 +629,7 @@ void scanGenericCommand(client *c, robj *o, unsigned long cursor) {
 /* The SCAN command completely relies on scanGenericCommand. */
 void scanCommand(client *c) {
     unsigned long cursor;
-    if (parseScanCursorOrReply(c,c->argv[1],&cursor) == REDIS_ERR) return;
+    if (parseScanCursorOrReply(c,c->argv[1],&cursor) == C_ERR) return;
     scanGenericCommand(c,NULL,cursor);
 }
 
@@ -685,7 +685,7 @@ void shutdownCommand(client *c) {
      * Also when in Sentinel mode clear the SAVE flag and force NOSAVE. */
     if (server.loading || server.sentinel_mode)
         flags = (flags & ~REDIS_SHUTDOWN_SAVE) | REDIS_SHUTDOWN_NOSAVE;
-    if (prepareForShutdown(flags) == REDIS_OK) exit(0);
+    if (prepareForShutdown(flags) == C_OK) exit(0);
     addReplyError(c,"Errors trying to SHUTDOWN. Check logs.");
 }
 
@@ -754,9 +754,9 @@ void moveCommand(client *c) {
     src = c->db;
     srcid = c->db->id;
 
-    if (getLongLongFromObject(c->argv[2],&dbid) == REDIS_ERR ||
+    if (getLongLongFromObject(c->argv[2],&dbid) == C_ERR ||
         dbid < INT_MIN || dbid > INT_MAX ||
-        selectDb(c,dbid) == REDIS_ERR)
+        selectDb(c,dbid) == C_ERR)
     {
         addReply(c,shared.outofrangeerr);
         return;
@@ -903,7 +903,7 @@ void expireGenericCommand(client *c, long long basetime, int unit) {
     robj *key = c->argv[1], *param = c->argv[2];
     long long when; /* unix time in milliseconds when the key will expire. */
 
-    if (getLongLongFromObjectOrReply(c, param, &when, NULL) != REDIS_OK)
+    if (getLongLongFromObjectOrReply(c, param, &when, NULL) != C_OK)
         return;
 
     if (unit == UNIT_SECONDS) when *= 1000;