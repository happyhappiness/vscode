             info = sdscatprintf(info,
                 "slave_priority:%d\r\n"
                 "slave_read_only:%d\r\n",
                 server.slave_priority,
                 server.repl_slave_ro);
         }
+
         info = sdscatprintf(info,
             "connected_slaves:%lu\r\n",
             listLength(server.slaves));
+
+        /* If min-slaves-to-write is active, write the number of slaves
+         * currently considered 'good'. */
+        if (server.repl_min_slaves_to_write &&
+            server.repl_min_slaves_max_lag) {
+            info = sdscatprintf(info,
+                "min_slaves_good_slaves:%d\r\n",
+                server.repl_good_slaves_count);
+        }
+
         if (listLength(server.slaves)) {
             int slaveid = 0;
             listNode *ln;
             listIter li;
 
             listRewind(server.slaves,&li);
             while((ln = listNext(&li))) {
                 redisClient *slave = listNodeValue(ln);
                 char *state = NULL;
-                char ip[32];
+                char ip[REDIS_IP_STR_LEN];
                 int port;
+                long lag = 0;
 
-                if (anetPeerToString(slave->fd,ip,&port) == -1) continue;
+                if (anetPeerToString(slave->fd,ip,sizeof(ip),&port) == -1) continue;
                 switch(slave->replstate) {
                 case REDIS_REPL_WAIT_BGSAVE_START:
                 case REDIS_REPL_WAIT_BGSAVE_END:
                     state = "wait_bgsave";
                     break;
                 case REDIS_REPL_SEND_BULK:
