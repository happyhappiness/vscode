@@ -61,6 +61,7 @@ static struct config {
     int pubsub_mode;
     int raw_output; /* output mode per command */
     int tty; /* flag for default output format */
+    char mb_sep;
     char *auth;
     char *historyfile;
 } config;
@@ -108,7 +109,7 @@ static int cliReadSingleLineReply(int fd, int quiet) {
 
     if (reply == NULL) return 1;
     if (!quiet)
-        printf("%s\n", reply);
+        printf("%s", reply);
     sdsfree(reply);
     return 0;
 }
@@ -162,7 +163,6 @@ static int cliReadBulkReply(int fd) {
         /* If you are producing output for the standard output we want
          * a more interesting output with quoted characters and so forth */
         printStringRepr(reply,bulklen);
-        printf("\n");
     }
     zfree(reply);
     return 0;
@@ -183,8 +183,9 @@ static int cliReadMultiBulkReply(int fd) {
         printf("(empty list or set)\n");
     }
     while(elements--) {
-        printf("%d. ", c);
+        if (config.tty) printf("%d. ", c);
         if (cliReadReply(fd)) return 1;
+        if (elements) printf("%c",config.mb_sep);
         c++;
     }
     return 0;
@@ -199,13 +200,13 @@ static int cliReadReply(int fd) {
     }
     switch(type) {
     case '-':
-        printf("(error) ");
+        if (config.tty) printf("(error) ");
         cliReadSingleLineReply(fd,0);
         return 1;
     case '+':
         return cliReadSingleLineReply(fd,0);
     case ':':
-        printf("(integer) ");
+        if (config.tty) printf("(integer) ");
         return cliReadSingleLineReply(fd,0);
     case '$':
         return cliReadBulkReply(fd);
@@ -275,14 +276,17 @@ static int cliSendCommand(int argc, char **argv, int repeat) {
             printf("Reading messages... (press Ctrl-c to quit)\n");
             while (1) {
                 cliReadReply(fd);
-                printf("\n");
+                printf("\n\n");
             }
         }
 
         retval = cliReadReply(fd);
         if (retval) {
             return retval;
         }
+        if (!config.raw_output && config.tty) {
+            printf("\n");
+        }
     }
     return 0;
 }
@@ -493,6 +497,7 @@ int main(int argc, char **argv) {
     config.auth = NULL;
     config.historyfile = NULL;
     config.tty = 1;
+    config.mb_sep = '\n';
 
     if (getenv("HOME") != NULL) {
         config.historyfile = malloc(256);
@@ -517,7 +522,7 @@ int main(int argc, char **argv) {
         repl();
     }
 
-    config.tty = isatty(stdout) || (getenv("FAKETTY") != NULL);
+    config.tty = isatty(fileno(stdout)) || (getenv("FAKETTY") != NULL);
     argvcopy = convertToSds(argc+1, argv);
     if (config.argn_from_stdin) {
         sds lastarg = readArgFromStdin();