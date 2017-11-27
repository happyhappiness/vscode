   if (fh != NULL) {
     fscache_read_stats_file(fh);
     fclose(fh);
 
   } else {
     printf("cant open file\n");
-    return (-1);
+    return -1;
   }
-  return (0);
+  return 0;
 }
 
 void module_register(void) {
   plugin_register_read("fscache", fscache_read);
 } /* void module_register */
-
-/* vim: set sw=4 sts=4 et : */
