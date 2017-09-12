@@ -51,6 +51,7 @@
 #include <float.h>
 #include <math.h>
 #include <pthread.h>
+#include <sys/resource.h>
 
 /* Our shared "common" objects */
 
@@ -170,6 +171,7 @@ struct redisCommand readonlyCommandTable[] = {
     {"info",infoCommand,1,REDIS_CMD_INLINE,NULL,0,0,0},
     {"monitor",monitorCommand,1,REDIS_CMD_INLINE,NULL,0,0,0},
     {"ttl",ttlCommand,2,REDIS_CMD_INLINE,NULL,1,1,1},
+    {"persist",persistCommand,2,REDIS_CMD_INLINE,NULL,1,1,1},
     {"slaveof",slaveofCommand,3,REDIS_CMD_INLINE,NULL,0,0,0},
     {"debug",debugCommand,-2,REDIS_CMD_INLINE,NULL,0,0,0},
     {"config",configCommand,-2,REDIS_CMD_BULK,NULL,0,0,0},
@@ -338,7 +340,7 @@ dictType zsetDictType = {
     NULL,                      /* val dup */
     dictEncObjKeyCompare,      /* key compare */
     dictRedisObjectDestructor, /* key destructor */
-    dictVanillaFree            /* val destructor of malloc(sizeof(double)) */
+    NULL                       /* val destructor */
 };
 
 /* Db->dict, keys are sds strings, vals are Redis objects. */
@@ -435,6 +437,48 @@ void updateDictResizePolicy(void) {
 
 /* ======================= Cron: called every 100 ms ======================== */
 
+/* Try to expire a few timed out keys. The algorithm used is adaptive and
+ * will use few CPU cycles if there are few expiring keys, otherwise
+ * it will get more aggressive to avoid that too much memory is used by
+ * keys that can be removed from the keyspace. */
+void activeExpireCycle(void) {
+    int j;
+
+    for (j = 0; j < server.dbnum; j++) {
+        int expired;
+        redisDb *db = server.db+j;
+
+        /* Continue to expire if at the end of the cycle more than 25%
+         * of the keys were expired. */
+        do {
+            long num = dictSize(db->expires);
+            time_t now = time(NULL);
+
+            expired = 0;
+            if (num > REDIS_EXPIRELOOKUPS_PER_CRON)
+                num = REDIS_EXPIRELOOKUPS_PER_CRON;
+            while (num--) {
+                dictEntry *de;
+                time_t t;
+
+                if ((de = dictGetRandomKey(db->expires)) == NULL) break;
+                t = (time_t) dictGetEntryVal(de);
+                if (now > t) {
+                    sds key = dictGetEntryKey(de);
+                    robj *keyobj = createStringObject(key,sdslen(key));
+
+                    propagateExpire(db,keyobj);
+                    dbDelete(db,keyobj);
+                    decrRefCount(keyobj);
+                    expired++;
+                    server.stat_expiredkeys++;
+                }
+            }
+        } while (expired > REDIS_EXPIRELOOKUPS_PER_CRON/4);
+    }
+}
+
+
 int serverCron(struct aeEventLoop *eventLoop, long long id, void *clientData) {
     int j, loops = server.cronloops++;
     REDIS_NOTUSED(eventLoop);
@@ -533,41 +577,10 @@ int serverCron(struct aeEventLoop *eventLoop, long long id, void *clientData) {
          }
     }
 
-    /* Try to expire a few timed out keys. The algorithm used is adaptive and
-     * will use few CPU cycles if there are few expiring keys, otherwise
-     * it will get more aggressive to avoid that too much memory is used by
-     * keys that can be removed from the keyspace. */
-    for (j = 0; j < server.dbnum; j++) {
-        int expired;
-        redisDb *db = server.db+j;
-
-        /* Continue to expire if at the end of the cycle more than 25%
-         * of the keys were expired. */
-        do {
-            long num = dictSize(db->expires);
-            time_t now = time(NULL);
-
-            expired = 0;
-            if (num > REDIS_EXPIRELOOKUPS_PER_CRON)
-                num = REDIS_EXPIRELOOKUPS_PER_CRON;
-            while (num--) {
-                dictEntry *de;
-                time_t t;
-
-                if ((de = dictGetRandomKey(db->expires)) == NULL) break;
-                t = (time_t) dictGetEntryVal(de);
-                if (now > t) {
-                    sds key = dictGetEntryKey(de);
-                    robj *keyobj = createStringObject(key,sdslen(key));
-
-                    dbDelete(db,keyobj);
-                    decrRefCount(keyobj);
-                    expired++;
-                    server.stat_expiredkeys++;
-                }
-            }
-        } while (expired > REDIS_EXPIRELOOKUPS_PER_CRON/4);
-    }
+    /* Expire a few keys per cycle, only if this is a master.
+     * On slaves we wait for DEL operations synthesized by the master
+     * in order to guarantee a strict consistency. */
+    if (server.masterhost == NULL) activeExpireCycle();
 
     /* Swap a few keys on disk if we are over the memory limit and VM
      * is enbled. Try to free objects from the free list first. */
@@ -734,6 +747,7 @@ void initServerConfig() {
     server.hash_max_zipmap_value = REDIS_HASH_MAX_ZIPMAP_VALUE;
     server.list_max_ziplist_entries = REDIS_LIST_MAX_ZIPLIST_ENTRIES;
     server.list_max_ziplist_value = REDIS_LIST_MAX_ZIPLIST_VALUE;
+    server.set_max_intset_entries = REDIS_SET_MAX_INTSET_ENTRIES;
     server.shutdown_asap = 0;
 
     resetServerSaveParams();
@@ -892,9 +906,6 @@ void call(redisClient *c, struct redisCommand *cmd) {
 int processCommand(redisClient *c) {
     struct redisCommand *cmd;
 
-    /* Free some memory if needed (maxmemory setting) */
-    if (server.maxmemory) freeMemoryIfNeeded();
-
     /* Handle the multi bulk command type. This is an alternative protocol
      * supported by Redis in order to receive commands that are composed of
      * multiple binary-safe "bulk" arguments. The latency of processing is
@@ -913,15 +924,20 @@ int processCommand(redisClient *c) {
     } else if (c->multibulk) {
         if (c->bulklen == -1) {
             if (((char*)c->argv[0]->ptr)[0] != '$') {
-                addReplySds(c,sdsnew("-ERR multi bulk protocol error\r\n"));
+                addReplyError(c,"multi bulk protocol error");
                 resetClient(c);
                 return 1;
             } else {
-                int bulklen = atoi(((char*)c->argv[0]->ptr)+1);
+                char *eptr;
+                long bulklen = strtol(((char*)c->argv[0]->ptr)+1,&eptr,10);
+                int perr = eptr[0] != '\0';
+
                 decrRefCount(c->argv[0]);
-                if (bulklen < 0 || bulklen > 1024*1024*1024) {
+                if (perr || bulklen == LONG_MIN || bulklen == LONG_MAX ||
+                    bulklen < 0 || bulklen > 1024*1024*1024)
+                {
                     c->argc--;
-                    addReplySds(c,sdsnew("-ERR invalid bulk write count\r\n"));
+                    addReplyError(c,"invalid bulk write count");
                     resetClient(c);
                     return 1;
                 }
@@ -974,27 +990,28 @@ int processCommand(redisClient *c) {
      * such wrong arity, bad command name and so forth. */
     cmd = lookupCommand(c->argv[0]->ptr);
     if (!cmd) {
-        addReplySds(c,
-            sdscatprintf(sdsempty(), "-ERR unknown command '%s'\r\n",
-                (char*)c->argv[0]->ptr));
+        addReplyErrorFormat(c,"unknown command '%s'",
+            (char*)c->argv[0]->ptr);
         resetClient(c);
         return 1;
     } else if ((cmd->arity > 0 && cmd->arity != c->argc) ||
                (c->argc < -cmd->arity)) {
-        addReplySds(c,
-            sdscatprintf(sdsempty(),
-                "-ERR wrong number of arguments for '%s' command\r\n",
-                cmd->name));
+        addReplyErrorFormat(c,"wrong number of arguments for '%s' command",
+            cmd->name);
         resetClient(c);
         return 1;
     } else if (cmd->flags & REDIS_CMD_BULK && c->bulklen == -1) {
         /* This is a bulk command, we have to read the last argument yet. */
-        int bulklen = atoi(c->argv[c->argc-1]->ptr);
+        char *eptr;
+        long bulklen = strtol(c->argv[c->argc-1]->ptr,&eptr,10);
+        int perr = eptr[0] != '\0';
 
         decrRefCount(c->argv[c->argc-1]);
-        if (bulklen < 0 || bulklen > 1024*1024*1024) {
+        if (perr || bulklen == LONG_MAX || bulklen == LONG_MIN ||
+            bulklen < 0 || bulklen > 1024*1024*1024)
+        {
             c->argc--;
-            addReplySds(c,sdsnew("-ERR invalid bulk write count\r\n"));
+            addReplyError(c,"invalid bulk write count");
             resetClient(c);
             return 1;
         }
@@ -1021,16 +1038,21 @@ int processCommand(redisClient *c) {
 
     /* Check if the user is authenticated */
     if (server.requirepass && !c->authenticated && cmd->proc != authCommand) {
-        addReplySds(c,sdsnew("-ERR operation not permitted\r\n"));
+        addReplyError(c,"operation not permitted");
         resetClient(c);
         return 1;
     }
 
-    /* Handle the maxmemory directive */
+    /* Handle the maxmemory directive.
+     *
+     * First we try to free some memory if possible (if there are volatile
+     * keys in the dataset). If there are not the only thing we can do
+     * is returning an error. */
+    if (server.maxmemory) freeMemoryIfNeeded();
     if (server.maxmemory && (cmd->flags & REDIS_CMD_DENYOOM) &&
         zmalloc_used_memory() > server.maxmemory)
     {
-        addReplySds(c,sdsnew("-ERR command not allowed when used memory > 'maxmemory'\r\n"));
+        addReplyError(c,"command not allowed when used memory > 'maxmemory'");
         resetClient(c);
         return 1;
     }
@@ -1040,7 +1062,7 @@ int processCommand(redisClient *c) {
         &&
         cmd->proc != subscribeCommand && cmd->proc != unsubscribeCommand &&
         cmd->proc != psubscribeCommand && cmd->proc != punsubscribeCommand) {
-        addReplySds(c,sdsnew("-ERR only (P)SUBSCRIBE / (P)UNSUBSCRIBE / QUIT allowed in this context\r\n"));
+        addReplyError(c,"only (P)SUBSCRIBE / (P)UNSUBSCRIBE / QUIT allowed in this context");
         resetClient(c);
         return 1;
     }
@@ -1081,11 +1103,7 @@ int prepareForShutdown() {
         if (server.vm_enabled) unlink(server.vm_swap_file);
     } else {
         /* Snapshotting. Perform a SYNC SAVE and exit */
-        if (rdbSave(server.dbfilename) == REDIS_OK) {
-            if (server.daemonize)
-                unlink(server.pidfile);
-            redisLog(REDIS_WARNING,"%zu bytes used at exit",zmalloc_used_memory());
-        } else {
+        if (rdbSave(server.dbfilename) != REDIS_OK) {
             /* Ooops.. error saving! The best we can do is to continue
              * operating. Note that if there was a background saving process,
              * in the next cron() Redis will be notified that the background
@@ -1095,6 +1113,7 @@ int prepareForShutdown() {
             return REDIS_ERR;
         }
     }
+    if (server.daemonize) unlink(server.pidfile);
     redisLog(REDIS_WARNING,"Server exit now, bye bye...");
     return REDIS_OK;
 }
@@ -1107,7 +1126,7 @@ void authCommand(redisClient *c) {
       addReply(c,shared.ok);
     } else {
       c->authenticated = 0;
-      addReplySds(c,sdscatprintf(sdsempty(),"-ERR invalid password\r\n"));
+      addReplyError(c,"invalid password");
     }
 }
 
@@ -1148,6 +1167,10 @@ sds genRedisInfoString(void) {
     time_t uptime = time(NULL)-server.stat_starttime;
     int j;
     char hmem[64];
+    struct rusage self_ru, c_ru;
+
+    getrusage(RUSAGE_SELF, &self_ru);
+    getrusage(RUSAGE_CHILDREN, &c_ru);
 
     bytesToHuman(hmem,zmalloc_used_memory());
     info = sdscatprintf(sdsempty(),
@@ -1159,11 +1182,16 @@ sds genRedisInfoString(void) {
         "process_id:%ld\r\n"
         "uptime_in_seconds:%ld\r\n"
         "uptime_in_days:%ld\r\n"
+        "used_cpu_sys:%.2f\r\n"
+        "used_cpu_user:%.2f\r\n"
+        "used_cpu_sys_childrens:%.2f\r\n"
+        "used_cpu_user_childrens:%.2f\r\n"
         "connected_clients:%d\r\n"
         "connected_slaves:%d\r\n"
         "blocked_clients:%d\r\n"
         "used_memory:%zu\r\n"
         "used_memory_human:%s\r\n"
+        "mem_fragmentation_ratio:%.2f\r\n"
         "changes_since_last_save:%lld\r\n"
         "bgsave_in_progress:%d\r\n"
         "last_save_time:%ld\r\n"
@@ -1185,11 +1213,16 @@ sds genRedisInfoString(void) {
         (long) getpid(),
         uptime,
         uptime/(3600*24),
+        (float)self_ru.ru_utime.tv_sec+(float)self_ru.ru_utime.tv_usec/1000000,
+        (float)self_ru.ru_stime.tv_sec+(float)self_ru.ru_stime.tv_usec/1000000,
+        (float)c_ru.ru_utime.tv_sec+(float)c_ru.ru_utime.tv_usec/1000000,
+        (float)c_ru.ru_stime.tv_sec+(float)c_ru.ru_stime.tv_usec/1000000,
         listLength(server.clients)-listLength(server.slaves),
         listLength(server.slaves),
         server.blpop_blocked_clients,
         zmalloc_used_memory(),
         hmem,
+        zmalloc_get_fragmentation_ratio(),
         server.dirty,
         server.bgsavechildpid != -1,
         server.lastsave,
@@ -1319,7 +1352,8 @@ void freeMemoryIfNeeded(void) {
         if (tryFreeOneObjectFromFreelist() == REDIS_OK) continue;
         for (j = 0; j < server.dbnum; j++) {
             int minttl = -1;
-            robj *minkey = NULL;
+            sds minkey = NULL;
+            robj *keyobj = NULL;
             struct dictEntry *de;
 
             if (dictSize(server.db[j].expires)) {
@@ -1336,7 +1370,10 @@ void freeMemoryIfNeeded(void) {
                         minttl = t;
                     }
                 }
-                dbDelete(server.db+j,minkey);
+                keyobj = createStringObject(minkey,sdslen(minkey));
+                dbDelete(server.db+j,keyobj);
+                server.stat_expiredkeys++;
+                decrRefCount(keyobj);
             }
         }
         if (!freed) return; /* nothing to free... */
@@ -1367,9 +1404,17 @@ void linuxOvercommitMemoryWarning(void) {
 }
 #endif /* __linux__ */
 
+void createPidFile(void) {
+    /* Try to write the pid file in a best-effort way. */
+    FILE *fp = fopen(server.pidfile,"w");
+    if (fp) {
+        fprintf(fp,"%d\n",getpid());
+        fclose(fp);
+    }
+}
+
 void daemonize(void) {
     int fd;
-    FILE *fp;
 
     if (fork() != 0) exit(0); /* parent exits */
     setsid(); /* create a new session */
@@ -1383,12 +1428,6 @@ void daemonize(void) {
         dup2(fd, STDERR_FILENO);
         if (fd > STDERR_FILENO) close(fd);
     }
-    /* Try to write the pid file */
-    fp = fopen(server.pidfile,"w");
-    if (fp) {
-        fprintf(fp,"%d\n",getpid());
-        fclose(fp);
-    }
 }
 
 void version() {
@@ -1421,6 +1460,7 @@ int main(int argc, char **argv) {
     }
     if (server.daemonize) daemonize();
     initServer();
+    if (server.daemonize) createPidFile();
     redisLog(REDIS_NOTICE,"Server started, Redis version " REDIS_VERSION);
 #ifdef __linux__
     linuxOvercommitMemoryWarning();
@@ -1500,6 +1540,7 @@ void segvHandler(int sig, siginfo_t *info, void *secret) {
         redisLog(REDIS_WARNING,"%s", messages[i]);
 
     /* free(messages); Don't call free() with possibly corrupted memory. */
+    if (server.daemonize) unlink(server.pidfile);
     _exit(0);
 }
 