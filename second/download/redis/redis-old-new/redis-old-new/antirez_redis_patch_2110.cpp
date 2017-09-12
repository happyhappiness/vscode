@@ -8604,22 +8604,35 @@ static void vmInit(void) {
     off_t totsize;
     int pipefds[2];
     size_t stacksize;
+    struct flock fl;
 
     if (server.vm_max_threads != 0)
         zmalloc_enable_thread_safeness(); /* we need thread safe zmalloc() */
 
     expandVmSwapFilename();
     redisLog(REDIS_NOTICE,"Using '%s' as swap file",server.vm_swap_file);
+    /* Try to open the old swap file, otherwise create it */
     if ((server.vm_fp = fopen(server.vm_swap_file,"r+b")) == NULL) {
         server.vm_fp = fopen(server.vm_swap_file,"w+b");
     }
     if (server.vm_fp == NULL) {
         redisLog(REDIS_WARNING,
-            "Impossible to open the swap file: %s. Exiting.",
+            "Can't open the swap file: %s. Exiting.",
             strerror(errno));
         exit(1);
     }
     server.vm_fd = fileno(server.vm_fp);
+    /* Lock the swap file for writing, this is useful in order to avoid
+     * another instance to use the same swap file for a config error. */
+    fl.l_type = F_WRLCK;
+    fl.l_whence = SEEK_SET;
+    fl.l_start = fl.l_len = 0;
+    if (fcntl(server.vm_fd,F_SETLK,&fl) == -1) {
+        redisLog(REDIS_WARNING,
+            "Can't lock the swap file at '%s': %s. Make sure it is not used by another Redis instance.", server.vm_swap_file, strerror(errno));
+        exit(1);
+    }
+    /* Initialize */
     server.vm_next_page = 0;
     server.vm_near_pages = 0;
     server.vm_stats_used_pages = 0;