@@ -55,6 +55,7 @@ static struct config {
     int hostport;
     char *hostsocket;
     long repeat;
+    long interval;
     int dbnum;
     int interactive;
     int shutdown;
@@ -87,9 +88,11 @@ static long long mstime(void) {
 
 static void cliRefreshPrompt(void) {
     if (config.dbnum == 0)
-        snprintf(config.prompt,sizeof(config.prompt),"redis> ");
+        snprintf(config.prompt,sizeof(config.prompt),"redis %s:%d> ",
+            config.hostip, config.hostport);
     else
-        snprintf(config.prompt,sizeof(config.prompt),"redis:%d> ",config.dbnum);
+        snprintf(config.prompt,sizeof(config.prompt),"redis %s:%d[%d]> ",
+            config.hostip, config.hostport, config.dbnum);
 }
 
 /*------------------------------------------------------------------------------
@@ -314,10 +317,9 @@ static int cliConnect(int force) {
     return REDIS_OK;
 }
 
-static void cliPrintContextErrorAndExit() {
+static void cliPrintContextError() {
     if (context == NULL) return;
     fprintf(stderr,"Error: %s\n",context->errstr);
-    exit(1);
 }
 
 static sds cliFormatReplyTTY(redisReply *r, char *prefix) {
@@ -436,7 +438,8 @@ static int cliReadReply(int output_raw_strings) {
             if (context->err == REDIS_ERR_EOF)
                 return REDIS_ERR;
         }
-        cliPrintContextErrorAndExit();
+        cliPrintContextError();
+        exit(1);
         return REDIS_ERR; /* avoid compiler warning */
     }
 
@@ -462,10 +465,7 @@ static int cliSendCommand(int argc, char **argv, int repeat) {
     size_t *argvlen;
     int j, output_raw;
 
-    if (context == NULL) {
-        printf("Not connected, please use: connect <host> <port>\n");
-        return REDIS_OK;
-    }
+    if (context == NULL) return REDIS_ERR;
 
     output_raw = 0;
     if (!strcasecmp(command,"info") ||
@@ -518,6 +518,8 @@ static int cliSendCommand(int argc, char **argv, int repeat) {
                 cliRefreshPrompt();
             }
         }
+        if (config.interval) usleep(config.interval);
+        fflush(stdout); /* Make it grep friendly */
     }
 
     free(argvlen);
@@ -553,6 +555,10 @@ static int parseOptions(int argc, char **argv) {
         } else if (!strcmp(argv[i],"-r") && !lastarg) {
             config.repeat = strtoll(argv[i+1],NULL,10);
             i++;
+        } else if (!strcmp(argv[i],"-i") && !lastarg) {
+            double seconds = atof(argv[i+1]);
+            config.interval = seconds*1000000;
+            i++;
         } else if (!strcmp(argv[i],"-n") && !lastarg) {
             config.dbnum = atoi(argv[i+1]);
             i++;
@@ -605,6 +611,8 @@ static void usage() {
 "  -s <socket>      Server socket (overrides hostname and port)\n"
 "  -a <password>    Password to use when connecting to the server\n"
 "  -r <repeat>      Execute specified command N times\n"
+"  -i <interval>    When -r is used, waits <interval> seconds per command.\n"
+"                   It is possible to specify sub-second times like -i 0.1.\n"
 "  -n <db>          Database number\n"
 "  -x               Read last argument from STDIN\n"
 "  -d <delimiter>   Multi-bulk delimiter in for raw formatting (default: \\n)\n"
@@ -616,6 +624,7 @@ static void usage() {
 "  cat /etc/passwd | redis-cli -x set mypasswd\n"
 "  redis-cli get mypasswd\n"
 "  redis-cli -r 100 lpush mylist x\n"
+"  redis-cli -r 100 -i 1 info | grep used_memory_human:\n"
 "\n"
 "When no command is given, redis-cli starts in interactive mode.\n"
 "Type \"help\" in interactive mode for information on available commands.\n"
@@ -681,14 +690,25 @@ static void repl() {
                     linenoiseClearScreen();
                 } else {
                     long long start_time = mstime(), elapsed;
+                    int repeat, skipargs = 0;
+
+                    repeat = atoi(argv[0]);
+                    if (repeat) {
+                        skipargs = 1;
+                    } else {
+                        repeat = 1;
+                    }
 
-                    if (cliSendCommand(argc,argv,1) != REDIS_OK) {
+                    if (cliSendCommand(argc-skipargs,argv+skipargs,repeat)
+                        != REDIS_OK)
+                    {
                         cliConnect(1);
 
-                        /* If we still cannot send the command,
-                         * print error and abort. */
-                        if (cliSendCommand(argc,argv,1) != REDIS_OK)
-                            cliPrintContextErrorAndExit();
+                        /* If we still cannot send the command print error.
+                         * We'll try to reconnect the next time. */
+                        if (cliSendCommand(argc-skipargs,argv+skipargs,repeat)
+                            != REDIS_OK)
+                            cliPrintContextError();
                     }
                     elapsed = mstime()-start_time;
                     if (elapsed >= 500) {
@@ -726,6 +746,7 @@ int main(int argc, char **argv) {
     config.hostport = 6379;
     config.hostsocket = NULL;
     config.repeat = 1;
+    config.interval = 0;
     config.dbnum = 0;
     config.interactive = 0;
     config.shutdown = 0;
@@ -741,11 +762,15 @@ int main(int argc, char **argv) {
     argc -= firstarg;
     argv += firstarg;
 
-    /* Try to connect */
-    if (cliConnect(0) != REDIS_OK) exit(1);
-
     /* Start interactive mode when no command is provided */
-    if (argc == 0) repl();
+    if (argc == 0) {
+        /* Note that in repl mode we don't abort on connection error.
+         * A new attempt will be performed for every command send. */
+        cliConnect(0);
+        repl();
+    }
+
     /* Otherwise, we have some arguments to execute */
+    if (cliConnect(0) != REDIS_OK) exit(1);
     return noninteractive(argc,convertToSds(argc,argv));
 }