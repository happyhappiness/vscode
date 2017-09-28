             dbOverwrite(c->db,c->argv[1],new);
         } else {
             dbAdd(c->db,c->argv[1],new);
         }
     }
     signalModifiedKey(c->db,c->argv[1]);
-    notifyKeyspaceEvent(REDIS_NOTIFY_STRING,"incrby",c->argv[1],c->db->id);
+    notifyKeyspaceEvent(NOTIFY_STRING,"incrby",c->argv[1],c->db->id);
     server.dirty++;
     addReply(c,shared.colon);
     addReply(c,new);
     addReply(c,shared.crlf);
 }
 
-void incrCommand(redisClient *c) {
+void incrCommand(client *c) {
     incrDecrCommand(c,1);
 }
 
-void decrCommand(redisClient *c) {
+void decrCommand(client *c) {
     incrDecrCommand(c,-1);
 }
 
-void incrbyCommand(redisClient *c) {
+void incrbyCommand(client *c) {
     long long incr;
 
-    if (getLongLongFromObjectOrReply(c, c->argv[2], &incr, NULL) != REDIS_OK) return;
+    if (getLongLongFromObjectOrReply(c, c->argv[2], &incr, NULL) != C_OK) return;
     incrDecrCommand(c,incr);
 }
 
-void decrbyCommand(redisClient *c) {
+void decrbyCommand(client *c) {
     long long incr;
 
-    if (getLongLongFromObjectOrReply(c, c->argv[2], &incr, NULL) != REDIS_OK) return;
+    if (getLongLongFromObjectOrReply(c, c->argv[2], &incr, NULL) != C_OK) return;
     incrDecrCommand(c,-incr);
 }
 
-void incrbyfloatCommand(redisClient *c) {
+void incrbyfloatCommand(client *c) {
     long double incr, value;
     robj *o, *new, *aux;
 
     o = lookupKeyWrite(c->db,c->argv[1]);
-    if (o != NULL && checkType(c,o,REDIS_STRING)) return;
-    if (getLongDoubleFromObjectOrReply(c,o,&value,NULL) != REDIS_OK ||
-        getLongDoubleFromObjectOrReply(c,c->argv[2],&incr,NULL) != REDIS_OK)
+    if (o != NULL && checkType(c,o,OBJ_STRING)) return;
+    if (getLongDoubleFromObjectOrReply(c,o,&value,NULL) != C_OK ||
+        getLongDoubleFromObjectOrReply(c,c->argv[2],&incr,NULL) != C_OK)
         return;
 
     value += incr;
     if (isnan(value) || isinf(value)) {
         addReplyError(c,"increment would produce NaN or Infinity");
         return;
