@@ -196,9 +196,8 @@ int dbSyncDelete(redisDb *db, robj *key) {
 /* This is a wrapper whose behavior depends on the Redis lazy free
  * configuration. Deletes the key synchronously or asynchronously. */
 int dbDelete(redisDb *db, robj *key) {
-    int async = 1; /* TODO: Fixme making this a proper option. */
-    if (async) return dbAsyncDelete(db,key);
-    else       return dbSyncDelete(db,key);
+    return server.lazyfree_lazy_server_del ? dbAsyncDelete(db,key) :
+                                             dbSyncDelete(db,key);
 }
 
 /* Prepare the string object stored at 'key' to be modified destructively
@@ -915,10 +914,10 @@ long long getExpire(redisDb *db, robj *key) {
  * AOF and the master->slave link guarantee operation ordering, everything
  * will be consistent even if we allow write operations against expiring
  * keys. */
-void propagateExpire(redisDb *db, robj *key) {
+void propagateExpire(redisDb *db, robj *key, int lazy) {
     robj *argv[2];
 
-    argv[0] = shared.del;
+    argv[0] = lazy ? shared.unlink : shared.del;
     argv[1] = key;
     incrRefCount(argv[0]);
     incrRefCount(argv[1]);
@@ -961,10 +960,11 @@ int expireIfNeeded(redisDb *db, robj *key) {
 
     /* Delete the key */
     server.stat_expiredkeys++;
-    propagateExpire(db,key);
+    propagateExpire(db,key,server.lazyfree_lazy_expire);
     notifyKeyspaceEvent(NOTIFY_EXPIRED,
         "expired",key,db->id);
-    return dbDelete(db,key);
+    return server.lazyfree_lazy_expire ? dbAsyncDelete(db,key) :
+                                         dbSyncDelete(db,key);
 }
 
 /*-----------------------------------------------------------------------------
@@ -1003,13 +1003,14 @@ void expireGenericCommand(client *c, long long basetime, int unit) {
     if (when <= mstime() && !server.loading && !server.masterhost) {
         robj *aux;
 
-        serverAssertWithInfo(c,key,dbDelete(c->db,key));
+        int deleted = server.lazyfree_lazy_expire ? dbAsyncDelete(c->db,key) :
+                                                    dbSyncDelete(c->db,key);
+        serverAssertWithInfo(c,key,deleted);
         server.dirty++;
 
-        /* Replicate/AOF this as an explicit DEL. */
-        aux = createStringObject("DEL",3);
+        /* Replicate/AOF this as an explicit DEL or UNLINK. */
+        aux = server.lazyfree_lazy_expire ? shared.unlink : shared.del;
         rewriteClientCommandVector(c,2,aux,key);
-        decrRefCount(aux);
         signalModifiedKey(c->db,key);
         notifyKeyspaceEvent(NOTIFY_GENERIC,"del",key,c->db->id);
         addReply(c, shared.cone);