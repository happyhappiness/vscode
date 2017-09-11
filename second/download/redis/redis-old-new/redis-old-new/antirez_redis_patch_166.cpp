@@ -1412,6 +1412,8 @@ void initServerConfig(void) {
     server.repl_min_slaves_to_write = CONFIG_DEFAULT_MIN_SLAVES_TO_WRITE;
     server.repl_min_slaves_max_lag = CONFIG_DEFAULT_MIN_SLAVES_MAX_LAG;
     server.slave_priority = CONFIG_DEFAULT_SLAVE_PRIORITY;
+    server.slave_announce_ip = CONFIG_DEFAULT_SLAVE_ANNOUNCE_IP;
+    server.slave_announce_port = CONFIG_DEFAULT_SLAVE_ANNOUNCE_PORT;
     server.master_repl_offset = 0;
 
     /* Replication partial resync backlog */
@@ -3056,11 +3058,15 @@ sds genRedisInfoString(char *section) {
             while((ln = listNext(&li))) {
                 client *slave = listNodeValue(ln);
                 char *state = NULL;
-                char ip[NET_IP_STR_LEN];
+                char ip[NET_IP_STR_LEN], *slaveip = slave->slave_ip;
                 int port;
                 long lag = 0;
 
-                if (anetPeerToString(slave->fd,ip,sizeof(ip),&port) == -1) continue;
+                if (slaveip[0] == '\0') {
+                    if (anetPeerToString(slave->fd,ip,sizeof(ip),&port) == -1)
+                        continue;
+                    slaveip = ip;
+                }
                 switch(slave->replstate) {
                 case SLAVE_STATE_WAIT_BGSAVE_START:
                 case SLAVE_STATE_WAIT_BGSAVE_END:
@@ -3080,7 +3086,7 @@ sds genRedisInfoString(char *section) {
                 info = sdscatprintf(info,
                     "slave%d:ip=%s,port=%d,state=%s,"
                     "offset=%lld,lag=%ld\r\n",
-                    slaveid,ip,slave->slave_listening_port,state,
+                    slaveid,slaveip,slave->slave_listening_port,state,
                     slave->repl_ack_off, lag);
                 slaveid++;
             }