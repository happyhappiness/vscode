@@ -242,7 +242,6 @@ int loadAppendOnlyFile(char *filename) {
         char buf[128];
         sds argsds;
         struct redisCommand *cmd;
-        int force_swapout;
 
         /* Serve the clients from time to time */
         if (!(loops++ % 1000)) {
@@ -286,17 +285,6 @@ int loadAppendOnlyFile(char *filename) {
         /* Clean up, ready for the next command */
         for (j = 0; j < argc; j++) decrRefCount(argv[j]);
         zfree(argv);
-
-        /* Handle swapping while loading big datasets when VM is on */
-        force_swapout = 0;
-        if ((zmalloc_used_memory() - server.vm_max_memory) > 1024*1024*32)
-            force_swapout = 1;
-
-        if (server.vm_enabled && force_swapout) {
-            while (zmalloc_used_memory() > server.vm_max_memory) {
-                if (vmSwapOneObjectBlocking() == REDIS_ERR) break;
-            }
-        }
     }
 
     /* This point can only be reached when EOF is reached without errors.
@@ -359,22 +347,11 @@ int rewriteAppendOnlyFile(char *filename) {
             sds keystr = dictGetEntryKey(de);
             robj key, *o;
             time_t expiretime;
-            int swapped;
 
             keystr = dictGetEntryKey(de);
             o = dictGetEntryVal(de);
             initStaticStringObject(key,keystr);
-            /* If the value for this key is swapped, load a preview in memory.
-             * We use a "swapped" flag to remember if we need to free the
-             * value object instead to just increment the ref count anyway
-             * in order to avoid copy-on-write of pages if we are forked() */
-            if (!server.vm_enabled || o->storage == REDIS_VM_MEMORY ||
-                o->storage == REDIS_VM_SWAPPING) {
-                swapped = 0;
-            } else {
-                o = vmPreviewObject(o);
-                swapped = 1;
-            }
+
             expiretime = getExpire(db,&key);
 
             /* Save the key and associated value */
@@ -509,7 +486,6 @@ int rewriteAppendOnlyFile(char *filename) {
                 if (fwriteBulkObject(fp,&key) == 0) goto werr;
                 if (fwriteBulkLongLong(fp,expiretime) == 0) goto werr;
             }
-            if (swapped) decrRefCount(o);
         }
         dictReleaseIterator(di);
     }
@@ -553,12 +529,11 @@ int rewriteAppendOnlyFileBackground(void) {
     pid_t childpid;
 
     if (server.bgrewritechildpid != -1) return REDIS_ERR;
-    if (server.vm_enabled) waitEmptyIOJobsQueue();
+    redisAssert(server.ds_enabled == 0);
     if ((childpid = fork()) == 0) {
         /* Child */
         char tmpfile[256];
 
-        if (server.vm_enabled) vmReopenSwapFile();
         if (server.ipfd > 0) close(server.ipfd);
         if (server.sofd > 0) close(server.sofd);
         snprintf(tmpfile,256,"temp-rewriteaof-bg-%d.aof", (int) getpid());