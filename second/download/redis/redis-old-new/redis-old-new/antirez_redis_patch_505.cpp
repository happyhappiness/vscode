@@ -300,8 +300,8 @@ struct evictionPoolEntry *evictionPoolAlloc(void);
 /*============================ Utility functions ============================ */
 
 /* Low level logging. To use only for very big messages, otherwise
- * redisLog() is to prefer. */
-void redisLogRaw(int level, const char *msg) {
+ * serverLog() is to prefer. */
+void serverLogRaw(int level, const char *msg) {
     const int syslogLevelMap[] = { LOG_DEBUG, LOG_INFO, LOG_NOTICE, LOG_WARNING };
     const char *c = ".-*#";
     FILE *fp;
@@ -342,10 +342,10 @@ void redisLogRaw(int level, const char *msg) {
     if (server.syslog_enabled) syslog(syslogLevelMap[level], "%s", msg);
 }
 
-/* Like redisLogRaw() but with printf-alike support. This is the function that
+/* Like serverLogRaw() but with printf-alike support. This is the function that
  * is used across the code. The raw version is only used in order to dump
  * the INFO output on crash. */
-void redisLog(int level, const char *fmt, ...) {
+void serverLog(int level, const char *fmt, ...) {
     va_list ap;
     char msg[REDIS_MAX_LOGMSG_LEN];
 
@@ -355,16 +355,16 @@ void redisLog(int level, const char *fmt, ...) {
     vsnprintf(msg, sizeof(msg), fmt, ap);
     va_end(ap);
 
-    redisLogRaw(level,msg);
+    serverLogRaw(level,msg);
 }
 
 /* Log a fixed message without printf-alike capabilities, in a way that is
  * safe to call from a signal handler.
  *
  * We actually use this only for signals that are not fatal from the point
  * of view of Redis. Signals that are going to kill the server anyway and
- * where we need printf-alike features are served by redisLog(). */
-void redisLogFromHandler(int level, const char *msg) {
+ * where we need printf-alike features are served by serverLog(). */
+void serverLogFromHandler(int level, const char *msg) {
     int fd;
     int log_to_stdout = server.logfile[0] == '\0';
     char buf[64];
@@ -925,7 +925,7 @@ int clientsCronHandleTimeout(redisClient *c, mstime_t now_ms) {
         !(c->flags & REDIS_PUBSUB) &&   /* no timeout for Pub/Sub clients */
         (now - c->lastinteraction > server.maxidletime))
     {
-        redisLog(REDIS_VERBOSE,"Closing idle client");
+        serverLog(REDIS_VERBOSE,"Closing idle client");
         freeClient(c);
         return 1;
     } else if (c->flags & REDIS_BLOCKED) {
@@ -1126,7 +1126,7 @@ int serverCron(struct aeEventLoop *eventLoop, long long id, void *clientData) {
      * not ok doing so inside the signal handler. */
     if (server.shutdown_asap) {
         if (prepareForShutdown(0) == REDIS_OK) exit(0);
-        redisLog(REDIS_WARNING,"SIGTERM received but errors trying to shut down the server, check the logs for more information");
+        serverLog(REDIS_WARNING,"SIGTERM received but errors trying to shut down the server, check the logs for more information");
         server.shutdown_asap = 0;
     }
 
@@ -1139,7 +1139,7 @@ int serverCron(struct aeEventLoop *eventLoop, long long id, void *clientData) {
             used = dictSize(server.db[j].dict);
             vkeys = dictSize(server.db[j].expires);
             if (used || vkeys) {
-                redisLog(REDIS_VERBOSE,"DB %d: %lld keys (%lld volatile) in %lld slots HT.",j,used,vkeys,size);
+                serverLog(REDIS_VERBOSE,"DB %d: %lld keys (%lld volatile) in %lld slots HT.",j,used,vkeys,size);
                 /* dictPrintStats(server.dict); */
             }
         }
@@ -1148,7 +1148,7 @@ int serverCron(struct aeEventLoop *eventLoop, long long id, void *clientData) {
     /* Show information about connected clients */
     if (!server.sentinel_mode) {
         run_with_period(5000) {
-            redisLog(REDIS_VERBOSE,
+            serverLog(REDIS_VERBOSE,
                 "%lu clients connected (%lu slaves), %zu bytes in use",
                 listLength(server.clients)-listLength(server.slaves),
                 listLength(server.slaves),
@@ -1186,7 +1186,7 @@ int serverCron(struct aeEventLoop *eventLoop, long long id, void *clientData) {
             } else if (pid == server.aof_child_pid) {
                 backgroundRewriteDoneHandler(exitcode,bysignal);
             } else {
-                redisLog(REDIS_WARNING,
+                serverLog(REDIS_WARNING,
                     "Warning, detected child with unmatched pid: %ld",
                     (long)pid);
             }
@@ -1208,7 +1208,7 @@ int serverCron(struct aeEventLoop *eventLoop, long long id, void *clientData) {
                  REDIS_BGSAVE_RETRY_DELAY ||
                  server.lastbgsave_status == REDIS_OK))
             {
-                redisLog(REDIS_NOTICE,"%d changes in %d seconds. Saving...",
+                serverLog(REDIS_NOTICE,"%d changes in %d seconds. Saving...",
                     sp->changes, (int)sp->seconds);
                 rdbSaveBackground(server.rdb_filename);
                 break;
@@ -1225,7 +1225,7 @@ int serverCron(struct aeEventLoop *eventLoop, long long id, void *clientData) {
                             server.aof_rewrite_base_size : 1;
             long long growth = (server.aof_current_size*100/base) - 100;
             if (growth >= server.aof_rewrite_perc) {
-                redisLog(REDIS_NOTICE,"Starting automatic rewriting of AOF on %lld%% growth",growth);
+                serverLog(REDIS_NOTICE,"Starting automatic rewriting of AOF on %lld%% growth",growth);
                 rewriteAppendOnlyFileBackground();
             }
          }
@@ -1583,7 +1583,7 @@ void adjustOpenFilesLimit(void) {
     struct rlimit limit;
 
     if (getrlimit(RLIMIT_NOFILE,&limit) == -1) {
-        redisLog(REDIS_WARNING,"Unable to obtain the current NOFILE limit (%s), assuming 1024 and setting the max clients configuration accordingly.",
+        serverLog(REDIS_WARNING,"Unable to obtain the current NOFILE limit (%s), assuming 1024 and setting the max clients configuration accordingly.",
             strerror(errno));
         server.maxclients = 1024-REDIS_MIN_RESERVED_FDS;
     } else {
@@ -1620,28 +1620,28 @@ void adjustOpenFilesLimit(void) {
                 int old_maxclients = server.maxclients;
                 server.maxclients = bestlimit-REDIS_MIN_RESERVED_FDS;
                 if (server.maxclients < 1) {
-                    redisLog(REDIS_WARNING,"Your current 'ulimit -n' "
+                    serverLog(REDIS_WARNING,"Your current 'ulimit -n' "
                         "of %llu is not enough for Redis to start. "
                         "Please increase your open file limit to at least "
                         "%llu. Exiting.",
                         (unsigned long long) oldlimit,
                         (unsigned long long) maxfiles);
                     exit(1);
                 }
-                redisLog(REDIS_WARNING,"You requested maxclients of %d "
+                serverLog(REDIS_WARNING,"You requested maxclients of %d "
                     "requiring at least %llu max file descriptors.",
                     old_maxclients,
                     (unsigned long long) maxfiles);
-                redisLog(REDIS_WARNING,"Redis can't set maximum open files "
+                serverLog(REDIS_WARNING,"Redis can't set maximum open files "
                     "to %llu because of OS error: %s.",
                     (unsigned long long) maxfiles, strerror(setrlimit_error));
-                redisLog(REDIS_WARNING,"Current maximum open files is %llu. "
+                serverLog(REDIS_WARNING,"Current maximum open files is %llu. "
                     "maxclients has been reduced to %d to compensate for "
                     "low ulimit. "
                     "If you need higher maxclients increase 'ulimit -n'.",
                     (unsigned long long) bestlimit, server.maxclients);
             } else {
-                redisLog(REDIS_NOTICE,"Increased maximum number of open files "
+                serverLog(REDIS_NOTICE,"Increased maximum number of open files "
                     "to %llu (it was originally set to %llu).",
                     (unsigned long long) maxfiles,
                     (unsigned long long) oldlimit);
@@ -1660,7 +1660,7 @@ void checkTcpBacklogSettings(void) {
     if (fgets(buf,sizeof(buf),fp) != NULL) {
         int somaxconn = atoi(buf);
         if (somaxconn > 0 && somaxconn < server.tcp_backlog) {
-            redisLog(REDIS_WARNING,"WARNING: The TCP backlog setting of %d cannot be enforced because /proc/sys/net/core/somaxconn is set to the lower value of %d.", server.tcp_backlog, somaxconn);
+            serverLog(REDIS_WARNING,"WARNING: The TCP backlog setting of %d cannot be enforced because /proc/sys/net/core/somaxconn is set to the lower value of %d.", server.tcp_backlog, somaxconn);
         }
     }
     fclose(fp);
@@ -1721,7 +1721,7 @@ int listenToPort(int port, int *fds, int *count) {
                 server.tcp_backlog);
         }
         if (fds[*count] == ANET_ERR) {
-            redisLog(REDIS_WARNING,
+            serverLog(REDIS_WARNING,
                 "Creating Server TCP listening socket %s:%d: %s",
                 server.bindaddr[j] ? server.bindaddr[j] : "*",
                 port, server.neterr);
@@ -1805,15 +1805,15 @@ void initServer(void) {
         server.sofd = anetUnixServer(server.neterr,server.unixsocket,
             server.unixsocketperm, server.tcp_backlog);
         if (server.sofd == ANET_ERR) {
-            redisLog(REDIS_WARNING, "Opening Unix socket: %s", server.neterr);
+            serverLog(REDIS_WARNING, "Opening Unix socket: %s", server.neterr);
             exit(1);
         }
         anetNonBlock(NULL,server.sofd);
     }
 
     /* Abort if there are no listening sockets at all. */
     if (server.ipfd_count == 0 && server.sofd < 0) {
-        redisLog(REDIS_WARNING, "Configured to not listen anywhere, exiting.");
+        serverLog(REDIS_WARNING, "Configured to not listen anywhere, exiting.");
         exit(1);
     }
 
@@ -1879,7 +1879,7 @@ void initServer(void) {
         server.aof_fd = open(server.aof_filename,
                                O_WRONLY|O_APPEND|O_CREAT,0644);
         if (server.aof_fd == -1) {
-            redisLog(REDIS_WARNING, "Can't open the append-only file: %s",
+            serverLog(REDIS_WARNING, "Can't open the append-only file: %s",
                 strerror(errno));
             exit(1);
         }
@@ -1890,7 +1890,7 @@ void initServer(void) {
      * at 3 GB using maxmemory with 'noeviction' policy'. This avoids
      * useless crashes of the Redis instance for out of memory. */
     if (server.arch_bits == 32 && server.maxmemory == 0) {
-        redisLog(REDIS_WARNING,"Warning: 32 bit instance detected but no memory limit set. Setting 3 GB maxmemory limit with 'noeviction' policy now.");
+        serverLog(REDIS_WARNING,"Warning: 32 bit instance detected but no memory limit set. Setting 3 GB maxmemory limit with 'noeviction' policy now.");
         server.maxmemory = 3072LL*(1024*1024); /* 3 GB */
         server.maxmemory_policy = REDIS_MAXMEMORY_NO_EVICTION;
     }
@@ -2372,7 +2372,7 @@ void closeListeningSockets(int unlink_unix_socket) {
     if (server.cluster_enabled)
         for (j = 0; j < server.cfd_count; j++) close(server.cfd[j]);
     if (unlink_unix_socket && server.unixsocket) {
-        redisLog(REDIS_NOTICE,"Removing the unix socket file.");
+        serverLog(REDIS_NOTICE,"Removing the unix socket file.");
         unlink(server.unixsocket); /* don't care if this fails */
     }
 }
@@ -2381,12 +2381,12 @@ int prepareForShutdown(int flags) {
     int save = flags & REDIS_SHUTDOWN_SAVE;
     int nosave = flags & REDIS_SHUTDOWN_NOSAVE;
 
-    redisLog(REDIS_WARNING,"User requested shutdown...");
+    serverLog(REDIS_WARNING,"User requested shutdown...");
     /* Kill the saving child if there is a background saving in progress.
        We want to avoid race conditions, for instance our saving child may
        overwrite the synchronous saving did by SHUTDOWN. */
     if (server.rdb_child_pid != -1) {
-        redisLog(REDIS_WARNING,"There is a child saving an .rdb. Killing it!");
+        serverLog(REDIS_WARNING,"There is a child saving an .rdb. Killing it!");
         kill(server.rdb_child_pid,SIGUSR1);
         rdbRemoveTempFile(server.rdb_child_pid);
     }
@@ -2397,37 +2397,37 @@ int prepareForShutdown(int flags) {
             /* If we have AOF enabled but haven't written the AOF yet, don't
              * shutdown or else the dataset will be lost. */
             if (server.aof_state == REDIS_AOF_WAIT_REWRITE) {
-                redisLog(REDIS_WARNING, "Writing initial AOF, can't exit.");
+                serverLog(REDIS_WARNING, "Writing initial AOF, can't exit.");
                 return REDIS_ERR;
             }
-            redisLog(REDIS_WARNING,
+            serverLog(REDIS_WARNING,
                 "There is a child rewriting the AOF. Killing it!");
             kill(server.aof_child_pid,SIGUSR1);
         }
         /* Append only file: fsync() the AOF and exit */
-        redisLog(REDIS_NOTICE,"Calling fsync() on the AOF file.");
+        serverLog(REDIS_NOTICE,"Calling fsync() on the AOF file.");
         aof_fsync(server.aof_fd);
     }
     if ((server.saveparamslen > 0 && !nosave) || save) {
-        redisLog(REDIS_NOTICE,"Saving the final RDB snapshot before exiting.");
+        serverLog(REDIS_NOTICE,"Saving the final RDB snapshot before exiting.");
         /* Snapshotting. Perform a SYNC SAVE and exit */
         if (rdbSave(server.rdb_filename) != REDIS_OK) {
             /* Ooops.. error saving! The best we can do is to continue
              * operating. Note that if there was a background saving process,
              * in the next cron() Redis will be notified that the background
              * saving aborted, handling special stuff like slaves pending for
              * synchronization... */
-            redisLog(REDIS_WARNING,"Error trying to save the DB, can't exit.");
+            serverLog(REDIS_WARNING,"Error trying to save the DB, can't exit.");
             return REDIS_ERR;
         }
     }
     if (server.daemonize || server.pidfile) {
-        redisLog(REDIS_NOTICE,"Removing the pid file.");
+        serverLog(REDIS_NOTICE,"Removing the pid file.");
         unlink(server.pidfile);
     }
     /* Close the listening sockets. Apparently this allows faster restarts. */
     closeListeningSockets(1);
-    redisLog(REDIS_WARNING,"%s is now ready to exit, bye bye...",
+    serverLog(REDIS_WARNING,"%s is now ready to exit, bye bye...",
         server.sentinel_mode ? "Sentinel" : "Redis");
     return REDIS_OK;
 }
@@ -3444,10 +3444,10 @@ int linuxOvercommitMemoryValue(void) {
 
 void linuxMemoryWarnings(void) {
     if (linuxOvercommitMemoryValue() == 0) {
-        redisLog(REDIS_WARNING,"WARNING overcommit_memory is set to 0! Background save may fail under low memory condition. To fix this issue add 'vm.overcommit_memory = 1' to /etc/sysctl.conf and then reboot or run the command 'sysctl vm.overcommit_memory=1' for this to take effect.");
+        serverLog(REDIS_WARNING,"WARNING overcommit_memory is set to 0! Background save may fail under low memory condition. To fix this issue add 'vm.overcommit_memory = 1' to /etc/sysctl.conf and then reboot or run the command 'sysctl vm.overcommit_memory=1' for this to take effect.");
     }
     if (THPIsEnabled()) {
-        redisLog(REDIS_WARNING,"WARNING you have Transparent Huge Pages (THP) support enabled in your kernel. This will create latency and memory usage issues with Redis. To fix this issue run the command 'echo never > /sys/kernel/mm/transparent_hugepage/enabled' as root, and add it to your /etc/rc.local in order to retain the setting after a reboot. Redis must be restarted after THP is disabled.");
+        serverLog(REDIS_WARNING,"WARNING you have Transparent Huge Pages (THP) support enabled in your kernel. This will create latency and memory usage issues with Redis. To fix this issue run the command 'echo never > /sys/kernel/mm/transparent_hugepage/enabled' as root, and add it to your /etc/rc.local in order to retain the setting after a reboot. Redis must be restarted after THP is disabled.");
     }
 }
 #endif /* __linux__ */
@@ -3520,7 +3520,7 @@ void redisAsciiArt(void) {
     else mode = "standalone";
 
     if (server.syslog_enabled) {
-        redisLog(REDIS_NOTICE,
+        serverLog(REDIS_NOTICE,
             "Redis %s (%s/%d) %s bit, %s mode, port %d, pid %ld ready to start.",
             REDIS_VERSION,
             redisGitSHA1(),
@@ -3538,7 +3538,7 @@ void redisAsciiArt(void) {
             mode, server.port,
             (long) getpid()
         );
-        redisLogRaw(REDIS_NOTICE|REDIS_LOG_RAW,buf);
+        serverLogRaw(REDIS_NOTICE|REDIS_LOG_RAW,buf);
     }
     zfree(buf);
 }
@@ -3562,14 +3562,14 @@ static void sigShutdownHandler(int sig) {
      * the user really wanting to quit ASAP without waiting to persist
      * on disk. */
     if (server.shutdown_asap && sig == SIGINT) {
-        redisLogFromHandler(REDIS_WARNING, "You insist... exiting now.");
+        serverLogFromHandler(REDIS_WARNING, "You insist... exiting now.");
         rdbRemoveTempFile(getpid());
         exit(1); /* Exit with an error since this was not a clean shutdown. */
     } else if (server.loading) {
         exit(0);
     }
 
-    redisLogFromHandler(REDIS_WARNING, msg);
+    serverLogFromHandler(REDIS_WARNING, msg);
     server.shutdown_asap = 1;
 }
 
@@ -3614,20 +3614,20 @@ void loadDataFromDisk(void) {
     long long start = ustime();
     if (server.aof_state == REDIS_AOF_ON) {
         if (loadAppendOnlyFile(server.aof_filename) == REDIS_OK)
-            redisLog(REDIS_NOTICE,"DB loaded from append only file: %.3f seconds",(float)(ustime()-start)/1000000);
+            serverLog(REDIS_NOTICE,"DB loaded from append only file: %.3f seconds",(float)(ustime()-start)/1000000);
     } else {
         if (rdbLoad(server.rdb_filename) == REDIS_OK) {
-            redisLog(REDIS_NOTICE,"DB loaded from disk: %.3f seconds",
+            serverLog(REDIS_NOTICE,"DB loaded from disk: %.3f seconds",
                 (float)(ustime()-start)/1000000);
         } else if (errno != ENOENT) {
-            redisLog(REDIS_WARNING,"Fatal error loading the DB: %s. Exiting.",strerror(errno));
+            serverLog(REDIS_WARNING,"Fatal error loading the DB: %s. Exiting.",strerror(errno));
             exit(1);
         }
     }
 }
 
 void redisOutOfMemoryHandler(size_t allocation_size) {
-    redisLog(REDIS_WARNING,"Out Of Memory allocating %zu bytes!",
+    serverLog(REDIS_WARNING,"Out Of Memory allocating %zu bytes!",
         allocation_size);
     redisPanic("Redis aborting for OUT OF MEMORY");
 }
@@ -3656,12 +3656,12 @@ int redisSupervisedUpstart(void) {
     const char *upstart_job = getenv("UPSTART_JOB");
 
     if (!upstart_job) {
-        redisLog(REDIS_WARNING,
+        serverLog(REDIS_WARNING,
                 "upstart supervision requested, but UPSTART_JOB not found");
         return 0;
     }
 
-    redisLog(REDIS_NOTICE, "supervised by upstart, will stop to signal readyness");
+    serverLog(REDIS_NOTICE, "supervised by upstart, will stop to signal readyness");
     raise(SIGSTOP);
     unsetenv("UPSTART_JOB");
     return 1;
@@ -3676,7 +3676,7 @@ int redisSupervisedSystemd(void) {
     int sendto_flags = 0;
 
     if (!notify_socket) {
-        redisLog(REDIS_WARNING,
+        serverLog(REDIS_WARNING,
                 "systemd supervision requested, but NOTIFY_SOCKET not found");
         return 0;
     }
@@ -3685,9 +3685,9 @@ int redisSupervisedSystemd(void) {
         return 0;
     }
 
-    redisLog(REDIS_NOTICE, "supervised by systemd, will signal readyness");
+    serverLog(REDIS_NOTICE, "supervised by systemd, will signal readyness");
     if ((fd = socket(AF_UNIX, SOCK_DGRAM, 0)) == -1) {
-        redisLog(REDIS_WARNING,
+        serverLog(REDIS_WARNING,
                 "Can't connect to systemd socket %s", notify_socket);
         return 0;
     }
@@ -3716,7 +3716,7 @@ int redisSupervisedSystemd(void) {
     sendto_flags |= MSG_NOSIGNAL;
 #endif
     if (sendmsg(fd, &hdr, sendto_flags) < 0) {
-        redisLog(REDIS_WARNING, "Can't send notification to systemd");
+        serverLog(REDIS_WARNING, "Can't send notification to systemd");
         close(fd);
         return 0;
     }
@@ -3847,9 +3847,9 @@ int main(int argc, char **argv) {
             j++;
         }
         if (server.sentinel_mode && configfile && *configfile == '-') {
-            redisLog(REDIS_WARNING,
+            serverLog(REDIS_WARNING,
                 "Sentinel config from STDIN not allowed.");
-            redisLog(REDIS_WARNING,
+            serverLog(REDIS_WARNING,
                 "Sentinel needs config file on disk to save state.  Exiting...");
             exit(1);
         }
@@ -3858,7 +3858,7 @@ int main(int argc, char **argv) {
         loadServerConfig(configfile,options);
         sdsfree(options);
     } else {
-        redisLog(REDIS_WARNING, "Warning: no config file specified, using the default config. In order to specify a config file use %s /path/to/%s.conf", argv[0], server.sentinel_mode ? "sentinel" : "redis");
+        serverLog(REDIS_WARNING, "Warning: no config file specified, using the default config. In order to specify a config file use %s /path/to/%s.conf", argv[0], server.sentinel_mode ? "sentinel" : "redis");
     }
 
     server.supervised = redisIsSupervised(server.supervised_mode);
@@ -3872,31 +3872,31 @@ int main(int argc, char **argv) {
 
     if (!server.sentinel_mode) {
         /* Things not needed when running in Sentinel mode. */
-        redisLog(REDIS_WARNING,"Server started, Redis version " REDIS_VERSION);
+        serverLog(REDIS_WARNING,"Server started, Redis version " REDIS_VERSION);
     #ifdef __linux__
         linuxMemoryWarnings();
     #endif
         checkTcpBacklogSettings();
         loadDataFromDisk();
         if (server.cluster_enabled) {
             if (verifyClusterConfigWithData() == REDIS_ERR) {
-                redisLog(REDIS_WARNING,
+                serverLog(REDIS_WARNING,
                     "You can't have keys in a DB different than DB 0 when in "
                     "Cluster mode. Exiting.");
                 exit(1);
             }
         }
         if (server.ipfd_count > 0)
-            redisLog(REDIS_NOTICE,"The server is now ready to accept connections on port %d", server.port);
+            serverLog(REDIS_NOTICE,"The server is now ready to accept connections on port %d", server.port);
         if (server.sofd > 0)
-            redisLog(REDIS_NOTICE,"The server is now ready to accept connections at %s", server.unixsocket);
+            serverLog(REDIS_NOTICE,"The server is now ready to accept connections at %s", server.unixsocket);
     } else {
         sentinelIsRunning();
     }
 
     /* Warning the user about suspicious maxmemory setting. */
     if (server.maxmemory > 0 && server.maxmemory < 1024*1024) {
-        redisLog(REDIS_WARNING,"WARNING: You specified a maxmemory value that is less than 1MB (current value is %llu bytes). Are you sure this is what you really want?", server.maxmemory);
+        serverLog(REDIS_WARNING,"WARNING: You specified a maxmemory value that is less than 1MB (current value is %llu bytes). Are you sure this is what you really want?", server.maxmemory);
     }
 
     aeSetBeforeSleepProc(server.el,beforeSleep);