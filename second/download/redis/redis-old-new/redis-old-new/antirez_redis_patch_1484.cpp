@@ -926,9 +926,10 @@ void getClientsMaxBuffers(unsigned long *longest_output_list,
 
 /* Turn a Redis client into an sds string representing its state. */
 sds getClientInfoString(redisClient *client) {
-    char ip[32], flags[16], *p;
+    char ip[32], flags[16], events[3], *p;
     int port;
     time_t now = time(NULL);
+    int emask;
 
     if (anetPeerToString(client->fd,ip,&port) == -1) {
         ip[0] = '?';
@@ -950,8 +951,14 @@ sds getClientInfoString(redisClient *client) {
     if (client->flags & REDIS_CLOSE_AFTER_REPLY) *p++ = 'c';
     if (client->flags & REDIS_UNBLOCKED) *p++ = 'u';
     *p++ = '\0';
+
+    emask = client->fd == -1 ? 0 : aeGetFileEvents(server.el,client->fd);
+    p = events;
+    if (emask & AE_READABLE) *p++ = 'r';
+    if (emask & AE_WRITABLE) *p++ = 'w';
+    *p = '\0';
     return sdscatprintf(sdsempty(),
-        "addr=%s:%d fd=%d idle=%ld flags=%s db=%d sub=%d psub=%d qbuf=%lu obl=%lu oll=%lu",
+        "addr=%s:%d fd=%d idle=%ld flags=%s db=%d sub=%d psub=%d qbuf=%lu obl=%lu oll=%lu events=%s",
         ip,port,client->fd,
         (long)(now - client->lastinteraction),
         flags,
@@ -960,7 +967,8 @@ sds getClientInfoString(redisClient *client) {
         (int) listLength(client->pubsub_patterns),
         (unsigned long) sdslen(client->querybuf),
         (unsigned long) client->bufpos,
-        (unsigned long) listLength(client->reply));
+        (unsigned long) listLength(client->reply),
+        events);
 }
 
 void clientCommand(redisClient *c) {