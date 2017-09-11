@@ -4606,8 +4606,9 @@ void migrateCommand(client *c) {
     long long ttl, expireat;
     robj **ov = zmalloc(sizeof(robj*)); /* Objects to migrate. */
     robj **kv = zmalloc(sizeof(robj*)); /* Key names. */
+    robj **newargv = NULL;
     rio cmd, payload;
-    int retry_num = 0;
+    int may_retry = 1;
     int write_error = 0;
 
     /* To support the KEYS option we need the following additional state. */
@@ -4645,10 +4646,12 @@ void migrateCommand(client *c) {
     }
 
     /* Sanity check */
-    if (getLongFromObjectOrReply(c,c->argv[5],&timeout,NULL) != C_OK)
-        return;
-    if (getLongFromObjectOrReply(c,c->argv[4],&dbid,NULL) != C_OK)
+    if (getLongFromObjectOrReply(c,c->argv[5],&timeout,NULL) != C_OK ||
+        getLongFromObjectOrReply(c,c->argv[4],&dbid,NULL) != C_OK)
+    {
+        zfree(ov); zfree(kv);
         return;
+    }
     if (timeout <= 0) timeout = 1000;
 
     /* Check if the keys are here. If at least one key is to migrate, do it
@@ -4675,7 +4678,10 @@ void migrateCommand(client *c) {
 
     /* Connect */
     cs = migrateGetSocket(c,c->argv[1],c->argv[2],timeout);
-    if (cs == NULL) return; /* error sent to the client by migrateGetSocket() */
+    if (cs == NULL) {
+        zfree(ov); zfree(kv);
+        return; /* error sent to the client by migrateGetSocket() */
+    }
 
     rioInitWithBuffer(&cmd,sdsempty());
 
@@ -4746,14 +4752,16 @@ void migrateCommand(client *c) {
 
     /* Read the RESTORE replies. */
     int error_from_target = 0;
+    int socket_error = 0;
     int del_idx = 1; /* Index of the key argument for the replicated DEL op. */
-    robj **newargv = NULL;
 
     if (!copy) newargv = zmalloc(sizeof(robj*)*(num_keys+1));
 
     for (j = 0; j < num_keys; j++) {
-        if (syncReadLine(cs->fd, buf2, sizeof(buf2), timeout) <= 0)
-            goto socket_err;
+        if (syncReadLine(cs->fd, buf2, sizeof(buf2), timeout) <= 0) {
+            socket_error = 1;
+            break;
+        }
         if ((select && buf1[0] == '-') || buf2[0] == '-') {
             /* On error assume that last_dbid is no longer valid. */
             if (!error_from_target) {
@@ -4776,27 +4784,48 @@ void migrateCommand(client *c) {
         }
     }
 
+    /* On socket error, if we want to retry, do it now before rewriting the
+     * command vector. We only retry if we are sure nothing was processed
+     * and we failed to read the first reply (j == 0 test). */
+    if (!error_from_target && socket_error && j == 0 && may_retry &&
+        errno != ETIMEDOUT)
+    {
+        zfree(newargv);
+        newargv = NULL; /* This will get reallocated on retry. */
+        goto socket_err; /* A retry is guaranteed because of tested conditions.*/
+    }
+
     if (!copy) {
         /* Translate MIGRATE as DEL for replication/AOF. */
         if (del_idx > 1) {
             newargv[0] = createStringObject("DEL",3);
+            /* Note that the following call takes ownership of newargv. */
             replaceClientCommandVector(c,del_idx,newargv);
         } else {
             /* No key transfer acknowledged, no need to rewrite as DEL. */
             zfree(newargv);
         }
+        newargv = NULL; /* Make it safe to call zfree() on it in the future. */
+    }
+
+    /* If we are here and a socket error happened, we don't want to retry.
+     * Just signal the problem to the client. */
+    if (!error_from_target && socket_error) {
+        may_retry = 0;
+        goto socket_err;
     }
 
     if (!error_from_target) {
         /* Update the last_dbid in migrateCachedSocket and reply +OK. */
         cs->last_dbid = dbid;
         addReply(c,shared.ok);
     } else {
-        /* On error we already sent it in the for loop above. */
+        /* On error we already sent it in the for loop above, and set
+         * the curretly selected socket to -1 to force SELECT the next time. */
     }
 
     sdsfree(cmd.io.buffer.ptr);
-    zfree(ov); zfree(kv);
+    zfree(ov); zfree(kv); zfree(newargv);
     return;
 
 /* On socket errors we try to close the cached socket and try again.
@@ -4805,8 +4834,12 @@ void migrateCommand(client *c) {
 socket_err:
     sdsfree(cmd.io.buffer.ptr);
     migrateCloseSocket(c->argv[1],c->argv[2]);
-    if (errno != ETIMEDOUT && retry_num++ == 0) goto try_again;
-    zfree(ov); zfree(kv);
+    /* Note: Closing the migrate socket will also force SELECT next time. */
+    if (errno != ETIMEDOUT && may_retry) {
+        may_retry = 0;
+        goto try_again;
+    }
+    zfree(ov); zfree(kv); zfree(newargv);
     addReplySds(c,
         sdscatprintf(sdsempty(),
             "-IOERR error or timeout %s to target instance\r\n",