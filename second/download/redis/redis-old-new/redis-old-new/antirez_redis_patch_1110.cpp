@@ -557,7 +557,7 @@ void acceptTcpHandler(aeEventLoop *el, int fd, void *privdata, int mask) {
     REDIS_NOTUSED(mask);
     REDIS_NOTUSED(privdata);
 
-    cfd = anetTcpAccept(server.neterr, fd, cip, &cport);
+    cfd = anetTcpAccept(server.neterr, fd, cip, sizeof(cip), &cport);
     if (cfd == AE_ERR) {
         redisLog(REDIS_WARNING,"Accepting client connection: %s", server.neterr);
         return;
@@ -1133,7 +1133,7 @@ sds getClientInfoString(redisClient *client) {
     int emask;
 
     if (!(client->flags & REDIS_UNIX_SOCKET))
-        anetPeerToString(client->fd,ip,&port);
+        anetPeerToString(client->fd,ip,sizeof(ip),&port);
     p = flags;
     if (client->flags & REDIS_SLAVE) {
         if (client->flags & REDIS_MONITOR)
@@ -1214,7 +1214,7 @@ void clientCommand(redisClient *c) {
             int port;
 
             client = listNodeValue(ln);
-            if (anetPeerToString(client->fd,ip,&port) == -1) continue;
+            if (anetPeerToString(client->fd,ip,sizeof(ip),&port) == -1) continue;
             snprintf(addr,sizeof(addr),"%s:%d",ip,port);
             if (strcmp(addr,c->argv[2]->ptr) == 0) {
                 addReply(c,shared.ok);