@@ -70,12 +70,12 @@ struct redisServer server; /* server global state */
 struct redisCommand *commandTable;
 struct redisCommand redisCommandTable[] = {
     {"get",getCommand,2,0,NULL,1,1,1,0,0},
-    {"set",setCommand,3,REDIS_CMD_DENYOOM,NULL,0,0,0,0,0},
-    {"setnx",setnxCommand,3,REDIS_CMD_DENYOOM,NULL,0,0,0,0,0},
-    {"setex",setexCommand,4,REDIS_CMD_DENYOOM,NULL,0,0,0,0,0},
+    {"set",setCommand,3,REDIS_CMD_DENYOOM,noPreloadGetKeys,1,1,1,0,0},
+    {"setnx",setnxCommand,3,REDIS_CMD_DENYOOM,noPreloadGetKeys,1,1,1,0,0},
+    {"setex",setexCommand,4,REDIS_CMD_DENYOOM,noPreloadGetKeys,2,2,1,0,0},
     {"append",appendCommand,3,REDIS_CMD_DENYOOM,NULL,1,1,1,0,0},
     {"strlen",strlenCommand,2,0,NULL,1,1,1,0,0},
-    {"del",delCommand,-2,0,NULL,0,0,0,0,0},
+    {"del",delCommand,-2,0,noPreloadGetKeys,1,-1,1,0,0},
     {"exists",existsCommand,2,0,NULL,1,1,1,0,0},
     {"setbit",setbitCommand,4,REDIS_CMD_DENYOOM,NULL,1,1,1,0,0},
     {"getbit",getbitCommand,3,0,NULL,1,1,1,0,0},
@@ -85,25 +85,25 @@ struct redisCommand redisCommandTable[] = {
     {"incr",incrCommand,2,REDIS_CMD_DENYOOM,NULL,1,1,1,0,0},
     {"decr",decrCommand,2,REDIS_CMD_DENYOOM,NULL,1,1,1,0,0},
     {"mget",mgetCommand,-2,0,NULL,1,-1,1,0,0},
-    {"rpush",rpushCommand,3,REDIS_CMD_DENYOOM,NULL,1,1,1,0,0},
-    {"lpush",lpushCommand,3,REDIS_CMD_DENYOOM,NULL,1,1,1,0,0},
+    {"rpush",rpushCommand,-3,REDIS_CMD_DENYOOM,NULL,1,1,1,0,0},
+    {"lpush",lpushCommand,-3,REDIS_CMD_DENYOOM,NULL,1,1,1,0,0},
     {"rpushx",rpushxCommand,3,REDIS_CMD_DENYOOM,NULL,1,1,1,0,0},
     {"lpushx",lpushxCommand,3,REDIS_CMD_DENYOOM,NULL,1,1,1,0,0},
     {"linsert",linsertCommand,5,REDIS_CMD_DENYOOM,NULL,1,1,1,0,0},
     {"rpop",rpopCommand,2,0,NULL,1,1,1,0,0},
     {"lpop",lpopCommand,2,0,NULL,1,1,1,0,0},
     {"brpop",brpopCommand,-3,0,NULL,1,1,1,0,0},
     {"brpoplpush",brpoplpushCommand,4,REDIS_CMD_DENYOOM,NULL,1,2,1,0,0},
-    {"blpop",blpopCommand,-3,0,NULL,1,1,1,0,0},
+    {"blpop",blpopCommand,-3,0,NULL,1,-2,1,0,0},
     {"llen",llenCommand,2,0,NULL,1,1,1,0,0},
     {"lindex",lindexCommand,3,0,NULL,1,1,1,0,0},
     {"lset",lsetCommand,4,REDIS_CMD_DENYOOM,NULL,1,1,1,0,0},
     {"lrange",lrangeCommand,4,0,NULL,1,1,1,0,0},
     {"ltrim",ltrimCommand,4,0,NULL,1,1,1,0,0},
     {"lrem",lremCommand,4,0,NULL,1,1,1,0,0},
     {"rpoplpush",rpoplpushCommand,3,REDIS_CMD_DENYOOM,NULL,1,2,1,0,0},
-    {"sadd",saddCommand,3,REDIS_CMD_DENYOOM,NULL,1,1,1,0,0},
-    {"srem",sremCommand,3,0,NULL,1,1,1,0,0},
+    {"sadd",saddCommand,-3,REDIS_CMD_DENYOOM,NULL,1,1,1,0,0},
+    {"srem",sremCommand,-3,0,NULL,1,1,1,0,0},
     {"smove",smoveCommand,4,0,NULL,1,2,1,0,0},
     {"sismember",sismemberCommand,3,0,NULL,1,1,1,0,0},
     {"scard",scardCommand,2,0,NULL,1,1,1,0,0},
@@ -121,8 +121,8 @@ struct redisCommand redisCommandTable[] = {
     {"zrem",zremCommand,3,0,NULL,1,1,1,0,0},
     {"zremrangebyscore",zremrangebyscoreCommand,4,0,NULL,1,1,1,0,0},
     {"zremrangebyrank",zremrangebyrankCommand,4,0,NULL,1,1,1,0,0},
-    {"zunionstore",zunionstoreCommand,-4,REDIS_CMD_DENYOOM,zunionInterBlockClientOnSwappedKeys,0,0,0,0,0},
-    {"zinterstore",zinterstoreCommand,-4,REDIS_CMD_DENYOOM,zunionInterBlockClientOnSwappedKeys,0,0,0,0,0},
+    {"zunionstore",zunionstoreCommand,-4,REDIS_CMD_DENYOOM,zunionInterGetKeys,0,0,0,0,0},
+    {"zinterstore",zinterstoreCommand,-4,REDIS_CMD_DENYOOM,zunionInterGetKeys,0,0,0,0,0},
     {"zrange",zrangeCommand,-4,0,NULL,1,1,1,0,0},
     {"zrangebyscore",zrangebyscoreCommand,-4,0,NULL,1,1,1,0,0},
     {"zrevrangebyscore",zrevrangebyscoreCommand,-4,0,NULL,1,1,1,0,0},
@@ -138,7 +138,7 @@ struct redisCommand redisCommandTable[] = {
     {"hmset",hmsetCommand,-4,REDIS_CMD_DENYOOM,NULL,1,1,1,0,0},
     {"hmget",hmgetCommand,-3,0,NULL,1,1,1,0,0},
     {"hincrby",hincrbyCommand,4,REDIS_CMD_DENYOOM,NULL,1,1,1,0,0},
-    {"hdel",hdelCommand,3,0,NULL,1,1,1,0,0},
+    {"hdel",hdelCommand,-3,0,NULL,1,1,1,0,0},
     {"hlen",hlenCommand,2,0,NULL,1,1,1,0,0},
     {"hkeys",hkeysCommand,2,0,NULL,1,1,1,0,0},
     {"hvals",hvalsCommand,2,0,NULL,1,1,1,0,0},
@@ -152,10 +152,10 @@ struct redisCommand redisCommandTable[] = {
     {"randomkey",randomkeyCommand,1,0,NULL,0,0,0,0,0},
     {"select",selectCommand,2,0,NULL,0,0,0,0,0},
     {"move",moveCommand,3,0,NULL,1,1,1,0,0},
-    {"rename",renameCommand,3,0,NULL,1,1,1,0,0},
-    {"renamenx",renamenxCommand,3,0,NULL,1,1,1,0,0},
-    {"expire",expireCommand,3,0,NULL,0,0,0,0,0},
-    {"expireat",expireatCommand,3,0,NULL,0,0,0,0,0},
+    {"rename",renameCommand,3,0,renameGetKeys,1,2,1,0,0},
+    {"renamenx",renamenxCommand,3,0,renameGetKeys,1,2,1,0,0},
+    {"expire",expireCommand,3,0,NULL,1,1,1,0,0},
+    {"expireat",expireatCommand,3,0,NULL,1,1,1,0,0},
     {"keys",keysCommand,2,0,NULL,0,0,0,0,0},
     {"dbsize",dbsizeCommand,1,0,NULL,0,0,0,0,0},
     {"auth",authCommand,2,0,NULL,0,0,0,0,0},
@@ -168,7 +168,7 @@ struct redisCommand redisCommandTable[] = {
     {"lastsave",lastsaveCommand,1,0,NULL,0,0,0,0,0},
     {"type",typeCommand,2,0,NULL,1,1,1,0,0},
     {"multi",multiCommand,1,0,NULL,0,0,0,0,0},
-    {"exec",execCommand,1,REDIS_CMD_DENYOOM,execBlockClientOnSwappedKeys,0,0,0,0,0},
+    {"exec",execCommand,1,REDIS_CMD_DENYOOM,NULL,0,0,0,0,0},
     {"discard",discardCommand,1,0,NULL,0,0,0,0,0},
     {"sync",syncCommand,1,0,NULL,0,0,0,0,0},
     {"flushdb",flushdbCommand,1,0,NULL,0,0,0,0,0},
@@ -186,8 +186,14 @@ struct redisCommand redisCommandTable[] = {
     {"psubscribe",psubscribeCommand,-2,0,NULL,0,0,0,0,0},
     {"punsubscribe",punsubscribeCommand,-1,0,NULL,0,0,0,0,0},
     {"publish",publishCommand,3,REDIS_CMD_FORCE_REPLICATION,NULL,0,0,0,0,0},
-    {"watch",watchCommand,-2,0,NULL,0,0,0,0,0},
-    {"unwatch",unwatchCommand,1,0,NULL,0,0,0,0,0}
+    {"watch",watchCommand,-2,0,noPreloadGetKeys,1,-1,1,0,0},
+    {"unwatch",unwatchCommand,1,0,NULL,0,0,0,0,0},
+    {"cluster",clusterCommand,-2,0,NULL,0,0,0,0,0},
+    {"restore",restoreCommand,4,0,NULL,0,0,0,0,0},
+    {"migrate",migrateCommand,6,0,NULL,0,0,0,0,0},
+    {"dump",dumpCommand,2,0,NULL,0,0,0,0,0},
+    {"object",objectCommand,-2,0,NULL,0,0,0,0,0},
+    {"client",clientCommand,-2,0,NULL,0,0,0,0,0}
 };
 
 /*============================ Utility functions ============================ */
@@ -200,14 +206,20 @@ void redisLogRaw(int level, const char *msg) {
     time_t now = time(NULL);
     FILE *fp;
     char buf[64];
+    int rawmode = (level & REDIS_LOG_RAW);
 
+    level &= 0xff; /* clear flags */
     if (level < server.verbosity) return;
 
     fp = (server.logfile == NULL) ? stdout : fopen(server.logfile,"a");
     if (!fp) return;
 
-    strftime(buf,sizeof(buf),"%d %b %H:%M:%S",localtime(&now));
-    fprintf(fp,"[%d] %s %c %s\n",(int)getpid(),buf,c[level],msg);
+    if (rawmode) {
+        fprintf(fp,"%s",msg);
+    } else {
+        strftime(buf,sizeof(buf),"%d %b %H:%M:%S",localtime(&now));
+        fprintf(fp,"[%d] %s %c %s\n",(int)getpid(),buf,c[level],msg);
+    }
     fflush(fp);
 
     if (server.logfile) fclose(fp);
@@ -222,7 +234,7 @@ void redisLog(int level, const char *fmt, ...) {
     va_list ap;
     char msg[REDIS_MAX_LOGMSG_LEN];
 
-    if (level < server.verbosity) return;
+    if ((level&0xff) < server.verbosity) return;
 
     va_start(ap, fmt);
     vsnprintf(msg, sizeof(msg), fmt, ap);
@@ -440,6 +452,17 @@ dictType keylistDictType = {
     dictListDestructor          /* val destructor */
 };
 
+/* Cluster nodes hash table, mapping nodes addresses 1.2.3.4:6379 to
+ * clusterNode structures. */
+dictType clusterNodesDictType = {
+    dictSdsHash,                /* hash function */
+    NULL,                       /* key dup */
+    NULL,                       /* val dup */
+    dictSdsKeyCompare,          /* key compare */
+    dictSdsDestructor,          /* key destructor */
+    NULL                        /* val destructor */
+};
+
 int htNeedsResize(dict *dict) {
     long long size, used;
 
@@ -563,6 +586,10 @@ int serverCron(struct aeEventLoop *eventLoop, long long id, void *clientData) {
      */
     updateLRUClock();
 
+    /* Record the max memory used since the server was started. */
+    if (zmalloc_used_memory() > server.stat_peak_memory)
+        server.stat_peak_memory = zmalloc_used_memory();
+
     /* We received a SIGTERM, shutting down here in a safe way, as it is
      * not ok doing so inside the signal handler. */
     if (server.shutdown_asap) {
@@ -669,6 +696,9 @@ int serverCron(struct aeEventLoop *eventLoop, long long id, void *clientData) {
      * to detect transfer failures. */
     if (!(loops % 10)) replicationCron();
 
+    /* Run other sub-systems specific cron jobs */
+    if (server.cluster_enabled && !(loops % 10)) clusterCron();
+
     server.cronloops++;
     return 100;
 }
@@ -821,8 +851,12 @@ void initServerConfig() {
     server.list_max_ziplist_entries = REDIS_LIST_MAX_ZIPLIST_ENTRIES;
     server.list_max_ziplist_value = REDIS_LIST_MAX_ZIPLIST_VALUE;
     server.set_max_intset_entries = REDIS_SET_MAX_INTSET_ENTRIES;
+    server.zset_max_ziplist_entries = REDIS_ZSET_MAX_ZIPLIST_ENTRIES;
+    server.zset_max_ziplist_value = REDIS_ZSET_MAX_ZIPLIST_VALUE;
     server.shutdown_asap = 0;
     server.cache_flush_delay = 0;
+    server.cluster_enabled = 0;
+    server.cluster.configfile = zstrdup("nodes.conf");
 
     updateLRUClock();
     resetServerSaveParams();
@@ -928,6 +962,7 @@ void initServer() {
     server.stat_starttime = time(NULL);
     server.stat_keyspace_misses = 0;
     server.stat_keyspace_hits = 0;
+    server.stat_peak_memory = 0;
     server.unixtime = time(NULL);
     aeCreateTimeEvent(server.el, 1, serverCron, NULL, NULL);
     if (server.ipfd > 0 && aeCreateFileEvent(server.el,server.ipfd,AE_READABLE,
@@ -945,6 +980,7 @@ void initServer() {
     }
 
     if (server.ds_enabled) dsInit();
+    if (server.cluster_enabled) clusterInit();
     srand(time(NULL)^getpid());
 }
 
@@ -1051,6 +1087,29 @@ int processCommand(redisClient *c) {
         return REDIS_OK;
     }
 
+    /* If cluster is enabled, redirect here */
+    if (server.cluster_enabled &&
+                !(cmd->getkeys_proc == NULL && cmd->firstkey == 0)) {
+        int hashslot;
+
+        if (server.cluster.state != REDIS_CLUSTER_OK) {
+            addReplyError(c,"The cluster is down. Check with CLUSTER INFO for more information");
+            return REDIS_OK;
+        } else {
+            int ask;
+            clusterNode *n = getNodeByQuery(c,cmd,c->argv,c->argc,&hashslot,&ask);
+            if (n == NULL) {
+                addReplyError(c,"Multi keys request invalid in cluster");
+                return REDIS_OK;
+            } else if (n != server.cluster.myself) {
+                addReplySds(c,sdscatprintf(sdsempty(),
+                    "-%s %d %s:%d\r\n", ask ? "ASK" : "MOVED",
+                    hashslot,n->ip,n->port));
+                return REDIS_OK;
+            }
+        }
+    }
+
     /* Handle the maxmemory directive.
      *
      * First we try to free some memory if possible (if there are volatile
@@ -1189,7 +1248,6 @@ sds genRedisInfoString(char *section) {
     sds info = sdsempty();
     time_t uptime = time(NULL)-server.stat_starttime;
     int j, numcommands;
-    char hmem[64];
     struct rusage self_ru, c_ru;
     unsigned long lol, bib;
     int allsections = 0, defsections = 0;
@@ -1203,7 +1261,6 @@ sds genRedisInfoString(char *section) {
     getrusage(RUSAGE_SELF, &self_ru);
     getrusage(RUSAGE_CHILDREN, &c_ru);
     getClientsMaxBuffers(&lol,&bib);
-    bytesToHuman(hmem,zmalloc_used_memory());
 
     /* Server */
     if (allsections || defsections || !strcasecmp(section,"server")) {
@@ -1248,23 +1305,28 @@ sds genRedisInfoString(char *section) {
 
     /* Memory */
     if (allsections || defsections || !strcasecmp(section,"memory")) {
+        char hmem[64];
+        char peak_hmem[64];
+
+        bytesToHuman(hmem,zmalloc_used_memory());
+        bytesToHuman(peak_hmem,server.stat_peak_memory);
         if (sections++) info = sdscat(info,"\r\n");
         info = sdscatprintf(info,
             "# Memory\r\n"
             "used_memory:%zu\r\n"
             "used_memory_human:%s\r\n"
             "used_memory_rss:%zu\r\n"
+            "used_memory_peak:%zu\r\n"
+            "used_memory_peak_human:%s\r\n"
             "mem_fragmentation_ratio:%.2f\r\n"
-            "use_tcmalloc:%d\r\n",
+            "mem_allocator:%s\r\n",
             zmalloc_used_memory(),
             hmem,
             zmalloc_get_rss(),
+            server.stat_peak_memory,
+            peak_hmem,
             zmalloc_get_fragmentation_ratio(),
-    #ifdef USE_TCMALLOC
-            1
-    #else
-            0
-    #endif
+            REDIS_MALLOC
             );
     }
 
@@ -1455,6 +1517,15 @@ sds genRedisInfoString(char *section) {
         }
     }
 
+    /* Clusetr */
+    if (allsections || defsections || !strcasecmp(section,"cluster")) {
+        if (sections++) info = sdscat(info,"\r\n");
+        info = sdscatprintf(info,
+        "# Cluster\r\n"
+        "cluster_enabled:%d\r\n",
+        server.cluster_enabled);
+    }
+
     /* Key space */
     if (allsections || defsections || !strcasecmp(section,"keyspace")) {
         if (sections++) info = sdscat(info,"\r\n");
@@ -1663,6 +1734,23 @@ void usage() {
     exit(1);
 }
 
+void redisAsciiArt(void) {
+#include "asciilogo.h"
+    char *buf = zmalloc(1024*16);
+
+    snprintf(buf,1024*16,ascii_logo,
+        REDIS_VERSION,
+        redisGitSHA1(),
+        strtol(redisGitDirty(),NULL,10) > 0,
+        (sizeof(long) == 8) ? "64" : "32",
+        server.cluster_enabled ? "cluster" : "stand alone",
+        server.port,
+        (long) getpid()
+    );
+    redisLogRaw(REDIS_NOTICE|REDIS_LOG_RAW,buf);
+    zfree(buf);
+}
+
 int main(int argc, char **argv) {
     long long start;
 
@@ -1681,6 +1769,7 @@ int main(int argc, char **argv) {
     if (server.daemonize) daemonize();
     initServer();
     if (server.daemonize) createPidFile();
+    redisAsciiArt();
     redisLog(REDIS_NOTICE,"Server started, Redis version " REDIS_VERSION);
 #ifdef __linux__
     linuxOvercommitMemoryWarning();