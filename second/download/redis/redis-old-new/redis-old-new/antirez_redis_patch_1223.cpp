@@ -320,7 +320,7 @@ void pushGenericCommand(redisClient *c, int where) {
         char *event = (where == REDIS_HEAD) ? "lpush" : "rpush";
 
         signalModifiedKey(c->db,c->argv[1]);
-        notifyKeyspaceEvent(event,c->argv[1],c->db->id);
+        notifyKeyspaceEvent(REDIS_NOTIFY_LIST,event,c->argv[1],c->db->id);
     }
     server.dirty += pushed;
 }
@@ -367,7 +367,8 @@ void pushxGenericCommand(redisClient *c, robj *refval, robj *val, int where) {
                 ziplistLen(subject->ptr) > server.list_max_ziplist_entries)
                     listTypeConvert(subject,REDIS_ENCODING_LINKEDLIST);
             signalModifiedKey(c->db,c->argv[1]);
-            notifyKeyspaceEvent("linsert",c->argv[1],c->db->id);
+            notifyKeyspaceEvent(REDIS_NOTIFY_LIST,"linsert",
+                                c->argv[1],c->db->id);
             server.dirty++;
         } else {
             /* Notify client of a failed insert */
@@ -379,7 +380,7 @@ void pushxGenericCommand(redisClient *c, robj *refval, robj *val, int where) {
 
         listTypePush(subject,val,where);
         signalModifiedKey(c->db,c->argv[1]);
-        notifyKeyspaceEvent(event,c->argv[1],c->db->id);
+        notifyKeyspaceEvent(REDIS_NOTIFY_LIST,event,c->argv[1],c->db->id);
         server.dirty++;
     }
 
@@ -474,7 +475,7 @@ void lsetCommand(redisClient *c) {
             decrRefCount(value);
             addReply(c,shared.ok);
             signalModifiedKey(c->db,c->argv[1]);
-            notifyKeyspaceEvent("lset",c->argv[1],c->db->id);
+            notifyKeyspaceEvent(REDIS_NOTIFY_LIST,"lset",c->argv[1],c->db->id);
             server.dirty++;
         }
     } else if (o->encoding == REDIS_ENCODING_LINKEDLIST) {
@@ -487,7 +488,7 @@ void lsetCommand(redisClient *c) {
             incrRefCount(value);
             addReply(c,shared.ok);
             signalModifiedKey(c->db,c->argv[1]);
-            notifyKeyspaceEvent("lset",c->argv[1],c->db->id);
+            notifyKeyspaceEvent(REDIS_NOTIFY_LIST,"lset",c->argv[1],c->db->id);
             server.dirty++;
         }
     } else {
@@ -507,9 +508,10 @@ void popGenericCommand(redisClient *c, int where) {
 
         addReplyBulk(c,value);
         decrRefCount(value);
-        notifyKeyspaceEvent(event,c->argv[1],c->db->id);
+        notifyKeyspaceEvent(REDIS_NOTIFY_LIST,event,c->argv[1],c->db->id);
         if (listTypeLength(o) == 0) {
-            notifyKeyspaceEvent("del",c->argv[1],c->db->id);
+            notifyKeyspaceEvent(REDIS_NOTIFY_GENERIC,"del",
+                                c->argv[1],c->db->id);
             dbDelete(c->db,c->argv[1]);
         }
         signalModifiedKey(c->db,c->argv[1]);
@@ -632,10 +634,10 @@ void ltrimCommand(redisClient *c) {
         redisPanic("Unknown list encoding");
     }
 
-    notifyKeyspaceEvent("ltrim",c->argv[1],c->db->id);
+    notifyKeyspaceEvent(REDIS_NOTIFY_LIST,"ltrim",c->argv[1],c->db->id);
     if (listTypeLength(o) == 0) {
         dbDelete(c->db,c->argv[1]);
-        notifyKeyspaceEvent("del",c->argv[1],c->db->id);
+        notifyKeyspaceEvent(REDIS_NOTIFY_GENERIC,"del",c->argv[1],c->db->id);
     }
     signalModifiedKey(c->db,c->argv[1]);
     server.dirty++;
@@ -711,7 +713,7 @@ void rpoplpushHandlePush(redisClient *c, robj *dstkey, robj *dstobj, robj *value
     }
     signalModifiedKey(c->db,dstkey);
     listTypePush(dstobj,value,REDIS_HEAD);
-    notifyKeyspaceEvent("lpush",dstkey,c->db->id);
+    notifyKeyspaceEvent(REDIS_NOTIFY_LIST,"lpush",dstkey,c->db->id);
     /* Always send the pushed value to the client. */
     addReplyBulk(c,value);
 }
@@ -741,10 +743,11 @@ void rpoplpushCommand(redisClient *c) {
         decrRefCount(value);
 
         /* Delete the source list when it is empty */
-        notifyKeyspaceEvent("rpop",touchedkey,c->db->id);
+        notifyKeyspaceEvent(REDIS_NOTIFY_LIST,"rpop",touchedkey,c->db->id);
         if (listTypeLength(sobj) == 0) {
             dbDelete(c->db,touchedkey);
-            notifyKeyspaceEvent("del",touchedkey,c->db->id);
+            notifyKeyspaceEvent(REDIS_NOTIFY_GENERIC,"del",
+                                touchedkey,c->db->id);
         }
         signalModifiedKey(c->db,touchedkey);
         decrRefCount(touchedkey);
@@ -1077,10 +1080,12 @@ void blockingPopGenericCommand(redisClient *c, int where) {
                     addReplyBulk(c,c->argv[j]);
                     addReplyBulk(c,value);
                     decrRefCount(value);
-                    notifyKeyspaceEvent(event,c->argv[j],c->db->id);
+                    notifyKeyspaceEvent(REDIS_NOTIFY_LIST,event,
+                                        c->argv[j],c->db->id);
                     if (listTypeLength(o) == 0) {
                         dbDelete(c->db,c->argv[j]);
-                        notifyKeyspaceEvent("del",c->argv[j],c->db->id);
+                        notifyKeyspaceEvent(REDIS_NOTIFY_GENERIC,"del",
+                                            c->argv[j],c->db->id);
                     }
                     signalModifiedKey(c->db,c->argv[j]);
                     server.dirty++;