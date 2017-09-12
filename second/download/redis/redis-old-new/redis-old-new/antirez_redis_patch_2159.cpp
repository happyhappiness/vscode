@@ -39,6 +39,7 @@
 #include "sds.h"
 #include "adlist.h"
 #include "zmalloc.h"
+#include "linenoise.h"
 
 #define REDIS_CMD_INLINE 1
 #define REDIS_CMD_BULK 2
@@ -451,39 +452,30 @@ static char **convertToSds(int count, char** args) {
   return sds;
 }
 
-static char *prompt(char *line, int size) {
-    char *retval;
-
-    do {
-        printf(">> ");
-        retval = fgets(line, size, stdin);
-    } while (retval && *line == '\n');
-    line[strlen(line) - 1] = '\0';
-
-    return retval;
-}
-
 static void repl() {
     int size = 4096, max = size >> 1, argc;
-    char buffer[size];
-    char *line = buffer;
+    char *line;
     char **ap, *args[max];
 
-    while (prompt(line, size)) {
-        argc = 0;
-
-        for (ap = args; (*ap = strsep(&line, " \t")) != NULL;) {
-            if (**ap != '\0') {
-                if (argc >= max) break;
-                if (strcasecmp(*ap,"quit") == 0 || strcasecmp(*ap,"exit") == 0)
-                    exit(0);
-                ap++;
-                argc++;
-            }
+    while((line = linenoise(">> ")) != NULL) {
+        if (line[0] != '\0') {
+          linenoiseHistoryAdd(line);
+          argc = 0;
+
+          for (ap = args; (*ap = strsep(&line, " \t")) != NULL;) {
+              if (**ap != '\0') {
+                  if (argc >= max) break;
+                  if (strcasecmp(*ap,"quit") == 0 || strcasecmp(*ap,"exit") == 0)
+                      exit(0);
+                  ap++;
+                  argc++;
+              }
+          }
+
+          cliSendCommand(argc, convertToSds(argc, args), 1);
         }
 
-        cliSendCommand(argc, convertToSds(argc, args), 1);
-        line = buffer;
+        free(line);
     }
 
     exit(0);