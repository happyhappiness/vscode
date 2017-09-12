@@ -40,11 +40,6 @@
 
 #define REDIS_CMD_INLINE 1
 #define REDIS_CMD_BULK 2
-#define REDIS_CMD_INTREPLY 4
-#define REDIS_CMD_RETCODEREPLY 8
-#define REDIS_CMD_BULKREPLY 16
-#define REDIS_CMD_MULTIBULKREPLY 32
-#define REDIS_CMD_SINGLELINEREPLY 64
 
 #define REDIS_NOTUSED(V) ((void) V)
 
@@ -60,54 +55,56 @@ struct redisCommand {
 };
 
 static struct redisCommand cmdTable[] = {
-    {"get",2,REDIS_CMD_INLINE|REDIS_CMD_BULKREPLY},
-    {"set",3,REDIS_CMD_BULK|REDIS_CMD_RETCODEREPLY},
-    {"setnx",3,REDIS_CMD_BULK|REDIS_CMD_INTREPLY},
-    {"del",2,REDIS_CMD_INLINE|REDIS_CMD_INTREPLY},
-    {"exists",2,REDIS_CMD_INLINE|REDIS_CMD_INTREPLY},
-    {"incr",2,REDIS_CMD_INLINE|REDIS_CMD_INTREPLY},
-    {"decr",2,REDIS_CMD_INLINE|REDIS_CMD_INTREPLY},
-    {"rpush",3,REDIS_CMD_BULK|REDIS_CMD_RETCODEREPLY},
-    {"lpush",3,REDIS_CMD_BULK|REDIS_CMD_RETCODEREPLY},
-    {"rpop",2,REDIS_CMD_INLINE|REDIS_CMD_BULKREPLY},
-    {"lpop",2,REDIS_CMD_INLINE|REDIS_CMD_BULKREPLY},
-    {"llen",2,REDIS_CMD_INLINE|REDIS_CMD_INTREPLY},
-    {"lindex",3,REDIS_CMD_INLINE|REDIS_CMD_BULKREPLY},
-    {"lset",4,REDIS_CMD_BULK|REDIS_CMD_RETCODEREPLY},
-    {"lrange",4,REDIS_CMD_INLINE|REDIS_CMD_MULTIBULKREPLY},
-    {"ltrim",4,REDIS_CMD_INLINE|REDIS_CMD_RETCODEREPLY},
-    {"lrem",4,REDIS_CMD_BULK|REDIS_CMD_INTREPLY},
-    {"sadd",3,REDIS_CMD_BULK|REDIS_CMD_INTREPLY},
-    {"srem",3,REDIS_CMD_BULK|REDIS_CMD_INTREPLY},
-    {"sismember",3,REDIS_CMD_BULK|REDIS_CMD_INTREPLY},
-    {"scard",2,REDIS_CMD_INLINE|REDIS_CMD_INTREPLY},
-    {"sinter",-2,REDIS_CMD_INLINE|REDIS_CMD_MULTIBULKREPLY},
-    {"sinterstore",-3,REDIS_CMD_INLINE|REDIS_CMD_RETCODEREPLY},
-    {"smembers",2,REDIS_CMD_INLINE|REDIS_CMD_MULTIBULKREPLY},
-    {"incrby",3,REDIS_CMD_INLINE|REDIS_CMD_INTREPLY},
-    {"decrby",3,REDIS_CMD_INLINE|REDIS_CMD_INTREPLY},
-    {"randomkey",1,REDIS_CMD_INLINE|REDIS_CMD_SINGLELINEREPLY},
-    {"select",2,REDIS_CMD_INLINE|REDIS_CMD_RETCODEREPLY},
-    {"move",3,REDIS_CMD_INLINE|REDIS_CMD_INTREPLY},
-    {"rename",3,REDIS_CMD_INLINE|REDIS_CMD_RETCODEREPLY},
-    {"renamenx",3,REDIS_CMD_INLINE|REDIS_CMD_INTREPLY},
-    {"keys",2,REDIS_CMD_INLINE|REDIS_CMD_BULKREPLY},
-    {"dbsize",1,REDIS_CMD_INLINE|REDIS_CMD_INTREPLY},
-    {"ping",1,REDIS_CMD_INLINE|REDIS_CMD_RETCODEREPLY},
-    {"echo",2,REDIS_CMD_BULK|REDIS_CMD_BULKREPLY},
-    {"save",1,REDIS_CMD_INLINE|REDIS_CMD_RETCODEREPLY},
-    {"bgsave",1,REDIS_CMD_INLINE|REDIS_CMD_RETCODEREPLY},
-    {"shutdown",1,REDIS_CMD_INLINE|REDIS_CMD_RETCODEREPLY},
-    {"lastsave",1,REDIS_CMD_INLINE|REDIS_CMD_INTREPLY},
-    {"type",2,REDIS_CMD_INLINE|REDIS_CMD_SINGLELINEREPLY},
-    {"flushdb",1,REDIS_CMD_INLINE|REDIS_CMD_RETCODEREPLY},
-    {"flushall",1,REDIS_CMD_INLINE|REDIS_CMD_RETCODEREPLY},
-    {"sort",-2,REDIS_CMD_INLINE|REDIS_CMD_MULTIBULKREPLY},
-    {"info",1,REDIS_CMD_INLINE|REDIS_CMD_BULKREPLY},
-    {"mget",-2,REDIS_CMD_INLINE|REDIS_CMD_MULTIBULKREPLY},
+    {"get",2,REDIS_CMD_INLINE},
+    {"set",3,REDIS_CMD_BULK},
+    {"setnx",3,REDIS_CMD_BULK},
+    {"del",2,REDIS_CMD_INLINE},
+    {"exists",2,REDIS_CMD_INLINE},
+    {"incr",2,REDIS_CMD_INLINE},
+    {"decr",2,REDIS_CMD_INLINE},
+    {"rpush",3,REDIS_CMD_BULK},
+    {"lpush",3,REDIS_CMD_BULK},
+    {"rpop",2,REDIS_CMD_INLINE},
+    {"lpop",2,REDIS_CMD_INLINE},
+    {"llen",2,REDIS_CMD_INLINE},
+    {"lindex",3,REDIS_CMD_INLINE},
+    {"lset",4,REDIS_CMD_BULK},
+    {"lrange",4,REDIS_CMD_INLINE},
+    {"ltrim",4,REDIS_CMD_INLINE},
+    {"lrem",4,REDIS_CMD_BULK},
+    {"sadd",3,REDIS_CMD_BULK},
+    {"srem",3,REDIS_CMD_BULK},
+    {"sismember",3,REDIS_CMD_BULK},
+    {"scard",2,REDIS_CMD_INLINE},
+    {"sinter",-2,REDIS_CMD_INLINE},
+    {"sinterstore",-3,REDIS_CMD_INLINE},
+    {"smembers",2,REDIS_CMD_INLINE},
+    {"incrby",3,REDIS_CMD_INLINE},
+    {"decrby",3,REDIS_CMD_INLINE},
+    {"randomkey",1,REDIS_CMD_INLINE},
+    {"select",2,REDIS_CMD_INLINE},
+    {"move",3,REDIS_CMD_INLINE},
+    {"rename",3,REDIS_CMD_INLINE},
+    {"renamenx",3,REDIS_CMD_INLINE},
+    {"keys",2,REDIS_CMD_INLINE},
+    {"dbsize",1,REDIS_CMD_INLINE},
+    {"ping",1,REDIS_CMD_INLINE},
+    {"echo",2,REDIS_CMD_BULK},
+    {"save",1,REDIS_CMD_INLINE},
+    {"bgsave",1,REDIS_CMD_INLINE},
+    {"shutdown",1,REDIS_CMD_INLINE},
+    {"lastsave",1,REDIS_CMD_INLINE},
+    {"type",2,REDIS_CMD_INLINE},
+    {"flushdb",1,REDIS_CMD_INLINE},
+    {"flushall",1,REDIS_CMD_INLINE},
+    {"sort",-2,REDIS_CMD_INLINE},
+    {"info",1,REDIS_CMD_INLINE},
+    {"mget",-2,REDIS_CMD_INLINE},
     {NULL,0,0}
 };
 
+static int cliReadReply(int fd);
+
 static struct redisCommand *lookupCommand(char *name) {
     int j = 0;
     while(cmdTable[j].name != NULL) {
@@ -150,71 +147,83 @@ static sds cliReadLine(int fd) {
     return sdstrim(line,"\r\n");
 }
 
-static int cliReadInlineReply(int fd, int type) {
+static int cliReadSingleLineReply(int fd) {
     sds reply = cliReadLine(fd);
 
     if (reply == NULL) return 1;
     printf("%s\n", reply);
-    if (type == REDIS_CMD_SINGLELINEREPLY) return 0;
-    if (type == REDIS_CMD_INTREPLY) return atoi(reply) < 0;
-    if (type == REDIS_CMD_RETCODEREPLY) return reply[0] == '-';
     return 0;
 }
 
-static int cliReadBulkReply(int fd, int multibulk) {
+static int cliReadBulkReply(int fd) {
     sds replylen = cliReadLine(fd);
     char *reply, crlf[2];
-    int bulklen, error = 0;
+    int bulklen;
 
     if (replylen == NULL) return 1;
-    if (strcmp(replylen,"nil") == 0) {
-        sdsfree(replylen);
-        printf("(nil)\n");
-        return 0;
-    }
     bulklen = atoi(replylen);
-    if (multibulk && bulklen == -1) {
+    if (bulklen == -1) {
         sdsfree(replylen);
         printf("(nil)");
         return 0;
     }
-    if (bulklen < 0) {
-        bulklen = -bulklen;
-        error = 1;
-    }
     reply = zmalloc(bulklen);
     anetRead(fd,reply,bulklen);
     anetRead(fd,crlf,2);
     if (bulklen && fwrite(reply,bulklen,1,stdout) == 0) {
         zfree(reply);
         return 1;
     }
-    if (!multibulk && isatty(fileno(stdout)) && reply[bulklen-1] != '\n')
+    if (isatty(fileno(stdout)) && reply[bulklen-1] != '\n')
         printf("\n");
     zfree(reply);
-    return error;
+    return 0;
 }
 
 static int cliReadMultiBulkReply(int fd) {
     sds replylen = cliReadLine(fd);
     int elements, c = 1;
 
     if (replylen == NULL) return 1;
-    if (strcmp(replylen,"nil") == 0) {
+    elements = atoi(replylen);
+    if (elements == -1) {
         sdsfree(replylen);
         printf("(nil)\n");
         return 0;
     }
-    elements = atoi(replylen);
+    if (elements == 0) {
+        printf("(empty list or set)\n");
+    }
     while(elements--) {
         printf("%d. ", c);
-        if (cliReadBulkReply(fd,1)) return 1;
-        printf("\n");
+        if (cliReadReply(fd)) return 1;
         c++;
     }
     return 0;
 }
 
+static int cliReadReply(int fd) {
+    char type;
+
+    if (anetRead(fd,&type,1) <= 0) exit(1);
+    switch(type) {
+    case '-':
+        printf("(error) ");
+        cliReadSingleLineReply(fd);
+        return 1;
+    case '+':
+    case ':':
+        return cliReadSingleLineReply(fd);
+    case '$':
+        return cliReadBulkReply(fd);
+    case '*':
+        return cliReadMultiBulkReply(fd);
+    default:
+        printf("protocol error, got '%c' as reply type byte\n", type);
+        return 1;
+    }
+}
+
 static int cliSendCommand(int argc, char **argv) {
     struct redisCommand *rc = lookupCommand(argv[0]);
     int fd, j, retval = 0;
@@ -247,17 +256,7 @@ static int cliSendCommand(int argc, char **argv) {
         cmd = sdscat(cmd,"\r\n");
     }
     anetWrite(fd,cmd,sdslen(cmd));
-    if (rc->flags & REDIS_CMD_INTREPLY) {
-        retval = cliReadInlineReply(fd,REDIS_CMD_INTREPLY);
-    } else if (rc->flags & REDIS_CMD_RETCODEREPLY) {
-        retval = cliReadInlineReply(fd,REDIS_CMD_RETCODEREPLY);
-    } else if (rc->flags & REDIS_CMD_SINGLELINEREPLY) {
-        retval = cliReadInlineReply(fd,REDIS_CMD_SINGLELINEREPLY);
-    } else if (rc->flags & REDIS_CMD_BULKREPLY) {
-        retval = cliReadBulkReply(fd,0);
-    } else if (rc->flags & REDIS_CMD_MULTIBULKREPLY) {
-        retval = cliReadMultiBulkReply(fd);
-    }
+    retval = cliReadReply(fd);
     if (retval) {
         close(fd);
         return retval;