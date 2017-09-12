@@ -870,15 +870,16 @@ void getClientsMaxBuffers(unsigned long *longest_output_list,
 }
 
 void clientCommand(redisClient *c) {
+    listNode *ln;
+    listIter li;
+    redisClient *client;
+
     if (!strcasecmp(c->argv[1]->ptr,"list") && c->argc == 2) {
-        listNode *ln;
-        listIter li;
         sds o = sdsempty();
         time_t now = time(NULL);
 
         listRewind(server.clients,&li);
         while ((ln = listNext(&li)) != NULL) {
-            redisClient *client;
             char ip[32], flags[16], *p;
             int port;
 
@@ -911,6 +912,26 @@ void clientCommand(redisClient *c) {
         }
         addReplyBulkCBuffer(c,o,sdslen(o));
         sdsfree(o);
+    } else if (!strcasecmp(c->argv[1]->ptr,"kill") && c->argc == 3) {
+        listRewind(server.clients,&li);
+        while ((ln = listNext(&li)) != NULL) {
+            char ip[32], addr[64];
+            int port;
+
+            client = listNodeValue(ln);
+            if (anetPeerToString(client->fd,ip,&port) == -1) continue;
+            snprintf(addr,sizeof(addr),"%s:%d",ip,port);
+            if (strcmp(addr,c->argv[2]->ptr) == 0) {
+                addReply(c,shared.ok);
+                if (c == client) {
+                    client->flags |= REDIS_CLOSE_AFTER_REPLY;
+                } else {
+                    freeClient(client);
+                }
+                return;
+            }
+        }
+        addReplyError(c,"No such client");
     } else {
         addReplyError(c, "Syntax error, try CLIENT (LIST | KILL ip:port)");
     }