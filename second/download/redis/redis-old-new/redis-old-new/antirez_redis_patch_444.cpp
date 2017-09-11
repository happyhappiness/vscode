@@ -267,7 +267,7 @@ void sortCommand(client *c) {
                 break;
             }
             listAddNodeTail(operations,createSortOperation(
-                REDIS_SORT_GET,c->argv[j+1]));
+                SORT_OP_GET,c->argv[j+1]));
             getop++;
             j++;
         } else {
@@ -293,7 +293,7 @@ void sortCommand(client *c) {
      * scripting and replication. */
     if (dontsort &&
         sortval->type == OBJ_SET &&
-        (storekey || c->flags & REDIS_LUA_CLIENT))
+        (storekey || c->flags & CLIENT_LUA))
     {
         /* Force ALPHA sorting */
         dontsort = 0;
@@ -310,7 +310,7 @@ void sortCommand(client *c) {
     case OBJ_LIST: vectorlen = listTypeLength(sortval); break;
     case OBJ_SET: vectorlen =  setTypeSize(sortval); break;
     case OBJ_ZSET: vectorlen = dictSize(((zset*)sortval->ptr)->dict); break;
-    default: vectorlen = 0; redisPanic("Bad SORT type"); /* Avoid GCC warning */
+    default: vectorlen = 0; serverPanic("Bad SORT type"); /* Avoid GCC warning */
     }
 
     /* Perform LIMIT start,count sanity checking. */
@@ -355,7 +355,7 @@ void sortCommand(client *c) {
             listTypeEntry entry;
             li = listTypeInitIterator(sortval,
                     desc ? (long)(listTypeLength(sortval) - start - 1) : start,
-                    desc ? REDIS_HEAD : REDIS_TAIL);
+                    desc ? LIST_HEAD : LIST_TAIL);
 
             while(j < vectorlen && listTypeNext(li,&entry)) {
                 vector[j].obj = listTypeGet(&entry);
@@ -369,7 +369,7 @@ void sortCommand(client *c) {
             start = 0;
         }
     } else if (sortval->type == OBJ_LIST) {
-        listTypeIterator *li = listTypeInitIterator(sortval,0,REDIS_TAIL);
+        listTypeIterator *li = listTypeInitIterator(sortval,0,LIST_TAIL);
         listTypeEntry entry;
         while(listTypeNext(li,&entry)) {
             vector[j].obj = listTypeGet(&entry);
@@ -440,7 +440,7 @@ void sortCommand(client *c) {
         }
         dictReleaseIterator(di);
     } else {
-        redisPanic("Unknown type");
+        serverPanic("Unknown type");
     }
     serverAssertWithInfo(c,sortval,j == vectorlen);
 
@@ -517,7 +517,7 @@ void sortCommand(client *c) {
                 robj *val = lookupKeyByPattern(c->db,sop->pattern,
                     vector[j].obj);
 
-                if (sop->type == REDIS_SORT_GET) {
+                if (sop->type == SORT_OP_GET) {
                     if (!val) {
                         addReply(c,shared.nullbulk);
                     } else {
@@ -526,7 +526,7 @@ void sortCommand(client *c) {
                     }
                 } else {
                     /* Always fails */
-                    serverAssertWithInfo(c,sortval,sop->type == REDIS_SORT_GET);
+                    serverAssertWithInfo(c,sortval,sop->type == SORT_OP_GET);
                 }
             }
         }
@@ -539,37 +539,37 @@ void sortCommand(client *c) {
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
-                        serverAssertWithInfo(c,sortval,sop->type == REDIS_SORT_GET);
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