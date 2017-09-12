@@ -4485,7 +4485,6 @@ static void shutdownCommand(redisClient *c) {
                 unlink(server.pidfile);
             redisLog(REDIS_WARNING,"%zu bytes used at exit",zmalloc_used_memory());
             redisLog(REDIS_WARNING,"Server exit now, bye bye...");
-            if (server.vm_enabled) unlink(server.vm_swap_file);
             exit(0);
         } else {
             /* Ooops.. error saving! The best we can do is to continue
@@ -8584,22 +8583,6 @@ static void aofRemoveTempFile(pid_t childpid) {
 
 /* =================== Virtual Memory - Blocking Side  ====================== */
 
-/* substitute the first occurrence of '%p' with the process pid in the
- * swap file name. */
-static void expandVmSwapFilename(void) {
-    char *p = strstr(server.vm_swap_file,"%p");
-    sds new;
-
-    if (!p) return;
-    new = sdsempty();
-    *p = '\0';
-    new = sdscat(new,server.vm_swap_file);
-    new = sdscatprintf(new,"%ld",(long) getpid());
-    new = sdscat(new,p+2);
-    zfree(server.vm_swap_file);
-    server.vm_swap_file = new;
-}
-
 static void vmInit(void) {
     off_t totsize;
     int pipefds[2];
@@ -8609,7 +8592,6 @@ static void vmInit(void) {
     if (server.vm_max_threads != 0)
         zmalloc_enable_thread_safeness(); /* we need thread safe zmalloc() */
 
-    expandVmSwapFilename();
     redisLog(REDIS_NOTICE,"Using '%s' as swap file",server.vm_swap_file);
     /* Try to open the old swap file, otherwise create it */
     if ((server.vm_fp = fopen(server.vm_swap_file,"r+b")) == NULL) {