@@ -734,8 +734,8 @@ static int serverCron(struct aeEventLoop *eventLoop, long long id, void *clientD
         size = dictSlots(server.db[j].dict);
         used = dictSize(server.db[j].dict);
         vkeys = dictSize(server.db[j].expires);
-        if (!(loops % 5) && used > 0) {
-            redisLog(REDIS_DEBUG,"DB %d: %d keys (%d volatile) in %d slots HT.",j,used,vkeys,size);
+        if (!(loops % 5) && (used || vkeys)) {
+            redisLog(REDIS_DEBUG,"DB %d: %lld keys (%lld volatile) in %lld slots HT.",j,used,vkeys,size);
             /* dictPrintStats(server.dict); */
         }
     }
@@ -3602,6 +3602,7 @@ static void sortCommand(redisClient *c) {
 static void infoCommand(redisClient *c) {
     sds info;
     time_t uptime = time(NULL)-server.stat_starttime;
+    int j;
     
     info = sdscatprintf(sdsempty(),
         "redis_version:%s\r\n"
@@ -3642,6 +3643,16 @@ static void infoCommand(redisClient *c) {
             (int)(time(NULL)-server.master->lastinteraction)
         );
     }
+    for (j = 0; j < server.dbnum; j++) {
+        long long keys, vkeys;
+
+        keys = dictSize(server.db[j].dict);
+        vkeys = dictSize(server.db[j].expires);
+        if (keys || vkeys) {
+            info = sdscatprintf(info, "db%d: keys=%lld,expires=%lld\r\n",
+                j, keys, vkeys);
+        }
+    }
     addReplySds(c,sdscatprintf(sdsempty(),"$%d\r\n",sdslen(info)));
     addReplySds(c,info);
     addReply(c,shared.crlf);