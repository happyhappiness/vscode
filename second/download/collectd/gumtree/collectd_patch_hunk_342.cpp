 #include "plugin.h"
 
 #include "utils_cmd_listval.h"
 #include "utils_cache.h"
 #include "utils_parse_option.h"
 
+#define free_everything_and_return(status) do { \
+    size_t j; \
+    for (j = 0; j < number; j++) { \
+      sfree(names[j]); \
+      names[j] = NULL; \
+    } \
+    sfree(names); \
+    sfree(times); \
+    return (status); \
+  } while (0)
+
 #define print_to_socket(fh, ...) \
   if (fprintf (fh, __VA_ARGS__) < 0) { \
     char errbuf[1024]; \
     WARNING ("handle_listval: failed to write to socket #%i: %s", \
 	fileno (fh), sstrerror (errno, errbuf, sizeof (errbuf))); \
-    return -1; \
+    free_everything_and_return (-1); \
   }
 
 int handle_listval (FILE *fh, char *buffer)
 {
   char *command;
   char **names = NULL;
