@@ -884,6 +884,11 @@ int processInlineBuffer(redisClient *c) {
     aux = sdsnewlen(c->querybuf,querylen);
     argv = sdssplitargs(aux,&argc);
     sdsfree(aux);
+    if (argv == NULL) {
+        addReplyError(c,"Protocol error: unbalanced quotes in request");
+        setProtocolError(c,0);
+        return REDIS_ERR;
+    }
 
     /* Leave data after the first line of the query in the buffer */
     sdsrange(c->querybuf,querylen+2,-1);