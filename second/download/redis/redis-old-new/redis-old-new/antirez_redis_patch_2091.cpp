@@ -2760,21 +2760,6 @@ static void addReplyDouble(redisClient *c, double d) {
         (unsigned long) strlen(buf),buf));
 }
 
-static void addReplyLong(redisClient *c, long l) {
-    char buf[128];
-    size_t len;
-
-    if (l == 0) {
-        addReply(c,shared.czero);
-        return;
-    } else if (l == 1) {
-        addReply(c,shared.cone);
-        return;
-    }
-    len = snprintf(buf,sizeof(buf),":%ld\r\n",l);
-    addReplySds(c,sdsnewlen(buf,len));
-}
-
 static void addReplyLongLong(redisClient *c, long long ll) {
     char buf[128];
     size_t len;
@@ -2786,8 +2771,11 @@ static void addReplyLongLong(redisClient *c, long long ll) {
         addReply(c,shared.cone);
         return;
     }
-    len = snprintf(buf,sizeof(buf),":%lld\r\n",ll);
-    addReplySds(c,sdsnewlen(buf,len));
+    buf[0] = ':';
+    len = ll2string(buf+1,sizeof(buf)-1,ll);
+    buf[len+1] = '\r';
+    buf[len+2] = '\n';
+    addReplySds(c,sdsnewlen(buf,len+3));
 }
 
 static void addReplyUlong(redisClient *c, unsigned long ul) {
@@ -2806,7 +2794,8 @@ static void addReplyUlong(redisClient *c, unsigned long ul) {
 }
 
 static void addReplyBulkLen(redisClient *c, robj *obj) {
-    size_t len;
+    size_t len, intlen;
+    char buf[128];
 
     if (obj->encoding == REDIS_ENCODING_RAW) {
         len = sdslen(obj->ptr);
@@ -2823,7 +2812,11 @@ static void addReplyBulkLen(redisClient *c, robj *obj) {
             len++;
         }
     }
-    addReplySds(c,sdscatprintf(sdsempty(),"$%lu\r\n",(unsigned long)len));
+    buf[0] = '$';
+    intlen = ll2string(buf+1,sizeof(buf)-1,(long long)len);
+    buf[intlen+1] = '\r';
+    buf[intlen+2] = '\n';
+    addReplySds(c,sdsnewlen(buf,intlen+3));
 }
 
 static void addReplyBulk(redisClient *c, robj *obj) {
@@ -4464,7 +4457,7 @@ static void delCommand(redisClient *c) {
             deleted++;
         }
     }
-    addReplyLong(c,deleted);
+    addReplyLongLong(c,deleted);
 }
 
 static void existsCommand(redisClient *c) {
@@ -4749,7 +4742,7 @@ static void pushGenericCommand(redisClient *c, int where) {
         incrRefCount(c->argv[2]);
     }
     server.dirty++;
-    addReplySds(c,sdscatprintf(sdsempty(),":%d\r\n",listLength(list)));
+    addReplyLongLong(c,listLength(list));
 }
 
 static void lpushCommand(redisClient *c) {
@@ -5251,7 +5244,7 @@ static void sinterGenericCommand(redisClient *c, robj **setskeys, unsigned long
         if (dictSize((dict*)dstset->ptr) > 0) {
             dictAdd(c->db->dict,dstkey,dstset);
             incrRefCount(dstkey);
-            addReplyLong(c,dictSize((dict*)dstset->ptr));
+            addReplyLongLong(c,dictSize((dict*)dstset->ptr));
         } else {
             decrRefCount(dstset);
             addReply(c,shared.czero);
@@ -5354,7 +5347,7 @@ static void sunionDiffGenericCommand(redisClient *c, robj **setskeys, int setsnu
         if (dictSize((dict*)dstset->ptr) > 0) {
             dictAdd(c->db->dict,dstkey,dstset);
             incrRefCount(dstkey);
-            addReplyLong(c,dictSize((dict*)dstset->ptr));
+            addReplyLongLong(c,dictSize((dict*)dstset->ptr));
         } else {
             decrRefCount(dstset);
             addReply(c,shared.czero);
@@ -5833,7 +5826,7 @@ static void zremrangebyscoreCommand(redisClient *c) {
     if (htNeedsResize(zs->dict)) dictResize(zs->dict);
     if (dictSize(zs->dict) == 0) deleteKey(c->db,c->argv[1]);
     server.dirty += deleted;
-    addReplyLong(c,deleted);
+    addReplyLongLong(c,deleted);
 }
 
 static void zremrangebyrankCommand(redisClient *c) {
@@ -5871,7 +5864,7 @@ static void zremrangebyrankCommand(redisClient *c) {
     if (htNeedsResize(zs->dict)) dictResize(zs->dict);
     if (dictSize(zs->dict) == 0) deleteKey(c->db,c->argv[1]);
     server.dirty += deleted;
-    addReplyLong(c, deleted);
+    addReplyLongLong(c, deleted);
 }
 
 typedef struct {
@@ -6057,7 +6050,7 @@ static void zunionInterGenericCommand(redisClient *c, robj *dstkey, int op) {
     if (dstzset->zsl->length) {
         dictAdd(c->db->dict,dstkey,dstobj);
         incrRefCount(dstkey);
-        addReplyLong(c, dstzset->zsl->length);
+        addReplyLongLong(c, dstzset->zsl->length);
         server.dirty++;
     } else {
         decrRefCount(dstobj);
@@ -6253,7 +6246,7 @@ static void genericZrangebyscoreCommand(redisClient *c, int justcount) {
                 if (limit > 0) limit--;
             }
             if (justcount) {
-                addReplyLong(c,(long)rangelen);
+                addReplyLongLong(c,(long)rangelen);
             } else {
                 lenobj->ptr = sdscatprintf(sdsempty(),"*%lu\r\n",
                      withscores ? (rangelen*2) : rangelen);
@@ -6323,9 +6316,9 @@ static void zrankGenericCommand(redisClient *c, int reverse) {
     rank = zslGetRank(zsl, *score, c->argv[2]);
     if (rank) {
         if (reverse) {
-            addReplyLong(c, zsl->length - rank);
+            addReplyLongLong(c, zsl->length - rank);
         } else {
-            addReplyLong(c, rank-1);
+            addReplyLongLong(c, rank-1);
         }
     } else {
         addReply(c,shared.nullbulk);
@@ -10035,7 +10028,7 @@ static int pubsubSubscribeChannel(redisClient *c, robj *channel) {
     addReply(c,shared.mbulk3);
     addReply(c,shared.subscribebulk);
     addReplyBulk(c,channel);
-    addReplyLong(c,dictSize(c->pubsub_channels)+listLength(c->pubsub_patterns));
+    addReplyLongLong(c,dictSize(c->pubsub_channels)+listLength(c->pubsub_patterns));
     return retval;
 }
 
@@ -10071,7 +10064,7 @@ static int pubsubUnsubscribeChannel(redisClient *c, robj *channel, int notify) {
         addReply(c,shared.mbulk3);
         addReply(c,shared.unsubscribebulk);
         addReplyBulk(c,channel);
-        addReplyLong(c,dictSize(c->pubsub_channels)+
+        addReplyLongLong(c,dictSize(c->pubsub_channels)+
                        listLength(c->pubsub_patterns));
 
     }
@@ -10097,7 +10090,7 @@ static int pubsubSubscribePattern(redisClient *c, robj *pattern) {
     addReply(c,shared.mbulk3);
     addReply(c,shared.psubscribebulk);
     addReplyBulk(c,pattern);
-    addReplyLong(c,dictSize(c->pubsub_channels)+listLength(c->pubsub_patterns));
+    addReplyLongLong(c,dictSize(c->pubsub_channels)+listLength(c->pubsub_patterns));
     return retval;
 }
 
@@ -10122,7 +10115,7 @@ static int pubsubUnsubscribePattern(redisClient *c, robj *pattern, int notify) {
         addReply(c,shared.mbulk3);
         addReply(c,shared.punsubscribebulk);
         addReplyBulk(c,pattern);
-        addReplyLong(c,dictSize(c->pubsub_channels)+
+        addReplyLongLong(c,dictSize(c->pubsub_channels)+
                        listLength(c->pubsub_patterns));
     }
     decrRefCount(pattern);
@@ -10250,7 +10243,7 @@ static void punsubscribeCommand(redisClient *c) {
 
 static void publishCommand(redisClient *c) {
     int receivers = pubsubPublishMessage(c->argv[1],c->argv[2]);
-    addReplyLong(c,receivers);
+    addReplyLongLong(c,receivers);
 }
 
 /* ================================= Debugging ============================== */