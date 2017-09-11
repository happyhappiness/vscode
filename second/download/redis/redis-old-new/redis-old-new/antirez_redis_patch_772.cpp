@@ -94,10 +94,11 @@ static struct config {
     sds mb_delim;
     char prompt[128];
     char *eval;
+    int last_cmd_type;
 } config;
 
 static volatile sig_atomic_t force_cancel_loop = 0;
-static void usage();
+static void usage(void);
 static void slaveMode(void);
 char *redisGitSHA1(void);
 char *redisGitDirty(void);
@@ -131,7 +132,7 @@ static void cliRefreshPrompt(void) {
                        strchr(config.hostip,':') ? "[%s]:%d" : "%s:%d",
                        config.hostip, config.hostport);
     /* Add [dbnum] if needed */
-    if (config.dbnum != 0)
+    if (config.dbnum != 0 && config.last_cmd_type != REDIS_REPLY_ERROR)
         len += snprintf(config.prompt+len,sizeof(config.prompt)-len,"[%d]",
             config.dbnum);
     snprintf(config.prompt+len,sizeof(config.prompt)-len,"> ");
@@ -157,7 +158,7 @@ typedef struct {
 static helpEntry *helpEntries;
 static int helpEntriesLen;
 
-static sds cliVersion() {
+static sds cliVersion(void) {
     sds version;
     version = sdscatprintf(sdsempty(), "%s", REDIS_VERSION);
 
@@ -171,7 +172,7 @@ static sds cliVersion() {
     return version;
 }
 
-static void cliInitHelp() {
+static void cliInitHelp(void) {
     int commandslen = sizeof(commandHelp)/sizeof(struct commandHelp);
     int groupslen = sizeof(commandGroups)/sizeof(char*);
     int i, len, pos = 0;
@@ -210,7 +211,7 @@ static void cliOutputCommandHelp(struct commandHelp *help, int group) {
 }
 
 /* Print generic help. */
-static void cliOutputGenericHelp() {
+static void cliOutputGenericHelp(void) {
     sds version = cliVersion();
     printf(
         "redis-cli %s\r\n"
@@ -320,8 +321,10 @@ static int cliSelect() {
 
     reply = redisCommand(context,"SELECT %d",config.dbnum);
     if (reply != NULL) {
+        int result = REDIS_OK;
+        if (reply->type == REDIS_REPLY_ERROR) result = REDIS_ERR;
         freeReplyObject(reply);
-        return REDIS_OK;
+        return result;
     }
     return REDIS_ERR;
 }
@@ -365,7 +368,7 @@ static int cliConnect(int force) {
     return REDIS_OK;
 }
 
-static void cliPrintContextError() {
+static void cliPrintContextError(void) {
     if (context == NULL) return;
     fprintf(stderr,"Error: %s\n",context->errstr);
 }
@@ -514,8 +517,11 @@ static int cliReadReply(int output_raw_strings) {
     int output = 1;
 
     if (redisGetReply(context,&_reply) != REDIS_OK) {
-        if (config.shutdown)
+        if (config.shutdown) {
+            redisFree(context);
+            context = NULL;
             return REDIS_OK;
+        }
         if (config.interactive) {
             /* Filter cases where we should reconnect */
             if (context->err == REDIS_ERR_IO && errno == ECONNRESET)
@@ -530,6 +536,8 @@ static int cliReadReply(int output_raw_strings) {
 
     reply = (redisReply*)_reply;
 
+    config.last_cmd_type = reply->type;
+
     /* Check if we need to connect to a different node and reissue the
      * request. */
     if (config.cluster_mode && reply->type == REDIS_REPLY_ERROR &&
@@ -639,6 +647,7 @@ static int cliSendCommand(int argc, char **argv, int repeat) {
             printf("Entering slave output mode...  (press Ctrl-C to quit)\n");
             slaveMode();
             config.slave_mode = 0;
+            free(argvlen);
             return REDIS_ERR;  /* Error = slaveMode lost connection to master */
         }
 
@@ -650,6 +659,8 @@ static int cliSendCommand(int argc, char **argv, int repeat) {
             if (!strcasecmp(command,"select") && argc == 2) {
                 config.dbnum = atoi(argv[1]);
                 cliRefreshPrompt();
+            } else if (!strcasecmp(command,"auth") && argc == 2) {
+                cliSelect();
             }
         }
         if (config.interval) usleep(config.interval);
@@ -724,6 +735,8 @@ static int parseOptions(int argc, char **argv) {
             config.auth = argv[++i];
         } else if (!strcmp(argv[i],"--raw")) {
             config.output = OUTPUT_RAW;
+        } else if (!strcmp(argv[i],"--no-raw")) {
+            config.output = OUTPUT_STANDARD;
         } else if (!strcmp(argv[i],"--csv")) {
             config.output = OUTPUT_CSV;
         } else if (!strcmp(argv[i],"--latency")) {
@@ -795,7 +808,7 @@ static sds readArgFromStdin(void) {
     return arg;
 }
 
-static void usage() {
+static void usage(void) {
     sds version = cliVersion();
     fprintf(stderr,
 "redis-cli %s\n"
@@ -814,6 +827,7 @@ static void usage() {
 "  -c                 Enable cluster mode (follow -ASK and -MOVED redirections).\n"
 "  --raw              Use raw formatting for replies (default when STDOUT is\n"
 "                     not a tty).\n"
+"  --no-raw           Force formatted output even when STDOUT is not a tty.\n"
 "  --csv              Output in CSV format.\n"
 "  --latency          Enter a special mode continuously sampling latency.\n"
 "  --latency-history  Like --latency but tracking latency changes over time.\n"
@@ -862,8 +876,7 @@ static char **convertToSds(int count, char** args) {
   return sds;
 }
 
-#define LINE_BUFLEN 4096
-static void repl() {
+static void repl(void) {
     sds historyfile = NULL;
     int history = 0;
     char *line;
@@ -1406,7 +1419,7 @@ static int toIntType(char *key, char *type) {
 
 static void getKeyTypes(redisReply *keys, int *types) {
     redisReply *reply;
-    int i;
+    unsigned int i;
 
     /* Pipeline TYPE commands */
     for(i=0;i<keys->elements;i++) {
@@ -1435,7 +1448,7 @@ static void getKeySizes(redisReply *keys, int *types,
 {
     redisReply *reply;
     char *sizecmds[] = {"STRLEN","LLEN","SCARD","HLEN","ZCARD"};
-    int i;
+    unsigned int i;
 
     /* Pipeline size commands */
     for(i=0;i<keys->elements;i++) {
@@ -1482,7 +1495,8 @@ static void findBigKeys(void) {
     char *typename[] = {"string","list","set","hash","zset"};
     char *typeunit[] = {"bytes","items","members","fields","members"};
     redisReply *reply, *keys;
-    int type, *types=NULL, arrsize=0, i;
+    unsigned int arrsize=0, i;
+    int type, *types=NULL;
     double pct;
 
     /* Total keys pre scanning */
@@ -1666,7 +1680,7 @@ void bytesToHuman(char *s, long long n) {
     }
 }
 
-static void statMode() {
+static void statMode(void) {
     redisReply *reply;
     long aux, requests = 0;
     int i = 0;
@@ -1752,7 +1766,7 @@ static void statMode() {
  * Scan mode
  *--------------------------------------------------------------------------- */
 
-static void scanMode() {
+static void scanMode(void) {
     redisReply *reply;
     unsigned long long cur = 0;
 
@@ -1769,7 +1783,7 @@ static void scanMode() {
             printf("ERROR: %s\n", reply->str);
             exit(1);
         } else {
-            int j;
+            unsigned int j;
 
             cur = strtoull(reply->element[0]->str,NULL,10);
             for (j = 0; j < reply->element[1]->elements; j++)
@@ -1840,11 +1854,15 @@ static void intrinsicLatencyMode(void) {
             printf("Max latency so far: %lld microseconds.\n", max_latency);
         }
 
+        double avg_us = (double)run_time/runs;
+        double avg_ns = avg_us * 10e3;
         if (force_cancel_loop || end > test_end) {
-            printf("\n%lld total runs (avg %lld microseconds per run).\n",
-                runs, run_time/runs);
-            printf("Worst run took %.02fx times the average.\n",
-                (double) max_latency / (run_time/runs));
+            printf("\n%lld total runs "
+                "(avg latency: "
+                "%.4f microseconds / %.2f nanoseconds per run).\n",
+                runs, avg_us, avg_ns);
+            printf("Worst run took %.0fx longer than the average latency.\n",
+                max_latency / avg_us);
             exit(0);
         }
     }
@@ -1883,6 +1901,8 @@ int main(int argc, char **argv) {
     config.stdinarg = 0;
     config.auth = NULL;
     config.eval = NULL;
+    config.last_cmd_type = -1;
+
     if (!isatty(fileno(stdout)) && (getenv("FAKETTY") == NULL))
         config.output = OUTPUT_RAW;
     else