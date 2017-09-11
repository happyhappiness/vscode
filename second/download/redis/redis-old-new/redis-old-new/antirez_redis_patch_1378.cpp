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
@@ -596,7 +602,7 @@ void replicationCron(void) {
             if (slave->replstate == REDIS_REPL_SEND_BULK) continue;
             if (slave->replstate == REDIS_REPL_ONLINE) {
                 /* If the slave is online send a normal ping */
-                addReplySds(slave,sdsnew("PING\r\n"));
+                addReplySds(slave,sdsnew("*1\r\n$4\r\nPING\r\n"));
             } else {
                 /* Otherwise we are in the pre-synchronization stage.
                  * Just a newline will do the work of refreshing the