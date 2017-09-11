@@ -577,7 +577,7 @@ void sentinelEvent(int level, char *type, sentinelRedisInstance *ri,
     if (level == REDIS_WARNING && ri != NULL) {
         sentinelRedisInstance *master = (ri->flags & SRI_MASTER) ?
                                          ri : ri->master;
-        if (master->notification_script) {
+        if (master && master->notification_script) {
             sentinelScheduleScriptExecution(master->notification_script,
                 type,msg,NULL);
         }
@@ -2908,10 +2908,7 @@ void sentinelInfoCommand(redisClient *c) {
         dictReleaseIterator(di);
     }
 
-    addReplySds(c,sdscatprintf(sdsempty(),"$%lu\r\n",
-        (unsigned long)sdslen(info)));
-    addReplySds(c,info);
-    addReply(c,shared.crlf);
+    addReplyBulkSds(c, info);
 }
 
 /* Implements Sentinel verison of the ROLE command. The output is