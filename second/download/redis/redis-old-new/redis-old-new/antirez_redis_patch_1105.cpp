@@ -1216,6 +1216,7 @@ void clientCommand(redisClient *c) {
 
             client = listNodeValue(ln);
             if (anetPeerToString(client->fd,ip,sizeof(ip),&port) == -1) continue;
+            /* IPV6: might want to wrap a v6 address in [] */
             snprintf(addr,sizeof(addr),"%s:%d",ip,port);
             if (strcmp(addr,c->argv[2]->ptr) == 0) {
                 addReply(c,shared.ok);