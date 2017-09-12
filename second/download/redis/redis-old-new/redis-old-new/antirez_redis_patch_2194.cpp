@@ -659,6 +659,7 @@ static void discardCommand(redisClient *c);
 static void blpopCommand(redisClient *c);
 static void brpopCommand(redisClient *c);
 static void appendCommand(redisClient *c);
+static void substrCommand(redisClient *c);
 static void zrankCommand(redisClient *c);
 
 /*================================= Globals ================================= */
@@ -670,6 +671,7 @@ static struct redisCommand cmdTable[] = {
     {"set",setCommand,3,REDIS_CMD_BULK|REDIS_CMD_DENYOOM,0,0,0},
     {"setnx",setnxCommand,3,REDIS_CMD_BULK|REDIS_CMD_DENYOOM,0,0,0},
     {"append",appendCommand,3,REDIS_CMD_BULK|REDIS_CMD_DENYOOM,1,1,1},
+    {"substr",substrCommand,4,REDIS_CMD_INLINE,1,1,1},
     {"del",delCommand,-2,REDIS_CMD_INLINE,0,0,0},
     {"exists",existsCommand,2,REDIS_CMD_INLINE,1,1,1},
     {"incr",incrCommand,2,REDIS_CMD_INLINE|REDIS_CMD_DENYOOM,1,1,1},
@@ -3764,6 +3766,45 @@ static void appendCommand(redisClient *c) {
     addReplySds(c,sdscatprintf(sdsempty(),":%lu\r\n",(unsigned long)totlen));
 }
 
+static void substrCommand(redisClient *c) {
+    robj *o;
+    long start = atoi(c->argv[2]->ptr);
+    long end = atoi(c->argv[3]->ptr);
+
+    o = lookupKeyRead(c->db,c->argv[1]);
+    if (o == NULL) {
+        addReply(c,shared.nullbulk);
+    } else {
+        if (o->type != REDIS_STRING) {
+            addReply(c,shared.wrongtypeerr);
+        } else {
+            size_t rangelen, strlen = sdslen(o->ptr);
+            sds range;
+
+            /* convert negative indexes */
+            if (start < 0) start = strlen+start;
+            if (end < 0) end = strlen+end;
+            if (start < 0) start = 0;
+            if (end < 0) end = 0;
+
+            /* indexes sanity checks */
+            if (start > end || (size_t)start >= strlen) {
+                /* Out of range start or start > end result in null reply */
+                addReply(c,shared.nullbulk);
+                return;
+            }
+            if ((size_t)end >= strlen) end = strlen-1;
+            rangelen = (end-start)+1;
+
+            /* Return the result */
+            addReplySds(c,sdscatprintf(sdsempty(),"$%lu\r\n",rangelen));
+            range = sdsnewlen((char*)o->ptr+start,rangelen);
+            addReplySds(c,range);
+            addReply(c,shared.crlf);
+        }
+    }
+}
+
 /* ========================= Type agnostic commands ========================= */
 
 static void delCommand(redisClient *c) {