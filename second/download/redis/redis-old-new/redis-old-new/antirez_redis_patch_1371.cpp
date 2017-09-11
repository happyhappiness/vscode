@@ -202,8 +202,10 @@ void loadServerConfigFromString(char *config) {
             if ((server.repl_serve_stale_data = yesnotoi(argv[1])) == -1) {
                 err = "argument must be 'yes' or 'no'"; goto loaderr;
             }
-        } else if (!strcasecmp(argv[0],"glueoutputbuf")) {
-            redisLog(REDIS_WARNING, "Deprecated configuration directive: \"%s\"", argv[0]);
+        } else if (!strcasecmp(argv[0],"slave-read-only") && argc == 2) {
+            if ((server.repl_slave_ro = yesnotoi(argv[1])) == -1) {
+                err = "argument must be 'yes' or 'no'"; goto loaderr;
+            }
         } else if (!strcasecmp(argv[0],"rdbcompression") && argc == 2) {
             if ((server.rdb_compression = yesnotoi(argv[1])) == -1) {
                 err = "argument must be 'yes' or 'no'"; goto loaderr;
@@ -262,10 +264,10 @@ void loadServerConfigFromString(char *config) {
         } else if (!strcasecmp(argv[0],"dbfilename") && argc == 2) {
             zfree(server.rdb_filename);
             server.rdb_filename = zstrdup(argv[1]);
-        } else if (!strcasecmp(argv[0],"hash-max-zipmap-entries") && argc == 2) {
-            server.hash_max_zipmap_entries = memtoll(argv[1], NULL);
-        } else if (!strcasecmp(argv[0],"hash-max-zipmap-value") && argc == 2) {
-            server.hash_max_zipmap_value = memtoll(argv[1], NULL);
+        } else if (!strcasecmp(argv[0],"hash-max-ziplist-entries") && argc == 2) {
+            server.hash_max_ziplist_entries = memtoll(argv[1], NULL);
+        } else if (!strcasecmp(argv[0],"hash-max-ziplist-value") && argc == 2) {
+            server.hash_max_ziplist_value = memtoll(argv[1], NULL);
         } else if (!strcasecmp(argv[0],"list-max-ziplist-entries") && argc == 2){
             server.list_max_ziplist_entries = memtoll(argv[1], NULL);
         } else if (!strcasecmp(argv[0],"list-max-ziplist-value") && argc == 2) {
@@ -336,6 +338,11 @@ void loadServerConfigFromString(char *config) {
             server.client_obuf_limits[class].hard_limit_bytes = hard;
             server.client_obuf_limits[class].soft_limit_bytes = soft;
             server.client_obuf_limits[class].soft_limit_seconds = soft_seconds;
+        } else if (!strcasecmp(argv[0],"stop-writes-on-bgsave-error") &&
+                   argc == 2) {
+            if ((server.stop_writes_on_bgsave_err = yesnotoi(argv[1])) == -1) {
+                err = "argument must be 'yes' or 'no'"; goto loaderr;
+            }
         } else {
             err = "Bad directive or wrong number of arguments"; goto loaderr;
         }
@@ -511,17 +518,22 @@ void configSetCommand(redisClient *c) {
 
         if (yn == -1) goto badfmt;
         server.repl_serve_stale_data = yn;
+    } else if (!strcasecmp(c->argv[2]->ptr,"slave-read-only")) {
+        int yn = yesnotoi(o->ptr);
+
+        if (yn == -1) goto badfmt;
+        server.repl_slave_ro = yn;
     } else if (!strcasecmp(c->argv[2]->ptr,"dir")) {
         if (chdir((char*)o->ptr) == -1) {
             addReplyErrorFormat(c,"Changing directory: %s", strerror(errno));
             return;
         }
-    } else if (!strcasecmp(c->argv[2]->ptr,"hash-max-zipmap-entries")) {
+    } else if (!strcasecmp(c->argv[2]->ptr,"hash-max-ziplist-entries")) {
         if (getLongLongFromObject(o,&ll) == REDIS_ERR || ll < 0) goto badfmt;
-        server.hash_max_zipmap_entries = ll;
-    } else if (!strcasecmp(c->argv[2]->ptr,"hash-max-zipmap-value")) {
+        server.hash_max_ziplist_entries = ll;
+    } else if (!strcasecmp(c->argv[2]->ptr,"hash-max-ziplist-value")) {
         if (getLongLongFromObject(o,&ll) == REDIS_ERR || ll < 0) goto badfmt;
-        server.hash_max_zipmap_value = ll;
+        server.hash_max_ziplist_value = ll;
     } else if (!strcasecmp(c->argv[2]->ptr,"list-max-ziplist-entries")) {
         if (getLongLongFromObject(o,&ll) == REDIS_ERR || ll < 0) goto badfmt;
         server.list_max_ziplist_entries = ll;
@@ -604,7 +616,17 @@ void configSetCommand(redisClient *c) {
             server.client_obuf_limits[class].soft_limit_seconds = soft_seconds;
         }
         sdsfreesplitres(v,vlen);
+    } else if (!strcasecmp(c->argv[2]->ptr,"stop-writes-on-bgsave-error")) {
+        int yn = yesnotoi(o->ptr);
 
+        if (yn == -1) goto badfmt;
+        server.stop_writes_on_bgsave_err = yn;
+    } else if (!strcasecmp(c->argv[2]->ptr,"repl-ping-slave-period")) {
+        if (getLongLongFromObject(o,&ll) == REDIS_ERR || ll <= 0) goto badfmt;
+        server.repl_ping_slave_period = ll;
+    } else if (!strcasecmp(c->argv[2]->ptr,"repl-timeout")) {
+        if (getLongLongFromObject(o,&ll) == REDIS_ERR || ll <= 0) goto badfmt;
+        server.repl_timeout = ll;
     } else {
         addReplyErrorFormat(c,"Unsupported CONFIG parameter: %s",
             (char*)c->argv[2]->ptr);
@@ -619,6 +641,31 @@ void configSetCommand(redisClient *c) {
             (char*)c->argv[2]->ptr);
 }
 
+#define config_get_string_field(_name,_var) do { \
+    if (stringmatch(pattern,_name,0)) { \
+        addReplyBulkCString(c,_name); \
+        addReplyBulkCString(c,_var ? _var : ""); \
+        matches++; \
+    } \
+} while(0);
+
+#define config_get_bool_field(_name,_var) do { \
+    if (stringmatch(pattern,_name,0)) { \
+        addReplyBulkCString(c,_name); \
+        addReplyBulkCString(c,_var ? "yes" : "no"); \
+        matches++; \
+    } \
+} while(0);
+
+#define config_get_numerical_field(_name,_var) do { \
+    if (stringmatch(pattern,_name,0)) { \
+        ll2string(buf,sizeof(buf),_var); \
+        addReplyBulkCString(c,_name); \
+        addReplyBulkCString(c,buf); \
+        matches++; \
+    } \
+} while(0);
+
 void configGetCommand(redisClient *c) {
     robj *o = c->argv[2];
     void *replylen = addDeferredMultiBulkLength(c);
@@ -627,6 +674,68 @@ void configGetCommand(redisClient *c) {
     int matches = 0;
     redisAssertWithInfo(c,o,o->encoding == REDIS_ENCODING_RAW);
 
+    /* String values */
+    config_get_string_field("dbfilename",server.rdb_filename);
+    config_get_string_field("requirepass",server.requirepass);
+    config_get_string_field("masterauth",server.requirepass);
+    config_get_string_field("bind",server.bindaddr);
+    config_get_string_field("unixsocket",server.unixsocket);
+    config_get_string_field("logfile",server.logfile);
+    config_get_string_field("pidfile",server.pidfile);
+
+    /* Numerical values */
+    config_get_numerical_field("maxmemory",server.maxmemory);
+    config_get_numerical_field("maxmemory-samples",server.maxmemory_samples);
+    config_get_numerical_field("timeout",server.maxidletime);
+    config_get_numerical_field("auto-aof-rewrite-percentage",
+            server.aof_rewrite_perc);
+    config_get_numerical_field("auto-aof-rewrite-min-size",
+            server.aof_rewrite_min_size);
+    config_get_numerical_field("hash-max-ziplist-entries",
+            server.hash_max_ziplist_entries);
+    config_get_numerical_field("hash-max-ziplist-value",
+            server.hash_max_ziplist_value);
+    config_get_numerical_field("list-max-ziplist-entries",
+            server.list_max_ziplist_entries);
+    config_get_numerical_field("list-max-ziplist-value",
+            server.list_max_ziplist_value);
+    config_get_numerical_field("set-max-intset-entries",
+            server.set_max_intset_entries);
+    config_get_numerical_field("zset-max-ziplist-entries",
+            server.zset_max_ziplist_entries);
+    config_get_numerical_field("zset-max-ziplist-value",
+            server.zset_max_ziplist_value);
+    config_get_numerical_field("lua-time-limit",server.lua_time_limit);
+    config_get_numerical_field("slowlog-log-slower-than",
+            server.slowlog_log_slower_than);
+    config_get_numerical_field("slowlog-max-len",
+            server.slowlog_max_len);
+    config_get_numerical_field("port",server.port);
+    config_get_numerical_field("databases",server.dbnum);
+    config_get_numerical_field("repl-ping-slave-period",server.repl_ping_slave_period);
+    config_get_numerical_field("repl-timeout",server.repl_timeout);
+    config_get_numerical_field("maxclients",server.maxclients);
+
+    /* Bool (yes/no) values */
+    config_get_bool_field("no-appendfsync-on-rewrite",
+            server.aof_no_fsync_on_rewrite);
+    config_get_bool_field("slave-serve-stale-data",
+            server.repl_serve_stale_data);
+    config_get_bool_field("slave-read-only",
+            server.repl_slave_ro);
+    config_get_bool_field("stop-writes-on-bgsave-error",
+            server.stop_writes_on_bgsave_err);
+    config_get_bool_field("daemonize", server.daemonize);
+    config_get_bool_field("rdbcompression", server.rdb_compression);
+    config_get_bool_field("activerehashing", server.activerehashing);
+
+    /* Everything we can't handle with macros follows. */
+
+    if (stringmatch(pattern,"appendonly",0)) {
+        addReplyBulkCString(c,"appendonly");
+        addReplyBulkCString(c,server.aof_state == REDIS_AOF_OFF ? "no" : "yes");
+        matches++;
+    }
     if (stringmatch(pattern,"dir",0)) {
         char buf[1024];
 
@@ -637,27 +746,6 @@ void configGetCommand(redisClient *c) {
         addReplyBulkCString(c,buf);
         matches++;
     }
-    if (stringmatch(pattern,"dbfilename",0)) {
-        addReplyBulkCString(c,"dbfilename");
-        addReplyBulkCString(c,server.rdb_filename);
-        matches++;
-    }
-    if (stringmatch(pattern,"requirepass",0)) {
-        addReplyBulkCString(c,"requirepass");
-        addReplyBulkCString(c,server.requirepass);
-        matches++;
-    }
-    if (stringmatch(pattern,"masterauth",0)) {
-        addReplyBulkCString(c,"masterauth");
-        addReplyBulkCString(c,server.masterauth);
-        matches++;
-    }
-    if (stringmatch(pattern,"maxmemory",0)) {
-        ll2string(buf,sizeof(buf),server.maxmemory);
-        addReplyBulkCString(c,"maxmemory");
-        addReplyBulkCString(c,buf);
-        matches++;
-    }
     if (stringmatch(pattern,"maxmemory-policy",0)) {
         char *s;
 
@@ -674,28 +762,6 @@ void configGetCommand(redisClient *c) {
         addReplyBulkCString(c,s);
         matches++;
     }
-    if (stringmatch(pattern,"maxmemory-samples",0)) {
-        ll2string(buf,sizeof(buf),server.maxmemory_samples);
-        addReplyBulkCString(c,"maxmemory-samples");
-        addReplyBulkCString(c,buf);
-        matches++;
-    }
-    if (stringmatch(pattern,"timeout",0)) {
-        ll2string(buf,sizeof(buf),server.maxidletime);
-        addReplyBulkCString(c,"timeout");
-        addReplyBulkCString(c,buf);
-        matches++;
-    }
-    if (stringmatch(pattern,"appendonly",0)) {
-        addReplyBulkCString(c,"appendonly");
-        addReplyBulkCString(c,server.aof_state == REDIS_AOF_OFF ? "no" : "yes");
-        matches++;
-    }
-    if (stringmatch(pattern,"no-appendfsync-on-rewrite",0)) {
-        addReplyBulkCString(c,"no-appendfsync-on-rewrite");
-        addReplyBulkCString(c,server.aof_no_fsync_on_rewrite ? "yes" : "no");
-        matches++;
-    }
     if (stringmatch(pattern,"appendfsync",0)) {
         char *policy;
 
@@ -725,71 +791,6 @@ void configGetCommand(redisClient *c) {
         sdsfree(buf);
         matches++;
     }
-    if (stringmatch(pattern,"auto-aof-rewrite-percentage",0)) {
-        addReplyBulkCString(c,"auto-aof-rewrite-percentage");
-        addReplyBulkLongLong(c,server.aof_rewrite_perc);
-        matches++;
-    }
-    if (stringmatch(pattern,"auto-aof-rewrite-min-size",0)) {
-        addReplyBulkCString(c,"auto-aof-rewrite-min-size");
-        addReplyBulkLongLong(c,server.aof_rewrite_min_size);
-        matches++;
-    }
-    if (stringmatch(pattern,"slave-serve-stale-data",0)) {
-        addReplyBulkCString(c,"slave-serve-stale-data");
-        addReplyBulkCString(c,server.repl_serve_stale_data ? "yes" : "no");
-        matches++;
-    }
-    if (stringmatch(pattern,"hash-max-zipmap-entries",0)) {
-        addReplyBulkCString(c,"hash-max-zipmap-entries");
-        addReplyBulkLongLong(c,server.hash_max_zipmap_entries);
-        matches++;
-    }
-    if (stringmatch(pattern,"hash-max-zipmap-value",0)) {
-        addReplyBulkCString(c,"hash-max-zipmap-value");
-        addReplyBulkLongLong(c,server.hash_max_zipmap_value);
-        matches++;
-    }
-    if (stringmatch(pattern,"list-max-ziplist-entries",0)) {
-        addReplyBulkCString(c,"list-max-ziplist-entries");
-        addReplyBulkLongLong(c,server.list_max_ziplist_entries);
-        matches++;
-    }
-    if (stringmatch(pattern,"list-max-ziplist-value",0)) {
-        addReplyBulkCString(c,"list-max-ziplist-value");
-        addReplyBulkLongLong(c,server.list_max_ziplist_value);
-        matches++;
-    }
-    if (stringmatch(pattern,"set-max-intset-entries",0)) {
-        addReplyBulkCString(c,"set-max-intset-entries");
-        addReplyBulkLongLong(c,server.set_max_intset_entries);
-        matches++;
-    }
-    if (stringmatch(pattern,"zset-max-ziplist-entries",0)) {
-        addReplyBulkCString(c,"zset-max-ziplist-entries");
-        addReplyBulkLongLong(c,server.zset_max_ziplist_entries);
-        matches++;
-    }
-    if (stringmatch(pattern,"zset-max-ziplist-value",0)) {
-        addReplyBulkCString(c,"zset-max-ziplist-value");
-        addReplyBulkLongLong(c,server.zset_max_ziplist_value);
-        matches++;
-    }
-    if (stringmatch(pattern,"lua-time-limit",0)) {
-        addReplyBulkCString(c,"lua-time-limit");
-        addReplyBulkLongLong(c,server.lua_time_limit);
-        matches++;
-    }
-    if (stringmatch(pattern,"slowlog-log-slower-than",0)) {
-        addReplyBulkCString(c,"slowlog-log-slower-than");
-        addReplyBulkLongLong(c,server.slowlog_log_slower_than);
-        matches++;
-    }
-    if (stringmatch(pattern,"slowlog-max-len",0)) {
-        addReplyBulkCString(c,"slowlog-max-len");
-        addReplyBulkLongLong(c,server.slowlog_max_len);
-        matches++;
-    }
     if (stringmatch(pattern,"loglevel",0)) {
         char *s;
 
@@ -822,6 +823,25 @@ void configGetCommand(redisClient *c) {
         sdsfree(buf);
         matches++;
     }
+    if (stringmatch(pattern,"unixsocketperm",0)) {
+        char buf[32];
+        snprintf(buf,sizeof(buf),"%o",server.unixsocketperm);
+        addReplyBulkCString(c,"unixsocketperm");
+        addReplyBulkCString(c,buf);
+        matches++;
+    }
+    if (stringmatch(pattern,"slaveof",0)) {
+        char buf[256];
+
+        addReplyBulkCString(c,"slaveof");
+        if (server.masterhost)
+            snprintf(buf,sizeof(buf),"%s %d",
+                server.masterhost, server.masterport);
+        else
+            buf[0] = '\0';
+        addReplyBulkCString(c,buf);
+        matches++;
+    }
     setDeferredMultiBulkLength(c,replylen,matches*2);
 }
 