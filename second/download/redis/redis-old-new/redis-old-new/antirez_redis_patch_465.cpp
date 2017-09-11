@@ -1125,7 +1125,7 @@ int serverCron(struct aeEventLoop *eventLoop, long long id, void *clientData) {
     /* We received a SIGTERM, shutting down here in a safe way, as it is
      * not ok doing so inside the signal handler. */
     if (server.shutdown_asap) {
-        if (prepareForShutdown(0) == REDIS_OK) exit(0);
+        if (prepareForShutdown(0) == C_OK) exit(0);
         serverLog(REDIS_WARNING,"SIGTERM received but errors trying to shut down the server, check the logs for more information");
         server.shutdown_asap = 0;
     }
@@ -1206,7 +1206,7 @@ int serverCron(struct aeEventLoop *eventLoop, long long id, void *clientData) {
                 server.unixtime-server.lastsave > sp->seconds &&
                 (server.unixtime-server.lastbgsave_try >
                  REDIS_BGSAVE_RETRY_DELAY ||
-                 server.lastbgsave_status == REDIS_OK))
+                 server.lastbgsave_status == C_OK))
             {
                 serverLog(REDIS_NOTICE,"%d changes in %d seconds. Saving...",
                     sp->changes, (int)sp->seconds);
@@ -1241,7 +1241,7 @@ int serverCron(struct aeEventLoop *eventLoop, long long id, void *clientData) {
      * however to try every second is enough in case of 'hz' is set to
      * an higher frequency. */
     run_with_period(1000) {
-        if (server.aof_last_write_status == REDIS_ERR)
+        if (server.aof_last_write_status == C_ERR)
             flushAppendOnlyFile(0);
     }
 
@@ -1451,7 +1451,7 @@ void initServerConfig(void) {
     server.aof_last_fsync = time(NULL);
     server.aof_rewrite_time_last = -1;
     server.aof_rewrite_time_start = -1;
-    server.aof_lastbgrewrite_status = REDIS_OK;
+    server.aof_lastbgrewrite_status = C_OK;
     server.aof_delayed_fsync = 0;
     server.aof_fd = -1;
     server.aof_selected_db = -1; /* Make sure the first time will not match */
@@ -1678,9 +1678,9 @@ void checkTcpBacklogSettings(void) {
  * contains no specific addresses to bind, this function will try to
  * bind * (all addresses) for both the IPv4 and IPv6 protocols.
  *
- * On success the function returns REDIS_OK.
+ * On success the function returns C_OK.
  *
- * On error the function returns REDIS_ERR. For the function to be on
+ * On error the function returns C_ERR. For the function to be on
  * error, at least one of the server.bindaddr addresses was
  * impossible to bind, or no bind addresses were specified in the server
  * configuration but the function is not able to bind * for at least
@@ -1725,12 +1725,12 @@ int listenToPort(int port, int *fds, int *count) {
                 "Creating Server TCP listening socket %s:%d: %s",
                 server.bindaddr[j] ? server.bindaddr[j] : "*",
                 port, server.neterr);
-            return REDIS_ERR;
+            return C_ERR;
         }
         anetNonBlock(NULL,fds[*count]);
         (*count)++;
     }
-    return REDIS_OK;
+    return C_OK;
 }
 
 /* Resets the stats that we expose via INFO or other means that we want
@@ -1796,7 +1796,7 @@ void initServer(void) {
 
     /* Open the TCP listening socket for the user commands. */
     if (server.port != 0 &&
-        listenToPort(server.port,server.ipfd,&server.ipfd_count) == REDIS_ERR)
+        listenToPort(server.port,server.ipfd,&server.ipfd_count) == C_ERR)
         exit(1);
 
     /* Open the listening Unix domain socket. */
@@ -1848,8 +1848,8 @@ void initServer(void) {
     server.stat_starttime = time(NULL);
     server.stat_peak_memory = 0;
     server.resident_set_size = 0;
-    server.lastbgsave_status = REDIS_OK;
-    server.aof_last_write_status = REDIS_OK;
+    server.lastbgsave_status = C_OK;
+    server.aof_last_write_status = C_OK;
     server.aof_last_write_errno = 0;
     server.repl_good_slaves_count = 0;
     updateCachedTime();
@@ -2187,7 +2187,7 @@ int processCommand(client *c) {
     if (!strcasecmp(c->argv[0]->ptr,"quit")) {
         addReply(c,shared.ok);
         c->flags |= REDIS_CLOSE_AFTER_REPLY;
-        return REDIS_ERR;
+        return C_ERR;
     }
 
     /* Now lookup the command and check ASAP about trivial error conditions
@@ -2197,21 +2197,21 @@ int processCommand(client *c) {
         flagTransaction(c);
         addReplyErrorFormat(c,"unknown command '%s'",
             (char*)c->argv[0]->ptr);
-        return REDIS_OK;
+        return C_OK;
     } else if ((c->cmd->arity > 0 && c->cmd->arity != c->argc) ||
                (c->argc < -c->cmd->arity)) {
         flagTransaction(c);
         addReplyErrorFormat(c,"wrong number of arguments for '%s' command",
             c->cmd->name);
-        return REDIS_OK;
+        return C_OK;
     }
 
     /* Check if the user is authenticated */
     if (server.requirepass && !c->authenticated && c->cmd->proc != authCommand)
     {
         flagTransaction(c);
         addReply(c,shared.noautherr);
-        return REDIS_OK;
+        return C_OK;
     }
 
     /* If cluster is enabled perform the cluster redirection here.
@@ -2229,14 +2229,14 @@ int processCommand(client *c) {
         if (server.cluster->state != REDIS_CLUSTER_OK) {
             flagTransaction(c);
             clusterRedirectClient(c,NULL,0,REDIS_CLUSTER_REDIR_DOWN_STATE);
-            return REDIS_OK;
+            return C_OK;
         } else {
             int error_code;
             clusterNode *n = getNodeByQuery(c,c->cmd,c->argv,c->argc,&hashslot,&error_code);
             if (n == NULL || n != server.cluster->myself) {
                 flagTransaction(c);
                 clusterRedirectClient(c,n,hashslot,error_code);
-                return REDIS_OK;
+                return C_OK;
             }
         }
     }
@@ -2248,32 +2248,32 @@ int processCommand(client *c) {
      * is returning an error. */
     if (server.maxmemory) {
         int retval = freeMemoryIfNeeded();
-        if ((c->cmd->flags & REDIS_CMD_DENYOOM) && retval == REDIS_ERR) {
+        if ((c->cmd->flags & REDIS_CMD_DENYOOM) && retval == C_ERR) {
             flagTransaction(c);
             addReply(c, shared.oomerr);
-            return REDIS_OK;
+            return C_OK;
         }
     }
 
     /* Don't accept write commands if there are problems persisting on disk
      * and if this is a master instance. */
     if (((server.stop_writes_on_bgsave_err &&
           server.saveparamslen > 0 &&
-          server.lastbgsave_status == REDIS_ERR) ||
-          server.aof_last_write_status == REDIS_ERR) &&
+          server.lastbgsave_status == C_ERR) ||
+          server.aof_last_write_status == C_ERR) &&
         server.masterhost == NULL &&
         (c->cmd->flags & REDIS_CMD_WRITE ||
          c->cmd->proc == pingCommand))
     {
         flagTransaction(c);
-        if (server.aof_last_write_status == REDIS_OK)
+        if (server.aof_last_write_status == C_OK)
             addReply(c, shared.bgsaveerr);
         else
             addReplySds(c,
                 sdscatprintf(sdsempty(),
                 "-MISCONF Errors writing to the AOF file: %s\r\n",
                 strerror(server.aof_last_write_errno)));
-        return REDIS_OK;
+        return C_OK;
     }
 
     /* Don't accept write commands if there are not enough good slaves and
@@ -2286,7 +2286,7 @@ int processCommand(client *c) {
     {
         flagTransaction(c);
         addReply(c, shared.noreplicaserr);
-        return REDIS_OK;
+        return C_OK;
     }
 
     /* Don't accept write commands if this is a read only slave. But
@@ -2296,7 +2296,7 @@ int processCommand(client *c) {
         c->cmd->flags & REDIS_CMD_WRITE)
     {
         addReply(c, shared.roslaveerr);
-        return REDIS_OK;
+        return C_OK;
     }
 
     /* Only allow SUBSCRIBE and UNSUBSCRIBE in the context of Pub/Sub */
@@ -2307,7 +2307,7 @@ int processCommand(client *c) {
         c->cmd->proc != psubscribeCommand &&
         c->cmd->proc != punsubscribeCommand) {
         addReplyError(c,"only (P)SUBSCRIBE / (P)UNSUBSCRIBE / QUIT allowed in this context");
-        return REDIS_OK;
+        return C_OK;
     }
 
     /* Only allow INFO and SLAVEOF when slave-serve-stale-data is no and
@@ -2318,14 +2318,14 @@ int processCommand(client *c) {
     {
         flagTransaction(c);
         addReply(c, shared.masterdownerr);
-        return REDIS_OK;
+        return C_OK;
     }
 
     /* Loading DB? Return an error if the command has not the
      * REDIS_CMD_LOADING flag. */
     if (server.loading && !(c->cmd->flags & REDIS_CMD_LOADING)) {
         addReply(c, shared.loadingerr);
-        return REDIS_OK;
+        return C_OK;
     }
 
     /* Lua script too slow? Only allow a limited number of commands. */
@@ -2341,7 +2341,7 @@ int processCommand(client *c) {
     {
         flagTransaction(c);
         addReply(c, shared.slowscripterr);
-        return REDIS_OK;
+        return C_OK;
     }
 
     /* Exec the command */
@@ -2357,7 +2357,7 @@ int processCommand(client *c) {
         if (listLength(server.ready_keys))
             handleClientsBlockedOnLists();
     }
-    return REDIS_OK;
+    return C_OK;
 }
 
 /*================================== Shutdown =============================== */
@@ -2398,7 +2398,7 @@ int prepareForShutdown(int flags) {
              * shutdown or else the dataset will be lost. */
             if (server.aof_state == REDIS_AOF_WAIT_REWRITE) {
                 serverLog(REDIS_WARNING, "Writing initial AOF, can't exit.");
-                return REDIS_ERR;
+                return C_ERR;
             }
             serverLog(REDIS_WARNING,
                 "There is a child rewriting the AOF. Killing it!");
@@ -2411,14 +2411,14 @@ int prepareForShutdown(int flags) {
     if ((server.saveparamslen > 0 && !nosave) || save) {
         serverLog(REDIS_NOTICE,"Saving the final RDB snapshot before exiting.");
         /* Snapshotting. Perform a SYNC SAVE and exit */
-        if (rdbSave(server.rdb_filename) != REDIS_OK) {
+        if (rdbSave(server.rdb_filename) != C_OK) {
             /* Ooops.. error saving! The best we can do is to continue
              * operating. Note that if there was a background saving process,
              * in the next cron() Redis will be notified that the background
              * saving aborted, handling special stuff like slaves pending for
              * synchronization... */
             serverLog(REDIS_WARNING,"Error trying to save the DB, can't exit.");
-            return REDIS_ERR;
+            return C_ERR;
         }
     }
     if (server.daemonize || server.pidfile) {
@@ -2429,7 +2429,7 @@ int prepareForShutdown(int flags) {
     closeListeningSockets(1);
     serverLog(REDIS_WARNING,"%s is now ready to exit, bye bye...",
         server.sentinel_mode ? "Sentinel" : "Redis");
-    return REDIS_OK;
+    return C_OK;
 }
 
 /*================================== Commands =============================== */
@@ -2828,7 +2828,7 @@ sds genRedisInfoString(char *section) {
             server.dirty,
             server.rdb_child_pid != -1,
             (intmax_t)server.lastsave,
-            (server.lastbgsave_status == REDIS_OK) ? "ok" : "err",
+            (server.lastbgsave_status == C_OK) ? "ok" : "err",
             (intmax_t)server.rdb_save_time_last,
             (intmax_t)((server.rdb_child_pid == -1) ?
                 -1 : time(NULL)-server.rdb_save_time_start),
@@ -2838,8 +2838,8 @@ sds genRedisInfoString(char *section) {
             (intmax_t)server.aof_rewrite_time_last,
             (intmax_t)((server.aof_child_pid == -1) ?
                 -1 : time(NULL)-server.aof_rewrite_time_start),
-            (server.aof_lastbgrewrite_status == REDIS_OK) ? "ok" : "err",
-            (server.aof_last_write_status == REDIS_OK) ? "ok" : "err");
+            (server.aof_lastbgrewrite_status == C_OK) ? "ok" : "err",
+            (server.aof_last_write_status == C_OK) ? "ok" : "err");
 
         if (server.aof_state != REDIS_AOF_OFF) {
             info = sdscatprintf(info,
@@ -3146,7 +3146,7 @@ void monitorCommand(client *c) {
  * evict accordingly to the configured policy.
  *
  * If all the bytes needed to return back under the limit were freed the
- * function returns REDIS_OK, otherwise REDIS_ERR is returned, and the caller
+ * function returns C_OK, otherwise C_ERR is returned, and the caller
  * should block the execution of commands that will result in more memory
  * used by the server.
  *
@@ -3288,10 +3288,10 @@ int freeMemoryIfNeeded(void) {
     }
 
     /* Check if we are over the memory limit. */
-    if (mem_used <= server.maxmemory) return REDIS_OK;
+    if (mem_used <= server.maxmemory) return C_OK;
 
     if (server.maxmemory_policy == REDIS_MAXMEMORY_NO_EVICTION)
-        return REDIS_ERR; /* We need to free memory, but policy forbids. */
+        return C_ERR; /* We need to free memory, but policy forbids. */
 
     /* Compute how much memory we need to free. */
     mem_tofree = mem_used - server.maxmemory;
@@ -3417,12 +3417,12 @@ int freeMemoryIfNeeded(void) {
         if (!keys_freed) {
             latencyEndMonitor(latency);
             latencyAddSampleIfNeeded("eviction-cycle",latency);
-            return REDIS_ERR; /* nothing to free... */
+            return C_ERR; /* nothing to free... */
         }
     }
     latencyEndMonitor(latency);
     latencyAddSampleIfNeeded("eviction-cycle",latency);
-    return REDIS_OK;
+    return C_OK;
 }
 
 /* =================================== Main! ================================ */
@@ -3613,10 +3613,10 @@ int checkForSentinelMode(int argc, char **argv) {
 void loadDataFromDisk(void) {
     long long start = ustime();
     if (server.aof_state == REDIS_AOF_ON) {
-        if (loadAppendOnlyFile(server.aof_filename) == REDIS_OK)
+        if (loadAppendOnlyFile(server.aof_filename) == C_OK)
             serverLog(REDIS_NOTICE,"DB loaded from append only file: %.3f seconds",(float)(ustime()-start)/1000000);
     } else {
-        if (rdbLoad(server.rdb_filename) == REDIS_OK) {
+        if (rdbLoad(server.rdb_filename) == C_OK) {
             serverLog(REDIS_NOTICE,"DB loaded from disk: %.3f seconds",
                 (float)(ustime()-start)/1000000);
         } else if (errno != ENOENT) {
@@ -3879,7 +3879,7 @@ int main(int argc, char **argv) {
         checkTcpBacklogSettings();
         loadDataFromDisk();
         if (server.cluster_enabled) {
-            if (verifyClusterConfigWithData() == REDIS_ERR) {
+            if (verifyClusterConfigWithData() == C_ERR) {
                 serverLog(REDIS_WARNING,
                     "You can't have keys in a DB different than DB 0 when in "
                     "Cluster mode. Exiting.");