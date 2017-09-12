@@ -448,6 +448,7 @@ static void zrangebyscoreCommand(redisClient *c);
 static void zrevrangeCommand(redisClient *c);
 static void zlenCommand(redisClient *c);
 static void zremCommand(redisClient *c);
+static void zscoreCommand(redisClient *c);
 
 /*================================= Globals ================================= */
 
@@ -492,6 +493,7 @@ static struct redisCommand cmdTable[] = {
     {"zrangebyscore",zrangebyscoreCommand,4,REDIS_CMD_INLINE},
     {"zrevrange",zrevrangeCommand,4,REDIS_CMD_INLINE},
     {"zlen",zlenCommand,2,REDIS_CMD_INLINE},
+    {"zscore",zscoreCommand,3,REDIS_CMD_BULK|REDIS_CMD_DENYOOM},
     {"incrby",incrbyCommand,3,REDIS_CMD_INLINE|REDIS_CMD_DENYOOM},
     {"decrby",decrbyCommand,3,REDIS_CMD_INLINE|REDIS_CMD_DENYOOM},
     {"getset",getsetCommand,3,REDIS_CMD_BULK|REDIS_CMD_DENYOOM},
@@ -4159,6 +4161,36 @@ static void zlenCommand(redisClient *c) {
     }
 }
 
+static void zscoreCommand(redisClient *c) {
+    robj *o;
+    zset *zs;
+    
+    o = lookupKeyRead(c->db,c->argv[1]);
+    if (o == NULL) {
+        addReply(c,shared.czero);
+        return;
+    } else {
+        if (o->type != REDIS_ZSET) {
+            addReply(c,shared.wrongtypeerr);
+        } else {
+            dictEntry *de;
+
+            zs = o->ptr;
+            de = dictFind(zs->dict,c->argv[2]);
+            if (!de) {
+                addReply(c,shared.nullbulk);
+            } else {
+                char buf[128];
+                double *score = dictGetEntryVal(de);
+
+                snprintf(buf,sizeof(buf),"%.16g",*score);
+                addReplySds(c,sdscatprintf(sdsempty(),"$%d\r\n%s\r\n",
+                    strlen(buf),buf));
+            }
+        }
+    }
+}
+
 /* ========================= Non type-specific commands  ==================== */
 
 static void flushdbCommand(redisClient *c) {