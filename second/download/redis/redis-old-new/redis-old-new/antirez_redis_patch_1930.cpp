@@ -189,6 +189,7 @@ struct redisClient *createFakeClient(void) {
     c->querybuf = sdsempty();
     c->argc = 0;
     c->argv = NULL;
+    c->bufpos = 0;
     c->flags = 0;
     /* We set the fake client as a slave waiting for the synchronization
      * so that Redis will not try to send replies to this client. */
@@ -272,12 +273,14 @@ int loadAppendOnlyFile(char *filename) {
         fakeClient->argc = argc;
         fakeClient->argv = argv;
         cmd->proc(fakeClient);
-        /* Discard the reply objects list from the fake client */
-        while(listLength(fakeClient->reply))
-            listDelNode(fakeClient->reply,listFirst(fakeClient->reply));
+
+        /* The fake client should not have a reply */
+        redisAssert(fakeClient->bufpos == 0 && listLength(fakeClient->reply) == 0);
+
         /* Clean up, ready for the next command */
         for (j = 0; j < argc; j++) decrRefCount(argv[j]);
         zfree(argv);
+
         /* Handle swapping while loading big datasets when VM is on */
         force_swapout = 0;
         if ((zmalloc_used_memory() - server.vm_max_memory) > 1024*1024*32)
@@ -629,12 +632,11 @@ int rewriteAppendOnlyFileBackground(void) {
 
 void bgrewriteaofCommand(redisClient *c) {
     if (server.bgrewritechildpid != -1) {
-        addReplySds(c,sdsnew("-ERR background append only file rewriting already in progress\r\n"));
+        addReplyError(c,"Background append only file rewriting already in progress");
         return;
     }
     if (rewriteAppendOnlyFileBackground() == REDIS_OK) {
-        char *status = "+Background append only file rewriting started\r\n";
-        addReplySds(c,sdsnew(status));
+        addReplyStatus(c,"Background append only file rewriting started");
     } else {
         addReply(c,shared.err);
     }