@@ -47,15 +47,20 @@ int cancelReplicationHandshake(void);
 
 /* Return the pointer to a string representing the slave ip:listening_port
  * pair. Mostly useful for logging, since we want to log a slave using its
- * IP address and it's listening port which is more clear for the user, for
+ * IP address and its listening port which is more clear for the user, for
  * example: "Closing connection with slave 10.1.2.3:6380". */
 char *replicationGetSlaveName(client *c) {
     static char buf[NET_PEER_ID_LEN];
     char ip[NET_IP_STR_LEN];
 
     ip[0] = '\0';
     buf[0] = '\0';
-    if (anetPeerToString(c->fd,ip,sizeof(ip),NULL) != -1) {
+    if (c->slave_ip[0] != '\0' ||
+        anetPeerToString(c->fd,ip,sizeof(ip),NULL) != -1)
+    {
+        /* Note that the 'ip' buffer is always larger than 'c->slave_ip' */
+        if (c->slave_ip[0] != '\0') memcpy(ip,c->slave_ip,sizeof(c->slave_ip));
+
         if (c->slave_listening_port)
             anetFormatAddr(buf,sizeof(buf),ip,c->slave_listening_port);
         else
@@ -717,6 +722,15 @@ void replconfCommand(client *c) {
                     &port,NULL) != C_OK))
                 return;
             c->slave_listening_port = port;
+        } else if (!strcasecmp(c->argv[j]->ptr,"ip-address")) {
+            sds ip = c->argv[j+1]->ptr;
+            if (sdslen(ip) < sizeof(c->slave_ip)) {
+                memcpy(c->slave_ip,ip,sdslen(ip)+1);
+            } else {
+                addReplyErrorFormat(c,"REPLCONF ip-address provided by "
+                    "slave instance is too long: %zd bytes", sdslen(ip));
+                return;
+            }
         } else if (!strcasecmp(c->argv[j]->ptr,"capa")) {
             /* Ignore capabilities not understood by this master. */
             if (!strcasecmp(c->argv[j+1]->ptr,"eof"))
@@ -1462,7 +1476,8 @@ void syncWithMaster(aeEventLoop *el, int fd, void *privdata, int mask) {
     /* Set the slave port, so that Master's INFO command can list the
      * slave listening port correctly. */
     if (server.repl_state == REPL_STATE_SEND_PORT) {
-        sds port = sdsfromlonglong(server.port);
+        sds port = sdsfromlonglong(server.slave_announce_port ?
+            server.slave_announce_port : server.port);
         err = sendSynchronousCommand(SYNC_CMD_WRITE,fd,"REPLCONF",
                 "listening-port",port, NULL);
         sdsfree(port);
@@ -1482,6 +1497,37 @@ void syncWithMaster(aeEventLoop *el, int fd, void *privdata, int mask) {
                                 "REPLCONF listening-port: %s", err);
         }
         sdsfree(err);
+        server.repl_state = REPL_STATE_SEND_IP;
+    }
+
+    /* Skip REPLCONF ip-address if there is no slave-announce-ip option set. */
+    if (server.repl_state == REPL_STATE_SEND_IP &&
+        server.slave_announce_ip == NULL)
+    {
+            server.repl_state = REPL_STATE_SEND_CAPA;
+    }
+
+    /* Set the slave ip, so that Master's INFO command can list the
+     * slave IP address port correctly in case of port forwarding or NAT. */
+    if (server.repl_state == REPL_STATE_SEND_IP) {
+        err = sendSynchronousCommand(SYNC_CMD_WRITE,fd,"REPLCONF",
+                "ip-address",server.slave_announce_ip, NULL);
+        if (err) goto write_error;
+        sdsfree(err);
+        server.repl_state = REPL_STATE_RECEIVE_IP;
+        return;
+    }
+
+    /* Receive REPLCONF ip-address reply. */
+    if (server.repl_state == REPL_STATE_RECEIVE_IP) {
+        err = sendSynchronousCommand(SYNC_CMD_READ,fd,NULL);
+        /* Ignore the error if any, not all the Redis versions support
+         * REPLCONF listening-port. */
+        if (err[0] == '-') {
+            serverLog(LL_NOTICE,"(Non critical) Master does not understand "
+                                "REPLCONF ip-address: %s", err);
+        }
+        sdsfree(err);
         server.repl_state = REPL_STATE_SEND_CAPA;
     }
 
@@ -1787,12 +1833,16 @@ void roleCommand(client *c) {
         listRewind(server.slaves,&li);
         while((ln = listNext(&li))) {
             client *slave = ln->value;
-            char ip[NET_IP_STR_LEN];
+            char ip[NET_IP_STR_LEN], *slaveip = slave->slave_ip;
 
-            if (anetPeerToString(slave->fd,ip,sizeof(ip),NULL) == -1) continue;
+            if (slaveip[0] == '\0') {
+                if (anetPeerToString(slave->fd,ip,sizeof(ip),NULL) == -1)
+                    continue;
+                slaveip = ip;
+            }
             if (slave->replstate != SLAVE_STATE_ONLINE) continue;
             addReplyMultiBulkLen(c,3);
-            addReplyBulkCString(c,ip);
+            addReplyBulkCString(c,slaveip);
             addReplyBulkLongLong(c,slave->slave_listening_port);
             addReplyBulkLongLong(c,slave->repl_ack_off);
             slaves++;