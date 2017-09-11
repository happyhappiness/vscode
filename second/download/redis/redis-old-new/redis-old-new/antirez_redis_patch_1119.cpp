@@ -125,8 +125,15 @@ void loadServerConfigFromString(char *config) {
             if (server.port < 0 || server.port > 65535) {
                 err = "Invalid port"; goto loaderr;
             }
-        } else if (!strcasecmp(argv[0],"bind") && argc == 2) {
-            server.bindaddr = zstrdup(argv[1]);
+        } else if (!strcasecmp(argv[0],"bind") && argc >= 2) {
+            int j, addresses = argc-1;
+
+            if (addresses > REDIS_BINDADDR_MAX) {
+                err = "Too many bind addresses specified"; goto loaderr;
+            }
+            for (j = 0; j < addresses; j++)
+                server.bindaddr[j] = zstrdup(argv[j+1]);
+            server.bindaddr_count = addresses;
         } else if (!strcasecmp(argv[0],"unixsocket") && argc == 2) {
             server.unixsocket = zstrdup(argv[1]);
         } else if (!strcasecmp(argv[0],"unixsocketperm") && argc == 2) {
@@ -917,7 +924,6 @@ void configGetCommand(redisClient *c) {
     config_get_string_field("dbfilename",server.rdb_filename);
     config_get_string_field("requirepass",server.requirepass);
     config_get_string_field("masterauth",server.masterauth);
-    config_get_string_field("bind",server.bindaddr);
     config_get_string_field("unixsocket",server.unixsocket);
     config_get_string_field("logfile",server.logfile);
     config_get_string_field("pidfile",server.pidfile);
@@ -1104,6 +1110,14 @@ void configGetCommand(redisClient *c) {
         decrRefCount(flagsobj);
         matches++;
     }
+    if (stringmatch(pattern,"bind",0)) {
+        sds aux = sdsjoin(server.bindaddr,server.bindaddr_count," ");
+
+        addReplyBulkCString(c,"bind");
+        addReplyBulkCString(c,aux);
+        sdsfree(aux);
+        matches++;
+    }
     setDeferredMultiBulkLength(c,replylen,matches*2);
 }
 
@@ -1495,6 +1509,25 @@ void rewriteConfigClientoutputbufferlimitOption(struct rewriteConfigState *state
     }
 }
 
+/* Rewrite the bind option. */
+void rewriteConfigBindOption(struct rewriteConfigState *state) {
+    int force = 1;
+    sds line, addresses;
+    char *option = "bind";
+
+    /* Nothing to rewrite if we don't have bind addresses. */
+    if (server.bindaddr_count == 0) return;
+
+    /* Rewrite as bind <addr1> <addr2> ... <addrN> */
+    addresses = sdsjoin(server.bindaddr,server.bindaddr_count," ");
+    line = sdsnew(option);
+    line = sdscatlen(line, " ", 1);
+    line = sdscatsds(line, addresses);
+    sdsfree(addresses);
+
+    rewriteConfigRewriteLine(state,option,line,force);
+}
+
 /* Glue together the configuration lines in the current configuration
  * rewrite state into a single string, stripping multiple empty lines. */
 sds rewriteConfigGetContentFromState(struct rewriteConfigState *state) {
@@ -1630,7 +1663,7 @@ int rewriteConfig(char *path) {
     rewriteConfigYesNoOption(state,"daemonize",server.daemonize,0);
     rewriteConfigStringOption(state,"pidfile",server.pidfile,REDIS_DEFAULT_PID_FILE);
     rewriteConfigNumericalOption(state,"port",server.port,REDIS_SERVERPORT);
-    rewriteConfigStringOption(state,"bind",server.bindaddr,NULL);
+    rewriteConfigBindOption(state);
     rewriteConfigStringOption(state,"unixsocket",server.unixsocket,NULL);
     rewriteConfigOctalOption(state,"unixsocketperm",server.unixsocketperm,REDIS_DEFAULT_UNIX_SOCKET_PERM);
     rewriteConfigNumericalOption(state,"timeout",server.maxidletime,REDIS_MAXIDLETIME);