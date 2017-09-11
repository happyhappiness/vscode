@@ -51,7 +51,7 @@ redisClient *createClient(int fd) {
     c->bulklen = -1;
     c->sentlen = 0;
     c->flags = 0;
-    c->lastinteraction = time(NULL);
+    c->ctime = c->lastinteraction = time(NULL);
     c->authenticated = 0;
     c->replstate = REDIS_REPL_NONE;
     c->reply = listCreate();
@@ -1111,8 +1111,9 @@ sds getClientInfoString(redisClient *client) {
     if (emask & AE_WRITABLE) *p++ = 'w';
     *p = '\0';
     return sdscatprintf(sdsempty(),
-        "addr=%s:%d fd=%d idle=%ld flags=%s db=%d sub=%d psub=%d qbuf=%lu obl=%lu oll=%lu omem=%lu events=%s cmd=%s",
+        "addr=%s:%d fd=%d age=%ld idle=%ld flags=%s db=%d sub=%d psub=%d qbuf=%lu obl=%lu oll=%lu omem=%lu events=%s cmd=%s",
         ip,port,client->fd,
+        (long)(now - client->ctime),
         (long)(now - client->lastinteraction),
         flags,
         client->db->id,