@@ -514,6 +514,9 @@ void loadServerConfigFromString(char *config) {
         } else if (!strcasecmp(argv[0],"cluster-config-file") && argc == 2) {
             zfree(server.cluster_configfile);
             server.cluster_configfile = zstrdup(argv[1]);
+        } else if (!strcasecmp(argv[0],"cluster-announce-ip") && argc == 2) {
+            zfree(server.cluster_announce_ip);
+            server.cluster_announce_ip = zstrdup(argv[1]);
         } else if (!strcasecmp(argv[0],"cluster-require-full-coverage") &&
                     argc == 2)
         {
@@ -745,6 +748,9 @@ void configSetCommand(client *c) {
     } config_set_special_field("masterauth") {
         zfree(server.masterauth);
         server.masterauth = ((char*)o->ptr)[0] ? zstrdup(o->ptr) : NULL;
+    } config_set_special_field("cluster-announce-ip") {
+        zfree(server.cluster_announce_ip);
+        server.cluster_announce_ip = ((char*)o->ptr)[0] ? zstrdup(o->ptr) : NULL;
     } config_set_special_field("maxclients") {
         int orig_value = server.maxclients;
 
@@ -1067,6 +1073,7 @@ void configGetCommand(client *c) {
     config_get_string_field("dbfilename",server.rdb_filename);
     config_get_string_field("requirepass",server.requirepass);
     config_get_string_field("masterauth",server.masterauth);
+    config_get_string_field("cluster-announce-ip",server.cluster_announce_ip);
     config_get_string_field("unixsocket",server.unixsocket);
     config_get_string_field("logfile",server.logfile);
     config_get_string_field("pidfile",server.pidfile);
@@ -1812,6 +1819,7 @@ int rewriteConfig(char *path) {
     rewriteConfigDirOption(state);
     rewriteConfigSlaveofOption(state);
     rewriteConfigStringOption(state,"masterauth",server.masterauth,NULL);
+    rewriteConfigStringOption(state,"cluster-announce-ip",server.cluster_announce_ip,NULL);
     rewriteConfigYesNoOption(state,"slave-serve-stale-data",server.repl_serve_stale_data,CONFIG_DEFAULT_SLAVE_SERVE_STALE_DATA);
     rewriteConfigYesNoOption(state,"slave-read-only",server.repl_slave_ro,CONFIG_DEFAULT_SLAVE_READ_ONLY);
     rewriteConfigNumericalOption(state,"repl-ping-slave-period",server.repl_ping_slave_period,CONFIG_DEFAULT_REPL_PING_SLAVE_PERIOD);