@@ -53,6 +53,7 @@ static struct config {
     int hostport;
     long repeat;
     int dbnum;
+    int argn_from_stdin;
     int interactive;
     int shutdown;
     int monitor_mode;
@@ -61,137 +62,9 @@ static struct config {
     char *auth;
 } config;
 
-struct redisCommand {
-    char *name;
-    int arity;
-    int flags;
-};
-
-#define CMDFLAG_NONE 0
-#define CMDFLAG_RAWOUTPUT 1
-
-static struct redisCommand cmdTable[] = {
-    {"auth",2,CMDFLAG_NONE},
-    {"get",2,CMDFLAG_NONE},
-    {"set",3,CMDFLAG_NONE},
-    {"setnx",3,CMDFLAG_NONE},
-    {"setex",4,CMDFLAG_NONE},
-    {"append",3,CMDFLAG_NONE},
-    {"substr",4,CMDFLAG_NONE},
-    {"del",-2,CMDFLAG_NONE},
-    {"exists",2,CMDFLAG_NONE},
-    {"incr",2,CMDFLAG_NONE},
-    {"decr",2,CMDFLAG_NONE},
-    {"rpush",3,CMDFLAG_NONE},
-    {"lpush",3,CMDFLAG_NONE},
-    {"rpop",2,CMDFLAG_NONE},
-    {"lpop",2,CMDFLAG_NONE},
-    {"brpop",-3,CMDFLAG_NONE},
-    {"blpop",-3,CMDFLAG_NONE},
-    {"llen",2,CMDFLAG_NONE},
-    {"lindex",3,CMDFLAG_NONE},
-    {"lset",4,CMDFLAG_NONE},
-    {"lrange",4,CMDFLAG_NONE},
-    {"ltrim",4,CMDFLAG_NONE},
-    {"lrem",4,CMDFLAG_NONE},
-    {"rpoplpush",3,CMDFLAG_NONE},
-    {"sadd",3,CMDFLAG_NONE},
-    {"srem",3,CMDFLAG_NONE},
-    {"smove",4,CMDFLAG_NONE},
-    {"sismember",3,CMDFLAG_NONE},
-    {"scard",2,CMDFLAG_NONE},
-    {"spop",2,CMDFLAG_NONE},
-    {"srandmember",2,CMDFLAG_NONE},
-    {"sinter",-2,CMDFLAG_NONE},
-    {"sinterstore",-3,CMDFLAG_NONE},
-    {"sunion",-2,CMDFLAG_NONE},
-    {"sunionstore",-3,CMDFLAG_NONE},
-    {"sdiff",-2,CMDFLAG_NONE},
-    {"sdiffstore",-3,CMDFLAG_NONE},
-    {"smembers",2,CMDFLAG_NONE},
-    {"zadd",4,CMDFLAG_NONE},
-    {"zincrby",4,CMDFLAG_NONE},
-    {"zrem",3,CMDFLAG_NONE},
-    {"zremrangebyscore",4,CMDFLAG_NONE},
-    {"zunion",-4,CMDFLAG_NONE},
-    {"zinter",-4,CMDFLAG_NONE},
-    {"zrange",-4,CMDFLAG_NONE},
-    {"zrank",3,CMDFLAG_NONE},
-    {"zrevrank",3,CMDFLAG_NONE},
-    {"zrangebyscore",-4,CMDFLAG_NONE},
-    {"zcount",4,CMDFLAG_NONE},
-    {"zrevrange",-4,CMDFLAG_NONE},
-    {"zcard",2,CMDFLAG_NONE},
-    {"zscore",3,CMDFLAG_NONE},
-    {"incrby",3,CMDFLAG_NONE},
-    {"decrby",3,CMDFLAG_NONE},
-    {"getset",3,CMDFLAG_NONE},
-    {"randomkey",1,CMDFLAG_NONE},
-    {"select",2,CMDFLAG_NONE},
-    {"move",3,CMDFLAG_NONE},
-    {"rename",3,CMDFLAG_NONE},
-    {"renamenx",3,CMDFLAG_NONE},
-    {"keys",2,CMDFLAG_NONE},
-    {"dbsize",1,CMDFLAG_NONE},
-    {"ping",1,CMDFLAG_NONE},
-    {"echo",2,CMDFLAG_NONE},
-    {"save",1,CMDFLAG_NONE},
-    {"bgsave",1,CMDFLAG_NONE},
-    {"rewriteaof",1,CMDFLAG_NONE},
-    {"bgrewriteaof",1,CMDFLAG_NONE},
-    {"shutdown",1,CMDFLAG_NONE},
-    {"lastsave",1,CMDFLAG_NONE},
-    {"type",2,CMDFLAG_NONE},
-    {"flushdb",1,CMDFLAG_NONE},
-    {"flushall",1,CMDFLAG_NONE},
-    {"sort",-2,CMDFLAG_NONE},
-    {"info",1,CMDFLAG_RAWOUTPUT},
-    {"mget",-2,CMDFLAG_NONE},
-    {"expire",3,CMDFLAG_NONE},
-    {"expireat",3,CMDFLAG_NONE},
-    {"ttl",2,CMDFLAG_NONE},
-    {"slaveof",3,CMDFLAG_NONE},
-    {"debug",-2,CMDFLAG_NONE},
-    {"mset",-3,CMDFLAG_NONE},
-    {"msetnx",-3,CMDFLAG_NONE},
-    {"monitor",1,CMDFLAG_NONE},
-    {"multi",1,CMDFLAG_NONE},
-    {"exec",1,CMDFLAG_NONE},
-    {"discard",1,CMDFLAG_NONE},
-    {"hset",4,CMDFLAG_NONE},
-    {"hget",3,CMDFLAG_NONE},
-    {"hmset",-4,CMDFLAG_NONE},
-    {"hmget",-3,CMDFLAG_NONE},
-    {"hincrby",4,CMDFLAG_NONE},
-    {"hdel",3,CMDFLAG_NONE},
-    {"hlen",2,CMDFLAG_NONE},
-    {"hkeys",2,CMDFLAG_NONE},
-    {"hvals",2,CMDFLAG_NONE},
-    {"hgetall",2,CMDFLAG_NONE},
-    {"hexists",3,CMDFLAG_NONE},
-    {"config",-2,CMDFLAG_NONE},
-    {"subscribe",-2,CMDFLAG_NONE},
-    {"unsubscribe",-1,CMDFLAG_NONE},
-    {"psubscribe",-2,CMDFLAG_NONE},
-    {"punsubscribe",-1,CMDFLAG_NONE},
-    {"publish",3,CMDFLAG_NONE},
-    {"watch",-2,CMDFLAG_NONE},
-    {"unwatch",1,CMDFLAG_NONE},
-    {NULL,0,CMDFLAG_NONE}
-};
-
 static int cliReadReply(int fd);
 static void usage();
 
-static struct redisCommand *lookupCommand(char *name) {
-    int j = 0;
-    while(cmdTable[j].name != NULL) {
-        if (!strcasecmp(name,cmdTable[j].name)) return &cmdTable[j];
-        j++;
-    }
-    return NULL;
-}
-
 static int cliConnect(void) {
     char err[ANET_ERR_LEN];
     static int fd = ANET_ERR;
@@ -361,26 +234,15 @@ static int selectDb(int fd) {
 }
 
 static int cliSendCommand(int argc, char **argv, int repeat) {
-    struct redisCommand *rc = lookupCommand(argv[0]);
+    char *command = argv[0];
     int fd, j, retval = 0;
     sds cmd;
 
-    if (!rc) {
-        fprintf(stderr,"Unknown command '%s'\n",argv[0]);
-        return 1;
-    }
-    config.raw_output = (rc->flags & CMDFLAG_RAWOUTPUT);
-
-    if ((rc->arity > 0 && argc != rc->arity) ||
-        (rc->arity < 0 && argc < -rc->arity)) {
-            fprintf(stderr,"Wrong number of arguments for '%s'\n",rc->name);
-            return 1;
-    }
-
-    if (!strcasecmp(rc->name,"shutdown")) config.shutdown = 1;
-    if (!strcasecmp(rc->name,"monitor")) config.monitor_mode = 1;
-    if (!strcasecmp(rc->name,"subscribe") ||
-        !strcasecmp(rc->name,"psubscribe")) config.pubsub_mode = 1;
+    config.raw_output = !strcasecmp(command,"info");
+    if (!strcasecmp(command,"shutdown")) config.shutdown = 1;
+    if (!strcasecmp(command,"monitor")) config.monitor_mode = 1;
+    if (!strcasecmp(command,"subscribe") ||
+        !strcasecmp(command,"psubscribe")) config.pubsub_mode = 1;
     if ((fd = cliConnect()) == -1) return 1;
 
     /* Select db number */
@@ -453,6 +315,8 @@ static int parseOptions(int argc, char **argv) {
             i++;
         } else if (!strcmp(argv[i],"-i")) {
             config.interactive = 1;
+        } else if (!strcmp(argv[i],"-c")) {
+            config.argn_from_stdin = 1;
         } else {
             break;
         }
@@ -479,7 +343,7 @@ static sds readArgFromStdin(void) {
 
 static void usage() {
     fprintf(stderr, "usage: redis-cli [-h host] [-p port] [-a authpw] [-r repeat_times] [-n db_num] [-i] cmd arg1 arg2 arg3 ... argN\n");
-    fprintf(stderr, "usage: echo \"argN\" | redis-cli [-h host] [-a authpw] [-p port] [-r repeat_times] [-n db_num] cmd arg1 arg2 ... arg(N-1)\n");
+    fprintf(stderr, "usage: echo \"argN\" | redis-cli -c [-h host] [-p port] [-a authpw] [-r repeat_times] [-n db_num] cmd arg1 arg2 ... arg(N-1)\n");
     fprintf(stderr, "\nIf a pipe from standard input is detected this data is used as last argument.\n\n");
     fprintf(stderr, "example: cat /etc/passwd | redis-cli set my_passwd\n");
     fprintf(stderr, "example: redis-cli get my_passwd\n");
@@ -491,7 +355,7 @@ static void usage() {
 /* Turn the plain C strings into Sds strings */
 static char **convertToSds(int count, char** args) {
   int j;
-  char **sds = zmalloc(sizeof(char*)*count+1);
+  char **sds = zmalloc(sizeof(char*)*count);
 
   for(j = 0; j < count; j++)
     sds[j] = sdsnew(args[j]);
@@ -594,12 +458,12 @@ static void repl() {
 int main(int argc, char **argv) {
     int firstarg;
     char **argvcopy;
-    struct redisCommand *rc;
 
     config.hostip = "127.0.0.1";
     config.hostport = 6379;
     config.repeat = 1;
     config.dbnum = 0;
+    config.argn_from_stdin = 0;
     config.shutdown = 0;
     config.interactive = 0;
     config.monitor_mode = 0;
@@ -621,16 +485,11 @@ int main(int argc, char **argv) {
 
     if (argc == 0 || config.interactive == 1) repl();
 
-    argvcopy = convertToSds(argc, argv);
-
-    /* Read the last argument from stdandard input if needed */
-    if ((rc = lookupCommand(argv[0])) != NULL) {
-      if (rc->arity > 0 && argc == rc->arity-1) {
+    argvcopy = convertToSds(argc+1, argv);
+    if (config.argn_from_stdin) {
         sds lastarg = readArgFromStdin();
         argvcopy[argc] = lastarg;
         argc++;
-      }
     }
-
     return cliSendCommand(argc, argvcopy, config.repeat);
 }