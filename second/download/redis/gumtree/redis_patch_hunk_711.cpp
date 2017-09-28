 }
 
 /*-----------------------------------------------------------------------------
  * Type agnostic commands operating on the key space
  *----------------------------------------------------------------------------*/
 
+/* Return the set of flags to use for the emptyDb() call for FLUSHALL
+ * and FLUSHDB commands.
+ *
+ * Currently the command just attempts to parse the "ASYNC" option. It
+ * also checks if the command arity is wrong.
+ *
+ * On success C_OK is returned and the flags are stored in *flags, otherwise
+ * C_ERR is returned and the function sends an error to the client. */
+int getFlushCommandFlags(client *c, int *flags) {
+    /* Parse the optional ASYNC option. */
+    if (c->argc > 1) {
+        if (c->argc > 2 || strcasecmp(c->argv[1]->ptr,"async")) {
+            addReply(c,shared.syntaxerr);
+            return C_ERR;
+        }
+        *flags = EMPTYDB_ASYNC;
+    } else {
+        *flags = EMPTYDB_NO_FLAGS;
+    }
+    return C_OK;
+}
+
+/* FLUSHDB [ASYNC]
+ *
+ * Flushes the currently SELECTed Redis DB. */
 void flushdbCommand(client *c) {
-    server.dirty += dictSize(c->db->dict);
+    int flags;
+
+    if (getFlushCommandFlags(c,&flags) == C_ERR) return;
     signalFlushedDb(c->db->id);
-    dictEmpty(c->db->dict,NULL);
-    dictEmpty(c->db->expires,NULL);
-    if (server.cluster_enabled) slotToKeyFlush();
+    server.dirty += emptyDb(c->db->id,flags,NULL);
     addReply(c,shared.ok);
 }
 
+/* FLUSHALL [ASYNC]
+ *
+ * Flushes the whole server data set. */
 void flushallCommand(client *c) {
+    int flags;
+
+    if (getFlushCommandFlags(c,&flags) == C_ERR) return;
     signalFlushedDb(-1);
-    server.dirty += emptyDb(NULL);
+    server.dirty += emptyDb(-1,flags,NULL);
     addReply(c,shared.ok);
     if (server.rdb_child_pid != -1) {
         kill(server.rdb_child_pid,SIGUSR1);
         rdbRemoveTempFile(server.rdb_child_pid);
     }
     if (server.saveparamslen > 0) {
         /* Normally rdbSave() will reset dirty, but we don't want this here
          * as otherwise FLUSHALL will not be replicated nor put into the AOF. */
         int saved_dirty = server.dirty;
-        rdbSave(server.rdb_filename);
+        rdbSave(server.rdb_filename,NULL);
         server.dirty = saved_dirty;
     }
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
  * Return value is the number of keys existing. */
 void existsCommand(client *c) {
     long long count = 0;
