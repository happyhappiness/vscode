@@ -69,125 +69,125 @@ double R_Zero, R_PosInf, R_NegInf, R_Nan;
 struct redisServer server; /* server global state */
 struct redisCommand *commandTable;
 struct redisCommand readonlyCommandTable[] = {
-    {"get",getCommand,2,0,NULL,1,1,1},
-    {"set",setCommand,3,REDIS_CMD_DENYOOM,NULL,0,0,0},
-    {"setnx",setnxCommand,3,REDIS_CMD_DENYOOM,NULL,0,0,0},
-    {"setex",setexCommand,4,REDIS_CMD_DENYOOM,NULL,0,0,0},
-    {"append",appendCommand,3,REDIS_CMD_DENYOOM,NULL,1,1,1},
-    {"strlen",strlenCommand,2,0,NULL,1,1,1},
-    {"del",delCommand,-2,0,NULL,0,0,0},
-    {"exists",existsCommand,2,0,NULL,1,1,1},
-    {"setbit",setbitCommand,4,REDIS_CMD_DENYOOM,NULL,1,1,1},
-    {"getbit",getbitCommand,3,0,NULL,1,1,1},
-    {"setrange",setrangeCommand,4,REDIS_CMD_DENYOOM,NULL,1,1,1},
-    {"getrange",getrangeCommand,4,0,NULL,1,1,1},
-    {"substr",getrangeCommand,4,0,NULL,1,1,1},
-    {"incr",incrCommand,2,REDIS_CMD_DENYOOM,NULL,1,1,1},
-    {"decr",decrCommand,2,REDIS_CMD_DENYOOM,NULL,1,1,1},
-    {"mget",mgetCommand,-2,0,NULL,1,-1,1},
-    {"rpush",rpushCommand,3,REDIS_CMD_DENYOOM,NULL,1,1,1},
-    {"lpush",lpushCommand,3,REDIS_CMD_DENYOOM,NULL,1,1,1},
-    {"rpushx",rpushxCommand,3,REDIS_CMD_DENYOOM,NULL,1,1,1},
-    {"lpushx",lpushxCommand,3,REDIS_CMD_DENYOOM,NULL,1,1,1},
-    {"linsert",linsertCommand,5,REDIS_CMD_DENYOOM,NULL,1,1,1},
-    {"rpop",rpopCommand,2,0,NULL,1,1,1},
-    {"lpop",lpopCommand,2,0,NULL,1,1,1},
-    {"brpop",brpopCommand,-3,0,NULL,1,1,1},
-    {"brpoplpush",brpoplpushCommand,4,REDIS_CMD_DENYOOM,NULL,1,2,1},
-    {"blpop",blpopCommand,-3,0,NULL,1,1,1},
-    {"llen",llenCommand,2,0,NULL,1,1,1},
-    {"lindex",lindexCommand,3,0,NULL,1,1,1},
-    {"lset",lsetCommand,4,REDIS_CMD_DENYOOM,NULL,1,1,1},
-    {"lrange",lrangeCommand,4,0,NULL,1,1,1},
-    {"ltrim",ltrimCommand,4,0,NULL,1,1,1},
-    {"lrem",lremCommand,4,0,NULL,1,1,1},
-    {"rpoplpush",rpoplpushCommand,3,REDIS_CMD_DENYOOM,NULL,1,2,1},
-    {"sadd",saddCommand,3,REDIS_CMD_DENYOOM,NULL,1,1,1},
-    {"srem",sremCommand,3,0,NULL,1,1,1},
-    {"smove",smoveCommand,4,0,NULL,1,2,1},
-    {"sismember",sismemberCommand,3,0,NULL,1,1,1},
-    {"scard",scardCommand,2,0,NULL,1,1,1},
-    {"spop",spopCommand,2,0,NULL,1,1,1},
-    {"srandmember",srandmemberCommand,2,0,NULL,1,1,1},
-    {"sinter",sinterCommand,-2,REDIS_CMD_DENYOOM,NULL,1,-1,1},
-    {"sinterstore",sinterstoreCommand,-3,REDIS_CMD_DENYOOM,NULL,2,-1,1},
-    {"sunion",sunionCommand,-2,REDIS_CMD_DENYOOM,NULL,1,-1,1},
-    {"sunionstore",sunionstoreCommand,-3,REDIS_CMD_DENYOOM,NULL,2,-1,1},
-    {"sdiff",sdiffCommand,-2,REDIS_CMD_DENYOOM,NULL,1,-1,1},
-    {"sdiffstore",sdiffstoreCommand,-3,REDIS_CMD_DENYOOM,NULL,2,-1,1},
-    {"smembers",sinterCommand,2,0,NULL,1,1,1},
-    {"zadd",zaddCommand,4,REDIS_CMD_DENYOOM,NULL,1,1,1},
-    {"zincrby",zincrbyCommand,4,REDIS_CMD_DENYOOM,NULL,1,1,1},
-    {"zrem",zremCommand,3,0,NULL,1,1,1},
-    {"zremrangebyscore",zremrangebyscoreCommand,4,0,NULL,1,1,1},
-    {"zremrangebyrank",zremrangebyrankCommand,4,0,NULL,1,1,1},
-    {"zunionstore",zunionstoreCommand,-4,REDIS_CMD_DENYOOM,zunionInterBlockClientOnSwappedKeys,0,0,0},
-    {"zinterstore",zinterstoreCommand,-4,REDIS_CMD_DENYOOM,zunionInterBlockClientOnSwappedKeys,0,0,0},
-    {"zrange",zrangeCommand,-4,0,NULL,1,1,1},
-    {"zrangebyscore",zrangebyscoreCommand,-4,0,NULL,1,1,1},
-    {"zrevrangebyscore",zrevrangebyscoreCommand,-4,0,NULL,1,1,1},
-    {"zcount",zcountCommand,4,0,NULL,1,1,1},
-    {"zrevrange",zrevrangeCommand,-4,0,NULL,1,1,1},
-    {"zcard",zcardCommand,2,0,NULL,1,1,1},
-    {"zscore",zscoreCommand,3,0,NULL,1,1,1},
-    {"zrank",zrankCommand,3,0,NULL,1,1,1},
-    {"zrevrank",zrevrankCommand,3,0,NULL,1,1,1},
-    {"hset",hsetCommand,4,REDIS_CMD_DENYOOM,NULL,1,1,1},
-    {"hsetnx",hsetnxCommand,4,REDIS_CMD_DENYOOM,NULL,1,1,1},
-    {"hget",hgetCommand,3,0,NULL,1,1,1},
-    {"hmset",hmsetCommand,-4,REDIS_CMD_DENYOOM,NULL,1,1,1},
-    {"hmget",hmgetCommand,-3,0,NULL,1,1,1},
-    {"hincrby",hincrbyCommand,4,REDIS_CMD_DENYOOM,NULL,1,1,1},
-    {"hdel",hdelCommand,3,0,NULL,1,1,1},
-    {"hlen",hlenCommand,2,0,NULL,1,1,1},
-    {"hkeys",hkeysCommand,2,0,NULL,1,1,1},
-    {"hvals",hvalsCommand,2,0,NULL,1,1,1},
-    {"hgetall",hgetallCommand,2,0,NULL,1,1,1},
-    {"hexists",hexistsCommand,3,0,NULL,1,1,1},
-    {"incrby",incrbyCommand,3,REDIS_CMD_DENYOOM,NULL,1,1,1},
-    {"decrby",decrbyCommand,3,REDIS_CMD_DENYOOM,NULL,1,1,1},
-    {"getset",getsetCommand,3,REDIS_CMD_DENYOOM,NULL,1,1,1},
-    {"mset",msetCommand,-3,REDIS_CMD_DENYOOM,NULL,1,-1,2},
-    {"msetnx",msetnxCommand,-3,REDIS_CMD_DENYOOM,NULL,1,-1,2},
-    {"randomkey",randomkeyCommand,1,0,NULL,0,0,0},
-    {"select",selectCommand,2,0,NULL,0,0,0},
-    {"move",moveCommand,3,0,NULL,1,1,1},
-    {"rename",renameCommand,3,0,NULL,1,1,1},
-    {"renamenx",renamenxCommand,3,0,NULL,1,1,1},
-    {"expire",expireCommand,3,0,NULL,0,0,0},
-    {"expireat",expireatCommand,3,0,NULL,0,0,0},
-    {"keys",keysCommand,2,0,NULL,0,0,0},
-    {"dbsize",dbsizeCommand,1,0,NULL,0,0,0},
-    {"auth",authCommand,2,0,NULL,0,0,0},
-    {"ping",pingCommand,1,0,NULL,0,0,0},
-    {"echo",echoCommand,2,0,NULL,0,0,0},
-    {"save",saveCommand,1,0,NULL,0,0,0},
-    {"bgsave",bgsaveCommand,1,0,NULL,0,0,0},
-    {"bgrewriteaof",bgrewriteaofCommand,1,0,NULL,0,0,0},
-    {"shutdown",shutdownCommand,1,0,NULL,0,0,0},
-    {"lastsave",lastsaveCommand,1,0,NULL,0,0,0},
-    {"type",typeCommand,2,0,NULL,1,1,1},
-    {"multi",multiCommand,1,0,NULL,0,0,0},
-    {"exec",execCommand,1,REDIS_CMD_DENYOOM,execBlockClientOnSwappedKeys,0,0,0},
-    {"discard",discardCommand,1,0,NULL,0,0,0},
-    {"sync",syncCommand,1,0,NULL,0,0,0},
-    {"flushdb",flushdbCommand,1,0,NULL,0,0,0},
-    {"flushall",flushallCommand,1,0,NULL,0,0,0},
-    {"sort",sortCommand,-2,REDIS_CMD_DENYOOM,NULL,1,1,1},
-    {"info",infoCommand,1,0,NULL,0,0,0},
-    {"monitor",monitorCommand,1,0,NULL,0,0,0},
-    {"ttl",ttlCommand,2,0,NULL,1,1,1},
-    {"persist",persistCommand,2,0,NULL,1,1,1},
-    {"slaveof",slaveofCommand,3,0,NULL,0,0,0},
-    {"debug",debugCommand,-2,0,NULL,0,0,0},
-    {"config",configCommand,-2,0,NULL,0,0,0},
-    {"subscribe",subscribeCommand,-2,0,NULL,0,0,0},
-    {"unsubscribe",unsubscribeCommand,-1,0,NULL,0,0,0},
-    {"psubscribe",psubscribeCommand,-2,0,NULL,0,0,0},
-    {"punsubscribe",punsubscribeCommand,-1,0,NULL,0,0,0},
-    {"publish",publishCommand,3,REDIS_CMD_FORCE_REPLICATION,NULL,0,0,0},
-    {"watch",watchCommand,-2,0,NULL,0,0,0},
-    {"unwatch",unwatchCommand,1,0,NULL,0,0,0}
+    {"get",getCommand,2,0,NULL,1,1,1,0},
+    {"set",setCommand,3,REDIS_CMD_DENYOOM,NULL,0,0,0,0},
+    {"setnx",setnxCommand,3,REDIS_CMD_DENYOOM,NULL,0,0,0,0},
+    {"setex",setexCommand,4,REDIS_CMD_DENYOOM,NULL,0,0,0,0},
+    {"append",appendCommand,3,REDIS_CMD_DENYOOM,NULL,1,1,1,0},
+    {"strlen",strlenCommand,2,0,NULL,1,1,1,0},
+    {"del",delCommand,-2,0,NULL,0,0,0,0},
+    {"exists",existsCommand,2,0,NULL,1,1,1,0},
+    {"setbit",setbitCommand,4,REDIS_CMD_DENYOOM,NULL,1,1,1,0},
+    {"getbit",getbitCommand,3,0,NULL,1,1,1,0},
+    {"setrange",setrangeCommand,4,REDIS_CMD_DENYOOM,NULL,1,1,1,0},
+    {"getrange",getrangeCommand,4,0,NULL,1,1,1,0},
+    {"substr",getrangeCommand,4,0,NULL,1,1,1,0},
+    {"incr",incrCommand,2,REDIS_CMD_DENYOOM,NULL,1,1,1,0},
+    {"decr",decrCommand,2,REDIS_CMD_DENYOOM,NULL,1,1,1,0},
+    {"mget",mgetCommand,-2,0,NULL,1,-1,1,0},
+    {"rpush",rpushCommand,3,REDIS_CMD_DENYOOM,NULL,1,1,1,0},
+    {"lpush",lpushCommand,3,REDIS_CMD_DENYOOM,NULL,1,1,1,0},
+    {"rpushx",rpushxCommand,3,REDIS_CMD_DENYOOM,NULL,1,1,1,0},
+    {"lpushx",lpushxCommand,3,REDIS_CMD_DENYOOM,NULL,1,1,1,0},
+    {"linsert",linsertCommand,5,REDIS_CMD_DENYOOM,NULL,1,1,1,0},
+    {"rpop",rpopCommand,2,0,NULL,1,1,1,0},
+    {"lpop",lpopCommand,2,0,NULL,1,1,1,0},
+    {"brpop",brpopCommand,-3,0,NULL,1,1,1,0},
+    {"brpoplpush",brpoplpushCommand,4,REDIS_CMD_DENYOOM,NULL,1,2,1,0},
+    {"blpop",blpopCommand,-3,0,NULL,1,1,1,0},
+    {"llen",llenCommand,2,0,NULL,1,1,1,0},
+    {"lindex",lindexCommand,3,0,NULL,1,1,1,0},
+    {"lset",lsetCommand,4,REDIS_CMD_DENYOOM,NULL,1,1,1,0},
+    {"lrange",lrangeCommand,4,0,NULL,1,1,1,0},
+    {"ltrim",ltrimCommand,4,0,NULL,1,1,1,0},
+    {"lrem",lremCommand,4,0,NULL,1,1,1,0},
+    {"rpoplpush",rpoplpushCommand,3,REDIS_CMD_DENYOOM,NULL,1,2,1,0},
+    {"sadd",saddCommand,3,REDIS_CMD_DENYOOM,NULL,1,1,1,0},
+    {"srem",sremCommand,3,0,NULL,1,1,1,0},
+    {"smove",smoveCommand,4,0,NULL,1,2,1,0},
+    {"sismember",sismemberCommand,3,0,NULL,1,1,1,0},
+    {"scard",scardCommand,2,0,NULL,1,1,1,0},
+    {"spop",spopCommand,2,0,NULL,1,1,1,0},
+    {"srandmember",srandmemberCommand,2,0,NULL,1,1,1,0},
+    {"sinter",sinterCommand,-2,REDIS_CMD_DENYOOM,NULL,1,-1,1,0},
+    {"sinterstore",sinterstoreCommand,-3,REDIS_CMD_DENYOOM,NULL,2,-1,1,0},
+    {"sunion",sunionCommand,-2,REDIS_CMD_DENYOOM,NULL,1,-1,1,0},
+    {"sunionstore",sunionstoreCommand,-3,REDIS_CMD_DENYOOM,NULL,2,-1,1,0},
+    {"sdiff",sdiffCommand,-2,REDIS_CMD_DENYOOM,NULL,1,-1,1,0},
+    {"sdiffstore",sdiffstoreCommand,-3,REDIS_CMD_DENYOOM,NULL,2,-1,1,0},
+    {"smembers",sinterCommand,2,0,NULL,1,1,1,0},
+    {"zadd",zaddCommand,4,REDIS_CMD_DENYOOM,NULL,1,1,1,0},
+    {"zincrby",zincrbyCommand,4,REDIS_CMD_DENYOOM,NULL,1,1,1,0},
+    {"zrem",zremCommand,3,0,NULL,1,1,1,0},
+    {"zremrangebyscore",zremrangebyscoreCommand,4,0,NULL,1,1,1,0},
+    {"zremrangebyrank",zremrangebyrankCommand,4,0,NULL,1,1,1,0},
+    {"zunionstore",zunionstoreCommand,-4,REDIS_CMD_DENYOOM,zunionInterBlockClientOnSwappedKeys,0,0,0,0},
+    {"zinterstore",zinterstoreCommand,-4,REDIS_CMD_DENYOOM,zunionInterBlockClientOnSwappedKeys,0,0,0,0},
+    {"zrange",zrangeCommand,-4,0,NULL,1,1,1,0},
+    {"zrangebyscore",zrangebyscoreCommand,-4,0,NULL,1,1,1,0},
+    {"zrevrangebyscore",zrevrangebyscoreCommand,-4,0,NULL,1,1,1,0},
+    {"zcount",zcountCommand,4,0,NULL,1,1,1,0},
+    {"zrevrange",zrevrangeCommand,-4,0,NULL,1,1,1,0},
+    {"zcard",zcardCommand,2,0,NULL,1,1,1,0},
+    {"zscore",zscoreCommand,3,0,NULL,1,1,1,0},
+    {"zrank",zrankCommand,3,0,NULL,1,1,1,0},
+    {"zrevrank",zrevrankCommand,3,0,NULL,1,1,1,0},
+    {"hset",hsetCommand,4,REDIS_CMD_DENYOOM,NULL,1,1,1,0},
+    {"hsetnx",hsetnxCommand,4,REDIS_CMD_DENYOOM,NULL,1,1,1,0},
+    {"hget",hgetCommand,3,0,NULL,1,1,1,0},
+    {"hmset",hmsetCommand,-4,REDIS_CMD_DENYOOM,NULL,1,1,1,0},
+    {"hmget",hmgetCommand,-3,0,NULL,1,1,1,0},
+    {"hincrby",hincrbyCommand,4,REDIS_CMD_DENYOOM,NULL,1,1,1,0},
+    {"hdel",hdelCommand,3,0,NULL,1,1,1,0},
+    {"hlen",hlenCommand,2,0,NULL,1,1,1,0},
+    {"hkeys",hkeysCommand,2,0,NULL,1,1,1,0},
+    {"hvals",hvalsCommand,2,0,NULL,1,1,1,0},
+    {"hgetall",hgetallCommand,2,0,NULL,1,1,1,0},
+    {"hexists",hexistsCommand,3,0,NULL,1,1,1,0},
+    {"incrby",incrbyCommand,3,REDIS_CMD_DENYOOM,NULL,1,1,1,0},
+    {"decrby",decrbyCommand,3,REDIS_CMD_DENYOOM,NULL,1,1,1,0},
+    {"getset",getsetCommand,3,REDIS_CMD_DENYOOM,NULL,1,1,1,0},
+    {"mset",msetCommand,-3,REDIS_CMD_DENYOOM,NULL,1,-1,2,0},
+    {"msetnx",msetnxCommand,-3,REDIS_CMD_DENYOOM,NULL,1,-1,2,0},
+    {"randomkey",randomkeyCommand,1,0,NULL,0,0,0,0},
+    {"select",selectCommand,2,0,NULL,0,0,0,0},
+    {"move",moveCommand,3,0,NULL,1,1,1,0},
+    {"rename",renameCommand,3,0,NULL,1,1,1,0},
+    {"renamenx",renamenxCommand,3,0,NULL,1,1,1,0},
+    {"expire",expireCommand,3,0,NULL,0,0,0,0},
+    {"expireat",expireatCommand,3,0,NULL,0,0,0,0},
+    {"keys",keysCommand,2,0,NULL,0,0,0,0},
+    {"dbsize",dbsizeCommand,1,0,NULL,0,0,0,0},
+    {"auth",authCommand,2,0,NULL,0,0,0,0},
+    {"ping",pingCommand,1,0,NULL,0,0,0,0},
+    {"echo",echoCommand,2,0,NULL,0,0,0,0},
+    {"save",saveCommand,1,0,NULL,0,0,0,0},
+    {"bgsave",bgsaveCommand,1,0,NULL,0,0,0,0},
+    {"bgrewriteaof",bgrewriteaofCommand,1,0,NULL,0,0,0,0},
+    {"shutdown",shutdownCommand,1,0,NULL,0,0,0,0},
+    {"lastsave",lastsaveCommand,1,0,NULL,0,0,0,0},
+    {"type",typeCommand,2,0,NULL,1,1,1,0},
+    {"multi",multiCommand,1,0,NULL,0,0,0,0},
+    {"exec",execCommand,1,REDIS_CMD_DENYOOM,execBlockClientOnSwappedKeys,0,0,0,0},
+    {"discard",discardCommand,1,0,NULL,0,0,0,0},
+    {"sync",syncCommand,1,0,NULL,0,0,0,0},
+    {"flushdb",flushdbCommand,1,0,NULL,0,0,0,0},
+    {"flushall",flushallCommand,1,0,NULL,0,0,0,0},
+    {"sort",sortCommand,-2,REDIS_CMD_DENYOOM,NULL,1,1,1,0},
+    {"info",infoCommand,1,0,NULL,0,0,0,0},
+    {"monitor",monitorCommand,1,0,NULL,0,0,0,0},
+    {"ttl",ttlCommand,2,0,NULL,1,1,1,0},
+    {"persist",persistCommand,2,0,NULL,1,1,1,0},
+    {"slaveof",slaveofCommand,3,0,NULL,0,0,0,0},
+    {"debug",debugCommand,-2,0,NULL,0,0,0,0},
+    {"config",configCommand,-2,0,NULL,0,0,0,0},
+    {"subscribe",subscribeCommand,-2,0,NULL,0,0,0,0},
+    {"unsubscribe",unsubscribeCommand,-1,0,NULL,0,0,0,0},
+    {"psubscribe",psubscribeCommand,-2,0,NULL,0,0,0,0},
+    {"punsubscribe",punsubscribeCommand,-1,0,NULL,0,0,0,0},
+    {"publish",publishCommand,3,REDIS_CMD_FORCE_REPLICATION,NULL,0,0,0,0},
+    {"watch",watchCommand,-2,0,NULL,0,0,0,0},
+    {"unwatch",unwatchCommand,1,0,NULL,0,0,0,0}
 };
 
 /*============================ Utility functions ============================ */
@@ -230,6 +230,17 @@ void oom(const char *msg) {
     abort();
 }
 
+/* Return the UNIX time in microseconds */
+long long ustime(void) {
+    struct timeval tv;
+    long long ust;
+
+    gettimeofday(&tv, NULL);
+    ust = ((long long)tv.tv_sec)*1000000;
+    ust += tv.tv_usec;
+    return ust;
+}
+
 /*====================== Hash table type implementation  ==================== */
 
 /* This is an hash table type that uses the SDS dynamic strings libary as
@@ -953,11 +964,12 @@ struct redisCommand *lookupCommandByCString(char *s) {
 
 /* Call() is the core of Redis execution of a command */
 void call(redisClient *c, struct redisCommand *cmd) {
-    long long dirty;
+    long long dirty, start = ustime();
 
     dirty = server.dirty;
     cmd->proc(c);
     dirty = server.dirty-dirty;
+    cmd->microseconds += ustime()-start;
 
     if (server.appendonly && dirty)
         feedAppendOnlyFile(cmd,c->db->id,c->argv,c->argc);
@@ -1147,7 +1159,7 @@ void bytesToHuman(char *s, unsigned long long n) {
 sds genRedisInfoString(void) {
     sds info;
     time_t uptime = time(NULL)-server.stat_starttime;
-    int j;
+    int j, numcommands;
     char hmem[64];
     struct rusage self_ru, c_ru;
     unsigned long lol, bib;
@@ -1320,6 +1332,13 @@ sds genRedisInfoString(void) {
     }
     info = sdscat(info,"\r\n");
 
+    numcommands = sizeof(readonlyCommandTable)/sizeof(struct redisCommand);
+    for (j = 0; j < numcommands; j++) {
+        struct redisCommand *c = readonlyCommandTable+j;
+        info = sdscatprintf(info,"command_%s:microseconds:%lld\r\n",
+            c->name, c->microseconds);
+    }
+
     for (j = 0; j < server.dbnum; j++) {
         long long keys, vkeys;
 