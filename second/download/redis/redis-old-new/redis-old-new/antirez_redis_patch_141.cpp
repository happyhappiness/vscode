@@ -1345,6 +1345,7 @@ void initServerConfig(void) {
     server.aof_flush_postponed_start = 0;
     server.aof_rewrite_incremental_fsync = CONFIG_DEFAULT_AOF_REWRITE_INCREMENTAL_FSYNC;
     server.aof_load_truncated = CONFIG_DEFAULT_AOF_LOAD_TRUNCATED;
+    server.aof_use_rdb_preamble = CONFIG_DEFAULT_AOF_USE_RDB_PREAMBLE;
     server.pidfile = NULL;
     server.rdb_filename = zstrdup(CONFIG_DEFAULT_RDB_FILENAME);
     server.aof_filename = zstrdup(CONFIG_DEFAULT_AOF_FILENAME);
@@ -1636,26 +1637,35 @@ int listenToPort(int port, int *fds, int *count) {
     if (server.bindaddr_count == 0) server.bindaddr[0] = NULL;
     for (j = 0; j < server.bindaddr_count || j == 0; j++) {
         if (server.bindaddr[j] == NULL) {
+            int unsupported = 0;
             /* Bind * for both IPv6 and IPv4, we enter here only if
              * server.bindaddr_count == 0. */
             fds[*count] = anetTcp6Server(server.neterr,port,NULL,
                 server.tcp_backlog);
             if (fds[*count] != ANET_ERR) {
                 anetNonBlock(NULL,fds[*count]);
                 (*count)++;
+            } else if (errno == EAFNOSUPPORT) {
+                unsupported++;
+                serverLog(LL_WARNING,"Not listening to IPv6: unsupproted");
+            }
 
+            if (*count == 1 || unsupported) {
                 /* Bind the IPv4 address as well. */
                 fds[*count] = anetTcpServer(server.neterr,port,NULL,
                     server.tcp_backlog);
                 if (fds[*count] != ANET_ERR) {
                     anetNonBlock(NULL,fds[*count]);
                     (*count)++;
+                } else if (errno == EAFNOSUPPORT) {
+                    unsupported++;
+                    serverLog(LL_WARNING,"Not listening to IPv4: unsupproted");
                 }
             }
             /* Exit the loop if we were able to bind * on IPv4 and IPv6,
              * otherwise fds[*count] will be ANET_ERR and we'll print an
              * error and return to the caller with an error. */
-            if (*count == 2) break;
+            if (*count + unsupported == 2) break;
         } else if (strchr(server.bindaddr[j],':')) {
             /* Bind IPv6 address. */
             fds[*count] = anetTcp6Server(server.neterr,port,server.bindaddr[j],