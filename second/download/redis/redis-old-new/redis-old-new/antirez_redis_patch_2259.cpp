@@ -521,7 +521,7 @@ static struct redisCommand cmdTable[] = {
     {"zrem",zremCommand,3,REDIS_CMD_BULK},
     {"zremrangebyscore",zremrangebyscoreCommand,4,REDIS_CMD_INLINE},
     {"zrange",zrangeCommand,4,REDIS_CMD_INLINE},
-    {"zrangebyscore",zrangebyscoreCommand,4,REDIS_CMD_INLINE},
+    {"zrangebyscore",zrangebyscoreCommand,-4,REDIS_CMD_INLINE},
     {"zrevrange",zrevrangeCommand,4,REDIS_CMD_INLINE},
     {"zcard",zcardCommand,2,REDIS_CMD_INLINE},
     {"zscore",zscoreCommand,3,REDIS_CMD_BULK|REDIS_CMD_DENYOOM},
@@ -4559,6 +4559,18 @@ static void zrangebyscoreCommand(redisClient *c) {
     robj *o;
     double min = strtod(c->argv[2]->ptr,NULL);
     double max = strtod(c->argv[3]->ptr,NULL);
+    int offset = 0, limit = -1;
+
+    if (c->argc != 4 && c->argc != 7) {
+        addReplySds(c,sdsnew("-ERR wrong number of arguments\r\n"));
+        return;
+    } else if (c->argc == 7 && strcasecmp(c->argv[4]->ptr,"limit")) {
+        addReply(c,shared.syntaxerr);
+        return;
+    } else if (c->argc == 7) {
+        offset = atoi(c->argv[5]->ptr);
+        limit = atoi(c->argv[6]->ptr);
+    }
 
     o = lookupKeyRead(c->db,c->argv[1]);
     if (o == NULL) {
@@ -4590,12 +4602,19 @@ static void zrangebyscoreCommand(redisClient *c) {
             decrRefCount(lenobj);
 
             while(ln && ln->score <= max) {
+                if (offset) {
+                    offset--;
+                    ln = ln->forward[0];
+                    continue;
+                }
+                if (limit == 0) break;
                 ele = ln->obj;
                 addReplyBulkLen(c,ele);
                 addReply(c,ele);
                 addReply(c,shared.crlf);
                 ln = ln->forward[0];
                 rangelen++;
+                if (limit > 0) limit--;
             }
             lenobj->ptr = sdscatprintf(sdsempty(),"*%d\r\n",rangelen);
         }