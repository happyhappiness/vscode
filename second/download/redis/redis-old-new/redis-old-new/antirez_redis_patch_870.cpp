@@ -239,7 +239,6 @@ void replicationFeedMonitors(redisClient *c, list *monitors, int dictid, robj **
     int j;
     sds cmdrepr = sdsnew("+");
     robj *cmdobj;
-    char peerid[REDIS_PEER_ID_LEN];
     struct timeval tv;
 
     gettimeofday(&tv,NULL);
@@ -249,8 +248,7 @@ void replicationFeedMonitors(redisClient *c, list *monitors, int dictid, robj **
     } else if (c->flags & REDIS_UNIX_SOCKET) {
         cmdrepr = sdscatprintf(cmdrepr,"[%d unix:%s] ",dictid,server.unixsocket);
     } else {
-        getClientPeerId(c,peerid,sizeof(peerid));
-        cmdrepr = sdscatprintf(cmdrepr,"[%d %s] ",dictid,peerid);
+        cmdrepr = sdscatprintf(cmdrepr,"[%d %s] ",dictid,getClientPeerId(c));
     }
 
     for (j = 0; j < argc; j++) {
@@ -1387,6 +1385,12 @@ void replicationCacheMaster(redisClient *c) {
     /* Set fd to -1 so that we can safely call freeClient(c) later. */
     c->fd = -1;
 
+    /* Invalidate the Peer ID cache. */
+    if (c->peerid) {
+        sdsfree(c->peerid);
+        c->peerid = NULL;
+    }
+
     /* Caching the master happens instead of the actual freeClient() call,
      * so make sure to adjust the replication state. This function will
      * also set server.master to NULL. */