@@ -1126,6 +1126,17 @@ void getClientsMaxBuffers(unsigned long *longest_output_list,
     *biggest_input_buffer = bib;
 }
 
+/* This is an helper function for getClientPeerId().
+ * It writes the specified ip/port to "peerid" as a null termiated string
+ * in the form ip:port if ip does not contain ":" itself, otherwise
+ * [ip]:port format is used (for IPv6 addresses basically). */
+void formatPeerId(char *peerid, size_t peerid_len, char *ip, int port) {
+    if (strchr(ip,':'))
+        snprintf(peerid,peerid_len,"[%s]:%d",ip,port);
+    else
+        snprintf(peerid,peerid_len,"%s:%d",ip,port);
+}
+
 /* A Redis "Peer ID" is a colon separated ip:port pair.
  * For IPv4 it's in the form x.y.z.k:pork, example: "127.0.0.1:1234".
  * For IPv6 addresses we use [] around the IP part, like in "[::1]:1234".
@@ -1150,10 +1161,7 @@ int getClientPeerId(redisClient *client, char *peerid, size_t peerid_len) {
     } else {
         /* TCP client. */
         int retval = anetPeerToString(client->fd,ip,sizeof(ip),&port);
-        if (strchr(ip,':'))
-            snprintf(peerid,peerid_len,"[%s]:%d",ip,port);
-        else
-            snprintf(peerid,peerid_len,"%s:%d",ip,port);
+        formatPeerId(peerid,peerid_len,ip,port);
         return (retval == -1) ? REDIS_ERR : REDIS_OK;
     }
 }