@@ -7035,9 +7035,13 @@ static void vmInit(void) {
 
     expandVmSwapFilename();
     redisLog(REDIS_NOTICE,"Using '%s' as swap file",server.vm_swap_file);
-    server.vm_fp = fopen(server.vm_swap_file,"r+b");
+    if ((server.vm_fp = fopen(server.vm_swap_file,"r+b")) == NULL) {
+        server.vm_fp = fopen(server.vm_swap_file,"w+b");
+    }
     if (server.vm_fp == NULL) {
-        redisLog(REDIS_WARNING,"Impossible to open the swap file. Exiting.");
+        redisLog(REDIS_WARNING,
+            "Impossible to open the swap file: %s. Exiting.",
+            strerror(errno));
         exit(1);
     }
     server.vm_fd = fileno(server.vm_fp);