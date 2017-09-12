@@ -138,6 +138,7 @@ static struct redisCommand cmdTable[] = {
 };
 
 static int cliReadReply(int fd);
+static void usage();
 
 static struct redisCommand *lookupCommand(char *name) {
     int j = 0;
@@ -360,6 +361,8 @@ static int parseOptions(int argc, char **argv) {
             }
             config.hostip = ip;
             i++;
+        } else if (!strcmp(argv[i],"-h") && lastarg) {
+            usage();
         } else if (!strcmp(argv[i],"-p") && !lastarg) {
             config.hostport = atoi(argv[i+1]);
             i++;
@@ -393,6 +396,16 @@ static sds readArgFromStdin(void) {
     return arg;
 }
 
+static void usage() {
+    fprintf(stderr, "usage: redis-cli [-h host] [-p port] [-r repeat_times] [-n db_num] cmd arg1 arg2 arg3 ... argN\n");
+    fprintf(stderr, "usage: echo \"argN\" | redis-cli [-h host] [-p port] [-r repeat_times] [-n db_num] cmd arg1 arg2 ... arg(N-1)\n");
+    fprintf(stderr, "\nIf a pipe from standard input is detected this data is used as last argument.\n\n");
+    fprintf(stderr, "example: cat /etc/passwd | redis-cli set my_passwd\n");
+    fprintf(stderr, "example: redis-cli get my_passwd\n");
+    fprintf(stderr, "example: redis-cli -r 100 lpush mylist x\n");
+    exit(1);
+}
+
 int main(int argc, char **argv) {
     int firstarg, j;
     char **argvcopy;
@@ -412,15 +425,7 @@ int main(int argc, char **argv) {
     for(j = 0; j < argc; j++)
         argvcopy[j] = sdsnew(argv[j]);
 
-    if (argc < 1) {
-        fprintf(stderr, "usage: redis-cli [-h host] [-p port] [-r repeat_times] [-n db_num] cmd arg1 arg2 arg3 ... argN\n");
-        fprintf(stderr, "usage: echo \"argN\" | redis-cli [-h host] [-p port] [-r repeat_times] [-n db_num] cmd arg1 arg2 ... arg(N-1)\n");
-        fprintf(stderr, "\nIf a pipe from standard input is detected this data is used as last argument.\n\n");
-        fprintf(stderr, "example: cat /etc/passwd | redis-cli set my_passwd\n");
-        fprintf(stderr, "example: redis-cli get my_passwd\n");
-        fprintf(stderr, "example: redis-cli -r 100 lpush mylist x\n");
-        exit(1);
-    }
+    if (argc < 1) usage();
 
     /* Read the last argument from stdandard input if needed */
     if ((rc = lookupCommand(argv[0])) != NULL) {