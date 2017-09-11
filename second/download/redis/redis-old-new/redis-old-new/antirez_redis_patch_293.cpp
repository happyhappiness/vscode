@@ -518,7 +518,7 @@ sentinelAddr *createSentinelAddr(char *hostname, int port) {
     char ip[NET_IP_STR_LEN];
     sentinelAddr *sa;
 
-    if (port <= 0 || port > 65535) {
+    if (port < 0 || port > 65535) {
         errno = EINVAL;
         return NULL;
     }
@@ -1132,7 +1132,8 @@ void sentinelDisconnectCallback(const redisAsyncContext *c, int status) {
  * createSentinelAddr() function.
  *
  * The function may also fail and return NULL with errno set to EBUSY if
- * a master or slave with the same name already exists. */
+ * a master with the same name, a slave with the same address, or a sentinel
+ * with the same ID already exists. */
 
 sentinelRedisInstance *createSentinelRedisInstance(char *name, int flags, char *hostname, int port, int quorum, sentinelRedisInstance *master) {
     sentinelRedisInstance *ri;
@@ -1147,8 +1148,8 @@ sentinelRedisInstance *createSentinelRedisInstance(char *name, int flags, char *
     addr = createSentinelAddr(hostname,port);
     if (addr == NULL) return NULL;
 
-    /* For slaves and sentinel we use ip:port as name. */
-    if (flags & (SRI_SLAVE|SRI_SENTINEL)) {
+    /* For slaves use ip:port as name. */
+    if (flags & SRI_SLAVE) {
         anetFormatAddr(slavename, sizeof(slavename), hostname, port);
         name = slavename;
     }
@@ -1657,15 +1658,15 @@ char *sentinelHandleConfiguration(char **argv, int argc) {
                (argc == 4 || argc == 5)) {
         sentinelRedisInstance *si;
 
-        /* known-sentinel <name> <ip> <port> [runid] */
-        ri = sentinelGetMasterByName(argv[1]);
-        if (!ri) return "No such master with specified name.";
-        if ((si = createSentinelRedisInstance(NULL,SRI_SENTINEL,argv[2],
-                    atoi(argv[3]), ri->quorum, ri)) == NULL)
-        {
-            return "Wrong hostname or port for sentinel.";
-        }
-        if (argc == 5) {
+        if (argc == 5) { /* Ignore the old form without runid. */
+            /* known-sentinel <name> <ip> <port> [runid] */
+            ri = sentinelGetMasterByName(argv[1]);
+            if (!ri) return "No such master with specified name.";
+            if ((si = createSentinelRedisInstance(argv[4],SRI_SENTINEL,argv[2],
+                        atoi(argv[3]), ri->quorum, ri)) == NULL)
+            {
+                return "Wrong hostname or port for sentinel.";
+            }
             si->runid = sdsnew(argv[4]);
             sentinelTryConnectionSharing(si);
         }
@@ -1796,11 +1797,10 @@ void rewriteConfigSentinelOption(struct rewriteConfigState *state) {
         di2 = dictGetIterator(master->sentinels);
         while((de = dictNext(di2)) != NULL) {
             ri = dictGetVal(de);
+            if (ri->runid == NULL) continue;
             line = sdscatprintf(sdsempty(),
-                "sentinel known-sentinel %s %s %d%s%s",
-                master->name, ri->addr->ip, ri->addr->port,
-                ri->runid ? " " : "",
-                ri->runid ? ri->runid : "");
+                "sentinel known-sentinel %s %s %d %s",
+                master->name, ri->addr->ip, ri->addr->port, ri->runid);
             rewriteConfigRewriteLine(state,"sentinel",line,1);
         }
         dictReleaseIterator(di2);
@@ -1895,6 +1895,7 @@ void sentinelSetClientName(sentinelRedisInstance *ri, redisAsyncContext *c, char
  * one of the two links (commands and pub/sub) is missing. */
 void sentinelReconnectInstance(sentinelRedisInstance *ri) {
     if (ri->link->disconnected == 0) return;
+    if (ri->addr->port == 0) return; /* port == 0 means invalid address. */
     instanceLink *link = ri->link;
     mstime_t now = mstime();
 
@@ -2340,11 +2341,25 @@ void sentinelProcessHelloMessage(char *hello, int hello_len) {
             if (removed) {
                 sentinelEvent(LL_NOTICE,"+sentinel-address-switch",master,
                     "%@ ip %s port %d for %s", token[0],port,token[2]);
+            } else {
+                /* Check if there is another Sentinel with the same address this
+                 * new one is reporting. What we do if this happens is to set its
+                 * port to 0, to signal the address is invalid. We'll update it
+                 * later if we get an HELLO message. */
+                sentinelRedisInstance *other =
+                    getSentinelRedisInstanceByAddrAndRunID(
+                        master->sentinels, token[0],port,NULL);
+                if (other) {
+                    sentinelEvent(LL_NOTICE,"+sentinel-invalid-addr",other,"%@");
+                    other->addr->port = 0; /* It means: invalid address. */
+                    sentinelUpdateSentinelAddressInAllMasters(other);
+                }
             }
 
             /* Add the new sentinel. */
-            si = createSentinelRedisInstance(NULL,SRI_SENTINEL,
+            si = createSentinelRedisInstance(token[2],SRI_SENTINEL,
                             token[0],port,master->quorum,master);
+
             if (si) {
                 if (!removed) sentinelEvent(LL_NOTICE,"+sentinel",si,"%@");
                 /* The runid is NULL after a new instance creation and
@@ -2366,7 +2381,7 @@ void sentinelProcessHelloMessage(char *hello, int hello_len) {
         }
 
         /* Update master info if received configuration is newer. */
-        if (master->config_epoch < master_config_epoch) {
+        if (si && master->config_epoch < master_config_epoch) {
             master->config_epoch = master_config_epoch;
             if (master_port != master->addr->port ||
                 strcmp(master->addr->ip, token[5]))