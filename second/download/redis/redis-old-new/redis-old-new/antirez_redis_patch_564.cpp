@@ -361,6 +361,7 @@ void sentinelFlushConfig(void);
 void sentinelGenerateInitialMonitorEvents(void);
 int sentinelSendPing(sentinelRedisInstance *ri);
 int sentinelForceHelloUpdateForMaster(sentinelRedisInstance *master);
+sentinelRedisInstance *getSentinelRedisInstanceByAddrAndRunID(dict *instances, char *ip, int port, char *runid);
 
 /* ========================= Dictionary types =============================== */
 
@@ -977,15 +978,39 @@ instanceLink *releaseInstanceLink(instanceLink *link, sentinelRedisInstance *ri)
  * This way multiple Sentinel objects that refer all to the same physical
  * Sentinel instance but in the context of different masters will use
  * a single connection, will send a single PING per second for failure
- * detection and so forth. */
-void tryConnectionSharing(sentinelRedisInstance *ri) {
+ * detection and so forth.
+ *
+ * Return REDIS_OK if a matching Sentinel was found in the context of a
+ * different master and sharing was performed. Otherwise REDIS_ERR
+ * is returned. */
+int sentinelTryConnectionSharing(sentinelRedisInstance *ri) {
     redisAssert(ri->flags & SRI_SENTINEL);
+    dictIterator *di;
+    dictEntry *de;
+
+    if (ri->runid == NULL) return REDIS_ERR; /* No way to identify it. */
+    if (ri->link->refcount > 1) return REDIS_ERR; /* Already shared. */
 
-    /* TODO:
-     * 1) Check if there is a match.
-     * 2) Free our current link.
-     * 3) Reference the other link and increment its reference count. */
-    REDIS_NOTUSED(ri);
+    di = dictGetIterator(sentinel.masters);
+    while((de = dictNext(di)) != NULL) {
+        sentinelRedisInstance *master = dictGetVal(de), *match;
+        /* We want to share with the same physical Senitnel referenced
+         * in other masters, so skip our master. */
+        if (master == ri->master) continue;
+        match = getSentinelRedisInstanceByAddrAndRunID(master->sentinels,
+                                                       NULL,0,ri->runid);
+        if (match == ri) continue; /* Should never happen but... safer. */
+
+        /* We identified a matching Sentinel, great! Let's free our link
+         * and use the one of the matching Sentinel. */
+        releaseInstanceLink(ri->link,NULL);
+        ri->link = match->link;
+        match->link->refcount++;
+        printf("SHARED!\n");
+        return REDIS_OK;
+    }
+    dictReleaseIterator(di);
+    return REDIS_ERR;
 }
 
 /* This function is called when an hiredis connection reported an error.
@@ -1572,7 +1597,7 @@ char *sentinelHandleConfiguration(char **argv, int argc) {
         }
         if (argc == 5) {
             si->runid = sdsnew(argv[4]);
-            tryConnectionSharing(si);
+            sentinelTryConnectionSharing(si);
         }
     } else if (!strcasecmp(argv[0],"announce-ip") && argc == 2) {
         /* announce-ip <ip-address> */
@@ -2249,7 +2274,7 @@ void sentinelProcessHelloMessage(char *hello, int hello_len) {
                  * for Sentinels we don't have a later chance to fill it,
                  * so do it now. */
                 si->runid = sdsnew(token[2]);
-                tryConnectionSharing(si);
+                sentinelTryConnectionSharing(si);
                 sentinelFlushConfig();
             }
         }