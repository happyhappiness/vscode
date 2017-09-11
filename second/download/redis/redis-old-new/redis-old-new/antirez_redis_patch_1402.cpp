@@ -50,17 +50,23 @@ void replicationFeedSlaves(list *slaves, int dictid, robj **argv, int argc) {
     }
 }
 
-void replicationFeedMonitors(list *monitors, int dictid, robj **argv, int argc) {
+void replicationFeedMonitors(redisClient *c, list *monitors, int dictid, robj **argv, int argc) {
     listNode *ln;
     listIter li;
-    int j;
+    int j, port;
     sds cmdrepr = sdsnew("+");
     robj *cmdobj;
+    char ip[32];
     struct timeval tv;
 
     gettimeofday(&tv,NULL);
     cmdrepr = sdscatprintf(cmdrepr,"%ld.%06ld ",(long)tv.tv_sec,(long)tv.tv_usec);
-    if (dictid != 0) cmdrepr = sdscatprintf(cmdrepr,"(db %d) ", dictid);
+    if (c->flags & REDIS_LUA_CLIENT) {
+        cmdrepr = sdscatprintf(cmdrepr,"[%d lua] ", dictid);
+    } else {
+        anetPeerToString(c->fd,ip,&port);
+        cmdrepr = sdscatprintf(cmdrepr,"[%d %s:%d] ", dictid,ip,port);
+    }
 
     for (j = 0; j < argc; j++) {
         if (argv[j]->encoding == REDIS_ENCODING_INT) {