             listRewind(operations,&li);
             while((ln = listNext(&li))) {
                 redisSortOperation *sop = ln->value;
                 robj *val = lookupKeyByPattern(c->db,sop->pattern,
                     vector[j].obj);
 
-                if (sop->type == REDIS_SORT_GET) {
+                if (sop->type == SORT_OP_GET) {
                     if (!val) {
                         addReply(c,shared.nullbulk);
                     } else {
                         addReplyBulk(c,val);
                         decrRefCount(val);
                     }
                 } else {
                     /* Always fails */
-                    redisAssertWithInfo(c,sortval,sop->type == REDIS_SORT_GET);
+                    serverAssertWithInfo(c,sortval,sop->type == SORT_OP_GET);
                 }
             }
         }
     } else {
-        robj *sobj = createZiplistObject();
+        robj *sobj = createQuicklistObject();
 
         /* STORE option specified, set the sorting result as a List object */
         for (j = start; j <= end; j++) {
             listNode *ln;
             listIter li;
 
             if (!getop) {
-                listTypePush(sobj,vector[j].obj,REDIS_TAIL);
+                listTypePush(sobj,vector[j].obj,LIST_TAIL);
             } else {
                 listRewind(operations,&li);
                 while((ln = listNext(&li))) {
                     redisSortOperation *sop = ln->value;
                     robj *val = lookupKeyByPattern(c->db,sop->pattern,
                         vector[j].obj);
 
-                    if (sop->type == REDIS_SORT_GET) {
+                    if (sop->type == SORT_OP_GET) {
                         if (!val) val = createStringObject("",0);
 
                         /* listTypePush does an incrRefCount, so we should take care
                          * care of the incremented refcount caused by either
                          * lookupKeyByPattern or createStringObject("",0) */
-                        listTypePush(sobj,val,REDIS_TAIL);
+                        listTypePush(sobj,val,LIST_TAIL);
                         decrRefCount(val);
                     } else {
                         /* Always fails */
-                        redisAssertWithInfo(c,sortval,sop->type == REDIS_SORT_GET);
+                        serverAssertWithInfo(c,sortval,sop->type == SORT_OP_GET);
                     }
                 }
             }
         }
         if (outputlen) {
             setKey(c->db,storekey,sobj);
-            notifyKeyspaceEvent(REDIS_NOTIFY_LIST,"sortstore",storekey,
+            notifyKeyspaceEvent(NOTIFY_LIST,"sortstore",storekey,
                                 c->db->id);
             server.dirty += outputlen;
         } else if (dbDelete(c->db,storekey)) {
             signalModifiedKey(c->db,storekey);
-            notifyKeyspaceEvent(REDIS_NOTIFY_GENERIC,"del",storekey,c->db->id);
+            notifyKeyspaceEvent(NOTIFY_GENERIC,"del",storekey,c->db->id);
             server.dirty++;
         }
         decrRefCount(sobj);
         addReplyLongLong(c,outputlen);
     }
 
     /* Cleanup */
-    if (sortval->type == REDIS_LIST || sortval->type == REDIS_SET)
+    if (sortval->type == OBJ_LIST || sortval->type == OBJ_SET)
         for (j = 0; j < vectorlen; j++)
             decrRefCount(vector[j].obj);
     decrRefCount(sortval);
     listRelease(operations);
     for (j = 0; j < vectorlen; j++) {
         if (alpha && vector[j].u.cmpobj)
