@@ -4481,7 +4481,6 @@ void migrateCommand(redisClient *c) {
 
 try_again:
     /* Initialization */
-    cs = NULL;
     copy = 0;
     replace = 0;
     ttl = 0;
@@ -4519,13 +4518,15 @@ void migrateCommand(redisClient *c) {
 
     rioInitWithBuffer(&cmd,sdsempty());
 
-    /* Create RESTORE payload and generate the protocol to call the command. */
-    if (cs->last_dbid != dbid) {
+    /* Send the SELECT command if the current DB is not already selected. */
+    int select = cs->last_dbid != dbid; /* Should we emit SELECT? */
+    if (select) {
         redisAssertWithInfo(c,NULL,rioWriteBulkCount(&cmd,'*',2));
         redisAssertWithInfo(c,NULL,rioWriteBulkString(&cmd,"SELECT",6));
         redisAssertWithInfo(c,NULL,rioWriteBulkLongLong(&cmd,dbid));
     }
 
+    /* Create RESTORE payload and generate the protocol to call the command. */
     expireat = getExpire(c->db,c->argv[3]);
     if (expireat != -1) {
         ttl = expireat-mstime();
@@ -4575,12 +4576,12 @@ void migrateCommand(redisClient *c) {
         char buf2[1024];
 
         /* Read the two replies */
-        if (cs->last_dbid != dbid && syncReadLine(cs->fd, buf1, sizeof(buf1), timeout) <= 0)
+        if (select && syncReadLine(cs->fd, buf1, sizeof(buf1), timeout) <= 0)
             goto socket_rd_err;
         if (syncReadLine(cs->fd, buf2, sizeof(buf2), timeout) <= 0)
             goto socket_rd_err;
-        if ((cs->last_dbid != dbid && buf1[0] == '-') || buf2[0] == '-') {
-            /* If we got an error at all, assume that the last_dbid is no longer valid */
+        if ((select && buf1[0] == '-') || buf2[0] == '-') {
+            /* On error assume that last_dbid is no longer valid. */
             cs->last_dbid = -1;
             addReplyErrorFormat(c,"Target instance replied with error: %s",
                 (cs->last_dbid != dbid && buf1[0] == '-') ? buf1+1 : buf2+1);
@@ -4589,15 +4590,14 @@ void migrateCommand(redisClient *c) {
             cs->last_dbid = dbid;
             robj *aux;
 
+            addReply(c,shared.ok);
+
             if (!copy) {
                 /* No COPY option: remove the local key, signal the change. */
                 dbDelete(c->db,c->argv[3]);
                 signalModifiedKey(c->db,c->argv[3]);
-            }
-            addReply(c,shared.ok);
-            server.dirty++;
+                server.dirty++;
 
-            if (!copy) {
                 /* Translate MIGRATE as DEL for replication/AOF. */
                 aux = createStringObject("DEL",3);
                 rewriteClientCommandVector(c,2,aux,c->argv[3]);