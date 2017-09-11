@@ -1868,6 +1868,15 @@ int processCommand(redisClient *c) {
         call(c,REDIS_CALL_FULL);
         if (listLength(server.ready_keys))
             handleClientsBlockedOnLists();
+        /* Acknowledge the master about the execution of this command. */
+        if (c->flags & REDIS_MASTER) {
+            c->flags |= REDIS_MASTER_FORCE_REPLY;
+            addReplyMultiBulkLen(c,3);
+            addReplyBulkCString(c,"REPLCONF");
+            addReplyBulkCString(c,"ACK");
+            addReplyBulkLongLong(c,c->reploff);
+            c->flags &= ~REDIS_MASTER_FORCE_REPLY;
+        }
     }
     return REDIS_OK;
 }
@@ -2337,8 +2346,9 @@ sds genRedisInfoString(char *section) {
                     break;
                 }
                 if (state == NULL) continue;
-                info = sdscatprintf(info,"slave%d:%s,%d,%s\r\n",
-                    slaveid,ip,slave->slave_listening_port,state);
+                info = sdscatprintf(info,"slave%d:%s,%d,%s,%lld\r\n",
+                    slaveid,ip,slave->slave_listening_port,state,
+                    slave->repl_ack_off);
                 slaveid++;
             }
         }