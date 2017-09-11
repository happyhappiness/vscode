@@ -70,6 +70,7 @@ redisClient *createClient(int fd) {
 
     selectDb(c,0);
     c->fd = fd;
+    c->name = NULL;
     c->bufpos = 0;
     c->querybuf = sdsempty();
     c->querybuf_peak = 0;
@@ -668,6 +669,7 @@ void freeClient(redisClient *c) {
     }
 
     /* Release memory */
+    if (c->name) decrRefCount(c->name);
     zfree(c->argv);
     freeClientMultiState(c);
     zfree(c);
@@ -1123,9 +1125,11 @@ sds getClientInfoString(redisClient *client) {
     if (emask & AE_WRITABLE) *p++ = 'w';
     *p = '\0';
     return sdscatprintf(sdsempty(),
-        "addr=%s:%d fd=%d age=%ld idle=%ld flags=%s db=%d sub=%d psub=%d multi=%d qbuf=%lu qbuf-free=%lu obl=%lu oll=%lu omem=%lu events=%s cmd=%s",
+        "addr=%s:%d fd=%d name=%s age=%ld idle=%ld flags=%s db=%d sub=%d psub=%d multi=%d qbuf=%lu qbuf-free=%lu obl=%lu oll=%lu omem=%lu events=%s cmd=%s",
         (client->flags & REDIS_UNIX_SOCKET) ? server.unixsocket : ip,
-        port,client->fd,
+        port,
+        client->fd,
+        client->name ? (char*)client->name->ptr : "",
         (long)(server.unixtime - client->ctime),
         (long)(server.unixtime - client->lastinteraction),
         flags,
@@ -1190,6 +1194,39 @@ void clientCommand(redisClient *c) {
             }
         }
         addReplyError(c,"No such client");
+    } else if (!strcasecmp(c->argv[1]->ptr,"setname") && c->argc == 3) {
+        int j, len = sdslen(c->argv[2]->ptr);
+        char *p = c->argv[2]->ptr;
+
+        /* Setting the client name to an empty string actually removes
+         * the current name. */
+        if (len == 0) {
+            if (c->name) decrRefCount(c->name);
+            c->name = NULL;
+            addReply(c,shared.ok);
+            return;
+        }
+
+        /* Otherwise check if the charset is ok. We need to do this otherwise
+         * CLIENT LIST format will break. You should always be able to
+         * split by space to get the different fields. */
+        for (j = 0; j < len; j++) {
+            if (p[j] < '!' || p[j] > '~') { /* ASCI is assumed. */
+                addReplyError(c,
+                    "Client names cannot contain spaces, "
+                    "newlines or special characters.");
+                return;
+            }
+        }
+        if (c->name) decrRefCount(c->name);
+        c->name = c->argv[2];
+        incrRefCount(c->name);
+        addReply(c,shared.ok);
+    } else if (!strcasecmp(c->argv[1]->ptr,"getname") && c->argc == 2) {
+        if (c->name)
+            addReplyBulk(c,c->name);
+        else
+            addReply(c,shared.nullbulk);
     } else {
         addReplyError(c, "Syntax error, try CLIENT (LIST | KILL ip:port)");
     }