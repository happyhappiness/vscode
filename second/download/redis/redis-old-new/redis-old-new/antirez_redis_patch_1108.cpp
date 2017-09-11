@@ -293,7 +293,7 @@ void replicationFeedMonitors(redisClient *c, list *monitors, int dictid, robj **
     int j, port;
     sds cmdrepr = sdsnew("+");
     robj *cmdobj;
-    char ip[32];
+    char ip[REDIS_IP_STR_LEN];
     struct timeval tv;
 
     gettimeofday(&tv,NULL);
@@ -303,7 +303,7 @@ void replicationFeedMonitors(redisClient *c, list *monitors, int dictid, robj **
     } else if (c->flags & REDIS_UNIX_SOCKET) {
         cmdrepr = sdscatprintf(cmdrepr,"[%d unix:%s] ",dictid,server.unixsocket);
     } else {
-        anetPeerToString(c->fd,ip,&port);
+        anetPeerToString(c->fd,ip,sizeof(ip),&port);
         cmdrepr = sdscatprintf(cmdrepr,"[%d %s:%d] ",dictid,ip,port);
     }
 