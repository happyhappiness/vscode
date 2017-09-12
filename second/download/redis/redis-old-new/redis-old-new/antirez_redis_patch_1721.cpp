@@ -69,125 +69,125 @@ double R_Zero, R_PosInf, R_NegInf, R_Nan;
 struct redisServer server; /* server global state */
 struct redisCommand *commandTable;
 struct redisCommand readonlyCommandTable[] = {
-    {"get",getCommand,2,0,NULL,1,1,1,0},
-    {"set",setCommand,3,REDIS_CMD_DENYOOM,NULL,0,0,0,0},
-    {"setnx",setnxCommand,3,REDIS_CMD_DENYOOM,NULL,0,0,0,0},
-    {"setex",setexCommand,4,REDIS_CMD_DENYOOM,NULL,0,0,0,0},
-    {"append",appendCommand,3,REDIS_CMD_DENYOOM,NULL,1,1,1,0},
-    {"strlen",strlenCommand,2,0,NULL,1,1,1,0},
-    {"del",delCommand,-2,0,NULL,0,0,0,0},
-    {"exists",existsCommand,2,0,NULL,1,1,1,0},
-    {"setbit",setbitCommand,4,REDIS_CMD_DENYOOM,NULL,1,1,1,0},
-    {"getbit",getbitCommand,3,0,NULL,1,1,1,0},
-    {"setrange",setrangeCommand,4,REDIS_CMD_DENYOOM,NULL,1,1,1,0},
-    {"getrange",getrangeCommand,4,0,NULL,1,1,1,0},
-    {"substr",getrangeCommand,4,0,NULL,1,1,1,0},
-    {"incr",incrCommand,2,REDIS_CMD_DENYOOM,NULL,1,1,1,0},
-    {"decr",decrCommand,2,REDIS_CMD_DENYOOM,NULL,1,1,1,0},
-    {"mget",mgetCommand,-2,0,NULL,1,-1,1,0},
-    {"rpush",rpushCommand,3,REDIS_CMD_DENYOOM,NULL,1,1,1,0},
-    {"lpush",lpushCommand,3,REDIS_CMD_DENYOOM,NULL,1,1,1,0},
-    {"rpushx",rpushxCommand,3,REDIS_CMD_DENYOOM,NULL,1,1,1,0},
-    {"lpushx",lpushxCommand,3,REDIS_CMD_DENYOOM,NULL,1,1,1,0},
-    {"linsert",linsertCommand,5,REDIS_CMD_DENYOOM,NULL,1,1,1,0},
-    {"rpop",rpopCommand,2,0,NULL,1,1,1,0},
-    {"lpop",lpopCommand,2,0,NULL,1,1,1,0},
-    {"brpop",brpopCommand,-3,0,NULL,1,1,1,0},
-    {"brpoplpush",brpoplpushCommand,4,REDIS_CMD_DENYOOM,NULL,1,2,1,0},
-    {"blpop",blpopCommand,-3,0,NULL,1,1,1,0},
-    {"llen",llenCommand,2,0,NULL,1,1,1,0},
-    {"lindex",lindexCommand,3,0,NULL,1,1,1,0},
-    {"lset",lsetCommand,4,REDIS_CMD_DENYOOM,NULL,1,1,1,0},
-    {"lrange",lrangeCommand,4,0,NULL,1,1,1,0},
-    {"ltrim",ltrimCommand,4,0,NULL,1,1,1,0},
-    {"lrem",lremCommand,4,0,NULL,1,1,1,0},
-    {"rpoplpush",rpoplpushCommand,3,REDIS_CMD_DENYOOM,NULL,1,2,1,0},
-    {"sadd",saddCommand,3,REDIS_CMD_DENYOOM,NULL,1,1,1,0},
-    {"srem",sremCommand,3,0,NULL,1,1,1,0},
-    {"smove",smoveCommand,4,0,NULL,1,2,1,0},
-    {"sismember",sismemberCommand,3,0,NULL,1,1,1,0},
-    {"scard",scardCommand,2,0,NULL,1,1,1,0},
-    {"spop",spopCommand,2,0,NULL,1,1,1,0},
-    {"srandmember",srandmemberCommand,2,0,NULL,1,1,1,0},
-    {"sinter",sinterCommand,-2,REDIS_CMD_DENYOOM,NULL,1,-1,1,0},
-    {"sinterstore",sinterstoreCommand,-3,REDIS_CMD_DENYOOM,NULL,2,-1,1,0},
-    {"sunion",sunionCommand,-2,REDIS_CMD_DENYOOM,NULL,1,-1,1,0},
-    {"sunionstore",sunionstoreCommand,-3,REDIS_CMD_DENYOOM,NULL,2,-1,1,0},
-    {"sdiff",sdiffCommand,-2,REDIS_CMD_DENYOOM,NULL,1,-1,1,0},
-    {"sdiffstore",sdiffstoreCommand,-3,REDIS_CMD_DENYOOM,NULL,2,-1,1,0},
-    {"smembers",sinterCommand,2,0,NULL,1,1,1,0},
-    {"zadd",zaddCommand,4,REDIS_CMD_DENYOOM,NULL,1,1,1,0},
-    {"zincrby",zincrbyCommand,4,REDIS_CMD_DENYOOM,NULL,1,1,1,0},
-    {"zrem",zremCommand,3,0,NULL,1,1,1,0},
-    {"zremrangebyscore",zremrangebyscoreCommand,4,0,NULL,1,1,1,0},
-    {"zremrangebyrank",zremrangebyrankCommand,4,0,NULL,1,1,1,0},
-    {"zunionstore",zunionstoreCommand,-4,REDIS_CMD_DENYOOM,zunionInterBlockClientOnSwappedKeys,0,0,0,0},
-    {"zinterstore",zinterstoreCommand,-4,REDIS_CMD_DENYOOM,zunionInterBlockClientOnSwappedKeys,0,0,0,0},
-    {"zrange",zrangeCommand,-4,0,NULL,1,1,1,0},
-    {"zrangebyscore",zrangebyscoreCommand,-4,0,NULL,1,1,1,0},
-    {"zrevrangebyscore",zrevrangebyscoreCommand,-4,0,NULL,1,1,1,0},
-    {"zcount",zcountCommand,4,0,NULL,1,1,1,0},
-    {"zrevrange",zrevrangeCommand,-4,0,NULL,1,1,1,0},
-    {"zcard",zcardCommand,2,0,NULL,1,1,1,0},
-    {"zscore",zscoreCommand,3,0,NULL,1,1,1,0},
-    {"zrank",zrankCommand,3,0,NULL,1,1,1,0},
-    {"zrevrank",zrevrankCommand,3,0,NULL,1,1,1,0},
-    {"hset",hsetCommand,4,REDIS_CMD_DENYOOM,NULL,1,1,1,0},
-    {"hsetnx",hsetnxCommand,4,REDIS_CMD_DENYOOM,NULL,1,1,1,0},
-    {"hget",hgetCommand,3,0,NULL,1,1,1,0},
-    {"hmset",hmsetCommand,-4,REDIS_CMD_DENYOOM,NULL,1,1,1,0},
-    {"hmget",hmgetCommand,-3,0,NULL,1,1,1,0},
-    {"hincrby",hincrbyCommand,4,REDIS_CMD_DENYOOM,NULL,1,1,1,0},
-    {"hdel",hdelCommand,3,0,NULL,1,1,1,0},
-    {"hlen",hlenCommand,2,0,NULL,1,1,1,0},
-    {"hkeys",hkeysCommand,2,0,NULL,1,1,1,0},
-    {"hvals",hvalsCommand,2,0,NULL,1,1,1,0},
-    {"hgetall",hgetallCommand,2,0,NULL,1,1,1,0},
-    {"hexists",hexistsCommand,3,0,NULL,1,1,1,0},
-    {"incrby",incrbyCommand,3,REDIS_CMD_DENYOOM,NULL,1,1,1,0},
-    {"decrby",decrbyCommand,3,REDIS_CMD_DENYOOM,NULL,1,1,1,0},
-    {"getset",getsetCommand,3,REDIS_CMD_DENYOOM,NULL,1,1,1,0},
-    {"mset",msetCommand,-3,REDIS_CMD_DENYOOM,NULL,1,-1,2,0},
-    {"msetnx",msetnxCommand,-3,REDIS_CMD_DENYOOM,NULL,1,-1,2,0},
-    {"randomkey",randomkeyCommand,1,0,NULL,0,0,0,0},
-    {"select",selectCommand,2,0,NULL,0,0,0,0},
-    {"move",moveCommand,3,0,NULL,1,1,1,0},
-    {"rename",renameCommand,3,0,NULL,1,1,1,0},
-    {"renamenx",renamenxCommand,3,0,NULL,1,1,1,0},
-    {"expire",expireCommand,3,0,NULL,0,0,0,0},
-    {"expireat",expireatCommand,3,0,NULL,0,0,0,0},
-    {"keys",keysCommand,2,0,NULL,0,0,0,0},
-    {"dbsize",dbsizeCommand,1,0,NULL,0,0,0,0},
-    {"auth",authCommand,2,0,NULL,0,0,0,0},
-    {"ping",pingCommand,1,0,NULL,0,0,0,0},
-    {"echo",echoCommand,2,0,NULL,0,0,0,0},
-    {"save",saveCommand,1,0,NULL,0,0,0,0},
-    {"bgsave",bgsaveCommand,1,0,NULL,0,0,0,0},
-    {"bgrewriteaof",bgrewriteaofCommand,1,0,NULL,0,0,0,0},
-    {"shutdown",shutdownCommand,1,0,NULL,0,0,0,0},
-    {"lastsave",lastsaveCommand,1,0,NULL,0,0,0,0},
-    {"type",typeCommand,2,0,NULL,1,1,1,0},
-    {"multi",multiCommand,1,0,NULL,0,0,0,0},
-    {"exec",execCommand,1,REDIS_CMD_DENYOOM,execBlockClientOnSwappedKeys,0,0,0,0},
-    {"discard",discardCommand,1,0,NULL,0,0,0,0},
-    {"sync",syncCommand,1,0,NULL,0,0,0,0},
-    {"flushdb",flushdbCommand,1,0,NULL,0,0,0,0},
-    {"flushall",flushallCommand,1,0,NULL,0,0,0,0},
-    {"sort",sortCommand,-2,REDIS_CMD_DENYOOM,NULL,1,1,1,0},
-    {"info",infoCommand,-1,0,NULL,0,0,0,0},
-    {"monitor",monitorCommand,1,0,NULL,0,0,0,0},
-    {"ttl",ttlCommand,2,0,NULL,1,1,1,0},
-    {"persist",persistCommand,2,0,NULL,1,1,1,0},
-    {"slaveof",slaveofCommand,3,0,NULL,0,0,0,0},
-    {"debug",debugCommand,-2,0,NULL,0,0,0,0},
-    {"config",configCommand,-2,0,NULL,0,0,0,0},
-    {"subscribe",subscribeCommand,-2,0,NULL,0,0,0,0},
-    {"unsubscribe",unsubscribeCommand,-1,0,NULL,0,0,0,0},
-    {"psubscribe",psubscribeCommand,-2,0,NULL,0,0,0,0},
-    {"punsubscribe",punsubscribeCommand,-1,0,NULL,0,0,0,0},
-    {"publish",publishCommand,3,REDIS_CMD_FORCE_REPLICATION,NULL,0,0,0,0},
-    {"watch",watchCommand,-2,0,NULL,0,0,0,0},
-    {"unwatch",unwatchCommand,1,0,NULL,0,0,0,0}
+    {"get",getCommand,2,0,NULL,1,1,1,0,0},
+    {"set",setCommand,3,REDIS_CMD_DENYOOM,NULL,0,0,0,0,0},
+    {"setnx",setnxCommand,3,REDIS_CMD_DENYOOM,NULL,0,0,0,0,0},
+    {"setex",setexCommand,4,REDIS_CMD_DENYOOM,NULL,0,0,0,0,0},
+    {"append",appendCommand,3,REDIS_CMD_DENYOOM,NULL,1,1,1,0,0},
+    {"strlen",strlenCommand,2,0,NULL,1,1,1,0,0},
+    {"del",delCommand,-2,0,NULL,0,0,0,0,0},
+    {"exists",existsCommand,2,0,NULL,1,1,1,0,0},
+    {"setbit",setbitCommand,4,REDIS_CMD_DENYOOM,NULL,1,1,1,0,0},
+    {"getbit",getbitCommand,3,0,NULL,1,1,1,0,0},
+    {"setrange",setrangeCommand,4,REDIS_CMD_DENYOOM,NULL,1,1,1,0,0},
+    {"getrange",getrangeCommand,4,0,NULL,1,1,1,0,0},
+    {"substr",getrangeCommand,4,0,NULL,1,1,1,0,0},
+    {"incr",incrCommand,2,REDIS_CMD_DENYOOM,NULL,1,1,1,0,0},
+    {"decr",decrCommand,2,REDIS_CMD_DENYOOM,NULL,1,1,1,0,0},
+    {"mget",mgetCommand,-2,0,NULL,1,-1,1,0,0},
+    {"rpush",rpushCommand,3,REDIS_CMD_DENYOOM,NULL,1,1,1,0,0},
+    {"lpush",lpushCommand,3,REDIS_CMD_DENYOOM,NULL,1,1,1,0,0},
+    {"rpushx",rpushxCommand,3,REDIS_CMD_DENYOOM,NULL,1,1,1,0,0},
+    {"lpushx",lpushxCommand,3,REDIS_CMD_DENYOOM,NULL,1,1,1,0,0},
+    {"linsert",linsertCommand,5,REDIS_CMD_DENYOOM,NULL,1,1,1,0,0},
+    {"rpop",rpopCommand,2,0,NULL,1,1,1,0,0},
+    {"lpop",lpopCommand,2,0,NULL,1,1,1,0,0},
+    {"brpop",brpopCommand,-3,0,NULL,1,1,1,0,0},
+    {"brpoplpush",brpoplpushCommand,4,REDIS_CMD_DENYOOM,NULL,1,2,1,0,0},
+    {"blpop",blpopCommand,-3,0,NULL,1,1,1,0,0},
+    {"llen",llenCommand,2,0,NULL,1,1,1,0,0},
+    {"lindex",lindexCommand,3,0,NULL,1,1,1,0,0},
+    {"lset",lsetCommand,4,REDIS_CMD_DENYOOM,NULL,1,1,1,0,0},
+    {"lrange",lrangeCommand,4,0,NULL,1,1,1,0,0},
+    {"ltrim",ltrimCommand,4,0,NULL,1,1,1,0,0},
+    {"lrem",lremCommand,4,0,NULL,1,1,1,0,0},
+    {"rpoplpush",rpoplpushCommand,3,REDIS_CMD_DENYOOM,NULL,1,2,1,0,0},
+    {"sadd",saddCommand,3,REDIS_CMD_DENYOOM,NULL,1,1,1,0,0},
+    {"srem",sremCommand,3,0,NULL,1,1,1,0,0},
+    {"smove",smoveCommand,4,0,NULL,1,2,1,0,0},
+    {"sismember",sismemberCommand,3,0,NULL,1,1,1,0,0},
+    {"scard",scardCommand,2,0,NULL,1,1,1,0,0},
+    {"spop",spopCommand,2,0,NULL,1,1,1,0,0},
+    {"srandmember",srandmemberCommand,2,0,NULL,1,1,1,0,0},
+    {"sinter",sinterCommand,-2,REDIS_CMD_DENYOOM,NULL,1,-1,1,0,0},
+    {"sinterstore",sinterstoreCommand,-3,REDIS_CMD_DENYOOM,NULL,2,-1,1,0,0},
+    {"sunion",sunionCommand,-2,REDIS_CMD_DENYOOM,NULL,1,-1,1,0,0},
+    {"sunionstore",sunionstoreCommand,-3,REDIS_CMD_DENYOOM,NULL,2,-1,1,0,0},
+    {"sdiff",sdiffCommand,-2,REDIS_CMD_DENYOOM,NULL,1,-1,1,0,0},
+    {"sdiffstore",sdiffstoreCommand,-3,REDIS_CMD_DENYOOM,NULL,2,-1,1,0,0},
+    {"smembers",sinterCommand,2,0,NULL,1,1,1,0,0},
+    {"zadd",zaddCommand,4,REDIS_CMD_DENYOOM,NULL,1,1,1,0,0},
+    {"zincrby",zincrbyCommand,4,REDIS_CMD_DENYOOM,NULL,1,1,1,0,0},
+    {"zrem",zremCommand,3,0,NULL,1,1,1,0,0},
+    {"zremrangebyscore",zremrangebyscoreCommand,4,0,NULL,1,1,1,0,0},
+    {"zremrangebyrank",zremrangebyrankCommand,4,0,NULL,1,1,1,0,0},
+    {"zunionstore",zunionstoreCommand,-4,REDIS_CMD_DENYOOM,zunionInterBlockClientOnSwappedKeys,0,0,0,0,0},
+    {"zinterstore",zinterstoreCommand,-4,REDIS_CMD_DENYOOM,zunionInterBlockClientOnSwappedKeys,0,0,0,0,0},
+    {"zrange",zrangeCommand,-4,0,NULL,1,1,1,0,0},
+    {"zrangebyscore",zrangebyscoreCommand,-4,0,NULL,1,1,1,0,0},
+    {"zrevrangebyscore",zrevrangebyscoreCommand,-4,0,NULL,1,1,1,0,0},
+    {"zcount",zcountCommand,4,0,NULL,1,1,1,0,0},
+    {"zrevrange",zrevrangeCommand,-4,0,NULL,1,1,1,0,0},
+    {"zcard",zcardCommand,2,0,NULL,1,1,1,0,0},
+    {"zscore",zscoreCommand,3,0,NULL,1,1,1,0,0},
+    {"zrank",zrankCommand,3,0,NULL,1,1,1,0,0},
+    {"zrevrank",zrevrankCommand,3,0,NULL,1,1,1,0,0},
+    {"hset",hsetCommand,4,REDIS_CMD_DENYOOM,NULL,1,1,1,0,0},
+    {"hsetnx",hsetnxCommand,4,REDIS_CMD_DENYOOM,NULL,1,1,1,0,0},
+    {"hget",hgetCommand,3,0,NULL,1,1,1,0,0},
+    {"hmset",hmsetCommand,-4,REDIS_CMD_DENYOOM,NULL,1,1,1,0,0},
+    {"hmget",hmgetCommand,-3,0,NULL,1,1,1,0,0},
+    {"hincrby",hincrbyCommand,4,REDIS_CMD_DENYOOM,NULL,1,1,1,0,0},
+    {"hdel",hdelCommand,3,0,NULL,1,1,1,0,0},
+    {"hlen",hlenCommand,2,0,NULL,1,1,1,0,0},
+    {"hkeys",hkeysCommand,2,0,NULL,1,1,1,0,0},
+    {"hvals",hvalsCommand,2,0,NULL,1,1,1,0,0},
+    {"hgetall",hgetallCommand,2,0,NULL,1,1,1,0,0},
+    {"hexists",hexistsCommand,3,0,NULL,1,1,1,0,0},
+    {"incrby",incrbyCommand,3,REDIS_CMD_DENYOOM,NULL,1,1,1,0,0},
+    {"decrby",decrbyCommand,3,REDIS_CMD_DENYOOM,NULL,1,1,1,0,0},
+    {"getset",getsetCommand,3,REDIS_CMD_DENYOOM,NULL,1,1,1,0,0},
+    {"mset",msetCommand,-3,REDIS_CMD_DENYOOM,NULL,1,-1,2,0,0},
+    {"msetnx",msetnxCommand,-3,REDIS_CMD_DENYOOM,NULL,1,-1,2,0,0},
+    {"randomkey",randomkeyCommand,1,0,NULL,0,0,0,0,0},
+    {"select",selectCommand,2,0,NULL,0,0,0,0,0},
+    {"move",moveCommand,3,0,NULL,1,1,1,0,0},
+    {"rename",renameCommand,3,0,NULL,1,1,1,0,0},
+    {"renamenx",renamenxCommand,3,0,NULL,1,1,1,0,0},
+    {"expire",expireCommand,3,0,NULL,0,0,0,0,0},
+    {"expireat",expireatCommand,3,0,NULL,0,0,0,0,0},
+    {"keys",keysCommand,2,0,NULL,0,0,0,0,0},
+    {"dbsize",dbsizeCommand,1,0,NULL,0,0,0,0,0},
+    {"auth",authCommand,2,0,NULL,0,0,0,0,0},
+    {"ping",pingCommand,1,0,NULL,0,0,0,0,0},
+    {"echo",echoCommand,2,0,NULL,0,0,0,0,0},
+    {"save",saveCommand,1,0,NULL,0,0,0,0,0},
+    {"bgsave",bgsaveCommand,1,0,NULL,0,0,0,0,0},
+    {"bgrewriteaof",bgrewriteaofCommand,1,0,NULL,0,0,0,0,0},
+    {"shutdown",shutdownCommand,1,0,NULL,0,0,0,0,0},
+    {"lastsave",lastsaveCommand,1,0,NULL,0,0,0,0,0},
+    {"type",typeCommand,2,0,NULL,1,1,1,0,0},
+    {"multi",multiCommand,1,0,NULL,0,0,0,0,0},
+    {"exec",execCommand,1,REDIS_CMD_DENYOOM,execBlockClientOnSwappedKeys,0,0,0,0,0},
+    {"discard",discardCommand,1,0,NULL,0,0,0,0,0},
+    {"sync",syncCommand,1,0,NULL,0,0,0,0,0},
+    {"flushdb",flushdbCommand,1,0,NULL,0,0,0,0,0},
+    {"flushall",flushallCommand,1,0,NULL,0,0,0,0,0},
+    {"sort",sortCommand,-2,REDIS_CMD_DENYOOM,NULL,1,1,1,0,0},
+    {"info",infoCommand,-1,0,NULL,0,0,0,0,0},
+    {"monitor",monitorCommand,1,0,NULL,0,0,0,0,0},
+    {"ttl",ttlCommand,2,0,NULL,1,1,1,0,0},
+    {"persist",persistCommand,2,0,NULL,1,1,1,0,0},
+    {"slaveof",slaveofCommand,3,0,NULL,0,0,0,0,0},
+    {"debug",debugCommand,-2,0,NULL,0,0,0,0,0},
+    {"config",configCommand,-2,0,NULL,0,0,0,0,0},
+    {"subscribe",subscribeCommand,-2,0,NULL,0,0,0,0,0},
+    {"unsubscribe",unsubscribeCommand,-1,0,NULL,0,0,0,0,0},
+    {"psubscribe",psubscribeCommand,-2,0,NULL,0,0,0,0,0},
+    {"punsubscribe",punsubscribeCommand,-1,0,NULL,0,0,0,0,0},
+    {"publish",publishCommand,3,REDIS_CMD_FORCE_REPLICATION,NULL,0,0,0,0,0},
+    {"watch",watchCommand,-2,0,NULL,0,0,0,0,0},
+    {"unwatch",unwatchCommand,1,0,NULL,0,0,0,0,0}
 };
 
 /*============================ Utility functions ============================ */
@@ -970,6 +970,7 @@ void call(redisClient *c, struct redisCommand *cmd) {
     cmd->proc(c);
     dirty = server.dirty-dirty;
     cmd->microseconds += ustime()-start;
+    cmd->calls++;
 
     if (server.appendonly && dirty)
         feedAppendOnlyFile(cmd,c->db->id,c->argv,c->argc);
@@ -1168,7 +1169,7 @@ sds genRedisInfoString(char *section) {
     
     if (section) {
         allsections = strcasecmp(section,"all") == 0;
-        allsections = strcasecmp(section,"default") == 0;
+        defsections = strcasecmp(section,"default") == 0;
     }
 
     getrusage(RUSAGE_SELF, &self_ru);
@@ -1237,7 +1238,12 @@ sds genRedisInfoString(char *section) {
             0
     #endif
             );
-        info = sdscat(info,"allocation_stats:");
+    }
+
+    /* Allocation statistics */
+    if (allsections || !strcasecmp(section,"allocstats")) {
+        if (sections++) info = sdscat(info,"\r\n");
+        info = sdscat(info, "# Allocstats\r\nallocation_stats:");
         for (j = 0; j <= ZMALLOC_MAX_ALLOC_STAT; j++) {
             size_t count = zmalloc_allocations_for_size(j);
             if (count) {
@@ -1247,6 +1253,7 @@ sds genRedisInfoString(char *section) {
                     j,count);
             }
         }
+        info = sdscat(info,"\r\n");
     }
 
     /* Persistence */
@@ -1379,11 +1386,11 @@ sds genRedisInfoString(char *section) {
             listLength(server.slaves));
     }
 
-    /* Profiling */
-    if (allsections || defsections || !strcasecmp(section,"profiling")) {
+    /* CPU */
+    if (allsections || defsections || !strcasecmp(section,"cpu")) {
         if (sections++) info = sdscat(info,"\r\n");
         info = sdscatprintf(info,
-        "# Profiling\r\n"
+        "# CPU\r\n"
         "used_cpu_sys:%.2f\r\n"
         "used_cpu_user:%.2f\r\n"
         "used_cpu_sys_childrens:%.2f\r\n"
@@ -1392,12 +1399,19 @@ sds genRedisInfoString(char *section) {
         (float)self_ru.ru_stime.tv_sec+(float)self_ru.ru_stime.tv_usec/1000000,
         (float)c_ru.ru_utime.tv_sec+(float)c_ru.ru_utime.tv_usec/1000000,
         (float)c_ru.ru_stime.tv_sec+(float)c_ru.ru_stime.tv_usec/1000000);
+    }
 
+    /* cmdtime */
+    if (allsections || !strcasecmp(section,"commandstats")) {
+        if (sections++) info = sdscat(info,"\r\n");
+        info = sdscatprintf(info, "# Commandstats\r\n");
         numcommands = sizeof(readonlyCommandTable)/sizeof(struct redisCommand);
         for (j = 0; j < numcommands; j++) {
             struct redisCommand *c = readonlyCommandTable+j;
-            info = sdscatprintf(info,"used_time_cmd_%s:%lld\r\n",
-                c->name, c->microseconds);
+
+            if (!c->microseconds) continue;
+            info = sdscatprintf(info,"cmdstat_%s:calls=%lld,usec=%lld\r\n",
+                c->name, c->calls, c->microseconds);
         }
     }
 