@@ -951,13 +951,16 @@ sds getClientInfoString(redisClient *client) {
     if (client->flags & REDIS_UNBLOCKED) *p++ = 'u';
     *p++ = '\0';
     return sdscatprintf(sdsempty(),
-        "addr=%s:%d fd=%d idle=%ld flags=%s db=%d sub=%d psub=%d",
+        "addr=%s:%d fd=%d idle=%ld flags=%s db=%d sub=%d psub=%d qbuf=%lu obl=%lu oll=%lu",
         ip,port,client->fd,
         (long)(now - client->lastinteraction),
         flags,
         client->db->id,
         (int) dictSize(client->pubsub_channels),
-        (int) listLength(client->pubsub_patterns));
+        (int) listLength(client->pubsub_patterns),
+        (unsigned long) sdslen(client->querybuf),
+        (unsigned long) client->bufpos,
+        (unsigned long) listLength(client->reply));
 }
 
 void clientCommand(redisClient *c) {