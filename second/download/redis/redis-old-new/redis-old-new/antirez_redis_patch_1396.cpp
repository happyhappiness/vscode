@@ -1111,7 +1111,7 @@ sds getClientInfoString(redisClient *client) {
     if (emask & AE_WRITABLE) *p++ = 'w';
     *p = '\0';
     return sdscatprintf(sdsempty(),
-        "addr=%s:%d fd=%d age=%ld idle=%ld flags=%s db=%d sub=%d psub=%d qbuf=%lu obl=%lu oll=%lu omem=%lu events=%s cmd=%s",
+        "addr=%s:%d fd=%d age=%ld idle=%ld flags=%s db=%d sub=%d psub=%d qbuf=%lu qbuf-free=%lu obl=%lu oll=%lu omem=%lu events=%s cmd=%s",
         ip,port,client->fd,
         (long)(now - client->ctime),
         (long)(now - client->lastinteraction),
@@ -1120,6 +1120,7 @@ sds getClientInfoString(redisClient *client) {
         (int) dictSize(client->pubsub_channels),
         (int) listLength(client->pubsub_patterns),
         (unsigned long) sdslen(client->querybuf),
+        (unsigned long) sdsavail(client->querybuf),
         (unsigned long) client->bufpos,
         (unsigned long) listLength(client->reply),
         getClientOutputBufferMemoryUsage(client),