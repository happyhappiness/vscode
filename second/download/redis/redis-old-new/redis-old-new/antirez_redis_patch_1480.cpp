@@ -36,7 +36,7 @@ redisClient *createClient(int fd) {
     c->reqtype = 0;
     c->argc = 0;
     c->argv = NULL;
-    c->cmd = NULL;
+    c->cmd = c->lastcmd = NULL;
     c->multibulklen = 0;
     c->bulklen = -1;
     c->sentlen = 0;
@@ -966,7 +966,7 @@ sds getClientInfoString(redisClient *client) {
     if (emask & AE_WRITABLE) *p++ = 'w';
     *p = '\0';
     return sdscatprintf(sdsempty(),
-        "addr=%s:%d fd=%d idle=%ld flags=%s db=%d sub=%d psub=%d qbuf=%lu obl=%lu oll=%lu events=%s",
+        "addr=%s:%d fd=%d idle=%ld flags=%s db=%d sub=%d psub=%d qbuf=%lu obl=%lu oll=%lu events=%s cmd=%s",
         ip,port,client->fd,
         (long)(now - client->lastinteraction),
         flags,
@@ -976,7 +976,8 @@ sds getClientInfoString(redisClient *client) {
         (unsigned long) sdslen(client->querybuf),
         (unsigned long) client->bufpos,
         (unsigned long) listLength(client->reply),
-        events);
+        events,
+        client->lastcmd ? client->lastcmd->name : "NULL");
 }
 
 void clientCommand(redisClient *c) {