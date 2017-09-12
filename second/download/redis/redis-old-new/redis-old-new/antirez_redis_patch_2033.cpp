@@ -273,12 +273,14 @@ void pushGenericCommand(redisClient *c, int where) {
             return;
         }
         if (handleClientsWaitingListPush(c,c->argv[1],c->argv[2])) {
+            touchWatchedKey(c->db,c->argv[1]);
             addReply(c,shared.cone);
             return;
         }
     }
     listTypePush(lobj,c->argv[2],where);
     addReplyLongLong(c,listTypeLength(lobj));
+    touchWatchedKey(c->db,c->argv[1]);
     server.dirty++;
 }
 
@@ -327,6 +329,7 @@ void pushxGenericCommand(redisClient *c, robj *refval, robj *val, int where) {
             if (subject->encoding == REDIS_ENCODING_ZIPLIST &&
                 ziplistLen(subject->ptr) > server.list_max_ziplist_entries)
                     listTypeConvert(subject,REDIS_ENCODING_LINKEDLIST);
+            touchWatchedKey(c->db,c->argv[1]);
             server.dirty++;
         } else {
             /* Notify client of a failed insert */
@@ -335,6 +338,7 @@ void pushxGenericCommand(redisClient *c, robj *refval, robj *val, int where) {
         }
     } else {
         listTypePush(subject,val,where);
+        touchWatchedKey(c->db,c->argv[1]);
         server.dirty++;
     }
 
@@ -419,6 +423,7 @@ void lsetCommand(redisClient *c) {
             o->ptr = ziplistInsert(o->ptr,p,value->ptr,sdslen(value->ptr));
             decrRefCount(value);
             addReply(c,shared.ok);
+            touchWatchedKey(c->db,c->argv[1]);
             server.dirty++;
         }
     } else if (o->encoding == REDIS_ENCODING_LINKEDLIST) {
@@ -430,6 +435,7 @@ void lsetCommand(redisClient *c) {
             listNodeValue(ln) = value;
             incrRefCount(value);
             addReply(c,shared.ok);
+            touchWatchedKey(c->db,c->argv[1]);
             server.dirty++;
         }
     } else {
@@ -448,6 +454,7 @@ void popGenericCommand(redisClient *c, int where) {
         addReplyBulk(c,value);
         decrRefCount(value);
         if (listTypeLength(o) == 0) dbDelete(c->db,c->argv[1]);
+        touchWatchedKey(c->db,c->argv[1]);
         server.dirty++;
     }
 }
@@ -546,6 +553,7 @@ void ltrimCommand(redisClient *c) {
         redisPanic("Unknown list encoding");
     }
     if (listTypeLength(o) == 0) dbDelete(c->db,c->argv[1]);
+    touchWatchedKey(c->db,c->argv[1]);
     server.dirty++;
     addReply(c,shared.ok);
 }
@@ -587,6 +595,7 @@ void lremCommand(redisClient *c) {
 
     if (listTypeLength(subject) == 0) dbDelete(c->db,c->argv[1]);
     addReplySds(c,sdscatprintf(sdsempty(),":%d\r\n",removed));
+    if (removed) touchWatchedKey(c->db,c->argv[1]);
 }
 
 /* This is the semantic of this command:
@@ -635,6 +644,7 @@ void rpoplpushcommand(redisClient *c) {
 
         /* Delete the source list when it is empty */
         if (listTypeLength(sobj) == 0) dbDelete(c->db,c->argv[1]);
+        touchWatchedKey(c->db,c->argv[1]);
         server.dirty++;
     }
 }