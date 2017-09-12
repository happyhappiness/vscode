@@ -320,6 +320,7 @@ static sds readArgFromStdin(void) {
 int main(int argc, char **argv) {
     int firstarg, j;
     char **argvcopy;
+    struct redisCommand *rc;
 
     config.hostip = "127.0.0.1";
     config.hostport = 6379;
@@ -333,13 +334,6 @@ int main(int argc, char **argv) {
     for(j = 0; j < argc; j++)
         argvcopy[j] = sdsnew(argv[j]);
 
-    /* Read the last argument from stdandard input */
-    if (!isatty(fileno(stdin))) {
-        sds lastarg = readArgFromStdin();
-        argvcopy[argc] = lastarg;
-        argc++;
-    }
-
     if (argc < 1) {
         fprintf(stderr, "usage: redis-cli [-h host] [-p port] cmd arg1 arg2 arg3 ... argN\n");
         fprintf(stderr, "usage: echo \"argN\" | redis-cli [-h host] [-p port] cmd arg1 arg2 ... arg(N-1)\n");
@@ -349,5 +343,14 @@ int main(int argc, char **argv) {
         exit(1);
     }
 
+    /* Read the last argument from stdandard input if needed */
+    if ((rc = lookupCommand(argv[0])) != NULL) {
+        if (rc->arity > 0 && argc == rc->arity-1) {
+            sds lastarg = readArgFromStdin();
+            argvcopy[argc] = lastarg;
+            argc++;
+        }
+    }
+
     return cliSendCommand(argc, argvcopy);
 }