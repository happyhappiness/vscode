@@ -1802,7 +1802,7 @@ static void replicationFeedSlaves(list *slaves, struct redisCommand *cmd, int di
             robj *lenobj;
 
             lenobj = createObject(REDIS_STRING,
-                sdscatprintf(sdsempty(),"%d\r\n",
+                sdscatprintf(sdsempty(),"%lu\r\n",
                     stringObjectLen(argv[j])));
             lenobj->refcount = 0;
             outv[outc++] = lenobj;
@@ -2019,7 +2019,7 @@ static void addReplyDouble(redisClient *c, double d) {
     char buf[128];
 
     snprintf(buf,sizeof(buf),"%.17g",d);
-    addReplySds(c,sdscatprintf(sdsempty(),"$%d\r\n%s\r\n",
+    addReplySds(c,sdscatprintf(sdsempty(),"$%lu\r\n%s\r\n",
         strlen(buf),buf));
 }
 
@@ -2040,7 +2040,7 @@ static void addReplyBulkLen(redisClient *c, robj *obj) {
             len++;
         }
     }
-    addReplySds(c,sdscatprintf(sdsempty(),"$%d\r\n",len));
+    addReplySds(c,sdscatprintf(sdsempty(),"$%lu\r\n",len));
 }
 
 static void acceptHandler(aeEventLoop *el, int fd, void *privdata, int mask) {
@@ -3214,7 +3214,7 @@ static void keysCommand(redisClient *c) {
     dictEntry *de;
     sds pattern = c->argv[1]->ptr;
     int plen = sdslen(pattern);
-    int numkeys = 0, keyslen = 0;
+    unsigned long numkeys = 0, keyslen = 0;
     robj *lenobj = createObject(REDIS_STRING,NULL);
 
     di = dictGetIterator(c->db->dict);
@@ -3871,7 +3871,7 @@ static void scardCommand(redisClient *c) {
             addReply(c,shared.wrongtypeerr);
         } else {
             s = o->ptr;
-            addReplySds(c,sdscatprintf(sdsempty(),":%d\r\n",
+            addReplySds(c,sdscatprintf(sdsempty(),":%lu\r\n",
                 dictSize(s)));
         }
     }
@@ -3936,12 +3936,12 @@ static int qsortCompareSetsByCardinality(const void *s1, const void *s2) {
     return dictSize(*d1)-dictSize(*d2);
 }
 
-static void sinterGenericCommand(redisClient *c, robj **setskeys, int setsnum, robj *dstkey) {
+static void sinterGenericCommand(redisClient *c, robj **setskeys, unsigned long setsnum, robj *dstkey) {
     dict **dv = zmalloc(sizeof(dict*)*setsnum);
     dictIterator *di;
     dictEntry *de;
     robj *lenobj = NULL, *dstset = NULL;
-    int j, cardinality = 0;
+    unsigned long j, cardinality = 0;
 
     for (j = 0; j < setsnum; j++) {
         robj *setobj;
@@ -4018,9 +4018,9 @@ static void sinterGenericCommand(redisClient *c, robj **setskeys, int setsnum, r
     }
 
     if (!dstkey) {
-        lenobj->ptr = sdscatprintf(sdsempty(),"*%d\r\n",cardinality);
+        lenobj->ptr = sdscatprintf(sdsempty(),"*%lu\r\n",cardinality);
     } else {
-        addReplySds(c,sdscatprintf(sdsempty(),":%d\r\n",
+        addReplySds(c,sdscatprintf(sdsempty(),":%lu\r\n",
             dictSize((dict*)dstset->ptr)));
         server.dirty++;
     }
@@ -4122,7 +4122,7 @@ static void sunionDiffGenericCommand(redisClient *c, robj **setskeys, int setsnu
     if (!dstkey) {
         decrRefCount(dstset);
     } else {
-        addReplySds(c,sdscatprintf(sdsempty(),":%d\r\n",
+        addReplySds(c,sdscatprintf(sdsempty(),":%lu\r\n",
             dictSize((dict*)dstset->ptr)));
         server.dirty++;
     }
@@ -4650,7 +4650,7 @@ static void zcardCommand(redisClient *c) {
             addReply(c,shared.wrongtypeerr);
         } else {
             zs = o->ptr;
-            addReplySds(c,sdscatprintf(sdsempty(),":%d\r\n",zs->zsl->length));
+            addReplySds(c,sdscatprintf(sdsempty(),":%lu\r\n",zs->zsl->length));
         }
     }
 }
@@ -5068,14 +5068,14 @@ static sds genRedisInfoString(void) {
         "redis_version:%s\r\n"
         "arch_bits:%s\r\n"
         "multiplexing_api:%s\r\n"
-        "uptime_in_seconds:%d\r\n"
-        "uptime_in_days:%d\r\n"
+        "uptime_in_seconds:%ld\r\n"
+        "uptime_in_days:%ld\r\n"
         "connected_clients:%d\r\n"
         "connected_slaves:%d\r\n"
         "used_memory:%zu\r\n"
         "changes_since_last_save:%lld\r\n"
         "bgsave_in_progress:%d\r\n"
-        "last_save_time:%d\r\n"
+        "last_save_time:%ld\r\n"
         "total_connections_received:%lld\r\n"
         "total_commands_processed:%lld\r\n"
         "role:%s\r\n"
@@ -5122,7 +5122,7 @@ static sds genRedisInfoString(void) {
 
 static void infoCommand(redisClient *c) {
     sds info = genRedisInfoString();
-    addReplySds(c,sdscatprintf(sdsempty(),"$%d\r\n",sdslen(info)));
+    addReplySds(c,sdscatprintf(sdsempty(),"$%lu\r\n",sdslen(info)));
     addReplySds(c,info);
     addReply(c,shared.crlf);
 }
@@ -5664,7 +5664,7 @@ static void feedAppendOnlyFile(struct redisCommand *cmd, int dictid, robj **argv
         char seldb[64];
 
         snprintf(seldb,sizeof(seldb),"%d",dictid);
-        buf = sdscatprintf(buf,"*2\r\n$6\r\nSELECT\r\n$%d\r\n%s\r\n",
+        buf = sdscatprintf(buf,"*2\r\n$6\r\nSELECT\r\n$%lu\r\n%s\r\n",
             strlen(seldb),seldb);
         server.appendseldb = dictid;
     }
@@ -5689,7 +5689,7 @@ static void feedAppendOnlyFile(struct redisCommand *cmd, int dictid, robj **argv
         robj *o = argv[j];
 
         o = getDecodedObject(o);
-        buf = sdscatprintf(buf,"$%d\r\n",sdslen(o->ptr));
+        buf = sdscatprintf(buf,"$%lu\r\n",sdslen(o->ptr));
         buf = sdscatlen(buf,o->ptr,sdslen(o->ptr));
         buf = sdscatlen(buf,"\r\n",2);
         decrRefCount(o);
@@ -6112,7 +6112,8 @@ static void debugCommand(redisClient *c) {
         val = dictGetEntryVal(de);
         addReplySds(c,sdscatprintf(sdsempty(),
             "+Key at:%p refcount:%d, value at:%p refcount:%d encoding:%d\r\n",
-                key, key->refcount, val, val->refcount, val->encoding));
+                (void*)key, key->refcount, (void*)val, val->refcount,
+                val->encoding));
     } else {
         addReplySds(c,sdsnew(
             "-ERR Syntax error, try DEBUG [SEGFAULT|OBJECT <key>|RELOAD]\r\n"));