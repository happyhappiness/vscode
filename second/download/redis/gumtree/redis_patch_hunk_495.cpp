         addReply(c,shared.ok);
     } else if (!strcasecmp(c->argv[1]->ptr,"set-active-expire") &&
                c->argc == 3)
     {
         server.active_expire_enabled = atoi(c->argv[2]->ptr);
         addReply(c,shared.ok);
+    } else if (!strcasecmp(c->argv[1]->ptr,"lua-always-replicate-commands") &&
+               c->argc == 3)
+    {
+        server.lua_always_replicate_commands = atoi(c->argv[2]->ptr);
+        addReply(c,shared.ok);
     } else if (!strcasecmp(c->argv[1]->ptr,"error") && c->argc == 3) {
         sds errstr = sdsnewlen("-",1);
 
         errstr = sdscatsds(errstr,c->argv[2]->ptr);
         errstr = sdsmapchars(errstr,"\n\r","  ",2); /* no newlines in errors. */
         errstr = sdscatlen(errstr,"\r\n",2);
         addReplySds(c,errstr);
+    } else if (!strcasecmp(c->argv[1]->ptr,"structsize") && c->argc == 2) {
+        sds sizes = sdsempty();
+        sizes = sdscatprintf(sizes,"bits:%d ",(sizeof(void*) == 8)?64:32);
+        sizes = sdscatprintf(sizes,"robj:%d ",(int)sizeof(robj));
+        sizes = sdscatprintf(sizes,"dictentry:%d ",(int)sizeof(dictEntry));
+        sizes = sdscatprintf(sizes,"sdshdr5:%d ",(int)sizeof(struct sdshdr5));
+        sizes = sdscatprintf(sizes,"sdshdr8:%d ",(int)sizeof(struct sdshdr8));
+        sizes = sdscatprintf(sizes,"sdshdr16:%d ",(int)sizeof(struct sdshdr16));
+        sizes = sdscatprintf(sizes,"sdshdr32:%d ",(int)sizeof(struct sdshdr32));
+        sizes = sdscatprintf(sizes,"sdshdr64:%d ",(int)sizeof(struct sdshdr64));
+        addReplyBulkSds(c,sizes);
+    } else if (!strcasecmp(c->argv[1]->ptr,"htstats") && c->argc == 3) {
+        long dbid;
+        sds stats = sdsempty();
+        char buf[4096];
+
+        if (getLongFromObjectOrReply(c, c->argv[2], &dbid, NULL) != C_OK)
+            return;
+        if (dbid < 0 || dbid >= server.dbnum) {
+            addReplyError(c,"Out of range database");
+            return;
+        }
+
+        stats = sdscatprintf(stats,"[Dictionary HT]\n");
+        dictGetStats(buf,sizeof(buf),server.db[dbid].dict);
+        stats = sdscat(stats,buf);
+
+        stats = sdscatprintf(stats,"[Expires HT]\n");
+        dictGetStats(buf,sizeof(buf),server.db[dbid].expires);
+        stats = sdscat(stats,buf);
+
+        addReplyBulkSds(c,stats);
+    } else if (!strcasecmp(c->argv[1]->ptr,"jemalloc") && c->argc == 3) {
+#if defined(USE_JEMALLOC)
+        if (!strcasecmp(c->argv[2]->ptr, "info")) {
+            sds info = sdsempty();
+            je_malloc_stats_print(inputCatSds, &info, NULL);
+            addReplyBulkSds(c, info);
+        } else if (!strcasecmp(c->argv[2]->ptr, "purge")) {
+            char tmp[32];
+            unsigned narenas = 0;
+            size_t sz = sizeof(unsigned);
+            if (!je_mallctl("arenas.narenas", &narenas, &sz, NULL, 0)) {
+                sprintf(tmp, "arena.%d.purge", narenas);
+                if (!je_mallctl(tmp, NULL, 0, NULL, 0)) {
+                    addReply(c, shared.ok);
+                    return;
+                }
+            }
+            addReplyError(c, "Error purging dirty pages");
+        } else {
+            addReplyErrorFormat(c, "Valid jemalloc debug fields: info, purge");
+        }
+#else
+        addReplyErrorFormat(c, "jemalloc support not available");
+#endif
     } else {
         addReplyErrorFormat(c, "Unknown DEBUG subcommand or wrong number of arguments for '%s'",
             (char*)c->argv[1]->ptr);
     }
 }
 
 /* =========================== Crash handling  ============================== */
 
-void _redisAssert(char *estr, char *file, int line) {
+void _serverAssert(char *estr, char *file, int line) {
     bugReportStart();
-    redisLog(REDIS_WARNING,"=== ASSERTION FAILED ===");
-    redisLog(REDIS_WARNING,"==> %s:%d '%s' is not true",file,line,estr);
+    serverLog(LL_WARNING,"=== ASSERTION FAILED ===");
+    serverLog(LL_WARNING,"==> %s:%d '%s' is not true",file,line,estr);
 #ifdef HAVE_BACKTRACE
     server.assert_failed = estr;
     server.assert_file = file;
     server.assert_line = line;
-    redisLog(REDIS_WARNING,"(forcing SIGSEGV to print the bug report.)");
+    serverLog(LL_WARNING,"(forcing SIGSEGV to print the bug report.)");
 #endif
     *((char*)-1) = 'x';
 }
 
-void _redisAssertPrintClientInfo(redisClient *c) {
+void _serverAssertPrintClientInfo(client *c) {
     int j;
 
     bugReportStart();
-    redisLog(REDIS_WARNING,"=== ASSERTION FAILED CLIENT CONTEXT ===");
-    redisLog(REDIS_WARNING,"client->flags = %d", c->flags);
-    redisLog(REDIS_WARNING,"client->fd = %d", c->fd);
-    redisLog(REDIS_WARNING,"client->argc = %d", c->argc);
+    serverLog(LL_WARNING,"=== ASSERTION FAILED CLIENT CONTEXT ===");
+    serverLog(LL_WARNING,"client->flags = %d", c->flags);
+    serverLog(LL_WARNING,"client->fd = %d", c->fd);
+    serverLog(LL_WARNING,"client->argc = %d", c->argc);
     for (j=0; j < c->argc; j++) {
         char buf[128];
         char *arg;
 
-        if (c->argv[j]->type == REDIS_STRING && sdsEncodedObject(c->argv[j])) {
+        if (c->argv[j]->type == OBJ_STRING && sdsEncodedObject(c->argv[j])) {
             arg = (char*) c->argv[j]->ptr;
         } else {
             snprintf(buf,sizeof(buf),"Object type: %u, encoding: %u",
                 c->argv[j]->type, c->argv[j]->encoding);
             arg = buf;
         }
-        redisLog(REDIS_WARNING,"client->argv[%d] = \"%s\" (refcount: %d)",
+        serverLog(LL_WARNING,"client->argv[%d] = \"%s\" (refcount: %d)",
             j, arg, c->argv[j]->refcount);
     }
 }
 
-void redisLogObjectDebugInfo(robj *o) {
-    redisLog(REDIS_WARNING,"Object type: %d", o->type);
-    redisLog(REDIS_WARNING,"Object encoding: %d", o->encoding);
-    redisLog(REDIS_WARNING,"Object refcount: %d", o->refcount);
-    if (o->type == REDIS_STRING && sdsEncodedObject(o)) {
-        redisLog(REDIS_WARNING,"Object raw string len: %zu", sdslen(o->ptr));
+void serverLogObjectDebugInfo(robj *o) {
+    serverLog(LL_WARNING,"Object type: %d", o->type);
+    serverLog(LL_WARNING,"Object encoding: %d", o->encoding);
+    serverLog(LL_WARNING,"Object refcount: %d", o->refcount);
+    if (o->type == OBJ_STRING && sdsEncodedObject(o)) {
+        serverLog(LL_WARNING,"Object raw string len: %zu", sdslen(o->ptr));
         if (sdslen(o->ptr) < 4096) {
             sds repr = sdscatrepr(sdsempty(),o->ptr,sdslen(o->ptr));
-            redisLog(REDIS_WARNING,"Object raw string content: %s", repr);
+            serverLog(LL_WARNING,"Object raw string content: %s", repr);
             sdsfree(repr);
         }
-    } else if (o->type == REDIS_LIST) {
-        redisLog(REDIS_WARNING,"List length: %d", (int) listTypeLength(o));
-    } else if (o->type == REDIS_SET) {
-        redisLog(REDIS_WARNING,"Set size: %d", (int) setTypeSize(o));
-    } else if (o->type == REDIS_HASH) {
-        redisLog(REDIS_WARNING,"Hash size: %d", (int) hashTypeLength(o));
-    } else if (o->type == REDIS_ZSET) {
-        redisLog(REDIS_WARNING,"Sorted set size: %d", (int) zsetLength(o));
-        if (o->encoding == REDIS_ENCODING_SKIPLIST)
-            redisLog(REDIS_WARNING,"Skiplist level: %d", (int) ((zset*)o->ptr)->zsl->level);
+    } else if (o->type == OBJ_LIST) {
+        serverLog(LL_WARNING,"List length: %d", (int) listTypeLength(o));
+    } else if (o->type == OBJ_SET) {
+        serverLog(LL_WARNING,"Set size: %d", (int) setTypeSize(o));
+    } else if (o->type == OBJ_HASH) {
+        serverLog(LL_WARNING,"Hash size: %d", (int) hashTypeLength(o));
+    } else if (o->type == OBJ_ZSET) {
+        serverLog(LL_WARNING,"Sorted set size: %d", (int) zsetLength(o));
+        if (o->encoding == OBJ_ENCODING_SKIPLIST)
+            serverLog(LL_WARNING,"Skiplist level: %d", (int) ((zset*)o->ptr)->zsl->level);
     }
 }
 
-void _redisAssertPrintObject(robj *o) {
+void _serverAssertPrintObject(robj *o) {
     bugReportStart();
-    redisLog(REDIS_WARNING,"=== ASSERTION FAILED OBJECT CONTEXT ===");
-    redisLogObjectDebugInfo(o);
+    serverLog(LL_WARNING,"=== ASSERTION FAILED OBJECT CONTEXT ===");
+    serverLogObjectDebugInfo(o);
 }
 
-void _redisAssertWithInfo(redisClient *c, robj *o, char *estr, char *file, int line) {
-    if (c) _redisAssertPrintClientInfo(c);
-    if (o) _redisAssertPrintObject(o);
-    _redisAssert(estr,file,line);
+void _serverAssertWithInfo(client *c, robj *o, char *estr, char *file, int line) {
+    if (c) _serverAssertPrintClientInfo(c);
+    if (o) _serverAssertPrintObject(o);
+    _serverAssert(estr,file,line);
 }
 
-void _redisPanic(char *msg, char *file, int line) {
+void _serverPanic(char *msg, char *file, int line) {
     bugReportStart();
-    redisLog(REDIS_WARNING,"------------------------------------------------");
-    redisLog(REDIS_WARNING,"!!! Software Failure. Press left mouse button to continue");
-    redisLog(REDIS_WARNING,"Guru Meditation: %s #%s:%d",msg,file,line);
+    serverLog(LL_WARNING,"------------------------------------------------");
+    serverLog(LL_WARNING,"!!! Software Failure. Press left mouse button to continue");
+    serverLog(LL_WARNING,"Guru Meditation: %s #%s:%d",msg,file,line);
 #ifdef HAVE_BACKTRACE
-    redisLog(REDIS_WARNING,"(forcing SIGSEGV in order to print the stack trace)");
+    serverLog(LL_WARNING,"(forcing SIGSEGV in order to print the stack trace)");
 #endif
-    redisLog(REDIS_WARNING,"------------------------------------------------");
+    serverLog(LL_WARNING,"------------------------------------------------");
     *((char*)-1) = 'x';
 }
 
 void bugReportStart(void) {
     if (server.bug_report_start == 0) {
-        redisLog(REDIS_WARNING,
-            "\n\n=== REDIS BUG REPORT START: Cut & paste starting from here ===");
+        serverLogRaw(LL_WARNING|LL_RAW,
+        "\n\n=== REDIS BUG REPORT START: Cut & paste starting from here ===\n");
         server.bug_report_start = 1;
     }
 }
 
 #ifdef HAVE_BACKTRACE
 static void *getMcontextEip(ucontext_t *uc) {
