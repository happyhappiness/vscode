@@ -5010,7 +5010,10 @@ static void sortCommand(redisClient *c) {
     zfree(vector);
 }
 
-static void infoCommand(redisClient *c) {
+/* Create the string returned by the INFO command. This is decoupled
+ * by the INFO command itself as we need to report the same information
+ * on memory corruption problems. */
+static sds genRedisInfoString(void) {
     sds info;
     time_t uptime = time(NULL)-server.stat_starttime;
     int j;
@@ -5068,6 +5071,11 @@ static void infoCommand(redisClient *c) {
                 j, keys, vkeys);
         }
     }
+    return info;
+}
+
+static void infoCommand(redisClient *c) {
+    sds info = genRedisInfoString();
     addReplySds(c,sdscatprintf(sdsempty(),"$%d\r\n",sdslen(info)));
     addReplySds(c,info);
     addReply(c,shared.crlf);
@@ -6177,36 +6185,16 @@ static void segvHandler(int sig, siginfo_t *info, void *secret) {
     char **messages = NULL;
     int i, trace_size = 0;
     unsigned long offset=0;
-    time_t uptime = time(NULL)-server.stat_starttime;
     ucontext_t *uc = (ucontext_t*) secret;
+    sds infostring;
     REDIS_NOTUSED(info);
 
     redisLog(REDIS_WARNING,
         "======= Ooops! Redis %s got signal: -%d- =======", REDIS_VERSION, sig);
-    redisLog(REDIS_WARNING, "%s", sdscatprintf(sdsempty(),
-        "redis_version:%s; "
-        "uptime_in_seconds:%d; "
-        "connected_clients:%d; "
-        "connected_slaves:%d; "
-        "used_memory:%zu; "
-        "changes_since_last_save:%lld; "
-        "bgsave_in_progress:%d; "
-        "last_save_time:%d; "
-        "total_connections_received:%lld; "
-        "total_commands_processed:%lld; "
-        "role:%s;"
-        ,REDIS_VERSION,
-        uptime,
-        listLength(server.clients)-listLength(server.slaves),
-        listLength(server.slaves),
-        server.usedmemory,
-        server.dirty,
-        server.bgsavechildpid != -1,
-        server.lastsave,
-        server.stat_numconnections,
-        server.stat_numcommands,
-        server.masterhost == NULL ? "master" : "slave"
-    ));
+    infostring = genRedisInfoString();
+    redisLog(REDIS_WARNING, "%s",infostring);
+    /* It's not safe to sdsfree() the returned string under memory
+     * corruption conditions. Let it leak as we are going to abort */
     
     trace_size = backtrace(trace, 100);
     /* overwrite sigaction with caller's address */
@@ -6225,7 +6213,7 @@ static void segvHandler(int sig, siginfo_t *info, void *secret) {
             redisLog(REDIS_WARNING,"%d redis-server %p %s + %d", i, trace[i], fn, (unsigned int)offset);
         }
     }
-    free(messages);
+    // free(messages); Don't call free() with possibly corrupted memory.
     exit(0);
 }
 