@@ -514,6 +514,25 @@ void loadServerConfigFromString(char *config) {
         } else if (!strcasecmp(argv[0],"cluster-config-file") && argc == 2) {
             zfree(server.cluster_configfile);
             server.cluster_configfile = zstrdup(argv[1]);
+        } else if (!strcasecmp(argv[0],"cluster-announce-ip") && argc == 2) {
+            zfree(server.cluster_announce_ip);
+            server.cluster_announce_ip = zstrdup(argv[1]);
+        } else if (!strcasecmp(argv[0],"cluster-announce-port") && argc == 2) {
+            server.cluster_announce_port = atoi(argv[1]);
+            if (server.cluster_announce_port < 0 ||
+                server.cluster_announce_port > 65535)
+            {
+                err = "Invalid port"; goto loaderr;
+            }
+        } else if (!strcasecmp(argv[0],"cluster-announce-bus-port") &&
+                   argc == 2)
+        {
+            server.cluster_announce_bus_port = atoi(argv[1]);
+            if (server.cluster_announce_bus_port < 0 ||
+                server.cluster_announce_bus_port > 65535)
+            {
+                err = "Invalid port"; goto loaderr;
+            }
         } else if (!strcasecmp(argv[0],"cluster-require-full-coverage") &&
                     argc == 2)
         {
@@ -745,6 +764,9 @@ void configSetCommand(client *c) {
     } config_set_special_field("masterauth") {
         zfree(server.masterauth);
         server.masterauth = ((char*)o->ptr)[0] ? zstrdup(o->ptr) : NULL;
+    } config_set_special_field("cluster-announce-ip") {
+        zfree(server.cluster_announce_ip);
+        server.cluster_announce_ip = ((char*)o->ptr)[0] ? zstrdup(o->ptr) : NULL;
     } config_set_special_field("maxclients") {
         int orig_value = server.maxclients;
 
@@ -964,6 +986,10 @@ void configSetCommand(client *c) {
     } config_set_numerical_field(
       "cluster-node-timeout",server.cluster_node_timeout,0,LLONG_MAX) {
     } config_set_numerical_field(
+      "cluster-announce-port",server.cluster_announce_port,0,65535) {
+    } config_set_numerical_field(
+      "cluster-announce-bus-port",server.cluster_announce_bus_port,0,65535) {
+    } config_set_numerical_field(
       "cluster-migration-barrier",server.cluster_migration_barrier,0,LLONG_MAX){
     } config_set_numerical_field(
       "cluster-slave-validity-factor",server.cluster_slave_validity_factor,0,LLONG_MAX) {
@@ -1067,6 +1093,7 @@ void configGetCommand(client *c) {
     config_get_string_field("dbfilename",server.rdb_filename);
     config_get_string_field("requirepass",server.requirepass);
     config_get_string_field("masterauth",server.masterauth);
+    config_get_string_field("cluster-announce-ip",server.cluster_announce_ip);
     config_get_string_field("unixsocket",server.unixsocket);
     config_get_string_field("logfile",server.logfile);
     config_get_string_field("pidfile",server.pidfile);
@@ -1103,6 +1130,8 @@ void configGetCommand(client *c) {
     config_get_numerical_field("slowlog-max-len",
             server.slowlog_max_len);
     config_get_numerical_field("port",server.port);
+    config_get_numerical_field("cluster-announce-port",server.cluster_announce_port);
+    config_get_numerical_field("cluster-announce-bus-port",server.cluster_announce_bus_port);
     config_get_numerical_field("tcp-backlog",server.tcp_backlog);
     config_get_numerical_field("databases",server.dbnum);
     config_get_numerical_field("repl-ping-slave-period",server.repl_ping_slave_period);
@@ -1792,6 +1821,8 @@ int rewriteConfig(char *path) {
     rewriteConfigYesNoOption(state,"daemonize",server.daemonize,0);
     rewriteConfigStringOption(state,"pidfile",server.pidfile,CONFIG_DEFAULT_PID_FILE);
     rewriteConfigNumericalOption(state,"port",server.port,CONFIG_DEFAULT_SERVER_PORT);
+    rewriteConfigNumericalOption(state,"cluster-announce-port",server.cluster_announce_port,CONFIG_DEFAULT_CLUSTER_ANNOUNCE_PORT);
+    rewriteConfigNumericalOption(state,"cluster-announce-bus-port",server.cluster_announce_bus_port,CONFIG_DEFAULT_CLUSTER_ANNOUNCE_BUS_PORT);
     rewriteConfigNumericalOption(state,"tcp-backlog",server.tcp_backlog,CONFIG_DEFAULT_TCP_BACKLOG);
     rewriteConfigBindOption(state);
     rewriteConfigStringOption(state,"unixsocket",server.unixsocket,NULL);
@@ -1812,6 +1843,7 @@ int rewriteConfig(char *path) {
     rewriteConfigDirOption(state);
     rewriteConfigSlaveofOption(state);
     rewriteConfigStringOption(state,"masterauth",server.masterauth,NULL);
+    rewriteConfigStringOption(state,"cluster-announce-ip",server.cluster_announce_ip,NULL);
     rewriteConfigYesNoOption(state,"slave-serve-stale-data",server.repl_serve_stale_data,CONFIG_DEFAULT_SLAVE_SERVE_STALE_DATA);
     rewriteConfigYesNoOption(state,"slave-read-only",server.repl_slave_ro,CONFIG_DEFAULT_SLAVE_READ_ONLY);
     rewriteConfigNumericalOption(state,"repl-ping-slave-period",server.repl_ping_slave_period,CONFIG_DEFAULT_REPL_PING_SLAVE_PERIOD);