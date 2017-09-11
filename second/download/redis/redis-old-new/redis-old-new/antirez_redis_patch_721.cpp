@@ -41,6 +41,30 @@ void replicationDiscardCachedMaster(void);
 void replicationResurrectCachedMaster(int newfd);
 void replicationSendAck(void);
 
+/* --------------------------- Utility functions ---------------------------- */
+
+/* Return the pointer to a string representing the slave ip:listening_port
+ * pair. Mostly useful for logging, since we want to log a slave using its
+ * IP address and it's listening port which is more clear for the user, for
+ * example: "Closing connection with slave 10.1.2.3:6380". */
+char *replicationGetSlaveName(redisClient *c) {
+    static char buf[REDIS_PEER_ID_LEN];
+    char ip[REDIS_IP_STR_LEN];
+
+    ip[0] = '\0';
+    buf[0] = '\0';
+    if (anetPeerToString(c->fd,ip,sizeof(ip),NULL) != -1) {
+        if (c->slave_listening_port)
+            snprintf(buf,sizeof(buf),"%s:%d",ip,c->slave_listening_port);
+        else
+            snprintf(buf,sizeof(buf),"%s:<unknown-slave-port>",ip);
+    } else {
+        snprintf(buf,sizeof(buf),"client id #%llu",
+            (unsigned long long) c->id);
+    }
+    return buf;
+}
+
 /* ---------------------------------- MASTER -------------------------------- */
 
 void createReplicationBacklog(void) {
@@ -1973,15 +1997,8 @@ void replicationCron(void) {
             if (slave->flags & REDIS_PRE_PSYNC) continue;
             if ((server.unixtime - slave->repl_ack_time) > server.repl_timeout)
             {
-                char ip[REDIS_IP_STR_LEN];
-                int port;
-
-                if (anetPeerToString(slave->fd,ip,sizeof(ip),&port) != -1) {
-                    redisLog(REDIS_WARNING,
-                        "Disconnecting timedout slave: %s:%d",
-                        ip, slave->slave_listening_port);
-                }
-                freeClient(slave);
+                    redisLog(REDIS_WARNING, "Disconnecting timedout slave: %s",
+                        replicationGetSlaveName(slave));
             }
         }
     }