@@ -74,6 +74,7 @@ struct redisCommand readonlyCommandTable[] = {
     {"setex",setexCommand,4,REDIS_CMD_BULK|REDIS_CMD_DENYOOM,NULL,0,0,0},
     {"append",appendCommand,3,REDIS_CMD_BULK|REDIS_CMD_DENYOOM,NULL,1,1,1},
     {"substr",substrCommand,4,REDIS_CMD_INLINE,NULL,1,1,1},
+    {"strlen",strlenCommand,2,REDIS_CMD_INLINE,NULL,1,1,1},
     {"del",delCommand,-2,REDIS_CMD_INLINE,NULL,0,0,0},
     {"exists",existsCommand,2,REDIS_CMD_INLINE,NULL,1,1,1},
     {"incr",incrCommand,2,REDIS_CMD_INLINE|REDIS_CMD_DENYOOM,NULL,1,1,1},
@@ -169,6 +170,7 @@ struct redisCommand readonlyCommandTable[] = {
     {"info",infoCommand,1,REDIS_CMD_INLINE,NULL,0,0,0},
     {"monitor",monitorCommand,1,REDIS_CMD_INLINE,NULL,0,0,0},
     {"ttl",ttlCommand,2,REDIS_CMD_INLINE,NULL,1,1,1},
+    {"persist",persistCommand,2,REDIS_CMD_INLINE,NULL,1,1,1},
     {"slaveof",slaveofCommand,3,REDIS_CMD_INLINE,NULL,0,0,0},
     {"debug",debugCommand,-2,REDIS_CMD_INLINE,NULL,0,0,0},
     {"config",configCommand,-2,REDIS_CMD_BULK,NULL,0,0,0},
@@ -186,23 +188,22 @@ struct redisCommand readonlyCommandTable[] = {
 void redisLog(int level, const char *fmt, ...) {
     va_list ap;
     FILE *fp;
+    char *c = ".-*#";
+    char buf[64];
+    time_t now;
+
+    if (level < server.verbosity) return;
 
     fp = (server.logfile == NULL) ? stdout : fopen(server.logfile,"a");
     if (!fp) return;
 
     va_start(ap, fmt);
-    if (level >= server.verbosity) {
-        char *c = ".-*#";
-        char buf[64];
-        time_t now;
-
-        now = time(NULL);
-        strftime(buf,64,"%d %b %H:%M:%S",localtime(&now));
-        fprintf(fp,"[%d] %s %c ",(int)getpid(),buf,c[level]);
-        vfprintf(fp, fmt, ap);
-        fprintf(fp,"\n");
-        fflush(fp);
-    }
+    now = time(NULL);
+    strftime(buf,64,"%d %b %H:%M:%S",localtime(&now));
+    fprintf(fp,"[%d] %s %c ",(int)getpid(),buf,c[level]);
+    vfprintf(fp, fmt, ap);
+    fprintf(fp,"\n");
+    fflush(fp);
     va_end(ap);
 
     if (server.logfile) fclose(fp);
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
@@ -761,6 +773,7 @@ void initServer() {
     signal(SIGPIPE, SIG_IGN);
     setupSigSegvAction();
 
+    server.mainthread = pthread_self();
     server.devnull = fopen("/dev/null","w");
     if (server.devnull == NULL) {
         redisLog(REDIS_WARNING, "Can't open /dev/null: %s", server.neterr);
@@ -827,7 +840,7 @@ int qsortRedisCommands(const void *r1, const void *r2) {
 
 void sortCommandTable() {
     /* Copy and sort the read-only version of the command table */
-    commandTable = (struct redisCommand*)malloc(sizeof(readonlyCommandTable));
+    commandTable = (struct redisCommand*)zmalloc(sizeof(readonlyCommandTable));
     memcpy(commandTable,readonlyCommandTable,sizeof(readonlyCommandTable));
     qsort(commandTable,
         sizeof(readonlyCommandTable)/sizeof(struct redisCommand),