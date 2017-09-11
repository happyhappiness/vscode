@@ -34,10 +34,26 @@
 #include <fcntl.h>
 #include <sys/stat.h>
 
-static struct {
-    const char     *name;
-    const int       value;
-} validSyslogFacilities[] = {
+/*-----------------------------------------------------------------------------
+ * Config file name-value maps.
+ *----------------------------------------------------------------------------*/
+
+typedef struct configEnum {
+    const char *name;
+    const int val;
+} configEnum;
+
+configEnum maxmemory_policy_enum[] = {
+    {"volatile-lru", REDIS_MAXMEMORY_VOLATILE_LRU},
+    {"volatile-random",REDIS_MAXMEMORY_VOLATILE_RANDOM},
+    {"volatile-ttl",REDIS_MAXMEMORY_VOLATILE_TTL},
+    {"allkeys-lru",REDIS_MAXMEMORY_ALLKEYS_LRU},
+    {"allkeys-random",REDIS_MAXMEMORY_ALLKEYS_RANDOM},
+    {"noeviction",REDIS_MAXMEMORY_NO_EVICTION},
+    {NULL, 0}
+};
+
+configEnum syslog_facility_enum[] = {
     {"user",    LOG_USER},
     {"local0",  LOG_LOCAL0},
     {"local1",  LOG_LOCAL1},
@@ -50,13 +66,48 @@ static struct {
     {NULL, 0}
 };
 
+/* Output buffer limits presets. */
 clientBufferLimitsConfig clientBufferLimitsDefaults[REDIS_CLIENT_TYPE_COUNT] = {
     {0, 0, 0}, /* normal */
     {1024*1024*256, 1024*1024*64, 60}, /* slave */
     {1024*1024*32, 1024*1024*8, 60}  /* pubsub */
 };
 
 /*-----------------------------------------------------------------------------
+ * Enum access functions
+ *----------------------------------------------------------------------------*/
+
+/* Get enum value from name. If there is no match INT_MIN is returned. */
+int configEnumGetValue(configEnum *ce, char *name) {
+    while(ce->name != NULL) {
+        if (!strcasecmp(ce->name,name)) return ce->val;
+        ce++;
+    }
+    return INT_MIN;
+}
+
+/* Get enum name from value. If no match is found NULL is returned. */
+const char *configEnumGetName(configEnum *ce, int val) {
+    while(ce->name != NULL) {
+        if (ce->val == val) return ce->name;
+        ce++;
+    }
+    return NULL;
+}
+
+/* Wrapper for configEnumGetName() returning "unknown" insetad of NULL if
+ * there is no match. */
+const char *configEnumGetNameOrUnknown(configEnum *ce, int val) {
+    const char *name = configEnumGetName(ce,val);
+    return name ? name : "unknown";
+}
+
+/* Used for INFO generation. */
+const char *maxmemoryToString(void) {
+    return configEnumGetNameOrUnknown(maxmemory_policy_enum,server.maxmemory);
+}
+
+/*-----------------------------------------------------------------------------
  * Config file parsing
  *----------------------------------------------------------------------------*/
 
@@ -201,16 +252,9 @@ void loadServerConfigFromString(char *config) {
             if (server.syslog_ident) zfree(server.syslog_ident);
             server.syslog_ident = zstrdup(argv[1]);
         } else if (!strcasecmp(argv[0],"syslog-facility") && argc == 2) {
-            int i;
-
-            for (i = 0; validSyslogFacilities[i].name; i++) {
-                if (!strcasecmp(validSyslogFacilities[i].name, argv[1])) {
-                    server.syslog_facility = validSyslogFacilities[i].value;
-                    break;
-                }
-            }
-
-            if (!validSyslogFacilities[i].name) {
+            server.syslog_facility =
+                configEnumGetValue(syslog_facility_enum,argv[1]);
+            if (server.syslog_facility == INT_MIN) {
                 err = "Invalid log facility. Must be one of USER or between LOCAL0-LOCAL7";
                 goto loaderr;
             }
@@ -229,19 +273,9 @@ void loadServerConfigFromString(char *config) {
         } else if (!strcasecmp(argv[0],"maxmemory") && argc == 2) {
             server.maxmemory = memtoll(argv[1],NULL);
         } else if (!strcasecmp(argv[0],"maxmemory-policy") && argc == 2) {
-            if (!strcasecmp(argv[1],"volatile-lru")) {
-                server.maxmemory_policy = REDIS_MAXMEMORY_VOLATILE_LRU;
-            } else if (!strcasecmp(argv[1],"volatile-random")) {
-                server.maxmemory_policy = REDIS_MAXMEMORY_VOLATILE_RANDOM;
-            } else if (!strcasecmp(argv[1],"volatile-ttl")) {
-                server.maxmemory_policy = REDIS_MAXMEMORY_VOLATILE_TTL;
-            } else if (!strcasecmp(argv[1],"allkeys-lru")) {
-                server.maxmemory_policy = REDIS_MAXMEMORY_ALLKEYS_LRU;
-            } else if (!strcasecmp(argv[1],"allkeys-random")) {
-                server.maxmemory_policy = REDIS_MAXMEMORY_ALLKEYS_RANDOM;
-            } else if (!strcasecmp(argv[1],"noeviction")) {
-                server.maxmemory_policy = REDIS_MAXMEMORY_NO_EVICTION;
-            } else {
+            server.maxmemory_policy =
+                configEnumGetValue(maxmemory_policy_enum,argv[1]);
+            if (server.maxmemory_policy == INT_MIN) {
                 err = "Invalid maxmemory policy";
                 goto loaderr;
             }
@@ -640,6 +674,12 @@ void loadServerConfig(char *filename, char *options) {
         if (err || ll < 0) goto badfmt; \
         _var = ll;
 
+#define config_set_enum_field(_name,_var,_enumvar) \
+    } else if (!strcasecmp(c->argv[2]->ptr,_name)) { \
+        int enumval = configEnumGetValue(_enumvar,o->ptr); \
+        if (enumval == INT_MIN) goto badfmt; \
+        _var = enumval;
+
 #define config_set_special_field(_name) \
     } else if (!strcasecmp(c->argv[2]->ptr,_name)) {
 
@@ -694,22 +734,8 @@ void configSetCommand(redisClient *c) {
                 }
             }
         }
-    } config_set_special_field("maxmemory-policy") {
-        if (!strcasecmp(o->ptr,"volatile-lru")) {
-            server.maxmemory_policy = REDIS_MAXMEMORY_VOLATILE_LRU;
-        } else if (!strcasecmp(o->ptr,"volatile-random")) {
-            server.maxmemory_policy = REDIS_MAXMEMORY_VOLATILE_RANDOM;
-        } else if (!strcasecmp(o->ptr,"volatile-ttl")) {
-            server.maxmemory_policy = REDIS_MAXMEMORY_VOLATILE_TTL;
-        } else if (!strcasecmp(o->ptr,"allkeys-lru")) {
-            server.maxmemory_policy = REDIS_MAXMEMORY_ALLKEYS_LRU;
-        } else if (!strcasecmp(o->ptr,"allkeys-random")) {
-            server.maxmemory_policy = REDIS_MAXMEMORY_ALLKEYS_RANDOM;
-        } else if (!strcasecmp(o->ptr,"noeviction")) {
-            server.maxmemory_policy = REDIS_MAXMEMORY_NO_EVICTION;
-        } else {
-            goto badfmt;
-        }
+    } config_set_enum_field(
+      "maxmemory-policy",server.maxmemory_policy,maxmemory_policy_enum) {
     } config_set_special_field("appendfsync") {
         if (!strcasecmp(o->ptr,"no")) {
             server.aof_fsync = AOF_FSYNC_NO;
@@ -988,19 +1014,13 @@ void configSetCommand(redisClient *c) {
     } \
 } while(0);
 
-char *maxmemoryToString() {
-    char *s;
-    switch(server.maxmemory_policy) {
-    case REDIS_MAXMEMORY_VOLATILE_LRU: s = "volatile-lru"; break;
-    case REDIS_MAXMEMORY_VOLATILE_TTL: s = "volatile-ttl"; break;
-    case REDIS_MAXMEMORY_VOLATILE_RANDOM: s = "volatile-random"; break;
-    case REDIS_MAXMEMORY_ALLKEYS_LRU: s = "allkeys-lru"; break;
-    case REDIS_MAXMEMORY_ALLKEYS_RANDOM: s = "allkeys-random"; break;
-    case REDIS_MAXMEMORY_NO_EVICTION: s = "noeviction"; break;
-    default: s = "unknown"; break;
-    }
-    return s;
-}
+#define config_get_enum_field(_name,_var,_enumvar) do { \
+    if (stringmatch(pattern,_name,0)) { \
+        addReplyBulkCString(c,_name); \
+        addReplyBulkCString(c,configEnumGetNameOrUnknown(_enumvar,_var)); \
+        matches++; \
+    } \
+} while(0);
 
 int supervisedToMode(const char *str) {
     int mode;
@@ -1029,6 +1049,7 @@ char *supervisedToString(void) {
     }
     return s;
 }
+
 void configGetCommand(redisClient *c) {
     robj *o = c->argv[2];
     void *replylen = addDeferredMultiBulkLength(c);
@@ -1119,6 +1140,10 @@ void configGetCommand(redisClient *c) {
     config_get_bool_field("aof-load-truncated",
             server.aof_load_truncated);
 
+    /* Enum values */
+    config_get_enum_field("maxmemory-policy",
+            server.maxmemory_policy,maxmemory_policy_enum);
+
     /* Everything we can't handle with macros follows. */
 
     if (stringmatch(pattern,"appendonly",0)) {
@@ -1136,11 +1161,6 @@ void configGetCommand(redisClient *c) {
         addReplyBulkCString(c,buf);
         matches++;
     }
-    if (stringmatch(pattern,"maxmemory-policy",0)) {
-        addReplyBulkCString(c,"maxmemory-policy");
-        addReplyBulkCString(c,maxmemoryToString());
-        matches++;
-    }
     if (stringmatch(pattern,"appendfsync",0)) {
         char *policy;
 
@@ -1313,7 +1333,7 @@ void rewriteConfigAddLineNumberToOption(struct rewriteConfigState *state, sds op
  * This is useful as only unused lines of processed options will be blanked
  * in the config file, while options the rewrite process does not understand
  * remain untouched. */
-void rewriteConfigMarkAsProcessed(struct rewriteConfigState *state, char *option) {
+void rewriteConfigMarkAsProcessed(struct rewriteConfigState *state, const char *option) {
     sds opt = sdsnew(option);
 
     if (dictAdd(state->rewritten,opt,NULL) != DICT_OK) sdsfree(opt);
@@ -1397,7 +1417,7 @@ struct rewriteConfigState *rewriteConfigReadOldFile(char *path) {
  *
  * "line" is either used, or freed, so the caller does not need to free it
  * in any way. */
-void rewriteConfigRewriteLine(struct rewriteConfigState *state, char *option, sds line, int force) {
+void rewriteConfigRewriteLine(struct rewriteConfigState *state, const char *option, sds line, int force) {
     sds o = sdsnew(option);
     list *l = dictFetchValue(state->option_to_line,o);
 
@@ -1536,17 +1556,12 @@ void rewriteConfigEnumOption(struct rewriteConfigState *state, char *option, int
 
 /* Rewrite the syslog-facility option. */
 void rewriteConfigSyslogfacilityOption(struct rewriteConfigState *state) {
-    int value = server.syslog_facility, j;
+    int value = server.syslog_facility;
     int force = value != LOG_LOCAL0;
-    char *name = NULL, *option = "syslog-facility";
+    const char *name = NULL, *option = "syslog-facility";
     sds line;
 
-    for (j = 0; validSyslogFacilities[j].name; j++) {
-        if (validSyslogFacilities[j].value == value) {
-            name = (char*) validSyslogFacilities[j].name;
-            break;
-        }
-    }
+    name = configEnumGetNameOrUnknown(syslog_facility_enum,value);
     line = sdscatprintf(sdsempty(),"%s %s",option,name);
     rewriteConfigRewriteLine(state,option,line,force);
 }