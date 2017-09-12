@@ -62,6 +62,7 @@ static struct config {
     int pubsub_mode;
     int raw_output; /* output mode per command */
     int tty; /* flag for default output format */
+    int stdinarg; /* get last arg from stdin. (-x option) */
     char mb_sep;
     char *auth;
     char *historyfile;
@@ -337,6 +338,8 @@ static int parseOptions(int argc, char **argv) {
             i++;
         } else if (!strcmp(argv[i],"-h") && lastarg) {
             usage();
+        } else if (!strcmp(argv[i],"-x")) {
+            config.stdinarg = 1;
         } else if (!strcmp(argv[i],"-p") && !lastarg) {
             config.hostport = atoi(argv[i+1]);
             i++;
@@ -389,9 +392,8 @@ static sds readArgFromStdin(void) {
 
 static void usage() {
     fprintf(stderr, "usage: redis-cli [-iv] [-h host] [-p port] [-a authpw] [-r repeat_times] [-n db_num] cmd arg1 arg2 arg3 ... argN\n");
-    fprintf(stderr, "usage: echo \"argN\" | redis-cli [-h host] [-p port] [-a authpw] [-r repeat_times] [-n db_num] cmd arg1 arg2 ... arg(N-1)\n");
-    fprintf(stderr, "\nIf a pipe from standard input is detected this data is used as last argument.\n\n");
-    fprintf(stderr, "example: cat /etc/passwd | redis-cli set my_passwd\n");
+    fprintf(stderr, "usage: echo \"argN\" | redis-cli -x [options] cmd arg1 arg2 ... arg(N-1)\n\n");
+    fprintf(stderr, "example: cat /etc/passwd | redis-cli -x set my_passwd\n");
     fprintf(stderr, "example: redis-cli get my_passwd\n");
     fprintf(stderr, "example: redis-cli -r 100 lpush mylist x\n");
     fprintf(stderr, "\nRun in interactive mode: redis-cli -i or just don't pass any command\n");
@@ -456,9 +458,7 @@ static void repl() {
 
 static int noninteractive(int argc, char **argv) {
     int retval = 0;
-    struct stat s;
-    fstat(fileno(stdin), &s);
-    if (S_ISFIFO(s.st_mode) || S_ISREG(s.st_mode)) { /* pipe, regular file */
+    if (config.stdinarg) {
         argv = zrealloc(argv, (argc+1)*sizeof(char*));
         argv[argc] = readArgFromStdin();
         retval = cliSendCommand(argc+1, argv, config.repeat);
@@ -481,6 +481,7 @@ int main(int argc, char **argv) {
     config.monitor_mode = 0;
     config.pubsub_mode = 0;
     config.raw_output = 0;
+    config.stdinarg = 0;
     config.auth = NULL;
     config.historyfile = NULL;
     config.tty = isatty(fileno(stdout)) || (getenv("FAKETTY") != NULL);