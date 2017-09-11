@@ -37,9 +37,9 @@
 static int checkStringLength(client *c, long long size) {
     if (size > 512*1024*1024) {
         addReplyError(c,"string exceeds maximum allowed size (512MB)");
-        return REDIS_ERR;
+        return C_ERR;
     }
-    return REDIS_OK;
+    return C_OK;
 }
 
 /* The setGenericCommand() function implements the SET operation with different
@@ -68,7 +68,7 @@ void setGenericCommand(client *c, int flags, robj *key, robj *val, robj *expire,
     long long milliseconds = 0; /* initialized to avoid any harmness warning */
 
     if (expire) {
-        if (getLongLongFromObjectOrReply(c, expire, &milliseconds, NULL) != REDIS_OK)
+        if (getLongLongFromObjectOrReply(c, expire, &milliseconds, NULL) != C_OK)
             return;
         if (milliseconds <= 0) {
             addReplyErrorFormat(c,"invalid expire time in %s",c->cmd->name);
@@ -158,14 +158,14 @@ int getGenericCommand(client *c) {
     robj *o;
 
     if ((o = lookupKeyReadOrReply(c,c->argv[1],shared.nullbulk)) == NULL)
-        return REDIS_OK;
+        return C_OK;
 
     if (o->type != OBJ_STRING) {
         addReply(c,shared.wrongtypeerr);
-        return REDIS_ERR;
+        return C_ERR;
     } else {
         addReplyBulk(c,o);
-        return REDIS_OK;
+        return C_OK;
     }
 }
 
@@ -174,7 +174,7 @@ void getCommand(client *c) {
 }
 
 void getsetCommand(client *c) {
-    if (getGenericCommand(c) == REDIS_ERR) return;
+    if (getGenericCommand(c) == C_ERR) return;
     c->argv[2] = tryObjectEncoding(c->argv[2]);
     setKey(c->db,c->argv[1],c->argv[2]);
     notifyKeyspaceEvent(REDIS_NOTIFY_STRING,"set",c->argv[1],c->db->id);
@@ -186,7 +186,7 @@ void setrangeCommand(client *c) {
     long offset;
     sds value = c->argv[3]->ptr;
 
-    if (getLongFromObjectOrReply(c,c->argv[2],&offset,NULL) != REDIS_OK)
+    if (getLongFromObjectOrReply(c,c->argv[2],&offset,NULL) != C_OK)
         return;
 
     if (offset < 0) {
@@ -203,7 +203,7 @@ void setrangeCommand(client *c) {
         }
 
         /* Return when the resulting string exceeds allowed size */
-        if (checkStringLength(c,offset+sdslen(value)) != REDIS_OK)
+        if (checkStringLength(c,offset+sdslen(value)) != C_OK)
             return;
 
         o = createObject(OBJ_STRING,sdsnewlen(NULL, offset+sdslen(value)));
@@ -223,7 +223,7 @@ void setrangeCommand(client *c) {
         }
 
         /* Return when the resulting string exceeds allowed size */
-        if (checkStringLength(c,offset+sdslen(value)) != REDIS_OK)
+        if (checkStringLength(c,offset+sdslen(value)) != C_OK)
             return;
 
         /* Create a copy when the object is shared or encoded. */
@@ -247,9 +247,9 @@ void getrangeCommand(client *c) {
     char *str, llbuf[32];
     size_t strlen;
 
-    if (getLongLongFromObjectOrReply(c,c->argv[2],&start,NULL) != REDIS_OK)
+    if (getLongLongFromObjectOrReply(c,c->argv[2],&start,NULL) != C_OK)
         return;
-    if (getLongLongFromObjectOrReply(c,c->argv[3],&end,NULL) != REDIS_OK)
+    if (getLongLongFromObjectOrReply(c,c->argv[3],&end,NULL) != C_OK)
         return;
     if ((o = lookupKeyReadOrReply(c,c->argv[1],shared.emptybulk)) == NULL ||
         checkType(c,o,OBJ_STRING)) return;
@@ -340,7 +340,7 @@ void incrDecrCommand(client *c, long long incr) {
 
     o = lookupKeyWrite(c->db,c->argv[1]);
     if (o != NULL && checkType(c,o,OBJ_STRING)) return;
-    if (getLongLongFromObjectOrReply(c,o,&value,NULL) != REDIS_OK) return;
+    if (getLongLongFromObjectOrReply(c,o,&value,NULL) != C_OK) return;
 
     oldvalue = value;
     if ((incr < 0 && oldvalue < 0 && incr < (LLONG_MIN-oldvalue)) ||
@@ -383,14 +383,14 @@ void decrCommand(client *c) {
 void incrbyCommand(client *c) {
     long long incr;
 
-    if (getLongLongFromObjectOrReply(c, c->argv[2], &incr, NULL) != REDIS_OK) return;
+    if (getLongLongFromObjectOrReply(c, c->argv[2], &incr, NULL) != C_OK) return;
     incrDecrCommand(c,incr);
 }
 
 void decrbyCommand(client *c) {
     long long incr;
 
-    if (getLongLongFromObjectOrReply(c, c->argv[2], &incr, NULL) != REDIS_OK) return;
+    if (getLongLongFromObjectOrReply(c, c->argv[2], &incr, NULL) != C_OK) return;
     incrDecrCommand(c,-incr);
 }
 
@@ -400,8 +400,8 @@ void incrbyfloatCommand(client *c) {
 
     o = lookupKeyWrite(c->db,c->argv[1]);
     if (o != NULL && checkType(c,o,OBJ_STRING)) return;
-    if (getLongDoubleFromObjectOrReply(c,o,&value,NULL) != REDIS_OK ||
-        getLongDoubleFromObjectOrReply(c,c->argv[2],&incr,NULL) != REDIS_OK)
+    if (getLongDoubleFromObjectOrReply(c,o,&value,NULL) != C_OK ||
+        getLongDoubleFromObjectOrReply(c,c->argv[2],&incr,NULL) != C_OK)
         return;
 
     value += incr;
@@ -447,7 +447,7 @@ void appendCommand(client *c) {
         /* "append" is an argument, so always an sds */
         append = c->argv[2];
         totlen = stringObjectLen(o)+sdslen(append->ptr);
-        if (checkStringLength(c,totlen) != REDIS_OK)
+        if (checkStringLength(c,totlen) != C_OK)
             return;
 
         /* Append the value */