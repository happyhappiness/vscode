@@ -42,7 +42,7 @@ void queueMultiCommand(redisClient *c, struct redisCommand *cmd) {
 
 void multiCommand(redisClient *c) {
     if (c->flags & REDIS_MULTI) {
-        addReplySds(c,sdsnew("-ERR MULTI calls can not be nested\r\n"));
+        addReplyError(c,"MULTI calls can not be nested");
         return;
     }
     c->flags |= REDIS_MULTI;
@@ -51,7 +51,7 @@ void multiCommand(redisClient *c) {
 
 void discardCommand(redisClient *c) {
     if (!(c->flags & REDIS_MULTI)) {
-        addReplySds(c,sdsnew("-ERR DISCARD without MULTI\r\n"));
+        addReplyError(c,"DISCARD without MULTI");
         return;
     }
 
@@ -82,7 +82,7 @@ void execCommand(redisClient *c) {
     int orig_argc;
 
     if (!(c->flags & REDIS_MULTI)) {
-        addReplySds(c,sdsnew("-ERR EXEC without MULTI\r\n"));
+        addReplyError(c,"EXEC without MULTI");
         return;
     }
 
@@ -251,7 +251,7 @@ void watchCommand(redisClient *c) {
     int j;
 
     if (c->flags & REDIS_MULTI) {
-        addReplySds(c,sdsnew("-ERR WATCH inside MULTI is not allowed\r\n"));
+        addReplyError(c,"WATCH inside MULTI is not allowed");
         return;
     }
     for (j = 1; j < c->argc; j++)