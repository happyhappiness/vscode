 
     /* Return when this key has not expired */
     if (now <= when) return 0;
 
     /* Delete the key */
     server.stat_expiredkeys++;
-    propagateExpire(db,key);
+    propagateExpire(db,key,server.lazyfree_lazy_expire);
     notifyKeyspaceEvent(NOTIFY_EXPIRED,
         "expired",key,db->id);
-    return dbDelete(db,key);
-}
-
-/*-----------------------------------------------------------------------------
- * Expires Commands
- *----------------------------------------------------------------------------*/
-
-/* This is the generic command implementation for EXPIRE, PEXPIRE, EXPIREAT
- * and PEXPIREAT. Because the commad second argument may be relative or absolute
- * the "basetime" argument is used to signal what the base time is (either 0
- * for *AT variants of the command, or the current time for relative expires).
- *
- * unit is either UNIT_SECONDS or UNIT_MILLISECONDS, and is only used for
- * the argv[2] parameter. The basetime is always specified in milliseconds. */
-void expireGenericCommand(client *c, long long basetime, int unit) {
-    robj *key = c->argv[1], *param = c->argv[2];
-    long long when; /* unix time in milliseconds when the key will expire. */
-
-    if (getLongLongFromObjectOrReply(c, param, &when, NULL) != C_OK)
-        return;
-
-    if (unit == UNIT_SECONDS) when *= 1000;
-    when += basetime;
-
-    /* No key, return zero. */
-    if (lookupKeyWrite(c->db,key) == NULL) {
-        addReply(c,shared.czero);
-        return;
-    }
-
-    /* EXPIRE with negative TTL, or EXPIREAT with a timestamp into the past
-     * should never be executed as a DEL when load the AOF or in the context
-     * of a slave instance.
-     *
-     * Instead we take the other branch of the IF statement setting an expire
-     * (possibly in the past) and wait for an explicit DEL from the master. */
-    if (when <= mstime() && !server.loading && !server.masterhost) {
-        robj *aux;
-
-        serverAssertWithInfo(c,key,dbDelete(c->db,key));
-        server.dirty++;
-
-        /* Replicate/AOF this as an explicit DEL. */
-        aux = createStringObject("DEL",3);
-        rewriteClientCommandVector(c,2,aux,key);
-        decrRefCount(aux);
-        signalModifiedKey(c->db,key);
-        notifyKeyspaceEvent(NOTIFY_GENERIC,"del",key,c->db->id);
-        addReply(c, shared.cone);
-        return;
-    } else {
-        setExpire(c->db,key,when);
-        addReply(c,shared.cone);
-        signalModifiedKey(c->db,key);
-        notifyKeyspaceEvent(NOTIFY_GENERIC,"expire",key,c->db->id);
-        server.dirty++;
-        return;
-    }
-}
-
-void expireCommand(client *c) {
-    expireGenericCommand(c,mstime(),UNIT_SECONDS);
-}
-
-void expireatCommand(client *c) {
-    expireGenericCommand(c,0,UNIT_SECONDS);
-}
-
-void pexpireCommand(client *c) {
-    expireGenericCommand(c,mstime(),UNIT_MILLISECONDS);
-}
-
-void pexpireatCommand(client *c) {
-    expireGenericCommand(c,0,UNIT_MILLISECONDS);
-}
-
-void ttlGenericCommand(client *c, int output_ms) {
-    long long expire, ttl = -1;
-
-    /* If the key does not exist at all, return -2 */
-    if (lookupKeyReadWithFlags(c->db,c->argv[1],LOOKUP_NOTOUCH) == NULL) {
-        addReplyLongLong(c,-2);
-        return;
-    }
-    /* The key exists. Return -1 if it has no expire, or the actual
-     * TTL value otherwise. */
-    expire = getExpire(c->db,c->argv[1]);
-    if (expire != -1) {
-        ttl = expire-mstime();
-        if (ttl < 0) ttl = 0;
-    }
-    if (ttl == -1) {
-        addReplyLongLong(c,-1);
-    } else {
-        addReplyLongLong(c,output_ms ? ttl : ((ttl+500)/1000));
-    }
-}
-
-void ttlCommand(client *c) {
-    ttlGenericCommand(c, 0);
-}
-
-void pttlCommand(client *c) {
-    ttlGenericCommand(c, 1);
-}
-
-void persistCommand(client *c) {
-    if (lookupKeyWrite(c->db,c->argv[1])) {
-        if (removeExpire(c->db,c->argv[1])) {
-            addReply(c,shared.cone);
-            server.dirty++;
-        } else {
-            addReply(c,shared.czero);
-        }
-    } else {
-        addReply(c,shared.czero);
-    }
-}
-
-/* TOUCH key1 [key2 key3 ... keyN] */
-void touchCommand(client *c) {
-    int touched = 0;
-    for (int j = 1; j < c->argc; j++)
-        if (lookupKeyRead(c->db,c->argv[j]) != NULL) touched++;
-    addReplyLongLong(c,touched);
+    return server.lazyfree_lazy_expire ? dbAsyncDelete(db,key) :
+                                         dbSyncDelete(db,key);
 }
 
 /* -----------------------------------------------------------------------------
  * API to get key arguments from commands
  * ---------------------------------------------------------------------------*/
 
