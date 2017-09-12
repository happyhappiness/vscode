@@ -27,7 +27,7 @@
  * POSSIBILITY OF SUCH DAMAGE.
  */
 
-#define REDIS_VERSION "1.3.10"
+#define REDIS_VERSION "1.3.12"
 
 #include "fmacros.h"
 #include "config.h"
@@ -76,6 +76,7 @@
 #include "pqsort.h" /* Partial qsort for SORT+LIMIT */
 #include "zipmap.h" /* Compact dictionary-alike data structure */
 #include "sha1.h"   /* SHA1 is used for DEBUG DIGEST */
+#include "release.h" /* Release and/or git repository information */
 
 /* Error codes */
 #define REDIS_OK                0
@@ -2760,21 +2761,6 @@ static void addReplyDouble(redisClient *c, double d) {
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
@@ -2786,8 +2772,11 @@ static void addReplyLongLong(redisClient *c, long long ll) {
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
@@ -2806,7 +2795,8 @@ static void addReplyUlong(redisClient *c, unsigned long ul) {
 }
 
 static void addReplyBulkLen(redisClient *c, robj *obj) {
-    size_t len;
+    size_t len, intlen;
+    char buf[128];
 
     if (obj->encoding == REDIS_ENCODING_RAW) {
         len = sdslen(obj->ptr);
@@ -2823,7 +2813,11 @@ static void addReplyBulkLen(redisClient *c, robj *obj) {
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
@@ -4334,8 +4328,7 @@ static void incrDecrCommand(redisClient *c, long long incr) {
     if (getLongLongFromObjectOrReply(c,o,&value,NULL) != REDIS_OK) return;
 
     value += incr;
-    o = createObject(REDIS_STRING,sdscatprintf(sdsempty(),"%lld",value));
-    o = tryObjectEncoding(o);
+    o = createStringObjectFromLongLong(value);
     retval = dictAdd(c->db->dict,c->argv[1],o);
     if (retval == DICT_ERR) {
         dictReplace(c->db->dict,c->argv[1],o);
@@ -4465,7 +4458,7 @@ static void delCommand(redisClient *c) {
             deleted++;
         }
     }
-    addReplyLong(c,deleted);
+    addReplyLongLong(c,deleted);
 }
 
 static void existsCommand(redisClient *c) {
@@ -4750,7 +4743,7 @@ static void pushGenericCommand(redisClient *c, int where) {
         incrRefCount(c->argv[2]);
     }
     server.dirty++;
-    addReplySds(c,sdscatprintf(sdsempty(),":%d\r\n",listLength(list)));
+    addReplyLongLong(c,listLength(list));
 }
 
 static void lpushCommand(redisClient *c) {
@@ -5252,7 +5245,7 @@ static void sinterGenericCommand(redisClient *c, robj **setskeys, unsigned long
         if (dictSize((dict*)dstset->ptr) > 0) {
             dictAdd(c->db->dict,dstkey,dstset);
             incrRefCount(dstkey);
-            addReplyLong(c,dictSize((dict*)dstset->ptr));
+            addReplyLongLong(c,dictSize((dict*)dstset->ptr));
         } else {
             decrRefCount(dstset);
             addReply(c,shared.czero);
@@ -5355,7 +5348,7 @@ static void sunionDiffGenericCommand(redisClient *c, robj **setskeys, int setsnu
         if (dictSize((dict*)dstset->ptr) > 0) {
             dictAdd(c->db->dict,dstkey,dstset);
             incrRefCount(dstkey);
-            addReplyLong(c,dictSize((dict*)dstset->ptr));
+            addReplyLongLong(c,dictSize((dict*)dstset->ptr));
         } else {
             decrRefCount(dstset);
             addReply(c,shared.czero);
@@ -5834,7 +5827,7 @@ static void zremrangebyscoreCommand(redisClient *c) {
     if (htNeedsResize(zs->dict)) dictResize(zs->dict);
     if (dictSize(zs->dict) == 0) deleteKey(c->db,c->argv[1]);
     server.dirty += deleted;
-    addReplyLong(c,deleted);
+    addReplyLongLong(c,deleted);
 }
 
 static void zremrangebyrankCommand(redisClient *c) {
@@ -5872,7 +5865,7 @@ static void zremrangebyrankCommand(redisClient *c) {
     if (htNeedsResize(zs->dict)) dictResize(zs->dict);
     if (dictSize(zs->dict) == 0) deleteKey(c->db,c->argv[1]);
     server.dirty += deleted;
-    addReplyLong(c, deleted);
+    addReplyLongLong(c, deleted);
 }
 
 typedef struct {
@@ -6058,7 +6051,7 @@ static void zunionInterGenericCommand(redisClient *c, robj *dstkey, int op) {
     if (dstzset->zsl->length) {
         dictAdd(c->db->dict,dstkey,dstobj);
         incrRefCount(dstkey);
-        addReplyLong(c, dstzset->zsl->length);
+        addReplyLongLong(c, dstzset->zsl->length);
         server.dirty++;
     } else {
         decrRefCount(dstobj);
@@ -6254,7 +6247,7 @@ static void genericZrangebyscoreCommand(redisClient *c, int justcount) {
                 if (limit > 0) limit--;
             }
             if (justcount) {
-                addReplyLong(c,(long)rangelen);
+                addReplyLongLong(c,(long)rangelen);
             } else {
                 lenobj->ptr = sdscatprintf(sdsempty(),"*%lu\r\n",
                      withscores ? (rangelen*2) : rangelen);
@@ -6324,9 +6317,9 @@ static void zrankGenericCommand(redisClient *c, int reverse) {
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
@@ -7183,6 +7176,8 @@ static sds genRedisInfoString(void) {
     bytesToHuman(hmem,zmalloc_used_memory());
     info = sdscatprintf(sdsempty(),
         "redis_version:%s\r\n"
+        "redis_git_sha1:%s\r\n"
+        "redis_git_dirty:%d\r\n"
         "arch_bits:%s\r\n"
         "multiplexing_api:%s\r\n"
         "process_id:%ld\r\n"
@@ -7200,13 +7195,15 @@ static sds genRedisInfoString(void) {
         "total_connections_received:%lld\r\n"
         "total_commands_processed:%lld\r\n"
         "expired_keys:%lld\r\n"
-        "hash_max_zipmap_entries:%ld\r\n"
-        "hash_max_zipmap_value:%ld\r\n"
+        "hash_max_zipmap_entries:%zu\r\n"
+        "hash_max_zipmap_value:%zu\r\n"
         "pubsub_channels:%ld\r\n"
         "pubsub_patterns:%u\r\n"
         "vm_enabled:%d\r\n"
         "role:%s\r\n"
         ,REDIS_VERSION,
+        REDIS_GIT_SHA1,
+        strtol(REDIS_GIT_DIRTY,NULL,10) > 0,
         (sizeof(long) == 8) ? "64" : "32",
         aeGetApiName(),
         (long) getpid(),
@@ -8727,6 +8724,48 @@ static void aofRemoveTempFile(pid_t childpid) {
  * as a fully non-blocking VM.
  */
 
+/* Called when the user switches from "appendonly yes" to "appendonly no"
+ * at runtime using the CONFIG command. */
+static void stopAppendOnly(void) {
+    flushAppendOnlyFile();
+    fsync(server.appendfd);
+    close(server.appendfd);
+
+    server.appendfd = -1;
+    server.appendseldb = -1;
+    server.appendonly = 0;
+    /* rewrite operation in progress? kill it, wait child exit */
+    if (server.bgsavechildpid != -1) {
+        int statloc;
+
+        if (kill(server.bgsavechildpid,SIGKILL) != -1)
+            wait3(&statloc,0,NULL);
+        /* reset the buffer accumulating changes while the child saves */
+        sdsfree(server.bgrewritebuf);
+        server.bgrewritebuf = sdsempty();
+        server.bgsavechildpid = -1;
+    }
+}
+
+/* Called when the user switches from "appendonly no" to "appendonly yes"
+ * at runtime using the CONFIG command. */
+static int startAppendOnly(void) {
+    server.appendonly = 1;
+    server.lastfsync = time(NULL);
+    server.appendfd = open(server.appendfilename,O_WRONLY|O_APPEND|O_CREAT,0644);
+    if (server.appendfd == -1) {
+        redisLog(REDIS_WARNING,"Used tried to switch on AOF via CONFIG, but I can't open the AOF file: %s",strerror(errno));
+        return REDIS_ERR;
+    }
+    if (rewriteAppendOnlyFileBackground() == REDIS_ERR) {
+        server.appendonly = 0;
+        close(server.appendfd);
+        redisLog(REDIS_WARNING,"Used tried to switch on AOF via CONFIG, I can't trigger a background AOF rewrite operation. Check the above logs for more info about the error.",strerror(errno));
+        return REDIS_ERR;
+    }
+    return REDIS_OK;
+}
+
 /* =================== Virtual Memory - Blocking Side  ====================== */
 
 static void vmInit(void) {
@@ -9829,6 +9868,8 @@ static void handleClientsBlockedOnSwappedKey(redisDb *db, robj *key) {
 
 static void configSetCommand(redisClient *c) {
     robj *o = getDecodedObject(c->argv[3]);
+    long long ll;
+
     if (!strcasecmp(c->argv[2]->ptr,"dbfilename")) {
         zfree(server.dbfilename);
         server.dbfilename = zstrdup(o->ptr);
@@ -9839,7 +9880,13 @@ static void configSetCommand(redisClient *c) {
         zfree(server.masterauth);
         server.masterauth = zstrdup(o->ptr);
     } else if (!strcasecmp(c->argv[2]->ptr,"maxmemory")) {
-        server.maxmemory = strtoll(o->ptr, NULL, 10);
+        if (getLongLongFromObject(o,&ll) == REDIS_ERR ||
+            ll < 0) goto badfmt;
+        server.maxmemory = ll;
+    } else if (!strcasecmp(c->argv[2]->ptr,"timeout")) {
+        if (getLongLongFromObject(o,&ll) == REDIS_ERR ||
+            ll < 0 || ll > LONG_MAX) goto badfmt;
+        server.maxidletime = ll;
     } else if (!strcasecmp(c->argv[2]->ptr,"appendfsync")) {
         if (!strcasecmp(o->ptr,"no")) {
             server.appendfsync = APPENDFSYNC_NO;
@@ -9850,6 +9897,23 @@ static void configSetCommand(redisClient *c) {
         } else {
             goto badfmt;
         }
+    } else if (!strcasecmp(c->argv[2]->ptr,"appendonly")) {
+        int old = server.appendonly;
+        int new = yesnotoi(o->ptr);
+
+        if (new == -1) goto badfmt;
+        if (old != new) {
+            if (new == 0) {
+                stopAppendOnly();
+            } else {
+                if (startAppendOnly() == REDIS_ERR) {
+                    addReplySds(c,sdscatprintf(sdsempty(),
+                        "-ERR Unable to turn on AOF. Check server logs.\r\n"));
+                    decrRefCount(o);
+                    return;
+                }
+            }
+        }
     } else if (!strcasecmp(c->argv[2]->ptr,"save")) {
         int vlen, j;
         sds *v = sdssplitlen(o->ptr,sdslen(o->ptr)," ",1,&vlen);
@@ -9930,11 +9994,24 @@ static void configGetCommand(redisClient *c) {
     if (stringmatch(pattern,"maxmemory",0)) {
         char buf[128];
 
-        snprintf(buf,128,"%llu\n",server.maxmemory);
+        ll2string(buf,128,server.maxmemory);
         addReplyBulkCString(c,"maxmemory");
         addReplyBulkCString(c,buf);
         matches++;
     }
+    if (stringmatch(pattern,"timeout",0)) {
+        char buf[128];
+
+        ll2string(buf,128,server.maxidletime);
+        addReplyBulkCString(c,"timeout");
+        addReplyBulkCString(c,buf);
+        matches++;
+    }
+    if (stringmatch(pattern,"appendonly",0)) {
+        addReplyBulkCString(c,"appendonly");
+        addReplyBulkCString(c,server.appendonly ? "yes" : "no");
+        matches++;
+    }
     if (stringmatch(pattern,"appendfsync",0)) {
         char *policy;
 
@@ -10036,7 +10113,7 @@ static int pubsubSubscribeChannel(redisClient *c, robj *channel) {
     addReply(c,shared.mbulk3);
     addReply(c,shared.subscribebulk);
     addReplyBulk(c,channel);
-    addReplyLong(c,dictSize(c->pubsub_channels)+listLength(c->pubsub_patterns));
+    addReplyLongLong(c,dictSize(c->pubsub_channels)+listLength(c->pubsub_patterns));
     return retval;
 }
 
@@ -10072,7 +10149,7 @@ static int pubsubUnsubscribeChannel(redisClient *c, robj *channel, int notify) {
         addReply(c,shared.mbulk3);
         addReply(c,shared.unsubscribebulk);
         addReplyBulk(c,channel);
-        addReplyLong(c,dictSize(c->pubsub_channels)+
+        addReplyLongLong(c,dictSize(c->pubsub_channels)+
                        listLength(c->pubsub_patterns));
 
     }
@@ -10098,7 +10175,7 @@ static int pubsubSubscribePattern(redisClient *c, robj *pattern) {
     addReply(c,shared.mbulk3);
     addReply(c,shared.psubscribebulk);
     addReplyBulk(c,pattern);
-    addReplyLong(c,dictSize(c->pubsub_channels)+listLength(c->pubsub_patterns));
+    addReplyLongLong(c,dictSize(c->pubsub_channels)+listLength(c->pubsub_patterns));
     return retval;
 }
 
@@ -10123,7 +10200,7 @@ static int pubsubUnsubscribePattern(redisClient *c, robj *pattern, int notify) {
         addReply(c,shared.mbulk3);
         addReply(c,shared.punsubscribebulk);
         addReplyBulk(c,pattern);
-        addReplyLong(c,dictSize(c->pubsub_channels)+
+        addReplyLongLong(c,dictSize(c->pubsub_channels)+
                        listLength(c->pubsub_patterns));
     }
     decrRefCount(pattern);
@@ -10251,7 +10328,7 @@ static void punsubscribeCommand(redisClient *c) {
 
 static void publishCommand(redisClient *c) {
     int receivers = pubsubPublishMessage(c->argv[1],c->argv[2]);
-    addReplyLong(c,receivers);
+    addReplyLongLong(c,receivers);
 }
 
 /* ================================= Debugging ============================== */