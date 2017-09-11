@@ -1059,17 +1059,20 @@ int rewriteAppendOnlyFile(char *filename) {
     /* Read again a few times to get more data from the parent.
      * We can't read forever (the server may receive data from clients
      * fater than it is able to send data to the child), so we try to read
-     * some more data in a loop and wait a bit if data is not available, but
-     * don't wait more than 100 ms total. */
+     * some more data in a loop as soon as there is a good chance more data
+     * will come. If it looks like we are wasting time, we abort (this
+     * happens after 20 ms without new data). */
     int nodata = 0;
-    for (j = 0; j < 100; j++) {
-        ssize_t nread_from_parent = aofReadDiffFromParent();
-        printf("%lld\n", (long long) nread_from_parent);
-        if (nread_from_parent == 0) {
+    mstime_t start = mstime();
+    while(mstime()-start < 1000 && nodata < 20) {
+        if (aeWait(server.aof_pipe_read_data_from_parent, AE_READABLE, 1) <= 0)
+        {
             nodata++;
-            if (nodata == 10) break;
-            usleep(10000);
+            continue;
         }
+        nodata = 0; /* Start counting from zero, we stop on N *contiguous*
+                       timeouts. */
+        aofReadDiffFromParent();
     }
 
     /* Ask the master to stop sending diffs. */