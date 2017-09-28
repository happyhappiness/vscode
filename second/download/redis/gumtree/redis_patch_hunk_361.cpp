      * has this state from the previous connection with the master. */
 
     refreshGoodSlavesCount();
     return REDIS_OK; /* The caller can return, no full resync needed. */
 
 need_full_resync:
-    /* We need a full resync for some reason... notify the client. */
-    psync_offset = server.master_repl_offset;
-    /* Add 1 to psync_offset if it the replication backlog does not exists
-     * as when it will be created later we'll increment the offset by one. */
-    if (server.repl_backlog == NULL) psync_offset++;
-    /* Again, we can't use the connection buffers (see above). */
-    buflen = snprintf(buf,sizeof(buf),"+FULLRESYNC %s %lld\r\n",
-                      server.runid,psync_offset);
-    if (write(c->fd,buf,buflen) != buflen) {
-        freeClientAsync(c);
-        return REDIS_OK;
-    }
+    /* We need a full resync for some reason... Note that we can't
+     * reply to PSYNC right now if a full SYNC is needed. The reply
+     * must include the master offset at the time the RDB file we transfer
+     * is generated, so we need to delay the reply to that moment. */
     return REDIS_ERR;
 }
 
 /* Start a BGSAVE for replication goals, which is, selecting the disk or
  * socket target depending on the configuration, and making sure that
  * the script cache is flushed before to start.
  *
+ * The mincapa argument is the bitwise AND among all the slaves capabilities
+ * of the slaves waiting for this BGSAVE, so represents the slave capabilities
+ * all the slaves support. Can be tested via SLAVE_CAPA_* macros.
+ *
+ * Side effects, other than starting a BGSAVE:
+ *
+ * 1) Handle the slaves in WAIT_START state, by preparing them for a full
+ *    sync if the BGSAVE was succesfully started, or sending them an error
+ *    and dropping them from the list of slaves.
+ *
+ * 2) Flush the Lua scripting script cache if the BGSAVE was actually
+ *    started.
+ *
  * Returns REDIS_OK on success or REDIS_ERR otherwise. */
-int startBgsaveForReplication(void) {
+int startBgsaveForReplication(int mincapa) {
     int retval;
+    int socket_target = server.repl_diskless_sync && (mincapa & SLAVE_CAPA_EOF);
+    listIter li;
+    listNode *ln;
 
     redisLog(REDIS_NOTICE,"Starting BGSAVE for SYNC with target: %s",
-        server.repl_diskless_sync ? "slaves sockets" : "disk");
+        socket_target ? "slaves sockets" : "disk");
 
-    if (server.repl_diskless_sync)
+    if (socket_target)
         retval = rdbSaveToSlavesSockets();
     else
         retval = rdbSaveBackground(server.rdb_filename);
 
+    /* If we failed to BGSAVE, remove the slaves waiting for a full
+     * resynchorinization from the list of salves, inform them with
+     * an error about what happened, close the connection ASAP. */
+    if (retval == REDIS_ERR) {
+        redisLog(REDIS_WARNING,"BGSAVE for replication failed");
+        listRewind(server.slaves,&li);
+        while((ln = listNext(&li))) {
+            redisClient *slave = ln->value;
+
+            if (slave->replstate == REDIS_REPL_WAIT_BGSAVE_START) {
+                slave->flags &= ~REDIS_SLAVE;
+                listDelNode(server.slaves,ln);
+                addReplyError(slave,
+                    "BGSAVE failed, replication can't continue");
+                slave->flags |= REDIS_CLOSE_AFTER_REPLY;
+            }
+        }
+        return retval;
+    }
+
+    /* If the target is socket, rdbSaveToSlavesSockets() already setup
+     * the salves for a full resync. Otherwise for disk target do it now.*/
+    if (!socket_target) {
+        listRewind(server.slaves,&li);
+        while((ln = listNext(&li))) {
+            redisClient *slave = ln->value;
+
+            if (slave->replstate == REDIS_REPL_WAIT_BGSAVE_START) {
+                    replicationSetupSlaveForFullResync(slave,
+                            getPsyncInitialOffset());
+            }
+        }
+    }
+
     /* Flush the script cache, since we need that slave differences are
      * accumulated without requiring slaves to match our cached scripts. */
     if (retval == REDIS_OK) replicationScriptCacheFlush();
     return retval;
 }
 
