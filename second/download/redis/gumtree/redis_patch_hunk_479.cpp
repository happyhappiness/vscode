     config_get_bool_field("stop-writes-on-bgsave-error",
             server.stop_writes_on_bgsave_err);
     config_get_bool_field("daemonize", server.daemonize);
     config_get_bool_field("rdbcompression", server.rdb_compression);
     config_get_bool_field("rdbchecksum", server.rdb_checksum);
     config_get_bool_field("activerehashing", server.activerehashing);
+    config_get_bool_field("protected-mode", server.protected_mode);
     config_get_bool_field("repl-disable-tcp-nodelay",
             server.repl_disable_tcp_nodelay);
     config_get_bool_field("repl-diskless-sync",
             server.repl_diskless_sync);
     config_get_bool_field("aof-rewrite-incremental-fsync",
             server.aof_rewrite_incremental_fsync);
     config_get_bool_field("aof-load-truncated",
             server.aof_load_truncated);
 
+    /* Enum values */
+    config_get_enum_field("maxmemory-policy",
+            server.maxmemory_policy,maxmemory_policy_enum);
+    config_get_enum_field("loglevel",
+            server.verbosity,loglevel_enum);
+    config_get_enum_field("supervised",
+            server.supervised_mode,supervised_mode_enum);
+    config_get_enum_field("appendfsync",
+            server.aof_fsync,aof_fsync_enum);
+    config_get_enum_field("syslog-facility",
+            server.syslog_facility,syslog_facility_enum);
+
     /* Everything we can't handle with macros follows. */
 
     if (stringmatch(pattern,"appendonly",0)) {
         addReplyBulkCString(c,"appendonly");
-        addReplyBulkCString(c,server.aof_state == REDIS_AOF_OFF ? "no" : "yes");
+        addReplyBulkCString(c,server.aof_state == AOF_OFF ? "no" : "yes");
         matches++;
     }
     if (stringmatch(pattern,"dir",0)) {
         char buf[1024];
 
         if (getcwd(buf,sizeof(buf)) == NULL)
             buf[0] = '\0';
 
         addReplyBulkCString(c,"dir");
         addReplyBulkCString(c,buf);
         matches++;
     }
-    if (stringmatch(pattern,"maxmemory-policy",0)) {
-        char *s;
-
-        switch(server.maxmemory_policy) {
-        case REDIS_MAXMEMORY_VOLATILE_LRU: s = "volatile-lru"; break;
-        case REDIS_MAXMEMORY_VOLATILE_TTL: s = "volatile-ttl"; break;
-        case REDIS_MAXMEMORY_VOLATILE_RANDOM: s = "volatile-random"; break;
-        case REDIS_MAXMEMORY_ALLKEYS_LRU: s = "allkeys-lru"; break;
-        case REDIS_MAXMEMORY_ALLKEYS_RANDOM: s = "allkeys-random"; break;
-        case REDIS_MAXMEMORY_NO_EVICTION: s = "noeviction"; break;
-        default: s = "unknown"; break; /* too harmless to panic */
-        }
-        addReplyBulkCString(c,"maxmemory-policy");
-        addReplyBulkCString(c,s);
-        matches++;
-    }
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
 
         for (j = 0; j < server.saveparamslen; j++) {
             buf = sdscatprintf(buf,"%jd %d",
