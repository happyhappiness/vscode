@@ -50,7 +50,6 @@
 #include <limits.h>
 #include <float.h>
 #include <math.h>
-#include <pthread.h>
 #include <sys/resource.h>
 
 /* Our shared "common" objects */
@@ -659,22 +658,7 @@ int serverCron(struct aeEventLoop *eventLoop, long long id, void *clientData) {
             }
             updateDictResizePolicy();
         }
-    } else if (server.bgsavethread != (pthread_t) -1) {
-        if (server.bgsavethread != (pthread_t) -1) {
-            int state;
-
-            pthread_mutex_lock(&server.bgsavethread_mutex);
-            state = server.bgsavethread_state;
-            pthread_mutex_unlock(&server.bgsavethread_mutex);
-
-            if (state == REDIS_BGSAVE_THREAD_DONE_OK ||
-                state == REDIS_BGSAVE_THREAD_DONE_ERR)
-            {
-                backgroundSaveDoneHandler(
-                    (state == REDIS_BGSAVE_THREAD_DONE_OK) ? 0 : 1, 0);
-            }
-        }
-    } else if (!server.ds_enabled) {
+    } else {
          time_t now = time(NULL);
 
         /* If there is not a background saving/rewrite in progress check if
@@ -712,10 +696,6 @@ int serverCron(struct aeEventLoop *eventLoop, long long id, void *clientData) {
      * in order to guarantee a strict consistency. */
     if (server.masterhost == NULL) activeExpireCycle();
 
-    /* Remove a few cached objects from memory if we are over the
-     * configured memory limit */
-    if (server.ds_enabled) cacheCron();
-
     /* Replication cron function -- used to reconnect to master and
      * to detect transfer failures. */
     if (!(loops % 10)) replicationCron();
@@ -735,31 +715,6 @@ void beforeSleep(struct aeEventLoop *eventLoop) {
     listNode *ln;
     redisClient *c;
 
-    /* Awake clients that got all the on disk keys they requested */
-    if (server.ds_enabled && listLength(server.io_ready_clients)) {
-        listIter li;
-
-        listRewind(server.io_ready_clients,&li);
-        while((ln = listNext(&li))) {
-            c = ln->value;
-            struct redisCommand *cmd;
-
-            /* Resume the client. */
-            listDelNode(server.io_ready_clients,ln);
-            c->flags &= (~REDIS_IO_WAIT);
-            server.cache_blocked_clients--;
-            aeCreateFileEvent(server.el, c->fd, AE_READABLE,
-                readQueryFromClient, c);
-            cmd = lookupCommand(c->argv[0]->ptr);
-            redisAssert(cmd != NULL);
-            call(c,cmd);
-            resetClient(c);
-            /* There may be more data to process in the input buffer. */
-            if (c->querybuf && sdslen(c->querybuf) > 0)
-                processInputBuffer(c);
-        }
-    }
-
     /* Try to process pending commands for clients that were just unblocked. */
     while (listLength(server.unblocked_clients)) {
         ln = listFirst(server.unblocked_clients);
@@ -870,10 +825,6 @@ void initServerConfig() {
     server.maxmemory = 0;
     server.maxmemory_policy = REDIS_MAXMEMORY_VOLATILE_LRU;
     server.maxmemory_samples = 3;
-    server.ds_enabled = 0;
-    server.ds_path = sdsnew("/tmp/redis.ds");
-    server.cache_max_memory = 64LL*1024*1024; /* 64 MB of RAM */
-    server.cache_blocked_clients = 0;
     server.hash_max_zipmap_entries = REDIS_HASH_MAX_ZIPMAP_ENTRIES;
     server.hash_max_zipmap_value = REDIS_HASH_MAX_ZIPMAP_VALUE;
     server.list_max_ziplist_entries = REDIS_LIST_MAX_ZIPLIST_ENTRIES;
@@ -882,7 +833,6 @@ void initServerConfig() {
     server.zset_max_ziplist_entries = REDIS_ZSET_MAX_ZIPLIST_ENTRIES;
     server.zset_max_ziplist_value = REDIS_ZSET_MAX_ZIPLIST_VALUE;
     server.shutdown_asap = 0;
-    server.cache_flush_delay = 0;
     server.cluster_enabled = 0;
     server.cluster.configfile = zstrdup("nodes.conf");
 
@@ -930,12 +880,10 @@ void initServer() {
             server.syslog_facility);
     }
 
-    server.mainthread = pthread_self();
     server.clients = listCreate();
     server.slaves = listCreate();
     server.monitors = listCreate();
     server.unblocked_clients = listCreate();
-    server.cache_io_queue = listCreate();
 
     createSharedObjects();
     server.el = aeCreateEventLoop();
@@ -965,11 +913,6 @@ void initServer() {
         server.db[j].expires = dictCreate(&keyptrDictType,NULL);
         server.db[j].blocking_keys = dictCreate(&keylistDictType,NULL);
         server.db[j].watched_keys = dictCreate(&keylistDictType,NULL);
-        if (server.ds_enabled) {
-            server.db[j].io_keys = dictCreate(&keylistDictType,NULL);
-            server.db[j].io_negcache = dictCreate(&setDictType,NULL);
-            server.db[j].io_queued = dictCreate(&setDictType,NULL);
-        }
         server.db[j].id = j;
     }
     server.pubsub_channels = dictCreate(&keylistDictType,NULL);
@@ -979,8 +922,6 @@ void initServer() {
     server.cronloops = 0;
     server.bgsavechildpid = -1;
     server.bgrewritechildpid = -1;
-    server.bgsavethread_state = REDIS_BGSAVE_THREAD_UNACTIVE;
-    server.bgsavethread = (pthread_t) -1;
     server.bgrewritebuf = sdsempty();
     server.aofbuf = sdsempty();
     server.lastsave = time(NULL);
@@ -1010,7 +951,6 @@ void initServer() {
         }
     }
 
-    if (server.ds_enabled) dsInit();
     if (server.cluster_enabled) clusterInit();
     srand(time(NULL)^getpid());
 }
@@ -1188,8 +1128,6 @@ int processCommand(redisClient *c) {
         queueMultiCommand(c,cmd);
         addReply(c,shared.queued);
     } else {
-        if (server.ds_enabled && blockClientOnSwappedKeys(c,cmd))
-            return REDIS_ERR;
         call(c,cmd);
     }
     return REDIS_OK;
@@ -1207,9 +1145,7 @@ int prepareForShutdown() {
         kill(server.bgsavechildpid,SIGKILL);
         rdbRemoveTempFile(server.bgsavechildpid);
     }
-    if (server.ds_enabled) {
-        /* FIXME: flush all objects on disk */
-    } else if (server.appendonly) {
+    if (server.appendonly) {
         /* Append only file: fsync() the AOF and exit */
         aof_fsync(server.appendfd);
     } else if (server.saveparamslen > 0) {
@@ -1391,8 +1327,7 @@ sds genRedisInfoString(char *section) {
             server.loading,
             server.appendonly,
             server.dirty,
-                server.bgsavechildpid != -1 ||
-                server.bgsavethread != (pthread_t) -1,
+            server.bgsavechildpid != -1,
             server.lastsave,
             server.bgrewritechildpid != -1);
 
@@ -1438,35 +1373,6 @@ sds genRedisInfoString(char *section) {
         }
     }
 
-    /* Diskstore */
-    if (allsections || defsections || !strcasecmp(section,"diskstore")) {
-        if (sections++) info = sdscat(info,"\r\n");
-        info = sdscatprintf(info,
-            "# Diskstore\r\n"
-            "ds_enabled:%d\r\n",
-            server.ds_enabled != 0);
-        if (server.ds_enabled) {
-            lockThreadedIO();
-            info = sdscatprintf(info,
-                "cache_max_memory:%llu\r\n"
-                "cache_blocked_clients:%lu\r\n"
-                "cache_io_queue_len:%lu\r\n"
-                "cache_io_jobs_new:%lu\r\n"
-                "cache_io_jobs_processing:%lu\r\n"
-                "cache_io_jobs_processed:%lu\r\n"
-                "cache_io_ready_clients:%lu\r\n"
-                ,(unsigned long long) server.cache_max_memory,
-                (unsigned long) server.cache_blocked_clients,
-                (unsigned long) listLength(server.cache_io_queue),
-                (unsigned long) listLength(server.io_newjobs),
-                (unsigned long) listLength(server.io_processing),
-                (unsigned long) listLength(server.io_processed),
-                (unsigned long) listLength(server.io_ready_clients)
-            );
-            unlockThreadedIO();
-        }
-    }
-
     /* Stats */
     if (allsections || defsections || !strcasecmp(section,"stats")) {
         if (sections++) info = sdscat(info,"\r\n");
@@ -1824,9 +1730,7 @@ int main(int argc, char **argv) {
     linuxOvercommitMemoryWarning();
 #endif
     start = ustime();
-    if (server.ds_enabled) {
-        redisLog(REDIS_NOTICE,"DB not loaded (running with disk back end)");
-    } else if (server.appendonly) {
+    if (server.appendonly) {
         if (loadAppendOnlyFile(server.appendfilename) == REDIS_OK)
             redisLog(REDIS_NOTICE,"DB loaded from append only file: %.3f seconds",(float)(ustime()-start)/1000000);
     } else {