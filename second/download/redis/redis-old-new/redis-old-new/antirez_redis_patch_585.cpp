@@ -625,14 +625,23 @@ void loadServerConfig(char *filename, char *options) {
     } else if (!strcasecmp(c->argv[2]->ptr,_name)) { \
         int yn = yesnotoi(o->ptr); \
         if (yn == -1) goto badfmt; \
-        _var = yn; \
+        _var = yn;
 
 #define config_set_numerical_field(_name,_var,min,max) \
     } else if (!strcasecmp(c->argv[2]->ptr,_name)) { \
         if (getLongLongFromObject(o,&ll) == REDIS_ERR || ll < 0) goto badfmt; \
         if (min != LLONG_MIN && ll < min) goto badfmt; \
         if (max != LLONG_MAX && ll > max) goto badfmt; \
-        _var = ll; \
+        _var = ll;
+
+#define config_set_memory_field(_name,_var) \
+    } else if (!strcasecmp(c->argv[2]->ptr,_name)) { \
+        ll = memtoll(o->ptr,&err); \
+        if (err || ll < 0) goto badfmt; \
+        _var = ll;
+
+#define config_set_special_field(_name) \
+    } else if (!strcasecmp(c->argv[2]->ptr,_name)) {
 
 void configSetCommand(redisClient *c) {
     robj *o;
@@ -642,31 +651,24 @@ void configSetCommand(redisClient *c) {
     redisAssertWithInfo(c,c->argv[3],sdsEncodedObject(c->argv[3]));
     o = c->argv[3];
 
-    if (!strcasecmp(c->argv[2]->ptr,"dbfilename")) {
+    if (0) { /* this starts the config_set macros else-if chain. */
+
+    /* Special fields that can't be handled with general macros. */
+    config_set_special_field("dbfilename") {
         if (!pathIsBaseName(o->ptr)) {
             addReplyError(c, "dbfilename can't be a path, just a filename");
             return;
         }
         zfree(server.rdb_filename);
         server.rdb_filename = zstrdup(o->ptr);
-    } else if (!strcasecmp(c->argv[2]->ptr,"requirepass")) {
+    } config_set_special_field("requirepass") {
         if (sdslen(o->ptr) > REDIS_AUTHPASS_MAX_LEN) goto badfmt;
         zfree(server.requirepass);
         server.requirepass = ((char*)o->ptr)[0] ? zstrdup(o->ptr) : NULL;
-    } else if (!strcasecmp(c->argv[2]->ptr,"masterauth")) {
+    } config_set_special_field("masterauth") {
         zfree(server.masterauth);
         server.masterauth = ((char*)o->ptr)[0] ? zstrdup(o->ptr) : NULL;
-    } else if (!strcasecmp(c->argv[2]->ptr,"maxmemory")) {
-        ll = memtoll(o->ptr,&err);
-        if (err || ll < 0) goto badfmt;
-        server.maxmemory = ll;
-        if (server.maxmemory) {
-            if (server.maxmemory < zmalloc_used_memory()) {
-                redisLog(REDIS_WARNING,"WARNING: the new maxmemory value set via CONFIG SET is smaller than the current memory usage. This will result in keys eviction and/or inability to accept new write commands depending on the maxmemory-policy.");
-            }
-            freeMemoryIfNeeded();
-        }
-    } else if (!strcasecmp(c->argv[2]->ptr,"maxclients")) {
+    } config_set_special_field("maxclients") {
         int orig_value = server.maxclients;
 
         if (getLongLongFromObject(o,&ll) == REDIS_ERR || ll < 1) goto badfmt;
@@ -692,7 +694,7 @@ void configSetCommand(redisClient *c) {
                 }
             }
         }
-    } else if (!strcasecmp(c->argv[2]->ptr,"maxmemory-policy")) {
+    } config_set_special_field("maxmemory-policy") {
         if (!strcasecmp(o->ptr,"volatile-lru")) {
             server.maxmemory_policy = REDIS_MAXMEMORY_VOLATILE_LRU;
         } else if (!strcasecmp(o->ptr,"volatile-random")) {
@@ -708,7 +710,7 @@ void configSetCommand(redisClient *c) {
         } else {
             goto badfmt;
         }
-    } else if (!strcasecmp(c->argv[2]->ptr,"appendfsync")) {
+    } config_set_special_field("appendfsync") {
         if (!strcasecmp(o->ptr,"no")) {
             server.aof_fsync = AOF_FSYNC_NO;
         } else if (!strcasecmp(o->ptr,"everysec")) {
@@ -718,7 +720,7 @@ void configSetCommand(redisClient *c) {
         } else {
             goto badfmt;
         }
-    } else if (!strcasecmp(c->argv[2]->ptr,"appendonly")) {
+    } config_set_special_field("appendonly") {
         int enable = yesnotoi(o->ptr);
 
         if (enable == -1) goto badfmt;
@@ -731,7 +733,7 @@ void configSetCommand(redisClient *c) {
                 return;
             }
         }
-    } else if (!strcasecmp(c->argv[2]->ptr,"save")) {
+    } config_set_special_field("save") {
         int vlen, j;
         sds *v = sdssplitlen(o->ptr,sdslen(o->ptr)," ",1,&vlen);
 
@@ -765,12 +767,12 @@ void configSetCommand(redisClient *c) {
             appendServerSaveParams(seconds, changes);
         }
         sdsfreesplitres(v,vlen);
-    } else if (!strcasecmp(c->argv[2]->ptr,"dir")) {
+    } config_set_special_field("dir") {
         if (chdir((char*)o->ptr) == -1) {
             addReplyErrorFormat(c,"Changing directory: %s", strerror(errno));
             return;
         }
-    } else if (!strcasecmp(c->argv[2]->ptr,"loglevel")) {
+    } config_set_special_field("loglevel") {
         if (!strcasecmp(o->ptr,"warning")) {
             server.verbosity = REDIS_WARNING;
         } else if (!strcasecmp(o->ptr,"notice")) {
@@ -782,7 +784,7 @@ void configSetCommand(redisClient *c) {
         } else {
             goto badfmt;
         }
-    } else if (!strcasecmp(c->argv[2]->ptr,"client-output-buffer-limit")) {
+    } config_set_special_field("client-output-buffer-limit") {
         int vlen, j;
         sds *v = sdssplitlen(o->ptr,sdslen(o->ptr)," ",1,&vlen);
 
@@ -827,19 +829,15 @@ void configSetCommand(redisClient *c) {
             server.client_obuf_limits[class].soft_limit_seconds = soft_seconds;
         }
         sdsfreesplitres(v,vlen);
-    } else if (!strcasecmp(c->argv[2]->ptr,"repl-backlog-size")) {
-        ll = memtoll(o->ptr,&err);
-        if (err || ll < 0) goto badfmt;
-        resizeReplicationBacklog(ll);
-    } else if (!strcasecmp(c->argv[2]->ptr,"notify-keyspace-events")) {
+    } config_set_special_field("notify-keyspace-events") {
         int flags = keyspaceEventsStringToFlags(o->ptr);
 
         if (flags == -1) goto badfmt;
         server.notify_keyspace_events = flags;
 
     /* Boolean fields.
      * config_set_bool_field(name,var). */
-    config_set_bool_field(
+    } config_set_bool_field(
       "rdbcompression", server.rdb_compression) {
     } config_set_bool_field(
       "repl-disable-tcp-nodelay",server.repl_disable_tcp_nodelay) {
@@ -932,6 +930,18 @@ void configSetCommand(redisClient *c) {
             enableWatchdog(ll);
         else
             disableWatchdog();
+
+    /* Memory fields.
+     * config_set_memory_field(name,var) */
+    } config_set_memory_field("maxmemory",server.maxmemory) {
+        if (server.maxmemory) {
+            if (server.maxmemory < zmalloc_used_memory()) {
+                redisLog(REDIS_WARNING,"WARNING: the new maxmemory value set via CONFIG SET is smaller than the current memory usage. This will result in keys eviction and/or inability to accept new write commands depending on the maxmemory-policy.");
+            }
+            freeMemoryIfNeeded();
+        }
+    } config_set_memory_field("repl-backlog-size",ll) {
+        resizeReplicationBacklog(ll);
     }
 
     /* Everyhing else is an error... */