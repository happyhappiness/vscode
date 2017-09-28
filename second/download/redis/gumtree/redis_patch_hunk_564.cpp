          * client structure representing the master into server.master. */
         server.repl_master_initial_offset = -1;
 
         if (server.cached_master) {
             psync_runid = server.cached_master->replrunid;
             snprintf(psync_offset,sizeof(psync_offset),"%lld", server.cached_master->reploff+1);
-            redisLog(REDIS_NOTICE,"Trying a partial resynchronization (request %s:%s).", psync_runid, psync_offset);
+            serverLog(LL_NOTICE,"Trying a partial resynchronization (request %s:%s).", psync_runid, psync_offset);
         } else {
-            redisLog(REDIS_NOTICE,"Partial resynchronization not possible (no cached master)");
+            serverLog(LL_NOTICE,"Partial resynchronization not possible (no cached master)");
             psync_runid = "?";
             memcpy(psync_offset,"-1",3);
         }
 
         /* Issue the PSYNC command */
         reply = sendSynchronousCommand(SYNC_CMD_WRITE,fd,"PSYNC",psync_runid,psync_offset,NULL);
         if (reply != NULL) {
-            redisLog(REDIS_WARNING,"Unable to send PSYNC to master: %s",reply);
+            serverLog(LL_WARNING,"Unable to send PSYNC to master: %s",reply);
             sdsfree(reply);
             aeDeleteFileEvent(server.el,fd,AE_READABLE);
             return PSYNC_WRITE_ERROR;
         }
         return PSYNC_WAIT_REPLY;
     }
