@@ -25,24 +25,15 @@ void replicationFeedSlaves(list *slaves, int dictid, robj **argv, int argc) {
         if (slave->slaveseldb != dictid) {
             robj *selectcmd;
 
-            switch(dictid) {
-            case 0: selectcmd = shared.select0; break;
-            case 1: selectcmd = shared.select1; break;
-            case 2: selectcmd = shared.select2; break;
-            case 3: selectcmd = shared.select3; break;
-            case 4: selectcmd = shared.select4; break;
-            case 5: selectcmd = shared.select5; break;
-            case 6: selectcmd = shared.select6; break;
-            case 7: selectcmd = shared.select7; break;
-            case 8: selectcmd = shared.select8; break;
-            case 9: selectcmd = shared.select9; break;
-            default:
+            if (dictid >= 0 && dictid < REDIS_SHARED_SELECT_CMDS) {
+                incrRefCount(shared.select[dictid]);
+                selectcmd = shared.select[dictid];
+            } else {
                 selectcmd = createObject(REDIS_STRING,
                     sdscatprintf(sdsempty(),"select %d\r\n",dictid));
-                selectcmd->refcount = 0;
-                break;
             }
             addReply(slave,selectcmd);
+            decrRefCount(selectcmd);
             slave->slaveseldb = dictid;
         }
         addReplyMultiBulkLen(slave,argc);