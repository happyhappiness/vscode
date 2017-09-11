@@ -4592,18 +4592,27 @@ void migrateCloseTimedoutSockets(void) {
     dictReleaseIterator(di);
 }
 
-/* MIGRATE host port key dbid timeout [COPY | REPLACE] */
+/* MIGRATE host port key dbid timeout [COPY | REPLACE]
+ *
+ * On in the multiple keys form:
+ *
+ * MIGRATE host port "" dbid timeout [COPY | REPLACE] KEYS key1 key2 ... keyN */
 void migrateCommand(client *c) {
     migrateCachedSocket *cs;
     int copy, replace, j;
     long timeout;
     long dbid;
     long long ttl, expireat;
-    robj *o;
+    robj **ov = zmalloc(sizeof(robj*)); /* Objects to migrate. */
+    robj **kv = zmalloc(sizeof(robj*)); /* Key names. */
     rio cmd, payload;
     int retry_num = 0;
+    int write_error = 0;
+
+    /* To support the KEYS option we need the following additional state. */
+    int first_key = 3; /* Argument index of the first key. */
+    int num_keys = 1;  /* By default only migrate the 'key' argument. */
 
-try_again:
     /* Initialization */
     copy = 0;
     replace = 0;
@@ -4615,6 +4624,19 @@ void migrateCommand(client *c) {
             copy = 1;
         } else if (!strcasecmp(c->argv[j]->ptr,"replace")) {
             replace = 1;
+        } else if (!strcasecmp(c->argv[j]->ptr,"keys")) {
+            if (sdslen(c->argv[3]->ptr) != 0) {
+                addReplyError(c,
+                    "When using MIGRATE KEYS option, the key argument"
+                    " must be set to the empty string");
+                zfree(ov); zfree(kv);
+                return;
+            }
+            first_key = j+1;
+            num_keys = c->argc - j - 1;
+            ov = zrealloc(ov,sizeof(robj*)*num_keys);
+            kv = zrealloc(kv,sizeof(robj*)*num_keys);
+            break; /* All the remaining args are keys. */
         } else {
             addReply(c,shared.syntaxerr);
             return;
@@ -4628,14 +4650,28 @@ void migrateCommand(client *c) {
         return;
     if (timeout <= 0) timeout = 1000;
 
-    /* Check if the key is here. If not we reply with success as there is
-     * nothing to migrate (for instance the key expired in the meantime), but
-     * we include such information in the reply string. */
-    if ((o = lookupKeyRead(c->db,c->argv[3])) == NULL) {
+    /* Check if the keys are here. If at least one key is to migrate, do it
+     * otherwise if all the keys are missing reply with "NOKEY" to signal
+     * the caller there was nothing to migrate. We don't return an error in
+     * this case, since often this is due to a normal condition like the key
+     * expiring in the meantime. */
+    int oi = 0;
+    for (j = 0; j < num_keys; j++) {
+        if ((ov[oi] = lookupKeyRead(c->db,c->argv[first_key+j])) != NULL) {
+            kv[oi] = c->argv[first_key+j];
+            oi++;
+        }
+    }
+    num_keys = oi;
+    if (num_keys == 0) {
+        zfree(ov); zfree(kv);
         addReplySds(c,sdsnew("+NOKEY\r\n"));
         return;
     }
 
+try_again:
+    write_error = 0;
+
     /* Connect */
     cs = migrateGetSocket(c,c->argv[1],c->argv[2],timeout);
     if (cs == NULL) return; /* error sent to the client by migrateGetSocket() */
@@ -4651,33 +4687,36 @@ void migrateCommand(client *c) {
     }
 
     /* Create RESTORE payload and generate the protocol to call the command. */
-    expireat = getExpire(c->db,c->argv[3]);
-    if (expireat != -1) {
-        ttl = expireat-mstime();
-        if (ttl < 1) ttl = 1;
-    }
-    serverAssertWithInfo(c,NULL,rioWriteBulkCount(&cmd,'*',replace ? 5 : 4));
-    if (server.cluster_enabled)
+    for (j = 0; j < num_keys; j++) {
+        expireat = getExpire(c->db,kv[j]);
+        if (expireat != -1) {
+            ttl = expireat-mstime();
+            if (ttl < 1) ttl = 1;
+        }
+        serverAssertWithInfo(c,NULL,rioWriteBulkCount(&cmd,'*',replace ? 5 : 4));
+        if (server.cluster_enabled)
+            serverAssertWithInfo(c,NULL,
+                rioWriteBulkString(&cmd,"RESTORE-ASKING",14));
+        else
+            serverAssertWithInfo(c,NULL,rioWriteBulkString(&cmd,"RESTORE",7));
+        serverAssertWithInfo(c,NULL,sdsEncodedObject(kv[j]));
+        serverAssertWithInfo(c,NULL,rioWriteBulkString(&cmd,kv[j]->ptr,
+                sdslen(kv[j]->ptr)));
+        serverAssertWithInfo(c,NULL,rioWriteBulkLongLong(&cmd,ttl));
+
+        /* Emit the payload argument, that is the serialized object using
+         * the DUMP format. */
+        createDumpPayload(&payload,ov[j]);
         serverAssertWithInfo(c,NULL,
-            rioWriteBulkString(&cmd,"RESTORE-ASKING",14));
-    else
-        serverAssertWithInfo(c,NULL,rioWriteBulkString(&cmd,"RESTORE",7));
-    serverAssertWithInfo(c,NULL,sdsEncodedObject(c->argv[3]));
-    serverAssertWithInfo(c,NULL,rioWriteBulkString(&cmd,c->argv[3]->ptr,
-            sdslen(c->argv[3]->ptr)));
-    serverAssertWithInfo(c,NULL,rioWriteBulkLongLong(&cmd,ttl));
-
-    /* Emit the payload argument, that is the serialized object using
-     * the DUMP format. */
-    createDumpPayload(&payload,o);
-    serverAssertWithInfo(c,NULL,rioWriteBulkString(&cmd,payload.io.buffer.ptr,
-                                sdslen(payload.io.buffer.ptr)));
-    sdsfree(payload.io.buffer.ptr);
-
-    /* Add the REPLACE option to the RESTORE command if it was specified
-     * as a MIGRATE option. */
-    if (replace)
-        serverAssertWithInfo(c,NULL,rioWriteBulkString(&cmd,"REPLACE",7));
+            rioWriteBulkString(&cmd,payload.io.buffer.ptr,
+                               sdslen(payload.io.buffer.ptr)));
+        sdsfree(payload.io.buffer.ptr);
+
+        /* Add the REPLACE option to the RESTORE command if it was specified
+         * as a MIGRATE option. */
+        if (replace)
+            serverAssertWithInfo(c,NULL,rioWriteBulkString(&cmd,"REPLACE",7));
+    }
 
     /* Transfer the query to the other node in 64K chunks. */
     errno = 0;
@@ -4689,64 +4728,77 @@ void migrateCommand(client *c) {
         while ((towrite = sdslen(buf)-pos) > 0) {
             towrite = (towrite > (64*1024) ? (64*1024) : towrite);
             nwritten = syncWrite(cs->fd,buf+pos,towrite,timeout);
-            if (nwritten != (signed)towrite) goto socket_wr_err;
+            if (nwritten != (signed)towrite) {
+                write_error = 1;
+                goto socket_err;
+            }
             pos += nwritten;
         }
     }
 
-    /* Read back the reply. */
-    {
-        char buf1[1024];
-        char buf2[1024];
+    char buf1[1024]; /* Select reply. */
+    char buf2[1024]; /* Restore reply. */
 
-        /* Read the two replies */
-        if (select && syncReadLine(cs->fd, buf1, sizeof(buf1), timeout) <= 0)
-            goto socket_rd_err;
+    /* Read the SELECT reply if needed. */
+    if (select && syncReadLine(cs->fd, buf1, sizeof(buf1), timeout) <= 0)
+        goto socket_err;
+
+    /* Read the RESTORE replies. */
+    int error_from_target = 0;
+    for (j = 0; j < num_keys; j++) {
         if (syncReadLine(cs->fd, buf2, sizeof(buf2), timeout) <= 0)
-            goto socket_rd_err;
+            goto socket_err;
+        if (error_from_target) continue; /* Just consume the replies. */
         if ((select && buf1[0] == '-') || buf2[0] == '-') {
             /* On error assume that last_dbid is no longer valid. */
             cs->last_dbid = -1;
             addReplyErrorFormat(c,"Target instance replied with error: %s",
                 (select && buf1[0] == '-') ? buf1+1 : buf2+1);
+            error_from_target = 1;
         } else {
-            /* Update the last_dbid in migrateCachedSocket */
-            cs->last_dbid = dbid;
-            robj *aux;
-
-            addReply(c,shared.ok);
-
             if (!copy) {
+                robj *aux;
+
                 /* No COPY option: remove the local key, signal the change. */
-                dbDelete(c->db,c->argv[3]);
-                signalModifiedKey(c->db,c->argv[3]);
+                dbDelete(c->db,kv[j]);
+                signalModifiedKey(c->db,kv[j]);
                 server.dirty++;
 
                 /* Translate MIGRATE as DEL for replication/AOF. */
-                aux = createStringObject("DEL",3);
-                rewriteClientCommandVector(c,2,aux,c->argv[3]);
-                decrRefCount(aux);
+                if (j == 0) {
+                    aux = createStringObject("DEL",3);
+                    rewriteClientCommandArgument(c,0,aux);
+                    decrRefCount(aux);
+                }
+                rewriteClientCommandArgument(c,j+1,kv[j]);
             }
         }
     }
 
-    sdsfree(cmd.io.buffer.ptr);
-    return;
+    if (!error_from_target) {
+        /* Update the last_dbid in migrateCachedSocket and reply +OK. */
+        cs->last_dbid = dbid;
+        addReply(c,shared.ok);
+    } else {
+        /* On error we already sent it in the for loop above. */
+    }
 
-socket_wr_err:
     sdsfree(cmd.io.buffer.ptr);
-    migrateCloseSocket(c->argv[1],c->argv[2]);
-    if (errno != ETIMEDOUT && retry_num++ == 0) goto try_again;
-    addReplySds(c,
-        sdsnew("-IOERR error or timeout writing to target instance\r\n"));
+    zfree(ov); zfree(kv);
     return;
 
-socket_rd_err:
+/* On socket errors we try to close the cached socket and try again.
+ * It is very common for the cached socket to get closed, if just reopening
+ * it works it's a shame to notify the error to the caller. */
+socket_err:
     sdsfree(cmd.io.buffer.ptr);
     migrateCloseSocket(c->argv[1],c->argv[2]);
     if (errno != ETIMEDOUT && retry_num++ == 0) goto try_again;
+    zfree(ov); zfree(kv);
     addReplySds(c,
-        sdsnew("-IOERR error or timeout reading from target node\r\n"));
+        sdscatprintf(sdsempty(),
+            "-IOERR error or timeout %s to target instance\r\n",
+            write_error ? "writing" : "reading"));
     return;
 }
 