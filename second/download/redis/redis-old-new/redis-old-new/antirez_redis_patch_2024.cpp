@@ -55,7 +55,6 @@ static struct config {
     long repeat;
     int dbnum;
     int argn_from_stdin;
-    int interactive;
     int shutdown;
     int monitor_mode;
     int pubsub_mode;
@@ -320,7 +319,10 @@ static int parseOptions(int argc, char **argv) {
             config.auth = argv[i+1];
             i++;
         } else if (!strcmp(argv[i],"-i")) {
-            config.interactive = 1;
+            fprintf(stderr,
+"Starting interactive mode using -i is deprecated. Interactive mode is started\n"
+"by default when redis-cli is executed without a command to execute.\n"
+            );
         } else if (!strcmp(argv[i],"-c")) {
             config.argn_from_stdin = 1;
         } else if (!strcmp(argv[i],"-v")) {
@@ -490,7 +492,6 @@ int main(int argc, char **argv) {
     config.dbnum = 0;
     config.argn_from_stdin = 0;
     config.shutdown = 0;
-    config.interactive = 0;
     config.monitor_mode = 0;
     config.pubsub_mode = 0;
     config.raw_output = 0;
@@ -517,10 +518,8 @@ int main(int argc, char **argv) {
         cliSendCommand(2, convertToSds(2, authargv), 1);
     }
 
-    if (argc == 0 || config.interactive == 1) {
-        config.interactive = 1;
-        repl();
-    }
+    /* Start interactive mode when no command is provided */
+    if (argc == 0) repl();
 
     argvcopy = convertToSds(argc+1, argv);
     if (config.argn_from_stdin) {