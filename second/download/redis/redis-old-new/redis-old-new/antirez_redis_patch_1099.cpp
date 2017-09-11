@@ -1134,25 +1134,27 @@ void getClientsMaxBuffers(unsigned long *longest_output_list,
  * A Peer ID always fits inside a buffer of REDIS_PEER_ID_LEN bytes, including
  * the null term.
  *
- * The function is always successful, but if the IP or port can't be extracted
- * for some reason, "?" and "0" are used (this is the semantics of
- * anetPeerToString() from anet.c). In practical terms this should never
- * happen. */
-void getClientPeerId(redisClient *client, char *peerid, size_t peerid_len) {
+ * The function returns REDIS_OK on succcess, and REDIS_ERR on failure.
+ *
+ * On failure the function still populates 'peerid' with the "?:0" string
+ * in case you want to relax error checking or need to display something
+ * anyway (see anetPeerToString implementation for more info). */
+int getClientPeerId(redisClient *client, char *peerid, size_t peerid_len) {
     char ip[REDIS_IP_STR_LEN];
     int port;
 
     if (client->flags & REDIS_UNIX_SOCKET) {
         /* Unix socket client. */
         snprintf(peerid,peerid_len,"%s:0",server.unixsocket);
-        return;
+        return REDIS_OK;
     } else {
         /* TCP client. */
-        anetPeerToString(client->fd,ip,sizeof(ip),&port);
+        int retval = anetPeerToString(client->fd,ip,sizeof(ip),&port);
         if (strchr(ip,':'))
             snprintf(peerid,peerid_len,"[%s]:%d",ip,port);
         else
             snprintf(peerid,peerid_len,"%s:%d",ip,port);
+        return (retval == -1) ? REDIS_ERR : REDIS_OK;
     }
 }
 
@@ -1237,14 +1239,12 @@ void clientCommand(redisClient *c) {
     } else if (!strcasecmp(c->argv[1]->ptr,"kill") && c->argc == 3) {
         listRewind(server.clients,&li);
         while ((ln = listNext(&li)) != NULL) {
-            char ip[REDIS_IP_STR_LEN], addr[REDIS_IP_STR_LEN+64];
-            int port;
+            char peerid[REDIS_PEER_ID_LEN];
 
             client = listNodeValue(ln);
-            if (anetPeerToString(client->fd,ip,sizeof(ip),&port) == -1) continue;
-            /* IPV6: might want to wrap a v6 address in [] */
-            snprintf(addr,sizeof(addr),"%s:%d",ip,port);
-            if (strcmp(addr,c->argv[2]->ptr) == 0) {
+            if (getClientPeerId(client,peerid,sizeof(peerid)) == REDIS_ERR)
+                continue;
+            if (strcmp(peerid,c->argv[2]->ptr) == 0) {
                 addReply(c,shared.ok);
                 if (c == client) {
                     client->flags |= REDIS_CLOSE_AFTER_REPLY;