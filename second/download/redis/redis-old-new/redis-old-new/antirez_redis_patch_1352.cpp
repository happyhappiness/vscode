@@ -26,8 +26,8 @@ void replicationFeedSlaves(list *slaves, int dictid, robj **argv, int argc) {
             robj *selectcmd;
 
             if (dictid >= 0 && dictid < REDIS_SHARED_SELECT_CMDS) {
-                incrRefCount(shared.select[dictid]);
                 selectcmd = shared.select[dictid];
+                incrRefCount(selectcmd);
             } else {
                 selectcmd = createObject(REDIS_STRING,
                     sdscatprintf(sdsempty(),"select %d\r\n",dictid));