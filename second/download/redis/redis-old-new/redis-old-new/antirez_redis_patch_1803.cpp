@@ -475,6 +475,8 @@ static int parseOptions(int argc, char **argv) {
             i++;
         } else if (!strcmp(argv[i],"-h") && lastarg) {
             usage();
+        } else if (!strcmp(argv[i],"--help")) {
+            usage();
         } else if (!strcmp(argv[i],"-x")) {
             config.stdinarg = 1;
         } else if (!strcmp(argv[i],"-p") && !lastarg) {
@@ -492,19 +494,10 @@ static int parseOptions(int argc, char **argv) {
         } else if (!strcmp(argv[i],"-a") && !lastarg) {
             config.auth = argv[i+1];
             i++;
-        } else if (!strcmp(argv[i],"-i")) {
-            fprintf(stderr,
-"Starting interactive mode using -i is deprecated. Interactive mode is started\n"
-"by default when redis-cli is executed without a command to execute.\n"
-            );
-        } else if (!strcmp(argv[i],"-c")) {
-            fprintf(stderr,
-"Reading last argument from standard input using -c is deprecated.\n"
-"When standard input is connected to a pipe or regular file, it is\n"
-"automatically used as last argument.\n"
-            );
-        } else if (!strcmp(argv[i],"-v")) {
-            printf("redis-cli shipped with Redis version %s (%s)\n", REDIS_VERSION, redisGitSHA1());
+        } else if (!strcmp(argv[i],"-v") || !strcmp(argv[i], "--version")) {
+            sds version = cliVersion();
+            printf("redis-cli %s\n", version);
+            sdsfree(version);
             exit(0);
         } else {
             break;
@@ -531,12 +524,31 @@ static sds readArgFromStdin(void) {
 }
 
 static void usage() {
-    fprintf(stderr, "usage: redis-cli [-iv] [-h host] [-p port] [-s /path/to/socket] [-a authpw] [-r repeat_times] [-n db_num] cmd arg1 arg2 arg3 ... argN\n");
-    fprintf(stderr, "usage: echo \"argN\" | redis-cli -x [options] cmd arg1 arg2 ... arg(N-1)\n\n");
-    fprintf(stderr, "example: cat /etc/passwd | redis-cli -x set my_passwd\n");
-    fprintf(stderr, "example: redis-cli get my_passwd\n");
-    fprintf(stderr, "example: redis-cli -r 100 lpush mylist x\n");
-    fprintf(stderr, "\nRun in interactive mode: redis-cli -i or just don't pass any command\n");
+    sds version = cliVersion();
+    fprintf(stderr,
+"redis-cli %s\n"
+"\n"
+"Usage: redis-cli [OPTIONS] [cmd [arg [arg ...]]]\n"
+"  -h <hostname>    Server hostname (default: 127.0.0.1)\n"
+"  -p <port>        Server port (default: 6379)\n"
+"  -s <socket>      Server socket (overrides hostname and port)\n"
+"  -a <password>    Password to use when connecting to the server\n"
+"  -r <repeat>      Execute specified command N times\n"
+"  -n <db>          Database number\n"
+"  -x               Read last argument from STDIN\n"
+"  --help           Output this help and exit\n"
+"  --version        Output version and exit\n"
+"\n"
+"Examples:\n"
+"  cat /etc/passwd | redis-cli -x set mypasswd\n"
+"  redis-cli get mypasswd\n"
+"  redis-cli -r 100 lpush mylist x\n"
+"\n"
+"When no command is given, redis-cli starts in interactive mode.\n"
+"Type \"help\" in interactive mode for information on available commands.\n"
+"\n",
+        version);
+    sdsfree(version);
     exit(1);
 }
 