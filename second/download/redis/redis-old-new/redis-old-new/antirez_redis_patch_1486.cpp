@@ -924,45 +924,55 @@ void getClientsMaxBuffers(unsigned long *longest_output_list,
     *biggest_input_buffer = bib;
 }
 
+/* Turn a Redis client into an sds string representing its state. */
+sds getClientInfoString(redisClient *client) {
+    char ip[32], flags[16], *p;
+    int port;
+    time_t now = time(NULL);
+
+    if (anetPeerToString(client->fd,ip,&port) == -1) {
+        ip[0] = '?';
+        ip[1] = '\0';
+        port = 0;
+    }
+    p = flags;
+    if (client->flags & REDIS_SLAVE) {
+        if (client->flags & REDIS_MONITOR)
+            *p++ = 'O';
+        else
+            *p++ = 'S';
+    }
+    if (client->flags & REDIS_MASTER) *p++ = 'M';
+    if (p == flags) *p++ = 'N';
+    if (client->flags & REDIS_MULTI) *p++ = 'x';
+    if (client->flags & REDIS_BLOCKED) *p++ = 'b';
+    if (client->flags & REDIS_DIRTY_CAS) *p++ = 'd';
+    if (client->flags & REDIS_CLOSE_AFTER_REPLY) *p++ = 'c';
+    if (client->flags & REDIS_UNBLOCKED) *p++ = 'u';
+    *p++ = '\0';
+    return sdscatprintf(sdsempty(),
+        "addr=%s:%d fd=%d idle=%ld flags=%s db=%d sub=%d psub=%d",
+        ip,port,client->fd,
+        (long)(now - client->lastinteraction),
+        flags,
+        client->db->id,
+        (int) dictSize(client->pubsub_channels),
+        (int) listLength(client->pubsub_patterns));
+}
+
 void clientCommand(redisClient *c) {
     listNode *ln;
     listIter li;
     redisClient *client;
 
     if (!strcasecmp(c->argv[1]->ptr,"list") && c->argc == 2) {
         sds o = sdsempty();
-        time_t now = time(NULL);
 
         listRewind(server.clients,&li);
         while ((ln = listNext(&li)) != NULL) {
-            char ip[32], flags[16], *p;
-            int port;
-
             client = listNodeValue(ln);
-            if (anetPeerToString(client->fd,ip,&port) == -1) continue;
-            p = flags;
-            if (client->flags & REDIS_SLAVE) {
-                if (client->flags & REDIS_MONITOR)
-                    *p++ = 'O';
-                else
-                    *p++ = 'S';
-            }
-            if (client->flags & REDIS_MASTER) *p++ = 'M';
-            if (p == flags) *p++ = 'N';
-            if (client->flags & REDIS_MULTI) *p++ = 'x';
-            if (client->flags & REDIS_BLOCKED) *p++ = 'b';
-            if (client->flags & REDIS_DIRTY_CAS) *p++ = 'd';
-            if (client->flags & REDIS_CLOSE_AFTER_REPLY) *p++ = 'c';
-            if (client->flags & REDIS_UNBLOCKED) *p++ = 'u';
-            *p++ = '\0';
-            o = sdscatprintf(o,
-                "addr=%s:%d fd=%d idle=%ld flags=%s db=%d sub=%d psub=%d\n",
-                ip,port,client->fd,
-                (long)(now - client->lastinteraction),
-                flags,
-                client->db->id,
-                (int) dictSize(client->pubsub_channels),
-                (int) listLength(client->pubsub_patterns));
+            o = sdscatsds(o,getClientInfoString(client));
+            o = sdscatlen(o,"\n",1);
         }
         addReplyBulkCBuffer(c,o,sdslen(o));
         sdsfree(o);