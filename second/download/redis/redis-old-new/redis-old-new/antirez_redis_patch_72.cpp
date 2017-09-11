@@ -688,10 +688,6 @@ void loadServerConfigFromString(char *config) {
                 err = sentinelHandleConfiguration(argv+1,argc-1);
                 if (err) goto loaderr;
             }
-        } else if (!strcasecmp(argv[0],"hll-use-loglogbeta") && argc == 2) {
-            if ((server.hll_use_loglogbeta = yesnotoi(argv[1])) == -1) {
-                err = "argument must be 'yes' or 'no'"; goto loaderr;
-            }
         } else {
             err = "Bad directive or wrong number of arguments"; goto loaderr;
         }
@@ -984,9 +980,7 @@ void configSetCommand(client *c) {
     } config_set_bool_field(
       "slave-lazy-flush",server.repl_slave_lazy_flush) {
     } config_set_bool_field(
-      "no-appendfsync-on-rewrite",server.aof_no_fsync_on_rewrite) { 
-    } config_set_bool_field(
-      "hll-use-loglogbeta",server.hll_use_loglogbeta) {
+      "no-appendfsync-on-rewrite",server.aof_no_fsync_on_rewrite) {
 
     /* Numerical fields.
      * config_set_numerical_field(name,var,min,max) */
@@ -1251,8 +1245,6 @@ void configGetCommand(client *c) {
             server.lazyfree_lazy_server_del);
     config_get_bool_field("slave-lazy-flush",
             server.repl_slave_lazy_flush);
-    config_get_bool_field("hll-use-loglogbeta",
-            server.hll_use_loglogbeta);
 
     /* Enum values */
     config_get_enum_field("maxmemory-policy",
@@ -1971,7 +1963,6 @@ int rewriteConfig(char *path) {
     rewriteConfigYesNoOption(state,"lazyfree-lazy-expire",server.lazyfree_lazy_expire,CONFIG_DEFAULT_LAZYFREE_LAZY_EXPIRE);
     rewriteConfigYesNoOption(state,"lazyfree-lazy-server-del",server.lazyfree_lazy_server_del,CONFIG_DEFAULT_LAZYFREE_LAZY_SERVER_DEL);
     rewriteConfigYesNoOption(state,"slave-lazy-flush",server.repl_slave_lazy_flush,CONFIG_DEFAULT_SLAVE_LAZY_FLUSH);
-    rewriteConfigYesNoOption(state,"hll-use-loglogbeta",server.hll_use_loglogbeta,CONFIG_DEFAULT_HLL_USE_LOGLOGBETA);
 
     /* Rewrite Sentinel config if in Sentinel mode. */
     if (server.sentinel_mode) rewriteConfigSentinelOption(state);