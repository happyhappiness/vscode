@@ -3011,7 +3011,12 @@ static int rdbSave(char *filename) {
     int j;
     time_t now = time(NULL);
 
-    waitEmptyIOJobsQueue(); /* Otherwise other threads may fseek() the swap */
+    /* Wait for I/O therads to terminate, just in case this is a
+     * foreground-saving, to avoid seeking the swap file descriptor at the
+     * same time. */
+    if (server.vm_enabled)
+        waitEmptyIOJobsQueue();
+
     snprintf(tmpfile,256,"temp-%d.rdb", (int) getpid());
     fp = fopen(tmpfile,"w");
     if (!fp) {