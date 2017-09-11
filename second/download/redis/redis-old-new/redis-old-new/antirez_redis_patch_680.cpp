@@ -1219,17 +1219,6 @@ void getClientsMaxBuffers(unsigned long *longest_output_list,
     *biggest_input_buffer = bib;
 }
 
-/* This is a helper function for genClientPeerId().
- * It writes the specified ip/port to "peerid" as a null termiated string
- * in the form ip:port if ip does not contain ":" itself, otherwise
- * [ip]:port format is used (for IPv6 addresses basically). */
-void formatPeerId(char *peerid, size_t peerid_len, char *ip, int port) {
-    if (strchr(ip,':'))
-        snprintf(peerid,peerid_len,"[%s]:%d",ip,port);
-    else
-        snprintf(peerid,peerid_len,"%s:%d",ip,port);
-}
-
 /* A Redis "Peer ID" is a colon separated ip:port pair.
  * For IPv4 it's in the form x.y.z.k:port, example: "127.0.0.1:1234".
  * For IPv6 addresses we use [] around the IP part, like in "[::1]:1234".
@@ -1238,24 +1227,17 @@ void formatPeerId(char *peerid, size_t peerid_len, char *ip, int port) {
  * A Peer ID always fits inside a buffer of REDIS_PEER_ID_LEN bytes, including
  * the null term.
  *
- * The function returns REDIS_OK on succcess, and REDIS_ERR on failure.
- *
  * On failure the function still populates 'peerid' with the "?:0" string
  * in case you want to relax error checking or need to display something
  * anyway (see anetPeerToString implementation for more info). */
-int genClientPeerId(redisClient *client, char *peerid, size_t peerid_len) {
-    char ip[REDIS_IP_STR_LEN];
-    int port;
-
+static void genClientPeerId(redisClient *client, char *peerid,
+                            size_t peerid_len) {
     if (client->flags & REDIS_UNIX_SOCKET) {
         /* Unix socket client. */
         snprintf(peerid,peerid_len,"%s:0",server.unixsocket);
-        return REDIS_OK;
     } else {
         /* TCP client. */
-        int retval = anetPeerToString(client->fd,ip,sizeof(ip),&port);
-        formatPeerId(peerid,peerid_len,ip,port);
-        return (retval == -1) ? REDIS_ERR : REDIS_OK;
+        anetFormatPeer(client->fd,peerid,peerid_len);
     }
 }
 