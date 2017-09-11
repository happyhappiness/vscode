@@ -60,6 +60,8 @@ clientBufferLimitsConfig clientBufferLimitsDefaults[REDIS_CLIENT_TYPE_COUNT] = {
  * Config file parsing
  *----------------------------------------------------------------------------*/
 
+int supervisedToMode(const char *str);
+
 int yesnotoi(char *s) {
     if (!strcasecmp(s,"yes")) return 1;
     else if (!strcasecmp(s,"no")) return 0;
@@ -533,6 +535,15 @@ void loadServerConfigFromString(char *config) {
                 goto loaderr;
             }
             server.notify_keyspace_events = flags;
+        } else if (!strcasecmp(argv[0],"supervised") && argc == 2) {
+            int mode = supervisedToMode(argv[1]);
+
+            if (mode == -1) {
+                err = "Invalid option for 'supervised'. "
+                    "Allowed values: 'upstart', 'systemd', 'auto', or 'no'";
+                goto loaderr;
+            }
+            server.supervised_mode = mode;
         } else if (!strcasecmp(argv[0],"sentinel")) {
             /* argc == 1 is handled by main() as we need to enter the sentinel
              * mode ASAP. */
@@ -1022,6 +1033,33 @@ char *maxmemoryToString() {
     return s;
 }
 
+int supervisedToMode(const char *str) {
+    int mode;
+    if (!strcasecmp(str,"upstart")) {
+        mode = REDIS_SUPERVISED_UPSTART;
+    } else if (!strcasecmp(str,"systemd")) {
+        mode = REDIS_SUPERVISED_SYSTEMD;
+    } else if (!strcasecmp(str,"auto")) {
+        mode = REDIS_SUPERVISED_AUTODETECT;
+    } else if (!strcasecmp(str,"no")) {
+        mode = REDIS_SUPERVISED_NONE;
+    } else {
+        mode = -1;
+    }
+    return mode;
+}
+
+char *supervisedToString(void) {
+    char *s;
+    switch(server.supervised_mode) {
+    case REDIS_SUPERVISED_UPSTART: s = "upstart"; break;
+    case REDIS_SUPERVISED_SYSTEMD: s = "systemd"; break;
+    case REDIS_SUPERVISED_AUTODETECT: s = "auto"; break;
+    case REDIS_SUPERVISED_NONE: s = "no"; break;
+    default: s = "no"; break;
+    }
+    return s;
+}
 void configGetCommand(redisClient *c) {
     robj *o = c->argv[2];
     void *replylen = addDeferredMultiBulkLength(c);
@@ -1177,6 +1215,11 @@ void configGetCommand(redisClient *c) {
         addReplyBulkCString(c,s);
         matches++;
     }
+    if (stringmatch(pattern,"supervised",0)) {
+        addReplyBulkCString(c,"supervised");
+        addReplyBulkCString(c,supervisedToString());
+        matches++;
+    }
     if (stringmatch(pattern,"client-output-buffer-limit",0)) {
         sds buf = sdsempty();
         int j;
@@ -1872,6 +1915,12 @@ int rewriteConfig(char *path) {
     rewriteConfigNumericalOption(state,"hz",server.hz,REDIS_DEFAULT_HZ);
     rewriteConfigYesNoOption(state,"aof-rewrite-incremental-fsync",server.aof_rewrite_incremental_fsync,REDIS_DEFAULT_AOF_REWRITE_INCREMENTAL_FSYNC);
     rewriteConfigYesNoOption(state,"aof-load-truncated",server.aof_load_truncated,REDIS_DEFAULT_AOF_LOAD_TRUNCATED);
+    rewriteConfigEnumOption(state,"supervised",server.supervised_mode,
+        "upstart", REDIS_SUPERVISED_UPSTART,
+        "systemd", REDIS_SUPERVISED_SYSTEMD,
+        "auto", REDIS_SUPERVISED_AUTODETECT,
+        "no", REDIS_SUPERVISED_NONE,
+        NULL, REDIS_SUPERVISED_NONE);
     if (server.sentinel_mode) rewriteConfigSentinelOption(state);
 
     /* Step 3: remove all the orphaned lines in the old file, that is, lines