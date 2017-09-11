@@ -703,7 +703,7 @@ int processMultibulkBuffer(redisClient *c) {
 
     if (c->multibulklen == 0) {
         /* The client should have been reset */
-        redisAssert(c->argc == 0);
+        redisAssertWithInfo(c,NULL,c->argc == 0);
 
         /* Multi bulk length cannot be read without a \r\n */
         newline = strchr(c->querybuf,'\r');
@@ -716,7 +716,7 @@ int processMultibulkBuffer(redisClient *c) {
 
         /* We know for sure there is a whole line since newline != NULL,
          * so go ahead and find out the multi bulk length. */
-        redisAssert(c->querybuf[0] == '*');
+        redisAssertWithInfo(c,NULL,c->querybuf[0] == '*');
         ok = string2ll(c->querybuf+1,newline-(c->querybuf+1),&ll);
         if (!ok || ll > 1024*1024) {
             addReplyError(c,"Protocol error: invalid multibulk length");
@@ -737,7 +737,7 @@ int processMultibulkBuffer(redisClient *c) {
         c->argv = zmalloc(sizeof(robj*)*c->multibulklen);
     }
 
-    redisAssert(c->multibulklen > 0);
+    redisAssertWithInfo(c,NULL,c->multibulklen > 0);
     while(c->multibulklen) {
         /* Read bulk length if unknown */
         if (c->bulklen == -1) {
@@ -970,7 +970,7 @@ void rewriteClientCommandVector(redisClient *c, int argc, ...) {
     c->argv = argv;
     c->argc = argc;
     c->cmd = lookupCommand(c->argv[0]->ptr);
-    redisAssert(c->cmd != NULL);
+    redisAssertWithInfo(c,NULL,c->cmd != NULL);
     va_end(ap);
 }
 
@@ -979,7 +979,7 @@ void rewriteClientCommandVector(redisClient *c, int argc, ...) {
 void rewriteClientCommandArgument(redisClient *c, int i, robj *newval) {
     robj *oldval;
    
-    redisAssert(i < c->argc);
+    redisAssertWithInfo(c,NULL,i < c->argc);
     oldval = c->argv[i];
     c->argv[i] = newval;
     incrRefCount(newval);
@@ -988,6 +988,6 @@ void rewriteClientCommandArgument(redisClient *c, int i, robj *newval) {
     /* If this is the command name make sure to fix c->cmd. */
     if (i == 0) {
         c->cmd = lookupCommand(c->argv[0]->ptr);
-        redisAssert(c->cmd != NULL);
+        redisAssertWithInfo(c,NULL,c->cmd != NULL);
     }
 }