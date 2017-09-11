@@ -677,7 +677,7 @@ void loadServerConfig(char *filename, char *options) {
 
 #define config_set_numerical_field(_name,_var,min,max) \
     } else if (!strcasecmp(c->argv[2]->ptr,_name)) { \
-        if (getLongLongFromObject(o,&ll) == REDIS_ERR || ll < 0) goto badfmt; \
+        if (getLongLongFromObject(o,&ll) == C_ERR || ll < 0) goto badfmt; \
         if (min != LLONG_MIN && ll < min) goto badfmt; \
         if (max != LLONG_MAX && ll > max) goto badfmt; \
         _var = ll;
@@ -727,7 +727,7 @@ void configSetCommand(client *c) {
     } config_set_special_field("maxclients") {
         int orig_value = server.maxclients;
 
-        if (getLongLongFromObject(o,&ll) == REDIS_ERR || ll < 1) goto badfmt;
+        if (getLongLongFromObject(o,&ll) == C_ERR || ll < 1) goto badfmt;
 
         /* Try to check if the OS is capable of supporting so many FDs. */
         server.maxclients = ll;
@@ -757,7 +757,7 @@ void configSetCommand(client *c) {
         if (enable == 0 && server.aof_state != REDIS_AOF_OFF) {
             stopAppendOnly();
         } else if (enable && server.aof_state == REDIS_AOF_OFF) {
-            if (startAppendOnly() == REDIS_ERR) {
+            if (startAppendOnly() == C_ERR) {
                 addReplyError(c,
                     "Unable to turn on AOF. Check server logs.");
                 return;