     sfree(names); \
     sfree(times); \
     return (status); \
   } while (0)
 
 #define print_to_socket(fh, ...) \
-  do { \
-    if (fprintf (fh, __VA_ARGS__) < 0) { \
-      char errbuf[1024]; \
-      WARNING ("handle_listval: failed to write to socket #%i: %s", \
-          fileno (fh), sstrerror (errno, errbuf, sizeof (errbuf))); \
-      free_everything_and_return (-1); \
-    } \
-    fflush(fh); \
-  } while (0)
+  if (fprintf (fh, __VA_ARGS__) < 0) { \
+    char errbuf[1024]; \
+    WARNING ("handle_listval: failed to write to socket #%i: %s", \
+	fileno (fh), sstrerror (errno, errbuf, sizeof (errbuf))); \
+    free_everything_and_return (-1); \
+  }
 
 int handle_listval (FILE *fh, char *buffer)
 {
   char *command;
   char **names = NULL;
   cdtime_t *times = NULL;
