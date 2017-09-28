     }
 
     c->argv[2] = tryObjectEncoding(c->argv[2]);
     setGenericCommand(c,flags,c->argv[1],c->argv[2],expire,unit,NULL,NULL);
 }
 
-void setnxCommand(redisClient *c) {
+void setnxCommand(client *c) {
     c->argv[2] = tryObjectEncoding(c->argv[2]);
-    setGenericCommand(c,REDIS_SET_NX,c->argv[1],c->argv[2],NULL,0,shared.cone,shared.czero);
+    setGenericCommand(c,OBJ_SET_NX,c->argv[1],c->argv[2],NULL,0,shared.cone,shared.czero);
 }
 
-void setexCommand(redisClient *c) {
+void setexCommand(client *c) {
     c->argv[3] = tryObjectEncoding(c->argv[3]);
-    setGenericCommand(c,REDIS_SET_NO_FLAGS,c->argv[1],c->argv[3],c->argv[2],UNIT_SECONDS,NULL,NULL);
+    setGenericCommand(c,OBJ_SET_NO_FLAGS,c->argv[1],c->argv[3],c->argv[2],UNIT_SECONDS,NULL,NULL);
 }
 
-void psetexCommand(redisClient *c) {
+void psetexCommand(client *c) {
     c->argv[3] = tryObjectEncoding(c->argv[3]);
-    setGenericCommand(c,REDIS_SET_NO_FLAGS,c->argv[1],c->argv[3],c->argv[2],UNIT_MILLISECONDS,NULL,NULL);
+    setGenericCommand(c,OBJ_SET_NO_FLAGS,c->argv[1],c->argv[3],c->argv[2],UNIT_MILLISECONDS,NULL,NULL);
 }
 
-int getGenericCommand(redisClient *c) {
+int getGenericCommand(client *c) {
     robj *o;
 
     if ((o = lookupKeyReadOrReply(c,c->argv[1],shared.nullbulk)) == NULL)
-        return REDIS_OK;
+        return C_OK;
 
-    if (o->type != REDIS_STRING) {
+    if (o->type != OBJ_STRING) {
         addReply(c,shared.wrongtypeerr);
-        return REDIS_ERR;
+        return C_ERR;
     } else {
         addReplyBulk(c,o);
-        return REDIS_OK;
+        return C_OK;
     }
 }
 
-void getCommand(redisClient *c) {
+void getCommand(client *c) {
     getGenericCommand(c);
 }
 
-void getsetCommand(redisClient *c) {
-    if (getGenericCommand(c) == REDIS_ERR) return;
+void getsetCommand(client *c) {
+    if (getGenericCommand(c) == C_ERR) return;
     c->argv[2] = tryObjectEncoding(c->argv[2]);
     setKey(c->db,c->argv[1],c->argv[2]);
-    notifyKeyspaceEvent(REDIS_NOTIFY_STRING,"set",c->argv[1],c->db->id);
+    notifyKeyspaceEvent(NOTIFY_STRING,"set",c->argv[1],c->db->id);
     server.dirty++;
 }
 
-void setrangeCommand(redisClient *c) {
+void setrangeCommand(client *c) {
     robj *o;
     long offset;
     sds value = c->argv[3]->ptr;
 
-    if (getLongFromObjectOrReply(c,c->argv[2],&offset,NULL) != REDIS_OK)
+    if (getLongFromObjectOrReply(c,c->argv[2],&offset,NULL) != C_OK)
         return;
 
     if (offset < 0) {
         addReplyError(c,"offset is out of range");
         return;
     }
