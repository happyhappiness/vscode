             intelligent = 1;
             dowork = 1;
             break;
         }
 
         if (dowork && !interrupted) {
-            if (!process_dir(path, instance) && !interrupted) {
-                purge(path, instance, max);
+            apr_off_t nodes = 0;
+            if (!process_dir(path, instance, &nodes) && !interrupted) {
+                purge(path, instance, max, inodes, nodes, round);
             }
             else if (!isdaemon && !interrupted) {
                 apr_file_printf(errfile, "An error occurred, cache cleaning "
                                          "aborted." APR_EOL_STR);
                 return 1;
             }
