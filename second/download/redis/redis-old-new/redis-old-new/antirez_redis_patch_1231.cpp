@@ -316,7 +316,12 @@ void pushGenericCommand(redisClient *c, int where) {
         pushed++;
     }
     addReplyLongLong(c, waiting + (lobj ? listTypeLength(lobj) : 0));
-    if (pushed) signalModifiedKey(c->db,c->argv[1]);
+    if (pushed) {
+        char *event = (where == REDIS_HEAD) ? "lpush" : "rpush";
+
+        signalModifiedKey(c->db,c->argv[1]);
+        notifyKeyspaceEvent(event,c->argv[1],c->db->id);
+    }
     server.dirty += pushed;
 }
 
@@ -338,10 +343,6 @@ void pushxGenericCommand(redisClient *c, robj *refval, robj *val, int where) {
         checkType(c,subject,REDIS_LIST)) return;
 
     if (refval != NULL) {
-        /* Note: we expect refval to be string-encoded because it is *not* the
-         * last argument of the multi-bulk LINSERT. */
-        redisAssertWithInfo(c,refval,refval->encoding == REDIS_ENCODING_RAW);
-
         /* We're not sure if this value can be inserted yet, but we cannot
          * convert the list inside the iterator. We don't want to loop over
          * the list twice (once to see if the value can be inserted and once
@@ -366,15 +367,19 @@ void pushxGenericCommand(redisClient *c, robj *refval, robj *val, int where) {
                 ziplistLen(subject->ptr) > server.list_max_ziplist_entries)
                     listTypeConvert(subject,REDIS_ENCODING_LINKEDLIST);
             signalModifiedKey(c->db,c->argv[1]);
+            notifyKeyspaceEvent("linsert",c->argv[1],c->db->id);
             server.dirty++;
         } else {
             /* Notify client of a failed insert */
             addReply(c,shared.cnegone);
             return;
         }
     } else {
+        char *event = (where == REDIS_HEAD) ? "lpush" : "rpush";
+
         listTypePush(subject,val,where);
         signalModifiedKey(c->db,c->argv[1]);
+        notifyKeyspaceEvent(event,c->argv[1],c->db->id);
         server.dirty++;
     }
 
@@ -469,6 +474,7 @@ void lsetCommand(redisClient *c) {
             decrRefCount(value);
             addReply(c,shared.ok);
             signalModifiedKey(c->db,c->argv[1]);
+            notifyKeyspaceEvent("lset",c->argv[1],c->db->id);
             server.dirty++;
         }
     } else if (o->encoding == REDIS_ENCODING_LINKEDLIST) {
@@ -481,6 +487,7 @@ void lsetCommand(redisClient *c) {
             incrRefCount(value);
             addReply(c,shared.ok);
             signalModifiedKey(c->db,c->argv[1]);
+            notifyKeyspaceEvent("lset",c->argv[1],c->db->id);
             server.dirty++;
         }
     } else {
@@ -496,9 +503,15 @@ void popGenericCommand(redisClient *c, int where) {
     if (value == NULL) {
         addReply(c,shared.nullbulk);
     } else {
+        char *event = (where == REDIS_HEAD) ? "lpop" : "rpop";
+
         addReplyBulk(c,value);
         decrRefCount(value);
-        if (listTypeLength(o) == 0) dbDelete(c->db,c->argv[1]);
+        notifyKeyspaceEvent(event,c->argv[1],c->db->id);
+        if (listTypeLength(o) == 0) {
+            notifyKeyspaceEvent("del",c->argv[1],c->db->id);
+            dbDelete(c->db,c->argv[1]);
+        }
         signalModifiedKey(c->db,c->argv[1]);
         server.dirty++;
     }
@@ -618,7 +631,12 @@ void ltrimCommand(redisClient *c) {
     } else {
         redisPanic("Unknown list encoding");
     }
-    if (listTypeLength(o) == 0) dbDelete(c->db,c->argv[1]);
+
+    notifyKeyspaceEvent("ltrim",c->argv[1],c->db->id);
+    if (listTypeLength(o) == 0) {
+        dbDelete(c->db,c->argv[1]);
+        notifyKeyspaceEvent("del",c->argv[1],c->db->id);
+    }
     signalModifiedKey(c->db,c->argv[1]);
     server.dirty++;
     addReply(c,shared.ok);
@@ -693,6 +711,7 @@ void rpoplpushHandlePush(redisClient *c, robj *dstkey, robj *dstobj, robj *value
     }
     signalModifiedKey(c->db,dstkey);
     listTypePush(dstobj,value,REDIS_HEAD);
+    notifyKeyspaceEvent("lpush",dstkey,c->db->id);
     /* Always send the pushed value to the client. */
     addReplyBulk(c,value);
 }
@@ -722,7 +741,11 @@ void rpoplpushCommand(redisClient *c) {
         decrRefCount(value);
 
         /* Delete the source list when it is empty */
-        if (listTypeLength(sobj) == 0) dbDelete(c->db,touchedkey);
+        notifyKeyspaceEvent("rpop",touchedkey,c->db->id);
+        if (listTypeLength(sobj) == 0) {
+            dbDelete(c->db,touchedkey);
+            notifyKeyspaceEvent("del",touchedkey,c->db->id);
+        }
         signalModifiedKey(c->db,touchedkey);
         decrRefCount(touchedkey);
         server.dirty++;
@@ -1046,14 +1069,19 @@ void blockingPopGenericCommand(redisClient *c, int where) {
             } else {
                 if (listTypeLength(o) != 0) {
                     /* Non empty list, this is like a non normal [LR]POP. */
+                    char *event = (where == REDIS_HEAD) ? "lpop" : "rpop";
                     robj *value = listTypePop(o,where);
                     redisAssert(value != NULL);
 
                     addReplyMultiBulkLen(c,2);
                     addReplyBulk(c,c->argv[j]);
                     addReplyBulk(c,value);
                     decrRefCount(value);
-                    if (listTypeLength(o) == 0) dbDelete(c->db,c->argv[j]);
+                    notifyKeyspaceEvent(event,c->argv[j],c->db->id);
+                    if (listTypeLength(o) == 0) {
+                        dbDelete(c->db,c->argv[j]);
+                        notifyKeyspaceEvent("del",c->argv[j],c->db->id);
+                    }
                     signalModifiedKey(c->db,c->argv[j]);
                     server.dirty++;
 