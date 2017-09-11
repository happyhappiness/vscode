@@ -1571,7 +1571,7 @@ int rewriteConfig(char *path) {
     rewriteConfigYesNoOption(state,"daemonize",server.daemonize,0);
     rewriteConfigStringOption(state,"pidfile",server.pidfile,REDIS_DEFAULT_PID_FILE);
     rewriteConfigNumericalOption(state,"port",server.port,REDIS_SERVERPORT);
-    rewriteConfigStringOption(state,"bindaddr",server.bindaddr,NULL);
+    rewriteConfigStringOption(state,"bind",server.bindaddr,NULL);
     rewriteConfigStringOption(state,"unixsocket",server.unixsocket,NULL);
     rewriteConfigOctalOption(state,"unixsocketperm",server.unixsocketperm,REDIS_DEFAULT_UNIX_SOCKET_PERM);
     rewriteConfigNumericalOption(state,"timeout",server.maxidletime,REDIS_MAXIDLETIME);