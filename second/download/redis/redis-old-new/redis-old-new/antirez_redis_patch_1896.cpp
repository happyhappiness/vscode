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
@@ -307,7 +310,7 @@ int loadAppendOnlyFile(char *filename) {
     }
     exit(1);
 fmterr:
-    redisLog(REDIS_WARNING,"Bad file format reading the append only file");
+    redisLog(REDIS_WARNING,"Bad file format reading the append only file: make a backup of your AOF file, then use ./redis-check-aof --fix <filename>");
     exit(1);
 }
 
@@ -463,20 +466,30 @@ int rewriteAppendOnlyFile(char *filename) {
                     redisPanic("Unknown list encoding");
                 }
             } else if (o->type == REDIS_SET) {
-                /* Emit the SADDs needed to rebuild the set */
-                dict *set = o->ptr;
-                dictIterator *di = dictGetIterator(set);
-                dictEntry *de;
+                char cmd[]="*3\r\n$4\r\nSADD\r\n";
 
-                while((de = dictNext(di)) != NULL) {
-                    char cmd[]="*3\r\n$4\r\nSADD\r\n";
-                    robj *eleobj = dictGetEntryKey(de);
-
-                    if (fwrite(cmd,sizeof(cmd)-1,1,fp) == 0) goto werr;
-                    if (fwriteBulkObject(fp,&key) == 0) goto werr;
-                    if (fwriteBulkObject(fp,eleobj) == 0) goto werr;
+                /* Emit the SADDs needed to rebuild the set */
+                if (o->encoding == REDIS_ENCODING_INTSET) {
+                    int ii = 0;
+                    int64_t llval;
+                    while(intsetGet(o->ptr,ii++,&llval)) {
+                        if (fwrite(cmd,sizeof(cmd)-1,1,fp) == 0) goto werr;
+                        if (fwriteBulkObject(fp,&key) == 0) goto werr;
+                        if (fwriteBulkLongLong(fp,llval) == 0) goto werr;
+                    }
+                } else if (o->encoding == REDIS_ENCODING_HT) {
+                    dictIterator *di = dictGetIterator(o->ptr);
+                    dictEntry *de;
+                    while((de = dictNext(di)) != NULL) {
+                        robj *eleobj = dictGetEntryKey(de);
+                        if (fwrite(cmd,sizeof(cmd)-1,1,fp) == 0) goto werr;
+                        if (fwriteBulkObject(fp,&key) == 0) goto werr;
+                        if (fwriteBulkObject(fp,eleobj) == 0) goto werr;
+                    }
+                    dictReleaseIterator(di);
+                } else {
+                    redisPanic("Unknown set encoding");
                 }
-                dictReleaseIterator(di);
             } else if (o->type == REDIS_ZSET) {
                 /* Emit the ZADDs needed to rebuild the sorted set */
                 zset *zs = o->ptr;
@@ -620,12 +633,11 @@ int rewriteAppendOnlyFileBackground(void) {
 
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