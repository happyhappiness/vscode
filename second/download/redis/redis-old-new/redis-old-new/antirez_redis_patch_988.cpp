@@ -127,6 +127,11 @@ void loadServerConfigFromString(char *config) {
             if (server.port < 0 || server.port > 65535) {
                 err = "Invalid port"; goto loaderr;
             }
+        } else if (!strcasecmp(argv[0],"backlog") && argc == 2) {
+            server.backlog = atoi(argv[1]);
+            if (server.backlog < 0) {
+                err = "Invalid backlog value"; goto loaderr;
+            }
         } else if (!strcasecmp(argv[0],"bind") && argc >= 2) {
             int j, addresses = argc-1;
 
@@ -975,6 +980,7 @@ void configGetCommand(redisClient *c) {
     config_get_numerical_field("slowlog-max-len",
             server.slowlog_max_len);
     config_get_numerical_field("port",server.port);
+    config_get_numerical_field("backlog",server.backlog);
     config_get_numerical_field("databases",server.dbnum);
     config_get_numerical_field("repl-ping-slave-period",server.repl_ping_slave_period);
     config_get_numerical_field("repl-timeout",server.repl_timeout);
@@ -1695,6 +1701,7 @@ int rewriteConfig(char *path) {
     rewriteConfigYesNoOption(state,"daemonize",server.daemonize,0);
     rewriteConfigStringOption(state,"pidfile",server.pidfile,REDIS_DEFAULT_PID_FILE);
     rewriteConfigNumericalOption(state,"port",server.port,REDIS_SERVERPORT);
+    rewriteConfigNumericalOption(state,"backlog",server.backlog,REDIS_BACKLOG);
     rewriteConfigBindOption(state);
     rewriteConfigStringOption(state,"unixsocket",server.unixsocket,NULL);
     rewriteConfigOctalOption(state,"unixsocketperm",server.unixsocketperm,REDIS_DEFAULT_UNIX_SOCKET_PERM);