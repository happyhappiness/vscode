@@ -2811,6 +2811,31 @@ sentinelRedisInstance *sentinelGetMasterByNameOrReplyError(redisClient *c,
     return ri;
 }
 
+#define SENTINEL_ISQR_OK 0
+#define SENTINEL_ISQR_NOQUORUM (1<<0)
+#define SENTINEL_ISQR_NOAUTH (1<<1)
+int sentinelIsQuorumReachable(sentinelRedisInstance *master, int *usableptr) {
+    dictIterator *di;
+    dictEntry *de;
+    int usable = 1; /* Number of usable Sentinels. Init to 1 to count myself. */
+    int result = SENTINEL_ISQR_OK;
+    int voters = dictSize(master->sentinels)+1; /* Known Sentinels + myself. */
+
+    di = dictGetIterator(master->sentinels);
+    while((de = dictNext(di)) != NULL) {
+        sentinelRedisInstance *ri = dictGetVal(de);
+
+        if (ri->flags & (SRI_S_DOWN|SRI_O_DOWN)) continue;
+        usable++;
+    }
+    dictReleaseIterator(di);
+
+    if (usable < (int)master->quorum) result |= SENTINEL_ISQR_NOQUORUM;
+    if (usable < voters/2+1) result |= SENTINEL_ISQR_NOAUTH;
+    if (usableptr) *usableptr = usable;
+    return result;
+}
+
 void sentinelCommand(redisClient *c) {
     if (!strcasecmp(c->argv[1]->ptr,"masters")) {
         /* SENTINEL MASTERS */
@@ -2993,6 +3018,32 @@ void sentinelCommand(redisClient *c) {
         dictDelete(sentinel.masters,c->argv[2]->ptr);
         sentinelFlushConfig();
         addReply(c,shared.ok);
+    } else if (!strcasecmp(c->argv[1]->ptr,"ckquorum")) {
+        /* SENTINEL CKQUORUM <name> */
+        sentinelRedisInstance *ri;
+        int usable;
+
+        if ((ri = sentinelGetMasterByNameOrReplyError(c,c->argv[2]))
+            == NULL) return;
+        int result = sentinelIsQuorumReachable(ri,&usable);
+        if (result == SENTINEL_ISQR_OK) {
+            addReplySds(c, sdscatfmt(sdsempty(),
+                "+OK %i usable Sentinels. Quorum and failover authorization "
+                "can be reached\r\n",usable));
+        } else {
+            sds e = sdscatfmt(sdsempty(),
+                "-NOQUORUM %i usable Sentinels. ",usable);
+            if (result & SENTINEL_ISQR_NOQUORUM)
+                e = sdscat(e,"Not enough available Sentinels to reach the"
+                             " specified quorum for this master");
+            if (result & SENTINEL_ISQR_NOAUTH) {
+                if (result & SENTINEL_ISQR_NOQUORUM) e = sdscat(e,". ");
+                e = sdscat(e, "Not enough available Sentinels to reach the"
+                              " majority and authorize a failover");
+            }
+            e = sdscat(e,"\r\n");
+            addReplySds(c,e);
+        }
     } else if (!strcasecmp(c->argv[1]->ptr,"set")) {
         if (c->argc < 3 || c->argc % 2 == 0) goto numargserr;
         sentinelSetCommand(c);