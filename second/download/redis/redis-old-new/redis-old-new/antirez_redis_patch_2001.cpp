@@ -37,6 +37,7 @@
 #include <unistd.h>
 #include <ctype.h>
 #include <errno.h>
+#include <sys/stat.h>
 
 #include "anet.h"
 #include "sds.h"
@@ -55,7 +56,6 @@ static struct config {
     int hostport;
     long repeat;
     int dbnum;
-    int argn_from_stdin;
     int interactive;
     int shutdown;
     int monitor_mode;
@@ -334,7 +334,11 @@ static int parseOptions(int argc, char **argv) {
 "by default when redis-cli is executed without a command to execute.\n"
             );
         } else if (!strcmp(argv[i],"-c")) {
-            config.argn_from_stdin = 1;
+            fprintf(stderr,
+"Reading last argument from standard input using -c is deprecated.\n"
+"When standard input is connected to a pipe or regular file, it is\n"
+"automatically used as last argument.\n"
+            );
         } else if (!strcmp(argv[i],"-v")) {
             printf("redis-cli shipped with Redis verison %s\n", REDIS_VERSION);
             exit(0);
@@ -364,7 +368,7 @@ static sds readArgFromStdin(void) {
 
 static void usage() {
     fprintf(stderr, "usage: redis-cli [-iv] [-h host] [-p port] [-a authpw] [-r repeat_times] [-n db_num] cmd arg1 arg2 arg3 ... argN\n");
-    fprintf(stderr, "usage: echo \"argN\" | redis-cli -c [-h host] [-p port] [-a authpw] [-r repeat_times] [-n db_num] cmd arg1 arg2 ... arg(N-1)\n");
+    fprintf(stderr, "usage: echo \"argN\" | redis-cli [-h host] [-p port] [-a authpw] [-r repeat_times] [-n db_num] cmd arg1 arg2 ... arg(N-1)\n");
     fprintf(stderr, "\nIf a pipe from standard input is detected this data is used as last argument.\n\n");
     fprintf(stderr, "example: cat /etc/passwd | redis-cli set my_passwd\n");
     fprintf(stderr, "example: redis-cli get my_passwd\n");
@@ -429,15 +433,28 @@ static void repl() {
     exit(0);
 }
 
+static int noninteractive(int argc, char **argv) {
+    int retval = 0;
+    struct stat s;
+    fstat(fileno(stdin), &s);
+    if (S_ISFIFO(s.st_mode) || S_ISREG(s.st_mode)) { /* pipe, regular file */
+        argv = zrealloc(argv, (argc+1)*sizeof(char*));
+        argv[argc] = readArgFromStdin();
+        retval = cliSendCommand(argc+1, argv, config.repeat);
+    } else {
+        /* stdin is probably a tty, can be tested with S_ISCHR(s.st_mode) */
+        retval = cliSendCommand(argc, argv, config.repeat);
+    }
+    return retval;
+}
+
 int main(int argc, char **argv) {
     int firstarg;
-    char **argvcopy;
 
     config.hostip = "127.0.0.1";
     config.hostport = 6379;
     config.repeat = 1;
     config.dbnum = 0;
-    config.argn_from_stdin = 0;
     config.interactive = 0;
     config.shutdown = 0;
     config.monitor_mode = 0;
@@ -468,12 +485,6 @@ int main(int argc, char **argv) {
 
     /* Start interactive mode when no command is provided */
     if (argc == 0) repl();
-
-    argvcopy = convertToSds(argc+1, argv);
-    if (config.argn_from_stdin) {
-        sds lastarg = readArgFromStdin();
-        argvcopy[argc] = lastarg;
-        argc++;
-    }
-    return cliSendCommand(argc, argvcopy, config.repeat);
+    /* Otherwise, we have some arguments to execute */
+    return noninteractive(argc,convertToSds(argc,argv));
 }