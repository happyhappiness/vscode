@@ -378,7 +378,7 @@ static char **splitArguments(char *line, int *argc) {
         if (*p) {
             /* get a token */
             int inq=0; /* set to 1 if we are in "quotes" */
-            int done = 0;
+            int done=0;
 
             if (current == NULL) current = sdsempty();
             while(!done) {
@@ -397,7 +397,12 @@ static char **splitArguments(char *line, int *argc) {
                         }
                         current = sdscatlen(current,&c,1);
                     } else if (*p == '"') {
-                        done = 1;
+                        /* closing quote must be followed by a space */
+                        if (*(p+1) && !isspace(*(p+1))) goto err;
+                        done=1;
+                    } else if (!*p) {
+                        /* unterminated quotes */
+                        goto err;
                     } else {
                         current = sdscatlen(current,p,1);
                     }
@@ -429,6 +434,13 @@ static char **splitArguments(char *line, int *argc) {
             return vector;
         }
     }
+
+err:
+    while(*argc--)
+        sdsfree(vector[*argc]);
+    zfree(vector);
+    if (current) sdsfree(current);
+    return NULL;
 }
 
 #define LINE_BUFLEN 4096
@@ -441,7 +453,10 @@ static void repl() {
             argv = splitArguments(line,&argc);
             linenoiseHistoryAdd(line);
             if (config.historyfile) linenoiseHistorySave(config.historyfile);
-            if (argc > 0) {
+            if (argv == NULL) {
+                printf("Invalid argument(s)\n");
+                continue;
+            } else if (argc > 0) {
                 if (strcasecmp(argv[0],"quit") == 0 ||
                     strcasecmp(argv[0],"exit") == 0)
                         exit(0);