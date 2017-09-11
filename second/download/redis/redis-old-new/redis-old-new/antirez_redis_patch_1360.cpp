@@ -627,6 +627,12 @@ void configSetCommand(redisClient *c) {
     } else if (!strcasecmp(c->argv[2]->ptr,"repl-timeout")) {
         if (getLongLongFromObject(o,&ll) == REDIS_ERR || ll <= 0) goto badfmt;
         server.repl_timeout = ll;
+    } else if (!strcasecmp(c->argv[2]->ptr,"watchdog-period")) {
+        if (getLongLongFromObject(o,&ll) == REDIS_ERR || ll < 0) goto badfmt;
+        if (ll)
+            enableWatchdog(ll);
+        else
+            disableWatchdog();
     } else {
         addReplyErrorFormat(c,"Unsupported CONFIG parameter: %s",
             (char*)c->argv[2]->ptr);
@@ -715,6 +721,7 @@ void configGetCommand(redisClient *c) {
     config_get_numerical_field("repl-ping-slave-period",server.repl_ping_slave_period);
     config_get_numerical_field("repl-timeout",server.repl_timeout);
     config_get_numerical_field("maxclients",server.maxclients);
+    config_get_numerical_field("watchdog-period",server.watchdog_period);
 
     /* Bool (yes/no) values */
     config_get_bool_field("no-appendfsync-on-rewrite",