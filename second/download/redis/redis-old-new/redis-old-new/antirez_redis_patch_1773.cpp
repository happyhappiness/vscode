@@ -395,12 +395,6 @@ off_t rdbSavedObjectLen(robj *o) {
     return len;
 }
 
-/* Return the number of pages required to save this object in the swap file */
-off_t rdbSavedObjectPages(robj *o) {
-    off_t bytes = rdbSavedObjectLen(o);
-    return (bytes+(server.vm_page_size-1))/server.vm_page_size;
-}
-
 /* Save the DB on disk. Return REDIS_ERR on error, REDIS_OK on success */
 int rdbSave(char *filename) {
     dictIterator *di = NULL;
@@ -410,11 +404,8 @@ int rdbSave(char *filename) {
     int j;
     time_t now = time(NULL);
 
-    /* Wait for I/O therads to terminate, just in case this is a
-     * foreground-saving, to avoid seeking the swap file descriptor at the
-     * same time. */
-    if (server.vm_enabled)
-        waitEmptyIOJobsQueue();
+    /* FIXME: implement .rdb save for disk store properly */
+    redisAssert(server.ds_enabled == 0);
 
     snprintf(tmpfile,256,"temp-%d.rdb", (int) getpid());
     fp = fopen(tmpfile,"w");
@@ -453,26 +444,10 @@ int rdbSave(char *filename) {
                 if (rdbSaveType(fp,REDIS_EXPIRETIME) == -1) goto werr;
                 if (rdbSaveTime(fp,expiretime) == -1) goto werr;
             }
-            /* Save the key and associated value. This requires special
-             * handling if the value is swapped out. */
-            if (!server.vm_enabled || o->storage == REDIS_VM_MEMORY ||
-                                      o->storage == REDIS_VM_SWAPPING) {
-                /* Save type, key, value */
-                if (rdbSaveType(fp,o->type) == -1) goto werr;
-                if (rdbSaveStringObject(fp,&key) == -1) goto werr;
-                if (rdbSaveObject(fp,o) == -1) goto werr;
-            } else {
-                /* REDIS_VM_SWAPPED or REDIS_VM_LOADING */
-                robj *po;
-                /* Get a preview of the object in memory */
-                po = vmPreviewObject(o);
-                /* Save type, key, value */
-                if (rdbSaveType(fp,po->type) == -1) goto werr;
-                if (rdbSaveStringObject(fp,&key) == -1) goto werr;
-                if (rdbSaveObject(fp,po) == -1) goto werr;
-                /* Remove the loaded object from memory */
-                decrRefCount(po);
-            }
+            /* Save type, key, value */
+            if (rdbSaveType(fp,o->type) == -1) goto werr;
+            if (rdbSaveStringObject(fp,&key) == -1) goto werr;
+            if (rdbSaveObject(fp,o) == -1) goto werr;
         }
         dictReleaseIterator(di);
     }
@@ -508,11 +483,10 @@ int rdbSaveBackground(char *filename) {
     pid_t childpid;
 
     if (server.bgsavechildpid != -1) return REDIS_ERR;
-    if (server.vm_enabled) waitEmptyIOJobsQueue();
+    redisAssert(server.ds_enabled == 0);
     server.dirty_before_bgsave = server.dirty;
     if ((childpid = fork()) == 0) {
         /* Child */
-        if (server.vm_enabled) vmReopenSwapFile();
         if (server.ipfd > 0) close(server.ipfd);
         if (server.sofd > 0) close(server.sofd);
         if (rdbSave(filename) == REDIS_OK) {
@@ -899,8 +873,6 @@ int rdbLoad(char *filename) {
     startLoading(fp);
     while(1) {
         robj *key, *val;
-        int force_swapout;
-
         expiretime = -1;
 
         /* Serve the clients from time to time */
@@ -970,21 +942,6 @@ int rdbLoad(char *filename) {
             continue;
         }
         decrRefCount(key);
-
-        /* Flush data on disk once 32 MB of additional RAM are used... */
-        force_swapout = 0;
-        if ((zmalloc_used_memory() - server.vm_max_memory) > 1024*1024*32)
-            force_swapout = 1;
-
-        /* If we have still some hope of having some value fitting memory
-         * then we try random sampling. */
-        if (!swap_all_values && server.vm_enabled && force_swapout) {
-            while (zmalloc_used_memory() > server.vm_max_memory) {
-                if (vmSwapOneObjectBlocking() == REDIS_ERR) break;
-            }
-            if (zmalloc_used_memory() > server.vm_max_memory)
-                swap_all_values = 1; /* We are already using too much mem */
-        }
     }
     fclose(fp);
     stopLoading();