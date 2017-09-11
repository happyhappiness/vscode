@@ -66,6 +66,29 @@ configEnum syslog_facility_enum[] = {
     {NULL, 0}
 };
 
+configEnum loglevel_enum[] = {
+    {"debug", REDIS_DEBUG},
+    {"verbose", REDIS_VERBOSE},
+    {"notice", REDIS_NOTICE},
+    {"warning", REDIS_WARNING},
+    {NULL,0}
+};
+
+configEnum supervised_mode_enum[] = {
+    {"upstart", REDIS_SUPERVISED_UPSTART},
+    {"systemd", REDIS_SUPERVISED_SYSTEMD},
+    {"auto", REDIS_SUPERVISED_AUTODETECT},
+    {"no", REDIS_SUPERVISED_NONE},
+    {NULL, 0}
+};
+
+configEnum aof_fsync_enum[] = {
+    {"everysec", AOF_FSYNC_EVERYSEC},
+    {"always", AOF_FSYNC_ALWAYS},
+    {"no", AOF_FSYNC_NO},
+    {NULL, 0}
+};
+
 /* Output buffer limits presets. */
 clientBufferLimitsConfig clientBufferLimitsDefaults[REDIS_CLIENT_TYPE_COUNT] = {
     {0, 0, 0}, /* normal */
@@ -111,8 +134,6 @@ const char *maxmemoryToString(void) {
  * Config file parsing
  *----------------------------------------------------------------------------*/
 
-int supervisedToMode(const char *str);
-
 int yesnotoi(char *s) {
     if (!strcasecmp(s,"yes")) return 1;
     else if (!strcasecmp(s,"no")) return 0;
@@ -220,12 +241,10 @@ void loadServerConfigFromString(char *config) {
                 exit(1);
             }
         } else if (!strcasecmp(argv[0],"loglevel") && argc == 2) {
-            if (!strcasecmp(argv[1],"debug")) server.verbosity = REDIS_DEBUG;
-            else if (!strcasecmp(argv[1],"verbose")) server.verbosity = REDIS_VERBOSE;
-            else if (!strcasecmp(argv[1],"notice")) server.verbosity = REDIS_NOTICE;
-            else if (!strcasecmp(argv[1],"warning")) server.verbosity = REDIS_WARNING;
-            else {
-                err = "Invalid log level. Must be one of debug, notice, warning";
+            server.verbosity = configEnumGetValue(loglevel_enum,argv[1]);
+            if (server.verbosity == INT_MIN) {
+                err = "Invalid log level. "
+                      "Must be one of debug, notice, warning";
                 goto loaderr;
             }
         } else if (!strcasecmp(argv[0],"logfile") && argc == 2) {
@@ -379,13 +398,8 @@ void loadServerConfigFromString(char *config) {
                 err = "argument must be 'yes' or 'no'"; goto loaderr;
             }
         } else if (!strcasecmp(argv[0],"appendfsync") && argc == 2) {
-            if (!strcasecmp(argv[1],"no")) {
-                server.aof_fsync = AOF_FSYNC_NO;
-            } else if (!strcasecmp(argv[1],"always")) {
-                server.aof_fsync = AOF_FSYNC_ALWAYS;
-            } else if (!strcasecmp(argv[1],"everysec")) {
-                server.aof_fsync = AOF_FSYNC_EVERYSEC;
-            } else {
+            server.aof_fsync = configEnumGetValue(aof_fsync_enum,argv[1]);
+            if (server.aof_fsync == INT_MIN) {
                 err = "argument must be 'no', 'always' or 'everysec'";
                 goto loaderr;
             }
@@ -570,14 +584,14 @@ void loadServerConfigFromString(char *config) {
             }
             server.notify_keyspace_events = flags;
         } else if (!strcasecmp(argv[0],"supervised") && argc == 2) {
-            int mode = supervisedToMode(argv[1]);
+            server.supervised_mode =
+                configEnumGetValue(supervised_mode_enum,argv[1]);
 
-            if (mode == -1) {
+            if (server.supervised_mode == INT_MIN) {
                 err = "Invalid option for 'supervised'. "
                     "Allowed values: 'upstart', 'systemd', 'auto', or 'no'";
                 goto loaderr;
             }
-            server.supervised_mode = mode;
         } else if (!strcasecmp(argv[0],"sentinel")) {
             /* argc == 1 is handled by main() as we need to enter the sentinel
              * mode ASAP. */
@@ -683,6 +697,8 @@ void loadServerConfig(char *filename, char *options) {
 #define config_set_special_field(_name) \
     } else if (!strcasecmp(c->argv[2]->ptr,_name)) {
 
+#define config_set_else } else
+
 void configSetCommand(redisClient *c) {
     robj *o;
     long long ll;
@@ -734,18 +750,6 @@ void configSetCommand(redisClient *c) {
                 }
             }
         }
-    } config_set_enum_field(
-      "maxmemory-policy",server.maxmemory_policy,maxmemory_policy_enum) {
-    } config_set_special_field("appendfsync") {
-        if (!strcasecmp(o->ptr,"no")) {
-            server.aof_fsync = AOF_FSYNC_NO;
-        } else if (!strcasecmp(o->ptr,"everysec")) {
-            server.aof_fsync = AOF_FSYNC_EVERYSEC;
-        } else if (!strcasecmp(o->ptr,"always")) {
-            server.aof_fsync = AOF_FSYNC_ALWAYS;
-        } else {
-            goto badfmt;
-        }
     } config_set_special_field("appendonly") {
         int enable = yesnotoi(o->ptr);
 
@@ -798,18 +802,6 @@ void configSetCommand(redisClient *c) {
             addReplyErrorFormat(c,"Changing directory: %s", strerror(errno));
             return;
         }
-    } config_set_special_field("loglevel") {
-        if (!strcasecmp(o->ptr,"warning")) {
-            server.verbosity = REDIS_WARNING;
-        } else if (!strcasecmp(o->ptr,"notice")) {
-            server.verbosity = REDIS_NOTICE;
-        } else if (!strcasecmp(o->ptr,"verbose")) {
-            server.verbosity = REDIS_VERBOSE;
-        } else if (!strcasecmp(o->ptr,"debug")) {
-            server.verbosity = REDIS_DEBUG;
-        } else {
-            goto badfmt;
-        }
     } config_set_special_field("client-output-buffer-limit") {
         int vlen, j;
         sds *v = sdssplitlen(o->ptr,sdslen(o->ptr)," ",1,&vlen);
@@ -968,14 +960,24 @@ void configSetCommand(redisClient *c) {
         }
     } config_set_memory_field("repl-backlog-size",ll) {
         resizeReplicationBacklog(ll);
-    }
+
+    /* Enumeration fields.
+     * config_set_enum_field(name,var,enum_var) */
+    } config_set_enum_field(
+      "loglevel",server.verbosity,loglevel_enum) {
+    } config_set_enum_field(
+      "maxmemory-policy",server.maxmemory_policy,maxmemory_policy_enum) {
+    } config_set_enum_field(
+      "appendfsync",server.aof_fsync,aof_fsync_enum) {
 
     /* Everyhing else is an error... */
-    } else {
+    } config_set_else {
         addReplyErrorFormat(c,"Unsupported CONFIG parameter: %s",
             (char*)c->argv[2]->ptr);
         return;
     }
+
+    /* On success we just return a generic OK for all the options. */
     addReply(c,shared.ok);
     return;
 
@@ -1022,34 +1024,6 @@ void configSetCommand(redisClient *c) {
     } \
 } while(0);
 
-int supervisedToMode(const char *str) {
-    int mode;
-    if (!strcasecmp(str,"upstart")) {
-        mode = REDIS_SUPERVISED_UPSTART;
-    } else if (!strcasecmp(str,"systemd")) {
-        mode = REDIS_SUPERVISED_SYSTEMD;
-    } else if (!strcasecmp(str,"auto")) {
-        mode = REDIS_SUPERVISED_AUTODETECT;
-    } else if (!strcasecmp(str,"no")) {
-        mode = REDIS_SUPERVISED_NONE;
-    } else {
-        mode = -1;
-    }
-    return mode;
-}
-
-char *supervisedToString(void) {
-    char *s;
-    switch(server.supervised_mode) {
-    case REDIS_SUPERVISED_UPSTART: s = "upstart"; break;
-    case REDIS_SUPERVISED_SYSTEMD: s = "systemd"; break;
-    case REDIS_SUPERVISED_AUTODETECT: s = "auto"; break;
-    case REDIS_SUPERVISED_NONE: s = "no"; break;
-    default: s = "no"; break;
-    }
-    return s;
-}
-
 void configGetCommand(redisClient *c) {
     robj *o = c->argv[2];
     void *replylen = addDeferredMultiBulkLength(c);
@@ -1143,6 +1117,12 @@ void configGetCommand(redisClient *c) {
     /* Enum values */
     config_get_enum_field("maxmemory-policy",
             server.maxmemory_policy,maxmemory_policy_enum);
+    config_get_enum_field("loglevel",
+            server.verbosity,loglevel_enum);
+    config_get_enum_field("supervised",
+            server.supervised_mode,supervised_mode_enum);
+    config_get_enum_field("appendfsync",
+            server.aof_fsync,aof_fsync_enum);
 
     /* Everything we can't handle with macros follows. */
 
@@ -1161,19 +1141,6 @@ void configGetCommand(redisClient *c) {
         addReplyBulkCString(c,buf);
         matches++;
     }
-    if (stringmatch(pattern,"appendfsync",0)) {
-        char *policy;
-
-        switch(server.aof_fsync) {
-        case AOF_FSYNC_NO: policy = "no"; break;
-        case AOF_FSYNC_EVERYSEC: policy = "everysec"; break;
-        case AOF_FSYNC_ALWAYS: policy = "always"; break;
-        default: policy = "unknown"; break; /* too harmless to panic */
-        }
-        addReplyBulkCString(c,"appendfsync");
-        addReplyBulkCString(c,policy);
-        matches++;
-    }
     if (stringmatch(pattern,"save",0)) {
         sds buf = sdsempty();
         int j;
@@ -1190,25 +1157,6 @@ void configGetCommand(redisClient *c) {
         sdsfree(buf);
         matches++;
     }
-    if (stringmatch(pattern,"loglevel",0)) {
-        char *s;
-
-        switch(server.verbosity) {
-        case REDIS_WARNING: s = "warning"; break;
-        case REDIS_VERBOSE: s = "verbose"; break;
-        case REDIS_NOTICE: s = "notice"; break;
-        case REDIS_DEBUG: s = "debug"; break;
-        default: s = "unknown"; break; /* too harmless to panic */
-        }
-        addReplyBulkCString(c,"loglevel");
-        addReplyBulkCString(c,s);
-        matches++;
-    }
-    if (stringmatch(pattern,"supervised",0)) {
-        addReplyBulkCString(c,"supervised");
-        addReplyBulkCString(c,supervisedToString());
-        matches++;
-    }
     if (stringmatch(pattern,"client-output-buffer-limit",0)) {
         sds buf = sdsempty();
         int j;
@@ -1528,29 +1476,15 @@ void rewriteConfigOctalOption(struct rewriteConfigState *state, char *option, in
     rewriteConfigRewriteLine(state,option,line,force);
 }
 
-/* Rewrite an enumeration option, after the "value" every enum/value pair
- * is specified, terminated by NULL. After NULL the default value is
- * specified. See how the function is used for more information. */
-void rewriteConfigEnumOption(struct rewriteConfigState *state, char *option, int value, ...) {
-    va_list ap;
-    char *enum_name, *matching_name = NULL;
-    int enum_val, def_val, force;
+/* Rewrite an enumeration option. It takes as usually state and option name,
+ * and in addition the enumeration array and the default value for the
+ * option. */
+void rewriteConfigEnumOption(struct rewriteConfigState *state, char *option, int value, configEnum *ce, int defval) {
     sds line;
+    const char *name = configEnumGetNameOrUnknown(ce,value);
+    int force = value != defval;
 
-    va_start(ap, value);
-    while(1) {
-        enum_name = va_arg(ap,char*);
-        enum_val = va_arg(ap,int);
-        if (enum_name == NULL) {
-            def_val = enum_val;
-            break;
-        }
-        if (value == enum_val) matching_name = enum_name;
-    }
-    va_end(ap);
-
-    force = value != def_val;
-    line = sdscatprintf(sdsempty(),"%s %s",option,matching_name);
+    line = sdscatprintf(sdsempty(),"%s %s",option,name);
     rewriteConfigRewriteLine(state,option,line,force);
 }
 
@@ -1822,12 +1756,7 @@ int rewriteConfig(char *path) {
     rewriteConfigOctalOption(state,"unixsocketperm",server.unixsocketperm,REDIS_DEFAULT_UNIX_SOCKET_PERM);
     rewriteConfigNumericalOption(state,"timeout",server.maxidletime,REDIS_MAXIDLETIME);
     rewriteConfigNumericalOption(state,"tcp-keepalive",server.tcpkeepalive,REDIS_DEFAULT_TCP_KEEPALIVE);
-    rewriteConfigEnumOption(state,"loglevel",server.verbosity,
-        "debug", REDIS_DEBUG,
-        "verbose", REDIS_VERBOSE,
-        "notice", REDIS_NOTICE,
-        "warning", REDIS_WARNING,
-        NULL, REDIS_DEFAULT_VERBOSITY);
+    rewriteConfigEnumOption(state,"loglevel",server.verbosity,loglevel_enum,REDIS_DEFAULT_VERBOSITY);
     rewriteConfigStringOption(state,"logfile",server.logfile,REDIS_DEFAULT_LOGFILE);
     rewriteConfigYesNoOption(state,"syslog-enabled",server.syslog_enabled,REDIS_DEFAULT_SYSLOG_ENABLED);
     rewriteConfigStringOption(state,"syslog-ident",server.syslog_ident,REDIS_DEFAULT_SYSLOG_IDENT);
@@ -1856,22 +1785,11 @@ int rewriteConfig(char *path) {
     rewriteConfigStringOption(state,"requirepass",server.requirepass,NULL);
     rewriteConfigNumericalOption(state,"maxclients",server.maxclients,REDIS_MAX_CLIENTS);
     rewriteConfigBytesOption(state,"maxmemory",server.maxmemory,REDIS_DEFAULT_MAXMEMORY);
-    rewriteConfigEnumOption(state,"maxmemory-policy",server.maxmemory_policy,
-        "volatile-lru", REDIS_MAXMEMORY_VOLATILE_LRU,
-        "allkeys-lru", REDIS_MAXMEMORY_ALLKEYS_LRU,
-        "volatile-random", REDIS_MAXMEMORY_VOLATILE_RANDOM,
-        "allkeys-random", REDIS_MAXMEMORY_ALLKEYS_RANDOM,
-        "volatile-ttl", REDIS_MAXMEMORY_VOLATILE_TTL,
-        "noeviction", REDIS_MAXMEMORY_NO_EVICTION,
-        NULL, REDIS_DEFAULT_MAXMEMORY_POLICY);
+    rewriteConfigEnumOption(state,"maxmemory-policy",server.maxmemory_policy,maxmemory_policy_enum,REDIS_DEFAULT_MAXMEMORY_POLICY);
     rewriteConfigNumericalOption(state,"maxmemory-samples",server.maxmemory_samples,REDIS_DEFAULT_MAXMEMORY_SAMPLES);
     rewriteConfigYesNoOption(state,"appendonly",server.aof_state != REDIS_AOF_OFF,0);
     rewriteConfigStringOption(state,"appendfilename",server.aof_filename,REDIS_DEFAULT_AOF_FILENAME);
-    rewriteConfigEnumOption(state,"appendfsync",server.aof_fsync,
-        "everysec", AOF_FSYNC_EVERYSEC,
-        "always", AOF_FSYNC_ALWAYS,
-        "no", AOF_FSYNC_NO,
-        NULL, REDIS_DEFAULT_AOF_FSYNC);
+    rewriteConfigEnumOption(state,"appendfsync",server.aof_fsync,aof_fsync_enum,REDIS_DEFAULT_AOF_FSYNC);
     rewriteConfigYesNoOption(state,"no-appendfsync-on-rewrite",server.aof_no_fsync_on_rewrite,REDIS_DEFAULT_AOF_NO_FSYNC_ON_REWRITE);
     rewriteConfigNumericalOption(state,"auto-aof-rewrite-percentage",server.aof_rewrite_perc,REDIS_AOF_REWRITE_PERC);
     rewriteConfigBytesOption(state,"auto-aof-rewrite-min-size",server.aof_rewrite_min_size,REDIS_AOF_REWRITE_MIN_SIZE);
@@ -1899,12 +1817,9 @@ int rewriteConfig(char *path) {
     rewriteConfigNumericalOption(state,"hz",server.hz,REDIS_DEFAULT_HZ);
     rewriteConfigYesNoOption(state,"aof-rewrite-incremental-fsync",server.aof_rewrite_incremental_fsync,REDIS_DEFAULT_AOF_REWRITE_INCREMENTAL_FSYNC);
     rewriteConfigYesNoOption(state,"aof-load-truncated",server.aof_load_truncated,REDIS_DEFAULT_AOF_LOAD_TRUNCATED);
-    rewriteConfigEnumOption(state,"supervised",server.supervised_mode,
-        "upstart", REDIS_SUPERVISED_UPSTART,
-        "systemd", REDIS_SUPERVISED_SYSTEMD,
-        "auto", REDIS_SUPERVISED_AUTODETECT,
-        "no", REDIS_SUPERVISED_NONE,
-        NULL, REDIS_SUPERVISED_NONE);
+    rewriteConfigEnumOption(state,"supervised",server.supervised_mode,supervised_mode_enum,REDIS_SUPERVISED_NONE);
+
+    /* Rewrite Sentinel config if in Sentinel mode. */
     if (server.sentinel_mode) rewriteConfigSentinelOption(state);
 
     /* Step 3: remove all the orphaned lines in the old file, that is, lines