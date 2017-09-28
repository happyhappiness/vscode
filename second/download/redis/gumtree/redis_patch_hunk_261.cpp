             zfree(msg);
         }
         zfree(clientids);
         exitFromChild((retval == REDIS_OK) ? 0 : 1);
     } else {
         /* Parent */
+        zfree(clientids); /* Not used by parent. Free ASAP. */
         server.stat_fork_time = ustime()-start;
         server.stat_fork_rate = (double) zmalloc_used_memory() * 1000000 / server.stat_fork_time / (1024*1024*1024); /* GB per second. */
         latencyAddSampleIfNeeded("fork",server.stat_fork_time/1000);
         if (childpid == -1) {
             redisLog(REDIS_WARNING,"Can't save in background: fork: %s",
                 strerror(errno));
-
-            /* Undo the state change. The caller will perform cleanup on
-             * all the slaves in BGSAVE_START state, but an early call to
-             * replicationSetupSlaveForFullResync() turned it into BGSAVE_END */
-            listRewind(server.slaves,&li);
-            while((ln = listNext(&li))) {
-                redisClient *slave = ln->value;
-                int j;
-
-                for (j = 0; j < numfds; j++) {
-                    if (slave->id == clientids[j]) {
-                        slave->replstate = REDIS_REPL_WAIT_BGSAVE_START;
-                        break;
-                    }
-                }
-            }
+            zfree(fds);
             close(pipefds[0]);
             close(pipefds[1]);
-        } else {
-            redisLog(REDIS_NOTICE,"Background RDB transfer started by pid %d",
-                childpid);
-            server.rdb_save_time_start = time(NULL);
-            server.rdb_child_pid = childpid;
-            server.rdb_child_type = REDIS_RDB_CHILD_TYPE_SOCKET;
-            updateDictResizePolicy();
+            return REDIS_ERR;
         }
-        zfree(clientids);
+        redisLog(REDIS_NOTICE,"Background RDB transfer started by pid %d",childpid);
+        server.rdb_save_time_start = time(NULL);
+        server.rdb_child_pid = childpid;
+        server.rdb_child_type = REDIS_RDB_CHILD_TYPE_SOCKET;
+        updateDictResizePolicy();
         zfree(fds);
-        return (childpid == -1) ? REDIS_ERR : REDIS_OK;
+        return REDIS_OK;
     }
-    return REDIS_OK; /* Unreached. */
+    return REDIS_OK; /* unreached */
 }
 
 void saveCommand(redisClient *c) {
     if (server.rdb_child_pid != -1) {
         addReplyError(c,"Background save already in progress");
         return;
