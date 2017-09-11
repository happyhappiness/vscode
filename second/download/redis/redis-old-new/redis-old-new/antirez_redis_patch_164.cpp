@@ -633,6 +633,16 @@ void loadServerConfigFromString(char *config) {
             }
         } else if (!strcasecmp(argv[0],"slave-priority") && argc == 2) {
             server.slave_priority = atoi(argv[1]);
+        } else if (!strcasecmp(argv[0],"slave-announce-ip") && argc == 2) {
+            zfree(server.slave_announce_ip);
+            server.slave_announce_ip = zstrdup(argv[1]);
+        } else if (!strcasecmp(argv[0],"slave-announce-port") && argc == 2) {
+            server.slave_announce_port = atoi(argv[1]);
+            if (server.slave_announce_port < 0 ||
+                server.slave_announce_port > 65535)
+            {
+                err = "Invalid port"; goto loaderr;
+            }
         } else if (!strcasecmp(argv[0],"min-slaves-to-write") && argc == 2) {
             server.repl_min_slaves_to_write = atoi(argv[1]);
             if (server.repl_min_slaves_to_write < 0) {
@@ -925,6 +935,9 @@ void configSetCommand(client *c) {
 
         if (flags == -1) goto badfmt;
         server.notify_keyspace_events = flags;
+    } config_set_special_field("slave-announce-ip") {
+        zfree(server.slave_announce_ip);
+        server.slave_announce_ip = ((char*)o->ptr)[0] ? zstrdup(o->ptr) : NULL;
 
     /* Boolean fields.
      * config_set_bool_field(name,var). */
@@ -1014,6 +1027,8 @@ void configSetCommand(client *c) {
     } config_set_numerical_field(
       "slave-priority",server.slave_priority,0,LLONG_MAX) {
     } config_set_numerical_field(
+      "slave-announce-port",server.slave_announce_port,0,65535) {
+    } config_set_numerical_field(
       "min-slaves-to-write",server.repl_min_slaves_to_write,0,LLONG_MAX) {
         refreshGoodSlavesCount();
     } config_set_numerical_field(
@@ -1133,6 +1148,7 @@ void configGetCommand(client *c) {
     config_get_string_field("unixsocket",server.unixsocket);
     config_get_string_field("logfile",server.logfile);
     config_get_string_field("pidfile",server.pidfile);
+    config_get_string_field("slave-announce-ip",server.slave_announce_ip);
 
     /* Numerical values */
     config_get_numerical_field("maxmemory",server.maxmemory);
@@ -1177,6 +1193,7 @@ void configGetCommand(client *c) {
     config_get_numerical_field("maxclients",server.maxclients);
     config_get_numerical_field("watchdog-period",server.watchdog_period);
     config_get_numerical_field("slave-priority",server.slave_priority);
+    config_get_numerical_field("slave-announce-port",server.slave_announce_port);
     config_get_numerical_field("min-slaves-to-write",server.repl_min_slaves_to_write);
     config_get_numerical_field("min-slaves-max-lag",server.repl_min_slaves_max_lag);
     config_get_numerical_field("hz",server.hz);
@@ -1865,6 +1882,7 @@ int rewriteConfig(char *path) {
     rewriteConfigOctalOption(state,"unixsocketperm",server.unixsocketperm,CONFIG_DEFAULT_UNIX_SOCKET_PERM);
     rewriteConfigNumericalOption(state,"timeout",server.maxidletime,CONFIG_DEFAULT_CLIENT_TIMEOUT);
     rewriteConfigNumericalOption(state,"tcp-keepalive",server.tcpkeepalive,CONFIG_DEFAULT_TCP_KEEPALIVE);
+    rewriteConfigNumericalOption(state,"slave-announce-port",server.slave_announce_port,CONFIG_DEFAULT_SLAVE_ANNOUNCE_PORT);
     rewriteConfigEnumOption(state,"loglevel",server.verbosity,loglevel_enum,CONFIG_DEFAULT_VERBOSITY);
     rewriteConfigStringOption(state,"logfile",server.logfile,CONFIG_DEFAULT_LOGFILE);
     rewriteConfigYesNoOption(state,"syslog-enabled",server.syslog_enabled,CONFIG_DEFAULT_SYSLOG_ENABLED);
@@ -1878,6 +1896,7 @@ int rewriteConfig(char *path) {
     rewriteConfigStringOption(state,"dbfilename",server.rdb_filename,CONFIG_DEFAULT_RDB_FILENAME);
     rewriteConfigDirOption(state);
     rewriteConfigSlaveofOption(state);
+    rewriteConfigStringOption(state,"slave-announce-ip",server.slave_announce_ip,CONFIG_DEFAULT_SLAVE_ANNOUNCE_IP);
     rewriteConfigStringOption(state,"masterauth",server.masterauth,NULL);
     rewriteConfigStringOption(state,"cluster-announce-ip",server.cluster_announce_ip,NULL);
     rewriteConfigYesNoOption(state,"slave-serve-stale-data",server.repl_serve_stale_data,CONFIG_DEFAULT_SLAVE_SERVE_STALE_DATA);