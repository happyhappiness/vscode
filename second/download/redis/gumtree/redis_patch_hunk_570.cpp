      * into a master. Otherwise the new master address is set. */
     if (!strcasecmp(c->argv[1]->ptr,"no") &&
         !strcasecmp(c->argv[2]->ptr,"one")) {
         if (server.masterhost) {
             replicationUnsetMaster();
             sds client = catClientInfoString(sdsempty(),c);
-            redisLog(REDIS_NOTICE,
-                "MASTER MODE enabled (user request from '%s')",client);
+            serverLog(LL_NOTICE,"MASTER MODE enabled (user request from '%s')",
+                client);
             sdsfree(client);
         }
     } else {
         long port;
 
-        if ((getLongFromObjectOrReply(c, c->argv[2], &port, NULL) != REDIS_OK))
+        if ((getLongFromObjectOrReply(c, c->argv[2], &port, NULL) != C_OK))
             return;
 
         /* Check if we are already attached to the specified slave */
         if (server.masterhost && !strcasecmp(server.masterhost,c->argv[1]->ptr)
             && server.masterport == port) {
-            redisLog(REDIS_NOTICE,"SLAVE OF would result into synchronization with the master we are already connected with. No operation performed.");
+            serverLog(LL_NOTICE,"SLAVE OF would result into synchronization with the master we are already connected with. No operation performed.");
             addReplySds(c,sdsnew("+OK Already connected to specified master\r\n"));
             return;
         }
         /* There was no previous master or the user specified a different one,
          * we can continue. */
         replicationSetMaster(c->argv[1]->ptr, port);
         sds client = catClientInfoString(sdsempty(),c);
-        redisLog(REDIS_NOTICE,"SLAVE OF %s:%d enabled (user request from '%s')",
+        serverLog(LL_NOTICE,"SLAVE OF %s:%d enabled (user request from '%s')",
             server.masterhost, server.masterport, client);
         sdsfree(client);
     }
     addReply(c,shared.ok);
 }
 
 /* ROLE command: provide information about the role of the instance
  * (master or slave) and additional information related to replication
  * in an easy to process format. */
-void roleCommand(redisClient *c) {
+void roleCommand(client *c) {
     if (server.masterhost == NULL) {
         listIter li;
         listNode *ln;
         void *mbcount;
         int slaves = 0;
 
         addReplyMultiBulkLen(c,3);
         addReplyBulkCBuffer(c,"master",6);
         addReplyLongLong(c,server.master_repl_offset);
         mbcount = addDeferredMultiBulkLength(c);
         listRewind(server.slaves,&li);
         while((ln = listNext(&li))) {
-            redisClient *slave = ln->value;
-            char ip[REDIS_IP_STR_LEN];
+            client *slave = ln->value;
+            char ip[NET_IP_STR_LEN];
 
             if (anetPeerToString(slave->fd,ip,sizeof(ip),NULL) == -1) continue;
-            if (slave->replstate != REDIS_REPL_ONLINE) continue;
+            if (slave->replstate != SLAVE_STATE_ONLINE) continue;
             addReplyMultiBulkLen(c,3);
             addReplyBulkCString(c,ip);
             addReplyBulkLongLong(c,slave->slave_listening_port);
             addReplyBulkLongLong(c,slave->repl_ack_off);
             slaves++;
         }
