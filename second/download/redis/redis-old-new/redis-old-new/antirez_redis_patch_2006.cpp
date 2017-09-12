@@ -170,6 +170,7 @@ struct redisCommand readonlyCommandTable[] = {
     {"info",infoCommand,1,REDIS_CMD_INLINE,NULL,0,0,0},
     {"monitor",monitorCommand,1,REDIS_CMD_INLINE,NULL,0,0,0},
     {"ttl",ttlCommand,2,REDIS_CMD_INLINE,NULL,1,1,1},
+    {"persist",persistCommand,2,REDIS_CMD_INLINE,NULL,1,1,1},
     {"slaveof",slaveofCommand,3,REDIS_CMD_INLINE,NULL,0,0,0},
     {"debug",debugCommand,-2,REDIS_CMD_INLINE,NULL,0,0,0},
     {"config",configCommand,-2,REDIS_CMD_BULK,NULL,0,0,0},
@@ -435,6 +436,48 @@ void updateDictResizePolicy(void) {
 
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
@@ -533,41 +576,10 @@ int serverCron(struct aeEventLoop *eventLoop, long long id, void *clientData) {
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
@@ -900,9 +912,14 @@ int processCommand(redisClient *c) {
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
                     addReplySds(c,sdsnew("-ERR invalid bulk write count\r\n"));
                     resetClient(c);
@@ -972,10 +989,14 @@ int processCommand(redisClient *c) {
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
             addReplySds(c,sdsnew("-ERR invalid bulk write count\r\n"));
             resetClient(c);
@@ -1064,11 +1085,7 @@ int prepareForShutdown() {
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
@@ -1078,6 +1095,7 @@ int prepareForShutdown() {
             return REDIS_ERR;
         }
     }
+    if (server.daemonize) unlink(server.pidfile);
     redisLog(REDIS_WARNING,"Server exit now, bye bye...");
     return REDIS_OK;
 }
@@ -1350,9 +1368,17 @@ void linuxOvercommitMemoryWarning(void) {
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
@@ -1366,12 +1392,6 @@ void daemonize(void) {
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
@@ -1404,6 +1424,7 @@ int main(int argc, char **argv) {
     }
     if (server.daemonize) daemonize();
     initServer();
+    if (server.daemonize) createPidFile();
     redisLog(REDIS_NOTICE,"Server started, Redis version " REDIS_VERSION);
 #ifdef __linux__
     linuxOvercommitMemoryWarning();
@@ -1480,6 +1501,7 @@ void segvHandler(int sig, siginfo_t *info, void *secret) {
         redisLog(REDIS_WARNING,"%s", messages[i]);
 
     /* free(messages); Don't call free() with possibly corrupted memory. */
+    if (server.daemonize) unlink(server.pidfile);
     _exit(0);
 }
 