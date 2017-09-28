              * another slave. Set the right state, and copy the buffer. */
             copyClientOutputBuffer(c,slave);
             c->replstate = REDIS_REPL_WAIT_BGSAVE_END;
             redisLog(REDIS_NOTICE,"Waiting for end of BGSAVE for SYNC");
         } else {
             /* No way, we need to wait for the next BGSAVE in order to
-             * register differences */
+             * register differences. */
             c->replstate = REDIS_REPL_WAIT_BGSAVE_START;
             redisLog(REDIS_NOTICE,"Waiting for next BGSAVE for SYNC");
         }
+    } else if (server.rdb_child_pid != -1 &&
+               server.rdb_child_type == REDIS_RDB_CHILD_TYPE_SOCKET)
+    {
+        /* There is an RDB child process but it is writing directly to
+         * children sockets. We need to wait for the next BGSAVE
+         * in order to synchronize. */
+        c->replstate = REDIS_REPL_WAIT_BGSAVE_START;
+        redisLog(REDIS_NOTICE,"Waiting for next BGSAVE for SYNC");
     } else {
-        /* Ok we don't have a BGSAVE in progress, let's start one */
-        redisLog(REDIS_NOTICE,"Starting BGSAVE for SYNC");
-        if (rdbSaveBackground(server.rdb_filename) != REDIS_OK) {
-            redisLog(REDIS_NOTICE,"Replication failed, can't BGSAVE");
-            addReplyError(c,"Unable to perform background save");
-            return;
+        if (server.repl_diskless_sync) {
+            /* Diskless replication RDB child is created inside
+             * replicationCron() since we want to delay its start a
+             * few seconds to wait for more slaves to arrive. */
+            c->replstate = REDIS_REPL_WAIT_BGSAVE_START;
+            if (server.repl_diskless_sync_delay)
+                redisLog(REDIS_NOTICE,"Delay next BGSAVE for SYNC");
+        } else {
+            /* Ok we don't have a BGSAVE in progress, let's start one. */
+            if (startBgsaveForReplication() != REDIS_OK) {
+                redisLog(REDIS_NOTICE,"Replication failed, can't BGSAVE");
+                addReplyError(c,"Unable to perform background save");
+                return;
+            }
+            c->replstate = REDIS_REPL_WAIT_BGSAVE_END;
         }
-        c->replstate = REDIS_REPL_WAIT_BGSAVE_END;
-        /* Flush the script cache for the new slave. */
-        replicationScriptCacheFlush();
     }
 
     if (server.repl_disable_tcp_nodelay)
         anetDisableTcpNoDelay(NULL, c->fd); /* Non critical if it fails. */
     c->repldbfd = -1;
     c->flags |= REDIS_SLAVE;
