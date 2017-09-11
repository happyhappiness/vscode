@@ -1085,14 +1085,15 @@ sds getClientInfoString(redisClient *client) {
     if (emask & AE_WRITABLE) *p++ = 'w';
     *p = '\0';
     return sdscatprintf(sdsempty(),
-        "addr=%s:%d fd=%d age=%ld idle=%ld flags=%s db=%d sub=%d psub=%d qbuf=%lu qbuf-free=%lu obl=%lu oll=%lu omem=%lu events=%s cmd=%s",
+        "addr=%s:%d fd=%d age=%ld idle=%ld flags=%s db=%d sub=%d psub=%d multi=%d qbuf=%lu qbuf-free=%lu obl=%lu oll=%lu omem=%lu events=%s cmd=%s",
         ip,port,client->fd,
         (long)(server.unixtime - client->ctime),
         (long)(server.unixtime - client->lastinteraction),
         flags,
         client->db->id,
         (int) dictSize(client->pubsub_channels),
         (int) listLength(client->pubsub_patterns),
+        (client->flags & REDIS_MULTI) ? client->mstate.count : -1,
         (unsigned long) sdslen(client->querybuf),
         (unsigned long) sdsavail(client->querybuf),
         (unsigned long) client->bufpos,