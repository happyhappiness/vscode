@@ -69,120 +69,120 @@ double R_Zero, R_PosInf, R_NegInf, R_Nan;
 struct redisServer server; /* server global state */
 struct redisCommand *commandTable;
 struct redisCommand readonlyCommandTable[] = {
-    {"get",getCommand,2,REDIS_CMD_INLINE,NULL,1,1,1},
-    {"set",setCommand,3,REDIS_CMD_BULK|REDIS_CMD_DENYOOM,NULL,0,0,0},
-    {"setnx",setnxCommand,3,REDIS_CMD_BULK|REDIS_CMD_DENYOOM,NULL,0,0,0},
-    {"setex",setexCommand,4,REDIS_CMD_BULK|REDIS_CMD_DENYOOM,NULL,0,0,0},
-    {"append",appendCommand,3,REDIS_CMD_BULK|REDIS_CMD_DENYOOM,NULL,1,1,1},
-    {"substr",substrCommand,4,REDIS_CMD_INLINE,NULL,1,1,1},
-    {"strlen",strlenCommand,2,REDIS_CMD_INLINE,NULL,1,1,1},
-    {"del",delCommand,-2,REDIS_CMD_INLINE,NULL,0,0,0},
-    {"exists",existsCommand,2,REDIS_CMD_INLINE,NULL,1,1,1},
-    {"incr",incrCommand,2,REDIS_CMD_INLINE|REDIS_CMD_DENYOOM,NULL,1,1,1},
-    {"decr",decrCommand,2,REDIS_CMD_INLINE|REDIS_CMD_DENYOOM,NULL,1,1,1},
-    {"mget",mgetCommand,-2,REDIS_CMD_INLINE,NULL,1,-1,1},
-    {"rpush",rpushCommand,3,REDIS_CMD_BULK|REDIS_CMD_DENYOOM,NULL,1,1,1},
-    {"lpush",lpushCommand,3,REDIS_CMD_BULK|REDIS_CMD_DENYOOM,NULL,1,1,1},
-    {"rpushx",rpushxCommand,3,REDIS_CMD_BULK|REDIS_CMD_DENYOOM,NULL,1,1,1},
-    {"lpushx",lpushxCommand,3,REDIS_CMD_BULK|REDIS_CMD_DENYOOM,NULL,1,1,1},
-    {"linsert",linsertCommand,5,REDIS_CMD_BULK|REDIS_CMD_DENYOOM,NULL,1,1,1},
-    {"rpop",rpopCommand,2,REDIS_CMD_INLINE,NULL,1,1,1},
-    {"lpop",lpopCommand,2,REDIS_CMD_INLINE,NULL,1,1,1},
-    {"brpop",brpopCommand,-3,REDIS_CMD_INLINE,NULL,1,1,1},
-    {"blpop",blpopCommand,-3,REDIS_CMD_INLINE,NULL,1,1,1},
-    {"llen",llenCommand,2,REDIS_CMD_INLINE,NULL,1,1,1},
-    {"lindex",lindexCommand,3,REDIS_CMD_INLINE,NULL,1,1,1},
-    {"lset",lsetCommand,4,REDIS_CMD_BULK|REDIS_CMD_DENYOOM,NULL,1,1,1},
-    {"lrange",lrangeCommand,4,REDIS_CMD_INLINE,NULL,1,1,1},
-    {"ltrim",ltrimCommand,4,REDIS_CMD_INLINE,NULL,1,1,1},
-    {"lrem",lremCommand,4,REDIS_CMD_BULK,NULL,1,1,1},
-    {"rpoplpush",rpoplpushcommand,3,REDIS_CMD_INLINE|REDIS_CMD_DENYOOM,NULL,1,2,1},
-    {"sadd",saddCommand,3,REDIS_CMD_BULK|REDIS_CMD_DENYOOM,NULL,1,1,1},
-    {"srem",sremCommand,3,REDIS_CMD_BULK,NULL,1,1,1},
-    {"smove",smoveCommand,4,REDIS_CMD_BULK,NULL,1,2,1},
-    {"sismember",sismemberCommand,3,REDIS_CMD_BULK,NULL,1,1,1},
-    {"scard",scardCommand,2,REDIS_CMD_INLINE,NULL,1,1,1},
-    {"spop",spopCommand,2,REDIS_CMD_INLINE,NULL,1,1,1},
-    {"srandmember",srandmemberCommand,2,REDIS_CMD_INLINE,NULL,1,1,1},
-    {"sinter",sinterCommand,-2,REDIS_CMD_INLINE|REDIS_CMD_DENYOOM,NULL,1,-1,1},
-    {"sinterstore",sinterstoreCommand,-3,REDIS_CMD_INLINE|REDIS_CMD_DENYOOM,NULL,2,-1,1},
-    {"sunion",sunionCommand,-2,REDIS_CMD_INLINE|REDIS_CMD_DENYOOM,NULL,1,-1,1},
-    {"sunionstore",sunionstoreCommand,-3,REDIS_CMD_INLINE|REDIS_CMD_DENYOOM,NULL,2,-1,1},
-    {"sdiff",sdiffCommand,-2,REDIS_CMD_INLINE|REDIS_CMD_DENYOOM,NULL,1,-1,1},
-    {"sdiffstore",sdiffstoreCommand,-3,REDIS_CMD_INLINE|REDIS_CMD_DENYOOM,NULL,2,-1,1},
-    {"smembers",sinterCommand,2,REDIS_CMD_INLINE,NULL,1,1,1},
-    {"zadd",zaddCommand,4,REDIS_CMD_BULK|REDIS_CMD_DENYOOM,NULL,1,1,1},
-    {"zincrby",zincrbyCommand,4,REDIS_CMD_BULK|REDIS_CMD_DENYOOM,NULL,1,1,1},
-    {"zrem",zremCommand,3,REDIS_CMD_BULK,NULL,1,1,1},
-    {"zremrangebyscore",zremrangebyscoreCommand,4,REDIS_CMD_INLINE,NULL,1,1,1},
-    {"zremrangebyrank",zremrangebyrankCommand,4,REDIS_CMD_INLINE,NULL,1,1,1},
-    {"zunionstore",zunionstoreCommand,-4,REDIS_CMD_INLINE|REDIS_CMD_DENYOOM,zunionInterBlockClientOnSwappedKeys,0,0,0},
-    {"zinterstore",zinterstoreCommand,-4,REDIS_CMD_INLINE|REDIS_CMD_DENYOOM,zunionInterBlockClientOnSwappedKeys,0,0,0},
-    {"zrange",zrangeCommand,-4,REDIS_CMD_INLINE,NULL,1,1,1},
-    {"zrangebyscore",zrangebyscoreCommand,-4,REDIS_CMD_INLINE,NULL,1,1,1},
-    {"zrevrangebyscore",zrevrangebyscoreCommand,-4,REDIS_CMD_INLINE,NULL,1,1,1},
-    {"zcount",zcountCommand,4,REDIS_CMD_INLINE,NULL,1,1,1},
-    {"zrevrange",zrevrangeCommand,-4,REDIS_CMD_INLINE,NULL,1,1,1},
-    {"zcard",zcardCommand,2,REDIS_CMD_INLINE,NULL,1,1,1},
-    {"zscore",zscoreCommand,3,REDIS_CMD_BULK|REDIS_CMD_DENYOOM,NULL,1,1,1},
-    {"zrank",zrankCommand,3,REDIS_CMD_BULK,NULL,1,1,1},
-    {"zrevrank",zrevrankCommand,3,REDIS_CMD_BULK,NULL,1,1,1},
-    {"hset",hsetCommand,4,REDIS_CMD_BULK|REDIS_CMD_DENYOOM,NULL,1,1,1},
-    {"hsetnx",hsetnxCommand,4,REDIS_CMD_BULK|REDIS_CMD_DENYOOM,NULL,1,1,1},
-    {"hget",hgetCommand,3,REDIS_CMD_BULK,NULL,1,1,1},
-    {"hmset",hmsetCommand,-4,REDIS_CMD_BULK|REDIS_CMD_DENYOOM,NULL,1,1,1},
-    {"hmget",hmgetCommand,-3,REDIS_CMD_BULK,NULL,1,1,1},
-    {"hincrby",hincrbyCommand,4,REDIS_CMD_INLINE|REDIS_CMD_DENYOOM,NULL,1,1,1},
-    {"hdel",hdelCommand,3,REDIS_CMD_BULK,NULL,1,1,1},
-    {"hlen",hlenCommand,2,REDIS_CMD_INLINE,NULL,1,1,1},
-    {"hkeys",hkeysCommand,2,REDIS_CMD_INLINE,NULL,1,1,1},
-    {"hvals",hvalsCommand,2,REDIS_CMD_INLINE,NULL,1,1,1},
-    {"hgetall",hgetallCommand,2,REDIS_CMD_INLINE,NULL,1,1,1},
-    {"hexists",hexistsCommand,3,REDIS_CMD_BULK,NULL,1,1,1},
-    {"incrby",incrbyCommand,3,REDIS_CMD_INLINE|REDIS_CMD_DENYOOM,NULL,1,1,1},
-    {"decrby",decrbyCommand,3,REDIS_CMD_INLINE|REDIS_CMD_DENYOOM,NULL,1,1,1},
-    {"getset",getsetCommand,3,REDIS_CMD_BULK|REDIS_CMD_DENYOOM,NULL,1,1,1},
-    {"mset",msetCommand,-3,REDIS_CMD_BULK|REDIS_CMD_DENYOOM,NULL,1,-1,2},
-    {"msetnx",msetnxCommand,-3,REDIS_CMD_BULK|REDIS_CMD_DENYOOM,NULL,1,-1,2},
-    {"randomkey",randomkeyCommand,1,REDIS_CMD_INLINE,NULL,0,0,0},
-    {"select",selectCommand,2,REDIS_CMD_INLINE,NULL,0,0,0},
-    {"move",moveCommand,3,REDIS_CMD_INLINE,NULL,1,1,1},
-    {"rename",renameCommand,3,REDIS_CMD_INLINE,NULL,1,1,1},
-    {"renamenx",renamenxCommand,3,REDIS_CMD_INLINE,NULL,1,1,1},
-    {"expire",expireCommand,3,REDIS_CMD_INLINE,NULL,0,0,0},
-    {"expireat",expireatCommand,3,REDIS_CMD_INLINE,NULL,0,0,0},
-    {"keys",keysCommand,2,REDIS_CMD_INLINE,NULL,0,0,0},
-    {"dbsize",dbsizeCommand,1,REDIS_CMD_INLINE,NULL,0,0,0},
-    {"auth",authCommand,2,REDIS_CMD_INLINE,NULL,0,0,0},
-    {"ping",pingCommand,1,REDIS_CMD_INLINE,NULL,0,0,0},
-    {"echo",echoCommand,2,REDIS_CMD_BULK,NULL,0,0,0},
-    {"save",saveCommand,1,REDIS_CMD_INLINE,NULL,0,0,0},
-    {"bgsave",bgsaveCommand,1,REDIS_CMD_INLINE,NULL,0,0,0},
-    {"bgrewriteaof",bgrewriteaofCommand,1,REDIS_CMD_INLINE,NULL,0,0,0},
-    {"shutdown",shutdownCommand,1,REDIS_CMD_INLINE,NULL,0,0,0},
-    {"lastsave",lastsaveCommand,1,REDIS_CMD_INLINE,NULL,0,0,0},
-    {"type",typeCommand,2,REDIS_CMD_INLINE,NULL,1,1,1},
-    {"multi",multiCommand,1,REDIS_CMD_INLINE,NULL,0,0,0},
-    {"exec",execCommand,1,REDIS_CMD_INLINE|REDIS_CMD_DENYOOM,execBlockClientOnSwappedKeys,0,0,0},
-    {"discard",discardCommand,1,REDIS_CMD_INLINE,NULL,0,0,0},
-    {"sync",syncCommand,1,REDIS_CMD_INLINE,NULL,0,0,0},
-    {"flushdb",flushdbCommand,1,REDIS_CMD_INLINE,NULL,0,0,0},
-    {"flushall",flushallCommand,1,REDIS_CMD_INLINE,NULL,0,0,0},
-    {"sort",sortCommand,-2,REDIS_CMD_INLINE|REDIS_CMD_DENYOOM,NULL,1,1,1},
-    {"info",infoCommand,1,REDIS_CMD_INLINE,NULL,0,0,0},
-    {"monitor",monitorCommand,1,REDIS_CMD_INLINE,NULL,0,0,0},
-    {"ttl",ttlCommand,2,REDIS_CMD_INLINE,NULL,1,1,1},
-    {"persist",persistCommand,2,REDIS_CMD_INLINE,NULL,1,1,1},
-    {"slaveof",slaveofCommand,3,REDIS_CMD_INLINE,NULL,0,0,0},
-    {"debug",debugCommand,-2,REDIS_CMD_INLINE,NULL,0,0,0},
-    {"config",configCommand,-2,REDIS_CMD_BULK,NULL,0,0,0},
-    {"subscribe",subscribeCommand,-2,REDIS_CMD_INLINE,NULL,0,0,0},
-    {"unsubscribe",unsubscribeCommand,-1,REDIS_CMD_INLINE,NULL,0,0,0},
-    {"psubscribe",psubscribeCommand,-2,REDIS_CMD_INLINE,NULL,0,0,0},
-    {"punsubscribe",punsubscribeCommand,-1,REDIS_CMD_INLINE,NULL,0,0,0},
-    {"publish",publishCommand,3,REDIS_CMD_BULK|REDIS_CMD_FORCE_REPLICATION,NULL,0,0,0},
-    {"watch",watchCommand,-2,REDIS_CMD_INLINE,NULL,0,0,0},
-    {"unwatch",unwatchCommand,1,REDIS_CMD_INLINE,NULL,0,0,0}
+    {"get",getCommand,2,0,NULL,1,1,1},
+    {"set",setCommand,3,REDIS_CMD_DENYOOM,NULL,0,0,0},
+    {"setnx",setnxCommand,3,REDIS_CMD_DENYOOM,NULL,0,0,0},
+    {"setex",setexCommand,4,REDIS_CMD_DENYOOM,NULL,0,0,0},
+    {"append",appendCommand,3,REDIS_CMD_DENYOOM,NULL,1,1,1},
+    {"substr",substrCommand,4,0,NULL,1,1,1},
+    {"strlen",strlenCommand,2,0,NULL,1,1,1},
+    {"del",delCommand,-2,0,NULL,0,0,0},
+    {"exists",existsCommand,2,0,NULL,1,1,1},
+    {"incr",incrCommand,2,REDIS_CMD_DENYOOM,NULL,1,1,1},
+    {"decr",decrCommand,2,REDIS_CMD_DENYOOM,NULL,1,1,1},
+    {"mget",mgetCommand,-2,0,NULL,1,-1,1},
+    {"rpush",rpushCommand,3,REDIS_CMD_DENYOOM,NULL,1,1,1},
+    {"lpush",lpushCommand,3,REDIS_CMD_DENYOOM,NULL,1,1,1},
+    {"rpushx",rpushxCommand,3,REDIS_CMD_DENYOOM,NULL,1,1,1},
+    {"lpushx",lpushxCommand,3,REDIS_CMD_DENYOOM,NULL,1,1,1},
+    {"linsert",linsertCommand,5,REDIS_CMD_DENYOOM,NULL,1,1,1},
+    {"rpop",rpopCommand,2,0,NULL,1,1,1},
+    {"lpop",lpopCommand,2,0,NULL,1,1,1},
+    {"brpop",brpopCommand,-3,0,NULL,1,1,1},
+    {"blpop",blpopCommand,-3,0,NULL,1,1,1},
+    {"llen",llenCommand,2,0,NULL,1,1,1},
+    {"lindex",lindexCommand,3,0,NULL,1,1,1},
+    {"lset",lsetCommand,4,REDIS_CMD_DENYOOM,NULL,1,1,1},
+    {"lrange",lrangeCommand,4,0,NULL,1,1,1},
+    {"ltrim",ltrimCommand,4,0,NULL,1,1,1},
+    {"lrem",lremCommand,4,0,NULL,1,1,1},
+    {"rpoplpush",rpoplpushcommand,3,REDIS_CMD_DENYOOM,NULL,1,2,1},
+    {"sadd",saddCommand,3,REDIS_CMD_DENYOOM,NULL,1,1,1},
+    {"srem",sremCommand,3,0,NULL,1,1,1},
+    {"smove",smoveCommand,4,0,NULL,1,2,1},
+    {"sismember",sismemberCommand,3,0,NULL,1,1,1},
+    {"scard",scardCommand,2,0,NULL,1,1,1},
+    {"spop",spopCommand,2,0,NULL,1,1,1},
+    {"srandmember",srandmemberCommand,2,0,NULL,1,1,1},
+    {"sinter",sinterCommand,-2,REDIS_CMD_DENYOOM,NULL,1,-1,1},
+    {"sinterstore",sinterstoreCommand,-3,REDIS_CMD_DENYOOM,NULL,2,-1,1},
+    {"sunion",sunionCommand,-2,REDIS_CMD_DENYOOM,NULL,1,-1,1},
+    {"sunionstore",sunionstoreCommand,-3,REDIS_CMD_DENYOOM,NULL,2,-1,1},
+    {"sdiff",sdiffCommand,-2,REDIS_CMD_DENYOOM,NULL,1,-1,1},
+    {"sdiffstore",sdiffstoreCommand,-3,REDIS_CMD_DENYOOM,NULL,2,-1,1},
+    {"smembers",sinterCommand,2,0,NULL,1,1,1},
+    {"zadd",zaddCommand,4,REDIS_CMD_DENYOOM,NULL,1,1,1},
+    {"zincrby",zincrbyCommand,4,REDIS_CMD_DENYOOM,NULL,1,1,1},
+    {"zrem",zremCommand,3,0,NULL,1,1,1},
+    {"zremrangebyscore",zremrangebyscoreCommand,4,0,NULL,1,1,1},
+    {"zremrangebyrank",zremrangebyrankCommand,4,0,NULL,1,1,1},
+    {"zunionstore",zunionstoreCommand,-4,REDIS_CMD_DENYOOM,zunionInterBlockClientOnSwappedKeys,0,0,0},
+    {"zinterstore",zinterstoreCommand,-4,REDIS_CMD_DENYOOM,zunionInterBlockClientOnSwappedKeys,0,0,0},
+    {"zrange",zrangeCommand,-4,0,NULL,1,1,1},
+    {"zrangebyscore",zrangebyscoreCommand,-4,0,NULL,1,1,1},
+    {"zrevrangebyscore",zrevrangebyscoreCommand,-4,0,NULL,1,1,1},
+    {"zcount",zcountCommand,4,0,NULL,1,1,1},
+    {"zrevrange",zrevrangeCommand,-4,0,NULL,1,1,1},
+    {"zcard",zcardCommand,2,0,NULL,1,1,1},
+    {"zscore",zscoreCommand,3,REDIS_CMD_DENYOOM,NULL,1,1,1},
+    {"zrank",zrankCommand,3,0,NULL,1,1,1},
+    {"zrevrank",zrevrankCommand,3,0,NULL,1,1,1},
+    {"hset",hsetCommand,4,REDIS_CMD_DENYOOM,NULL,1,1,1},
+    {"hsetnx",hsetnxCommand,4,REDIS_CMD_DENYOOM,NULL,1,1,1},
+    {"hget",hgetCommand,3,0,NULL,1,1,1},
+    {"hmset",hmsetCommand,-4,REDIS_CMD_DENYOOM,NULL,1,1,1},
+    {"hmget",hmgetCommand,-3,0,NULL,1,1,1},
+    {"hincrby",hincrbyCommand,4,REDIS_CMD_DENYOOM,NULL,1,1,1},
+    {"hdel",hdelCommand,3,0,NULL,1,1,1},
+    {"hlen",hlenCommand,2,0,NULL,1,1,1},
+    {"hkeys",hkeysCommand,2,0,NULL,1,1,1},
+    {"hvals",hvalsCommand,2,0,NULL,1,1,1},
+    {"hgetall",hgetallCommand,2,0,NULL,1,1,1},
+    {"hexists",hexistsCommand,3,0,NULL,1,1,1},
+    {"incrby",incrbyCommand,3,REDIS_CMD_DENYOOM,NULL,1,1,1},
+    {"decrby",decrbyCommand,3,REDIS_CMD_DENYOOM,NULL,1,1,1},
+    {"getset",getsetCommand,3,REDIS_CMD_DENYOOM,NULL,1,1,1},
+    {"mset",msetCommand,-3,REDIS_CMD_DENYOOM,NULL,1,-1,2},
+    {"msetnx",msetnxCommand,-3,REDIS_CMD_DENYOOM,NULL,1,-1,2},
+    {"randomkey",randomkeyCommand,1,0,NULL,0,0,0},
+    {"select",selectCommand,2,0,NULL,0,0,0},
+    {"move",moveCommand,3,0,NULL,1,1,1},
+    {"rename",renameCommand,3,0,NULL,1,1,1},
+    {"renamenx",renamenxCommand,3,0,NULL,1,1,1},
+    {"expire",expireCommand,3,0,NULL,0,0,0},
+    {"expireat",expireatCommand,3,0,NULL,0,0,0},
+    {"keys",keysCommand,2,0,NULL,0,0,0},
+    {"dbsize",dbsizeCommand,1,0,NULL,0,0,0},
+    {"auth",authCommand,2,0,NULL,0,0,0},
+    {"ping",pingCommand,1,0,NULL,0,0,0},
+    {"echo",echoCommand,2,0,NULL,0,0,0},
+    {"save",saveCommand,1,0,NULL,0,0,0},
+    {"bgsave",bgsaveCommand,1,0,NULL,0,0,0},
+    {"bgrewriteaof",bgrewriteaofCommand,1,0,NULL,0,0,0},
+    {"shutdown",shutdownCommand,1,0,NULL,0,0,0},
+    {"lastsave",lastsaveCommand,1,0,NULL,0,0,0},
+    {"type",typeCommand,2,0,NULL,1,1,1},
+    {"multi",multiCommand,1,0,NULL,0,0,0},
+    {"exec",execCommand,1,REDIS_CMD_DENYOOM,execBlockClientOnSwappedKeys,0,0,0},
+    {"discard",discardCommand,1,0,NULL,0,0,0},
+    {"sync",syncCommand,1,0,NULL,0,0,0},
+    {"flushdb",flushdbCommand,1,0,NULL,0,0,0},
+    {"flushall",flushallCommand,1,0,NULL,0,0,0},
+    {"sort",sortCommand,-2,REDIS_CMD_DENYOOM,NULL,1,1,1},
+    {"info",infoCommand,1,0,NULL,0,0,0},
+    {"monitor",monitorCommand,1,0,NULL,0,0,0},
+    {"ttl",ttlCommand,2,0,NULL,1,1,1},
+    {"persist",persistCommand,2,0,NULL,1,1,1},
+    {"slaveof",slaveofCommand,3,0,NULL,0,0,0},
+    {"debug",debugCommand,-2,0,NULL,0,0,0},
+    {"config",configCommand,-2,0,NULL,0,0,0},
+    {"subscribe",subscribeCommand,-2,0,NULL,0,0,0},
+    {"unsubscribe",unsubscribeCommand,-1,0,NULL,0,0,0},
+    {"psubscribe",psubscribeCommand,-2,0,NULL,0,0,0},
+    {"punsubscribe",punsubscribeCommand,-1,0,NULL,0,0,0},
+    {"publish",publishCommand,3,REDIS_CMD_FORCE_REPLICATION,NULL,0,0,0},
+    {"watch",watchCommand,-2,0,NULL,0,0,0},
+    {"unwatch",unwatchCommand,1,0,NULL,0,0,0}
 };
 
 /*============================ Utility functions ============================ */
@@ -899,84 +899,14 @@ void call(redisClient *c, struct redisCommand *cmd) {
 int processCommand(redisClient *c) {
     struct redisCommand *cmd;
 
-    /* Handle the multi bulk command type. This is an alternative protocol
-     * supported by Redis in order to receive commands that are composed of
-     * multiple binary-safe "bulk" arguments. The latency of processing is
-     * a bit higher but this allows things like multi-sets, so if this
-     * protocol is used only for MSET and similar commands this is a big win. */
-    if (c->multibulk == 0 && c->argc == 1 && ((char*)(c->argv[0]->ptr))[0] == '*') {
-        c->multibulk = atoi(((char*)c->argv[0]->ptr)+1);
-        if (c->multibulk <= 0) {
-            resetClient(c);
-            return 1;
-        } else {
-            decrRefCount(c->argv[c->argc-1]);
-            c->argc--;
-            return 1;
-        }
-    } else if (c->multibulk) {
-        if (c->bulklen == -1) {
-            if (((char*)c->argv[0]->ptr)[0] != '$') {
-                addReplyError(c,"multi bulk protocol error");
-                resetClient(c);
-                return 1;
-            } else {
-                char *eptr;
-                long bulklen = strtol(((char*)c->argv[0]->ptr)+1,&eptr,10);
-                int perr = eptr[0] != '\0';
-
-                decrRefCount(c->argv[0]);
-                if (perr || bulklen == LONG_MIN || bulklen == LONG_MAX ||
-                    bulklen < 0 || bulklen > 1024*1024*1024)
-                {
-                    c->argc--;
-                    addReplyError(c,"invalid bulk write count");
-                    resetClient(c);
-                    return 1;
-                }
-                c->argc--;
-                c->bulklen = bulklen+2; /* add two bytes for CR+LF */
-                return 1;
-            }
-        } else {
-            c->mbargv = zrealloc(c->mbargv,(sizeof(robj*))*(c->mbargc+1));
-            c->mbargv[c->mbargc] = c->argv[0];
-            c->mbargc++;
-            c->argc--;
-            c->multibulk--;
-            if (c->multibulk == 0) {
-                robj **auxargv;
-                int auxargc;
-
-                /* Here we need to swap the multi-bulk argc/argv with the
-                 * normal argc/argv of the client structure. */
-                auxargv = c->argv;
-                c->argv = c->mbargv;
-                c->mbargv = auxargv;
-
-                auxargc = c->argc;
-                c->argc = c->mbargc;
-                c->mbargc = auxargc;
-
-                /* We need to set bulklen to something different than -1
-                 * in order for the code below to process the command without
-                 * to try to read the last argument of a bulk command as
-                 * a special argument. */
-                c->bulklen = 0;
-                /* continue below and process the command */
-            } else {
-                c->bulklen = -1;
-                return 1;
-            }
-        }
-    }
-    /* -- end of multi bulk commands processing -- */
-
-    /* The QUIT command is handled as a special case. Normal command
-     * procs are unable to close the client connection safely */
+    /* The QUIT command is handled separately. Normal command procs will
+     * go through checking for replication and QUIT will cause trouble
+     * when FORCE_REPLICATION is enabled and would be implemented in
+     * a regular command proc. */
     if (!strcasecmp(c->argv[0]->ptr,"quit")) {
-        freeClient(c);
-        return 0;
+        addReply(c,shared.ok);
+        c->flags |= REDIS_CLOSE_AFTER_REPLY;
+        return REDIS_ERR;
     }
 
     /* Now lookup the command and check ASAP about trivial error conditions
@@ -985,55 +915,18 @@ int processCommand(redisClient *c) {
     if (!cmd) {
         addReplyErrorFormat(c,"unknown command '%s'",
             (char*)c->argv[0]->ptr);
-        resetClient(c);
-        return 1;
+        return REDIS_OK;
     } else if ((cmd->arity > 0 && cmd->arity != c->argc) ||
                (c->argc < -cmd->arity)) {
         addReplyErrorFormat(c,"wrong number of arguments for '%s' command",
             cmd->name);
-        resetClient(c);
-        return 1;
-    } else if (cmd->flags & REDIS_CMD_BULK && c->bulklen == -1) {
-        /* This is a bulk command, we have to read the last argument yet. */
-        char *eptr;
-        long bulklen = strtol(c->argv[c->argc-1]->ptr,&eptr,10);
-        int perr = eptr[0] != '\0';
-
-        decrRefCount(c->argv[c->argc-1]);
-        if (perr || bulklen == LONG_MAX || bulklen == LONG_MIN ||
-            bulklen < 0 || bulklen > 1024*1024*1024)
-        {
-            c->argc--;
-            addReplyError(c,"invalid bulk write count");
-            resetClient(c);
-            return 1;
-        }
-        c->argc--;
-        c->bulklen = bulklen+2; /* add two bytes for CR+LF */
-        /* It is possible that the bulk read is already in the
-         * buffer. Check this condition and handle it accordingly.
-         * This is just a fast path, alternative to call processInputBuffer().
-         * It's a good idea since the code is small and this condition
-         * happens most of the times. */
-        if ((signed)sdslen(c->querybuf) >= c->bulklen) {
-            c->argv[c->argc] = createStringObject(c->querybuf,c->bulklen-2);
-            c->argc++;
-            c->querybuf = sdsrange(c->querybuf,c->bulklen,-1);
-        } else {
-            /* Otherwise return... there is to read the last argument
-             * from the socket. */
-            return 1;
-        }
+        return REDIS_OK;
     }
-    /* Let's try to encode the bulk object to save space. */
-    if (cmd->flags & REDIS_CMD_BULK)
-        c->argv[c->argc-1] = tryObjectEncoding(c->argv[c->argc-1]);
 
     /* Check if the user is authenticated */
     if (server.requirepass && !c->authenticated && cmd->proc != authCommand) {
         addReplyError(c,"operation not permitted");
-        resetClient(c);
-        return 1;
+        return REDIS_OK;
     }
 
     /* Handle the maxmemory directive.
@@ -1046,8 +939,7 @@ int processCommand(redisClient *c) {
         zmalloc_used_memory() > server.maxmemory)
     {
         addReplyError(c,"command not allowed when used memory > 'maxmemory'");
-        resetClient(c);
-        return 1;
+        return REDIS_OK;
     }
 
     /* Only allow SUBSCRIBE and UNSUBSCRIBE in the context of Pub/Sub */
@@ -1056,8 +948,7 @@ int processCommand(redisClient *c) {
         cmd->proc != subscribeCommand && cmd->proc != unsubscribeCommand &&
         cmd->proc != psubscribeCommand && cmd->proc != punsubscribeCommand) {
         addReplyError(c,"only (P)SUBSCRIBE / (P)UNSUBSCRIBE / QUIT allowed in this context");
-        resetClient(c);
-        return 1;
+        return REDIS_OK;
     }
 
     /* Exec the command */
@@ -1069,13 +960,10 @@ int processCommand(redisClient *c) {
         addReply(c,shared.queued);
     } else {
         if (server.vm_enabled && server.vm_max_threads > 0 &&
-            blockClientOnSwappedKeys(c,cmd)) return 1;
+            blockClientOnSwappedKeys(c,cmd)) return REDIS_ERR;
         call(c,cmd);
     }
-
-    /* Prepare the client for the next command */
-    resetClient(c);
-    return 1;
+    return REDIS_OK;
 }
 
 /*================================== Shutdown =============================== */