@@ -388,6 +388,7 @@ struct redisServer {
     int sort_bypattern;
     /* Virtual memory configuration */
     int vm_enabled;
+    char *vm_swap_file;
     off_t vm_page_size;
     off_t vm_pages;
     unsigned long long vm_max_memory;
@@ -568,7 +569,8 @@ static void freeIOJob(iojob *j);
 static void queueIOJob(iojob *j);
 static int vmWriteObjectOnSwap(robj *o, off_t page);
 static robj *vmReadObjectFromSwap(off_t page, int type);
-static void waitZeroActiveThreads(void);
+static void waitEmptyIOJobsQueue(void);
+static void vmReopenSwapFile(void);
 
 static void authCommand(redisClient *c);
 static void pingCommand(redisClient *c);
@@ -874,7 +876,7 @@ static void redisLog(int level, const char *fmt, ...) {
 
         now = time(NULL);
         strftime(buf,64,"%d %b %H:%M:%S",localtime(&now));
-        fprintf(fp,"%s %c ",buf,c[level]);
+        fprintf(fp,"[%d] %s %c ",(int)getpid(),buf,c[level]);
         vfprintf(fp, fmt, ap);
         fprintf(fp,"\n");
         fflush(fp);
@@ -1377,6 +1379,7 @@ static void initServerConfig() {
     server.blockedclients = 0;
     server.maxmemory = 0;
     server.vm_enabled = 0;
+    server.vm_swap_file = zstrdup("/tmp/redis-%p.vm");
     server.vm_page_size = 256;          /* 256 bytes per page */
     server.vm_pages = 1024*1024*100;    /* 104 millions of pages */
     server.vm_max_memory = 1024LL*1024*1024*1; /* 1 GB of RAM */
@@ -1620,15 +1623,17 @@ static void loadServerConfig(char *filename) {
                 goto loaderr;
             }
         } else if (!strcasecmp(argv[0],"requirepass") && argc == 2) {
-          server.requirepass = zstrdup(argv[1]);
+            server.requirepass = zstrdup(argv[1]);
         } else if (!strcasecmp(argv[0],"pidfile") && argc == 2) {
-          server.pidfile = zstrdup(argv[1]);
+            server.pidfile = zstrdup(argv[1]);
         } else if (!strcasecmp(argv[0],"dbfilename") && argc == 2) {
-          server.dbfilename = zstrdup(argv[1]);
+            server.dbfilename = zstrdup(argv[1]);
         } else if (!strcasecmp(argv[0],"vm-enabled") && argc == 2) {
             if ((server.vm_enabled = yesnotoi(argv[1])) == -1) {
                 err = "argument must be 'yes' or 'no'"; goto loaderr;
             }
+        } else if (!strcasecmp(argv[0],"vm-swap-file") && argc == 2) {
+            server.vm_swap_file = zstrdup(argv[1]);
         } else if (!strcasecmp(argv[0],"vm-max-memory") && argc == 2) {
             server.vm_max_memory = strtoll(argv[1], NULL, 10);
         } else if (!strcasecmp(argv[0],"vm-page-size") && argc == 2) {
@@ -3006,6 +3011,7 @@ static int rdbSave(char *filename) {
     int j;
     time_t now = time(NULL);
 
+    waitEmptyIOJobsQueue(); /* Otherwise other threads may fseek() the swap */
     snprintf(tmpfile,256,"temp-%d.rdb", (int) getpid());
     fp = fopen(tmpfile,"w");
     if (!fp) {
@@ -3095,9 +3101,10 @@ static int rdbSaveBackground(char *filename) {
     pid_t childpid;
 
     if (server.bgsavechildpid != -1) return REDIS_ERR;
-    if (server.vm_enabled) waitZeroActiveThreads();
+    if (server.vm_enabled) waitEmptyIOJobsQueue();
     if ((childpid = fork()) == 0) {
         /* Child */
+        if (server.vm_enabled) vmReopenSwapFile();
         close(server.fd);
         if (rdbSave(filename) == REDIS_OK) {
             exit(0);
@@ -3768,6 +3775,7 @@ static void shutdownCommand(redisClient *c) {
     if (server.appendonly) {
         /* Append only file: fsync() the AOF and exit */
         fsync(server.appendfd);
+        if (server.vm_enabled) unlink(server.vm_swap_file);
         exit(0);
     } else {
         /* Snapshotting. Perform a SYNC SAVE and exit */
@@ -3776,6 +3784,7 @@ static void shutdownCommand(redisClient *c) {
                 unlink(server.pidfile);
             redisLog(REDIS_WARNING,"%zu bytes used at exit",zmalloc_used_memory());
             redisLog(REDIS_WARNING,"Server exit now, bye bye...");
+            if (server.vm_enabled) unlink(server.vm_swap_file);
             exit(0);
         } else {
             /* Ooops.. error saving! The best we can do is to continue operating.
@@ -6917,12 +6926,13 @@ static int rewriteAppendOnlyFileBackground(void) {
     pid_t childpid;
 
     if (server.bgrewritechildpid != -1) return REDIS_ERR;
-    if (server.vm_enabled) waitZeroActiveThreads();
+    if (server.vm_enabled) waitEmptyIOJobsQueue();
     if ((childpid = fork()) == 0) {
         /* Child */
         char tmpfile[256];
-        close(server.fd);
 
+        if (server.vm_enabled) vmReopenSwapFile();
+        close(server.fd);
         snprintf(tmpfile,256,"temp-rewriteaof-bg-%d.aof", (int) getpid());
         if (rewriteAppendOnlyFile(tmpfile) == REDIS_OK) {
             exit(0);
@@ -6992,6 +7002,23 @@ static void aofRemoveTempFile(pid_t childpid) {
  */
 
 /* =================== Virtual Memory - Blocking Side  ====================== */
+
+/* substitute the first occurrence of '%p' with the process pid in the
+ * swap file name. */
+static void expandVmSwapFilename(void) {
+    char *p = strstr(server.vm_swap_file,"%p");
+    sds new;
+    
+    if (!p) return;
+    new = sdsempty();
+    *p = '\0';
+    new = sdscat(new,server.vm_swap_file);
+    new = sdscatprintf(new,"%ld",(long) getpid());
+    new = sdscat(new,p+2);
+    zfree(server.vm_swap_file);
+    server.vm_swap_file = new;
+}
+
 static void vmInit(void) {
     off_t totsize;
     int pipefds[2];
@@ -7000,7 +7027,9 @@ static void vmInit(void) {
     if (server.vm_max_threads != 0)
         zmalloc_enable_thread_safeness(); /* we need thread safe zmalloc() */
 
-    server.vm_fp = fopen("/tmp/redisvm","w+b");
+    expandVmSwapFilename();
+    redisLog(REDIS_NOTICE,"Using '%s' as swap file",server.vm_swap_file);
+    server.vm_fp = fopen(server.vm_swap_file,"r+b");
     if (server.vm_fp == NULL) {
         redisLog(REDIS_WARNING,"Impossible to open the swap file. Exiting.");
         exit(1);
@@ -7025,9 +7054,6 @@ static void vmInit(void) {
     redisLog(REDIS_VERBOSE,"Allocated %lld bytes page table for %lld pages",
         (long long) (server.vm_pages+7)/8, server.vm_pages);
     memset(server.vm_bitmap,0,(server.vm_pages+7)/8);
-    /* Try to remove the swap file, so the OS will really delete it from the
-     * file system when Redis exists. */
-    unlink("/tmp/redisvm");
 
     /* Initialize threaded I/O (used by Virtual Memory) */
     server.io_newjobs = listCreate();
@@ -7509,9 +7535,13 @@ static void vmThreadedIOCompletedJob(aeEventLoop *el, int fd, void *privdata,
             /* Now we know the amount of pages required to swap this object.
              * Let's find some space for it, and queue this task again
              * rebranded as REDIS_IOJOB_DO_SWAP. */
-            if (vmFindContiguousPages(&j->page,j->pages) == REDIS_ERR) {
-                /* Ooops... no space! */
+            if (!vmCanSwapOut() ||
+                vmFindContiguousPages(&j->page,j->pages) == REDIS_ERR)
+            {
+                /* Ooops... no space or we can't swap as there is
+                 * a fork()ed Redis trying to save stuff on disk. */
                 freeIOJob(j);
+                key->storage = REDIS_VM_MEMORY; /* undo operation */
             } else {
                 /* Note that we need to mark this pages as used now,
                  * if the job will be canceled, we'll mark them as freed
@@ -7551,7 +7581,7 @@ static void vmThreadedIOCompletedJob(aeEventLoop *el, int fd, void *privdata,
             freeIOJob(j);
             /* Put a few more swap requests in queue if we are still
              * out of memory */
-            if (zmalloc_used_memory() > server.vm_max_memory) {
+            if (vmCanSwapOut() && zmalloc_used_memory() > server.vm_max_memory){
                 int more = 1;
                 while(more) {
                     lockThreadedIO();
@@ -7731,10 +7761,13 @@ static void spawnIOThread(void) {
 
 /* We need to wait for the last thread to exit before we are able to
  * fork() in order to BGSAVE or BGREWRITEAOF. */
-static void waitZeroActiveThreads(void) {
+static void waitEmptyIOJobsQueue(void) {
     while(1) {
         lockThreadedIO();
-        if (server.io_active_threads == 0) {
+        if (listLength(server.io_newjobs) == 0 &&
+            listLength(server.io_processing) == 0 &&
+            server.io_active_threads == 0)
+        {
             unlockThreadedIO();
             return;
         }
@@ -7743,6 +7776,17 @@ static void waitZeroActiveThreads(void) {
     }
 }
 
+static void vmReopenSwapFile(void) {
+    fclose(server.vm_fp);
+    server.vm_fp = fopen(server.vm_swap_file,"r+b");
+    if (server.vm_fp == NULL) {
+        redisLog(REDIS_WARNING,"Can't re-open the VM swap file: %s. Exiting.",
+            server.vm_swap_file);
+        exit(1);
+    }
+    server.vm_fd = fileno(server.vm_fp);
+}
+
 /* This function must be called while with threaded IO locked */
 static void queueIOJob(iojob *j) {
     redisLog(REDIS_DEBUG,"Queued IO Job %p type %d about key '%s'\n",