@@ -354,6 +354,8 @@ void loadServerConfigFromString(char *config) {
             if ((server.stop_writes_on_bgsave_err = yesnotoi(argv[1])) == -1) {
                 err = "argument must be 'yes' or 'no'"; goto loaderr;
             }
+        } else if (!strcasecmp(argv[0],"slave-priority") && argc == 2) {
+            server.slave_priority = atoi(argv[1]);
         } else if (!strcasecmp(argv[0],"sentinel")) {
             /* argc == 1 is handled by main() as we need to enter the sentinel
              * mode ASAP. */
@@ -666,6 +668,10 @@ void configSetCommand(redisClient *c) {
 
         if (yn == -1) goto badfmt;
         server.rdb_checksum = yn;
+    } else if (!strcasecmp(c->argv[2]->ptr,"slave-priority")) {
+        if (getLongLongFromObject(o,&ll) == REDIS_ERR ||
+            ll <= 0) goto badfmt;
+        server.slave_priority = ll;
     } else {
         addReplyErrorFormat(c,"Unsupported CONFIG parameter: %s",
             (char*)c->argv[2]->ptr);
@@ -755,6 +761,7 @@ void configGetCommand(redisClient *c) {
     config_get_numerical_field("repl-timeout",server.repl_timeout);
     config_get_numerical_field("maxclients",server.maxclients);
     config_get_numerical_field("watchdog-period",server.watchdog_period);
+    config_get_numerical_field("slave-priority",server.slave_priority);
 
     /* Bool (yes/no) values */
     config_get_bool_field("no-appendfsync-on-rewrite",