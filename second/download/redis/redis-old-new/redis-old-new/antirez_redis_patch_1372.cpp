@@ -40,6 +40,13 @@ void queueMultiCommand(redisClient *c) {
     c->mstate.count++;
 }
 
+void discardTransaction(redisClient *c) {
+    freeClientMultiState(c);
+    initClientMultiState(c);
+    c->flags &= ~(REDIS_MULTI|REDIS_DIRTY_CAS);;
+    unwatchAllKeys(c);
+}
+
 void multiCommand(redisClient *c) {
     if (c->flags & REDIS_MULTI) {
         addReplyError(c,"MULTI calls can not be nested");
@@ -54,11 +61,7 @@ void discardCommand(redisClient *c) {
         addReplyError(c,"DISCARD without MULTI");
         return;
     }
-
-    freeClientMultiState(c);
-    initClientMultiState(c);
-    c->flags &= ~(REDIS_MULTI|REDIS_DIRTY_CAS);;
-    unwatchAllKeys(c);
+    discardTransaction(c);
     addReply(c,shared.ok);
 }
 