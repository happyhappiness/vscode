@@ -536,9 +536,9 @@ static struct redisCommand cmdTable[] = {
     {"zincrby",zincrbyCommand,4,REDIS_CMD_BULK|REDIS_CMD_DENYOOM},
     {"zrem",zremCommand,3,REDIS_CMD_BULK},
     {"zremrangebyscore",zremrangebyscoreCommand,4,REDIS_CMD_INLINE},
-    {"zrange",zrangeCommand,4,REDIS_CMD_INLINE},
+    {"zrange",zrangeCommand,-4,REDIS_CMD_INLINE},
     {"zrangebyscore",zrangebyscoreCommand,-4,REDIS_CMD_INLINE},
-    {"zrevrange",zrevrangeCommand,4,REDIS_CMD_INLINE},
+    {"zrevrange",zrevrangeCommand,-4,REDIS_CMD_INLINE},
     {"zcard",zcardCommand,2,REDIS_CMD_INLINE},
     {"zscore",zscoreCommand,3,REDIS_CMD_BULK|REDIS_CMD_DENYOOM},
     {"incrby",incrbyCommand,3,REDIS_CMD_INLINE|REDIS_CMD_DENYOOM},
@@ -4531,6 +4531,14 @@ static void zrangeGenericCommand(redisClient *c, int reverse) {
     robj *o;
     int start = atoi(c->argv[2]->ptr);
     int end = atoi(c->argv[3]->ptr);
+    int withscores = 0;
+
+    if (c->argc == 5 && !strcasecmp(c->argv[4]->ptr,"withscores")) {
+        withscores = 1;
+    } else if (c->argc >= 5) {
+        addReply(c,shared.syntaxerr);
+        return;
+    }
 
     o = lookupKeyRead(c->db,c->argv[1]);
     if (o == NULL) {
@@ -4573,12 +4581,15 @@ static void zrangeGenericCommand(redisClient *c, int reverse) {
                     ln = ln->forward[0];
             }
 
-            addReplySds(c,sdscatprintf(sdsempty(),"*%d\r\n",rangelen));
+            addReplySds(c,sdscatprintf(sdsempty(),"*%d\r\n",
+                withscores ? (rangelen*2) : rangelen));
             for (j = 0; j < rangelen; j++) {
                 ele = ln->obj;
                 addReplyBulkLen(c,ele);
                 addReply(c,ele);
                 addReply(c,shared.crlf);
+                if (withscores)
+                    addReplyDouble(c,ln->score);
                 ln = reverse ? ln->backward : ln->forward[0];
             }
         }