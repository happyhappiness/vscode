 } /* void parse_file */
 
 int read_types_list(const char *file) {
   FILE *fh;
 
   if (file == NULL)
-    return (-1);
+    return -1;
 
   fh = fopen(file, "r");
   if (fh == NULL) {
     char errbuf[1024];
     fprintf(stderr, "Failed to open types database `%s': %s.\n", file,
             sstrerror(errno, errbuf, sizeof(errbuf)));
     ERROR("Failed to open types database `%s': %s", file,
           sstrerror(errno, errbuf, sizeof(errbuf)));
-    return (-1);
+    return -1;
   }
 
   parse_file(fh);
 
   fclose(fh);
   fh = NULL;
 
   DEBUG("Done parsing `%s'", file);
 
-  return (0);
+  return 0;
 } /* int read_types_list */
-
-/*
- * vim: shiftwidth=2:softtabstop=2:tabstop=8
- */
