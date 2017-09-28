         if (sdslen(value) == 0) {
             addReply(c,shared.czero);
             return;
         }
 
         /* Return when the resulting string exceeds allowed size */
-        if (checkStringLength(c,offset+sdslen(value)) != REDIS_OK)
+        if (checkStringLength(c,offset+sdslen(value)) != C_OK)
             return;
 
-        o = createObject(REDIS_STRING,sdsempty());
+        o = createObject(OBJ_STRING,sdsnewlen(NULL, offset+sdslen(value)));
         dbAdd(c->db,c->argv[1],o);
     } else {
         size_t olen;
 
         /* Key exists, check type */
-        if (checkType(c,o,REDIS_STRING))
+        if (checkType(c,o,OBJ_STRING))
             return;
 
         /* Return existing string length when setting nothing */
         olen = stringObjectLen(o);
         if (sdslen(value) == 0) {
             addReplyLongLong(c,olen);
             return;
         }
 
         /* Return when the resulting string exceeds allowed size */
-        if (checkStringLength(c,offset+sdslen(value)) != REDIS_OK)
+        if (checkStringLength(c,offset+sdslen(value)) != C_OK)
             return;
 
         /* Create a copy when the object is shared or encoded. */
         o = dbUnshareStringValue(c->db,c->argv[1],o);
     }
 
     if (sdslen(value) > 0) {
         o->ptr = sdsgrowzero(o->ptr,offset+sdslen(value));
         memcpy((char*)o->ptr+offset,value,sdslen(value));
         signalModifiedKey(c->db,c->argv[1]);
-        notifyKeyspaceEvent(REDIS_NOTIFY_STRING,
+        notifyKeyspaceEvent(NOTIFY_STRING,
             "setrange",c->argv[1],c->db->id);
         server.dirty++;
     }
     addReplyLongLong(c,sdslen(o->ptr));
 }
 
-void getrangeCommand(redisClient *c) {
+void getrangeCommand(client *c) {
     robj *o;
     long long start, end;
     char *str, llbuf[32];
     size_t strlen;
 
-    if (getLongLongFromObjectOrReply(c,c->argv[2],&start,NULL) != REDIS_OK)
+    if (getLongLongFromObjectOrReply(c,c->argv[2],&start,NULL) != C_OK)
         return;
-    if (getLongLongFromObjectOrReply(c,c->argv[3],&end,NULL) != REDIS_OK)
+    if (getLongLongFromObjectOrReply(c,c->argv[3],&end,NULL) != C_OK)
         return;
     if ((o = lookupKeyReadOrReply(c,c->argv[1],shared.emptybulk)) == NULL ||
-        checkType(c,o,REDIS_STRING)) return;
+        checkType(c,o,OBJ_STRING)) return;
 
-    if (o->encoding == REDIS_ENCODING_INT) {
+    if (o->encoding == OBJ_ENCODING_INT) {
         str = llbuf;
         strlen = ll2string(llbuf,sizeof(llbuf),(long)o->ptr);
     } else {
         str = o->ptr;
         strlen = sdslen(str);
     }
