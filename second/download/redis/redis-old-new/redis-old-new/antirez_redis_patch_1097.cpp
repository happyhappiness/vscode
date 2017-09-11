@@ -290,10 +290,10 @@ void replicationFeedSlaves(list *slaves, int dictid, robj **argv, int argc) {
 void replicationFeedMonitors(redisClient *c, list *monitors, int dictid, robj **argv, int argc) {
     listNode *ln;
     listIter li;
-    int j, port;
+    int j;
     sds cmdrepr = sdsnew("+");
     robj *cmdobj;
-    char ip[REDIS_IP_STR_LEN];
+    char peerid[REDIS_PEER_ID_LEN];
     struct timeval tv;
 
     gettimeofday(&tv,NULL);
@@ -303,8 +303,8 @@ void replicationFeedMonitors(redisClient *c, list *monitors, int dictid, robj **
     } else if (c->flags & REDIS_UNIX_SOCKET) {
         cmdrepr = sdscatprintf(cmdrepr,"[%d unix:%s] ",dictid,server.unixsocket);
     } else {
-        anetPeerToString(c->fd,ip,sizeof(ip),&port);
-        cmdrepr = sdscatprintf(cmdrepr,"[%d %s:%d] ",dictid,ip,port);
+        getClientPeerId(c,peerid,sizeof(peerid));
+        cmdrepr = sdscatprintf(cmdrepr,"[%d %s] ",dictid,peerid);
     }
 
     for (j = 0; j < argc; j++) {