     if (listLength(server.slaves)) {
         listIter li;
         listNode *ln;
 
         listRewind(server.slaves,&li);
         while((ln = listNext(&li))) {
-            redisClient *slave = ln->value;
+            client *slave = ln->value;
 
-            if (slave->replstate != REDIS_REPL_ONLINE) continue;
-            if (slave->flags & REDIS_PRE_PSYNC) continue;
+            if (slave->replstate != SLAVE_STATE_ONLINE) continue;
+            if (slave->flags & CLIENT_PRE_PSYNC) continue;
             if ((server.unixtime - slave->repl_ack_time) > server.repl_timeout)
             {
-                redisLog(REDIS_WARNING, "Disconnecting timedout slave: %s",
+                serverLog(LL_WARNING, "Disconnecting timedout slave: %s",
                     replicationGetSlaveName(slave));
                 freeClient(slave);
             }
         }
     }
 
