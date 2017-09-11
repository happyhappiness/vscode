@@ -33,10 +33,6 @@
 #include <signal.h>
 #include <ctype.h>
 
-void slotToKeyAdd(robj *key);
-void slotToKeyDel(robj *key);
-void slotToKeyFlush(void);
-
 /*-----------------------------------------------------------------------------
  * C-level DB API
  *----------------------------------------------------------------------------*/
@@ -184,7 +180,7 @@ robj *dbRandomKey(redisDb *db) {
 }
 
 /* Delete a key, value, and associated expiration entry if any, from the DB */
-int dbDelete(redisDb *db, robj *key) {
+int dbSyncDelete(redisDb *db, robj *key) {
     /* Deleting an entry from the expires dict will not free the sds of
      * the key, because it is shared with the main dictionary. */
     if (dictSize(db->expires) > 0) dictDelete(db->expires,key->ptr);
@@ -196,6 +192,14 @@ int dbDelete(redisDb *db, robj *key) {
     }
 }
 
+/* This is a wrapper whose behavior depends on the Redis lazy free
+ * configuration. Deletes the key synchronously or asynchronously. */
+int dbDelete(redisDb *db, robj *key) {
+    int async = 1; /* TODO: Fixme making this a proper option. */
+    if (async) return dbAsyncDelete(db,key);
+    else       return dbSyncDelete(db,key);
+}
+
 /* Prepare the string object stored at 'key' to be modified destructively
  * to implement commands like SETBIT or APPEND.
  *
@@ -302,20 +306,31 @@ void flushallCommand(client *c) {
     server.dirty++;
 }
 
-void delCommand(client *c) {
-    int deleted = 0, j;
+/* This command implements DEL and LAZYDEL. */
+void delGenericCommand(client *c, int lazy) {
+    int numdel = 0, j;
 
     for (j = 1; j < c->argc; j++) {
         expireIfNeeded(c->db,c->argv[j]);
-        if (dbDelete(c->db,c->argv[j])) {
+        int deleted  = lazy ? dbAsyncDelete(c->db,c->argv[j]) :
+                              dbSyncDelete(c->db,c->argv[j]);
+        if (deleted) {
             signalModifiedKey(c->db,c->argv[j]);
             notifyKeyspaceEvent(NOTIFY_GENERIC,
                 "del",c->argv[j],c->db->id);
             server.dirty++;
-            deleted++;
+            numdel++;
         }
     }
-    addReplyLongLong(c,deleted);
+    addReplyLongLong(c,numdel);
+}
+
+void delCommand(client *c) {
+    delGenericCommand(c,0);
+}
+
+void unlinkCommand(client *c) {
+    delGenericCommand(c,1);
 }
 
 /* EXISTS key1 key2 ... key_N.