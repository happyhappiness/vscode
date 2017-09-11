@@ -1067,23 +1067,23 @@ void configSetCommand(client *c) {
  *----------------------------------------------------------------------------*/
 
 #define config_get_string_field(_name,_var) do { \
-    if (stringmatch(pattern,_name,0)) { \
+    if (stringmatch(pattern,_name,1)) { \
         addReplyBulkCString(c,_name); \
         addReplyBulkCString(c,_var ? _var : ""); \
         matches++; \
     } \
 } while(0);
 
 #define config_get_bool_field(_name,_var) do { \
-    if (stringmatch(pattern,_name,0)) { \
+    if (stringmatch(pattern,_name,1)) { \
         addReplyBulkCString(c,_name); \
         addReplyBulkCString(c,_var ? "yes" : "no"); \
         matches++; \
     } \
 } while(0);
 
 #define config_get_numerical_field(_name,_var) do { \
-    if (stringmatch(pattern,_name,0)) { \
+    if (stringmatch(pattern,_name,1)) { \
         ll2string(buf,sizeof(buf),_var); \
         addReplyBulkCString(c,_name); \
         addReplyBulkCString(c,buf); \
@@ -1092,7 +1092,7 @@ void configSetCommand(client *c) {
 } while(0);
 
 #define config_get_enum_field(_name,_var,_enumvar) do { \
-    if (stringmatch(pattern,_name,0)) { \
+    if (stringmatch(pattern,_name,1)) { \
         addReplyBulkCString(c,_name); \
         addReplyBulkCString(c,configEnumGetNameOrUnknown(_enumvar,_var)); \
         matches++; \
@@ -1215,12 +1215,12 @@ void configGetCommand(client *c) {
 
     /* Everything we can't handle with macros follows. */
 
-    if (stringmatch(pattern,"appendonly",0)) {
+    if (stringmatch(pattern,"appendonly",1)) {
         addReplyBulkCString(c,"appendonly");
         addReplyBulkCString(c,server.aof_state == AOF_OFF ? "no" : "yes");
         matches++;
     }
-    if (stringmatch(pattern,"dir",0)) {
+    if (stringmatch(pattern,"dir",1)) {
         char buf[1024];
 
         if (getcwd(buf,sizeof(buf)) == NULL)
@@ -1230,7 +1230,7 @@ void configGetCommand(client *c) {
         addReplyBulkCString(c,buf);
         matches++;
     }
-    if (stringmatch(pattern,"save",0)) {
+    if (stringmatch(pattern,"save",1)) {
         sds buf = sdsempty();
         int j;
 
@@ -1246,7 +1246,7 @@ void configGetCommand(client *c) {
         sdsfree(buf);
         matches++;
     }
-    if (stringmatch(pattern,"client-output-buffer-limit",0)) {
+    if (stringmatch(pattern,"client-output-buffer-limit",1)) {
         sds buf = sdsempty();
         int j;
 
@@ -1264,14 +1264,14 @@ void configGetCommand(client *c) {
         sdsfree(buf);
         matches++;
     }
-    if (stringmatch(pattern,"unixsocketperm",0)) {
+    if (stringmatch(pattern,"unixsocketperm",1)) {
         char buf[32];
         snprintf(buf,sizeof(buf),"%o",server.unixsocketperm);
         addReplyBulkCString(c,"unixsocketperm");
         addReplyBulkCString(c,buf);
         matches++;
     }
-    if (stringmatch(pattern,"slaveof",0)) {
+    if (stringmatch(pattern,"slaveof",1)) {
         char buf[256];
 
         addReplyBulkCString(c,"slaveof");
@@ -1283,7 +1283,7 @@ void configGetCommand(client *c) {
         addReplyBulkCString(c,buf);
         matches++;
     }
-    if (stringmatch(pattern,"notify-keyspace-events",0)) {
+    if (stringmatch(pattern,"notify-keyspace-events",1)) {
         robj *flagsobj = createObject(OBJ_STRING,
             keyspaceEventsFlagsToString(server.notify_keyspace_events));
 
@@ -1292,7 +1292,7 @@ void configGetCommand(client *c) {
         decrRefCount(flagsobj);
         matches++;
     }
-    if (stringmatch(pattern,"bind",0)) {
+    if (stringmatch(pattern,"bind",1)) {
         sds aux = sdsjoin(server.bindaddr,server.bindaddr_count," ");
 
         addReplyBulkCString(c,"bind");