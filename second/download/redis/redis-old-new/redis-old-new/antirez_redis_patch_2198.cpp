@@ -51,6 +51,7 @@ static struct config {
     int hostport;
     long repeat;
     int dbnum;
+    int interactive;
 } config;
 
 struct redisCommand {
@@ -266,8 +267,7 @@ static int cliReadReply(int fd) {
     }
 }
 
-static int selectDb(int fd)
-{
+static int selectDb(int fd) {
     int retval;
     sds cmd;
     char type;
@@ -283,7 +283,7 @@ static int selectDb(int fd)
     retval = cliReadSingleLineReply(fd,1);
     if (retval) {
         close(fd);
-	return retval;
+        return retval;
     }
     return 0;
 }
@@ -313,7 +313,7 @@ static int cliSendCommand(int argc, char **argv) {
         fprintf(stderr,"Error setting DB num\n");
         return 1;
     }
- 
+
     while(config.repeat--) {
         /* Build the command to send */
         cmd = sdsempty();
@@ -363,7 +363,7 @@ static int parseOptions(int argc, char **argv) {
 
     for (i = 1; i < argc; i++) {
         int lastarg = i==argc-1;
-        
+
         if (!strcmp(argv[i],"-h") && !lastarg) {
             char *ip = zmalloc(32);
             if (anetResolve(NULL,argv[i+1],ip) == ANET_ERR) {
@@ -383,6 +383,8 @@ static int parseOptions(int argc, char **argv) {
         } else if (!strcmp(argv[i],"-n") && !lastarg) {
             config.dbnum = atoi(argv[i+1]);
             i++;
+        } else if (!strcmp(argv[i],"-i")) {
+            config.interactive = 1;
         } else {
             break;
         }
@@ -408,43 +410,92 @@ static sds readArgFromStdin(void) {
 }
 
 static void usage() {
-    fprintf(stderr, "usage: redis-cli [-h host] [-p port] [-r repeat_times] [-n db_num] cmd arg1 arg2 arg3 ... argN\n");
+    fprintf(stderr, "usage: redis-cli [-h host] [-p port] [-r repeat_times] [-n db_num] [-i] cmd arg1 arg2 arg3 ... argN\n");
     fprintf(stderr, "usage: echo \"argN\" | redis-cli [-h host] [-p port] [-r repeat_times] [-n db_num] cmd arg1 arg2 ... arg(N-1)\n");
     fprintf(stderr, "\nIf a pipe from standard input is detected this data is used as last argument.\n\n");
     fprintf(stderr, "example: cat /etc/passwd | redis-cli set my_passwd\n");
     fprintf(stderr, "example: redis-cli get my_passwd\n");
     fprintf(stderr, "example: redis-cli -r 100 lpush mylist x\n");
+    fprintf(stderr, "\nRun in interactive mode: redis-cli -i \n");
     exit(1);
 }
 
+/* Turn the plain C strings into Sds strings */
+static char **convertToSds(int count, char** args) {
+  int j;
+  char **sds = zmalloc(sizeof(char*)*count+1);
+
+  for(j = 0; j < count; j++)
+    sds[j] = sdsnew(args[j]);
+
+  return sds;
+}
+
+static char *prompt(char *line, int size) {
+    char *retval;
+
+    do {
+        printf(">> ");
+        retval = fgets(line, size, stdin);
+    } while (retval && *line == '\n');
+
+    fpurge(stdin);
+    return retval;
+}
+
+static void repl() {
+    int size = 4096, max = size >> 1, argc;
+    char buffer[size];
+    char *line = buffer;
+    char **ap, *args[max];
+
+    while (prompt(line, size)) {
+        argc = 0;
+
+        for (ap = args; (*ap = strsep(&line, " \t")) != NULL;) {
+            if (**ap != '\0') {
+                if (argc >= max) break;
+                ap++;
+                argc++;
+            }
+        }
+
+        config.repeat = 1;
+        cliSendCommand(argc, convertToSds(argc, args));
+        line = buffer;
+    }
+
+    exit(0);
+}
+
 int main(int argc, char **argv) {
-    int firstarg, j;
+    int firstarg;
     char **argvcopy;
     struct redisCommand *rc;
 
     config.hostip = "127.0.0.1";
     config.hostport = 6379;
     config.repeat = 1;
     config.dbnum = 0;
+    config.interactive = 0;
 
     firstarg = parseOptions(argc,argv);
+
     argc -= firstarg;
     argv += firstarg;
-    
-    /* Turn the plain C strings into Sds strings */
-    argvcopy = zmalloc(sizeof(char*)*argc+1);
-    for(j = 0; j < argc; j++)
-        argvcopy[j] = sdsnew(argv[j]);
 
+    if (config.interactive == 1) repl();
     if (argc < 1) usage();
 
+    argvcopy = convertToSds(argc, argv);
+
     /* Read the last argument from stdandard input if needed */
     if ((rc = lookupCommand(argv[0])) != NULL) {
-        if (rc->arity > 0 && argc == rc->arity-1) {
-            sds lastarg = readArgFromStdin();
-            argvcopy[argc] = lastarg;
-            argc++;
-        }
+      if (rc->arity > 0 && argc == rc->arity-1) {
+        sds lastarg = readArgFromStdin();
+        argvcopy[argc] = lastarg;
+        argc++;
+      }
     }
 
     return cliSendCommand(argc, argvcopy);