@@ -29,6 +29,7 @@
  */
 
 #include "fmacros.h"
+#include "version.h"
 
 #include <stdio.h>
 #include <string.h>
@@ -315,6 +316,9 @@ static int parseOptions(int argc, char **argv) {
             config.interactive = 1;
         } else if (!strcmp(argv[i],"-c")) {
             config.argn_from_stdin = 1;
+        } else if (!strcmp(argv[i],"-v")) {
+            printf("redis-cli shipped with Redis verison %s\n", REDIS_VERSION);
+            exit(0);
         } else {
             break;
         }
@@ -340,7 +344,7 @@ static sds readArgFromStdin(void) {
 }
 
 static void usage() {
-    fprintf(stderr, "usage: redis-cli [-h host] [-p port] [-a authpw] [-r repeat_times] [-n db_num] [-i] cmd arg1 arg2 arg3 ... argN\n");
+    fprintf(stderr, "usage: redis-cli [-iv] [-h host] [-p port] [-a authpw] [-r repeat_times] [-n db_num] cmd arg1 arg2 arg3 ... argN\n");
     fprintf(stderr, "usage: echo \"argN\" | redis-cli -c [-h host] [-p port] [-a authpw] [-r repeat_times] [-n db_num] cmd arg1 arg2 ... arg(N-1)\n");
     fprintf(stderr, "\nIf a pipe from standard input is detected this data is used as last argument.\n\n");
     fprintf(stderr, "example: cat /etc/passwd | redis-cli set my_passwd\n");