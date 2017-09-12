@@ -60,16 +60,16 @@ static struct config {
     int shutdown;
     int monitor_mode;
     int pubsub_mode;
-    int raw_output; /* output mode per command */
-    int tty; /* flag for default output format */
     int stdinarg; /* get last arg from stdin. (-x option) */
-    char mb_sep;
     char *auth;
     char *historyfile;
+    int raw_output; /* output mode per command */
+    sds mb_delim;
 } config;
 
 static void usage();
 char *redisGitSHA1(void);
+char *redisGitDirty(void);
 
 /*------------------------------------------------------------------------------
  * Utility functions
@@ -105,6 +105,20 @@ typedef struct {
 static helpEntry *helpEntries;
 static int helpEntriesLen;
 
+static sds cliVersion() {
+    sds version;
+    version = sdscatprintf(sdsempty(), "%s", REDIS_VERSION);
+
+    /* Add git commit and working tree status when available */
+    if (strtoll(redisGitSHA1(),NULL,16)) {
+        version = sdscatprintf(version, " (git:%s", redisGitSHA1());
+        if (strtoll(redisGitDirty(),NULL,10))
+            version = sdscatprintf(version, "-dirty");
+        version = sdscat(version, ")");
+    }
+    return version;
+}
+
 static void cliInitHelp() {
     int commandslen = sizeof(commandHelp)/sizeof(struct commandHelp);
     int groupslen = sizeof(commandGroups)/sizeof(char*);
@@ -145,14 +159,16 @@ static void cliOutputCommandHelp(struct commandHelp *help, int group) {
 
 /* Print generic help. */
 static void cliOutputGenericHelp() {
+    sds version = cliVersion();
     printf(
         "redis-cli %s\r\n"
         "Type: \"help @<group>\" to get a list of commands in <group>\r\n"
         "      \"help <command>\" for help on <command>\r\n"
         "      \"help <tab>\" to get a list of possible help topics\r\n"
         "      \"quit\" to exit\r\n",
-        REDIS_VERSION
+        version
     );
+    sdsfree(version);
 }
 
 /* Output all command help, filtering by group or command name. */
@@ -299,30 +315,24 @@ static void cliPrintContextErrorAndExit() {
     exit(1);
 }
 
-static sds cliFormatReply(redisReply *r, char *prefix) {
+static sds cliFormatReplyTTY(redisReply *r, char *prefix) {
     sds out = sdsempty();
     switch (r->type) {
     case REDIS_REPLY_ERROR:
-        if (config.tty) out = sdscat(out,"(error) ");
-        out = sdscatprintf(out,"%s\n", r->str);
+        out = sdscatprintf(out,"(error) %s\n", r->str);
     break;
     case REDIS_REPLY_STATUS:
         out = sdscat(out,r->str);
         out = sdscat(out,"\n");
     break;
     case REDIS_REPLY_INTEGER:
-        if (config.tty) out = sdscat(out,"(integer) ");
-        out = sdscatprintf(out,"%lld\n",r->integer);
+        out = sdscatprintf(out,"(integer) %lld\n",r->integer);
     break;
     case REDIS_REPLY_STRING:
-        if (config.raw_output || !config.tty) {
-            out = sdscatlen(out,r->str,r->len);
-        } else {
-            /* If you are producing output for the standard output we want
-             * a more interesting output with quoted characters and so forth */
-            out = sdscatrepr(out,r->str,r->len);
-            out = sdscat(out,"\n");
-        }
+        /* If you are producing output for the standard output we want
+        * a more interesting output with quoted characters and so forth */
+        out = sdscatrepr(out,r->str,r->len);
+        out = sdscat(out,"\n");
     break;
     case REDIS_REPLY_NIL:
         out = sdscat(out,"(nil)\n");
@@ -358,7 +368,7 @@ static sds cliFormatReply(redisReply *r, char *prefix) {
                 out = sdscatprintf(out,_prefixfmt,i == 0 ? "" : prefix,i+1);
 
                 /* Format the multi bulk entry */
-                tmp = cliFormatReply(r->element[i],_prefix);
+                tmp = cliFormatReplyTTY(r->element[i],_prefix);
                 out = sdscatlen(out,tmp,sdslen(tmp));
                 sdsfree(tmp);
             }
@@ -372,7 +382,38 @@ static sds cliFormatReply(redisReply *r, char *prefix) {
     return out;
 }
 
-static int cliReadReply() {
+static sds cliFormatReplyRaw(redisReply *r) {
+    sds out = sdsempty(), tmp;
+    size_t i;
+
+    switch (r->type) {
+    case REDIS_REPLY_NIL:
+        /* Nothing... */
+    break;
+    case REDIS_REPLY_ERROR:
+    case REDIS_REPLY_STATUS:
+    case REDIS_REPLY_STRING:
+        out = sdscatlen(out,r->str,r->len);
+    break;
+    case REDIS_REPLY_INTEGER:
+        out = sdscatprintf(out,"%lld",r->integer);
+    break;
+    case REDIS_REPLY_ARRAY:
+        for (i = 0; i < r->elements; i++) {
+            if (i > 0) out = sdscat(out,config.mb_delim);
+            tmp = cliFormatReplyRaw(r->element[i]);
+            out = sdscatlen(out,tmp,sdslen(tmp));
+            sdsfree(tmp);
+        }
+    break;
+    default:
+        fprintf(stderr,"Unknown reply type: %d\n", r->type);
+        exit(1);
+    }
+    return out;
+}
+
+static int cliReadReply(int output_raw_strings) {
     redisReply *reply;
     sds out;
 
@@ -390,24 +431,33 @@ static int cliReadReply() {
         return REDIS_ERR; /* avoid compiler warning */
     }
 
-    out = cliFormatReply(reply,"");
-    freeReplyObject(reply);
+    if (output_raw_strings) {
+        out = cliFormatReplyRaw(reply);
+    } else {
+        if (config.raw_output) {
+            out = cliFormatReplyRaw(reply);
+            out = sdscat(out,"\n");
+        } else {
+            out = cliFormatReplyTTY(reply,"");
+        }
+    }
     fwrite(out,sdslen(out),1,stdout);
     sdsfree(out);
+    freeReplyObject(reply);
     return REDIS_OK;
 }
 
 static int cliSendCommand(int argc, char **argv, int repeat) {
     char *command = argv[0];
     size_t *argvlen;
-    int j;
+    int j, output_raw;
 
     if (context == NULL) {
         printf("Not connected, please use: connect <host> <port>\n");
         return REDIS_OK;
     }
 
-    config.raw_output = !strcasecmp(command,"info");
+    output_raw = !strcasecmp(command,"info");
     if (!strcasecmp(command,"help") || !strcasecmp(command,"?")) {
         cliOutputHelp(--argc, ++argv);
         return REDIS_OK;
@@ -425,18 +475,19 @@ static int cliSendCommand(int argc, char **argv, int repeat) {
     while(repeat--) {
         redisAppendCommandArgv(context,argc,(const char**)argv,argvlen);
         while (config.monitor_mode) {
-            if (cliReadReply() != REDIS_OK) exit(1);
+            if (cliReadReply(output_raw) != REDIS_OK) exit(1);
             fflush(stdout);
         }
 
         if (config.pubsub_mode) {
-            printf("Reading messages... (press Ctrl-C to quit)\n");
+            if (!config.raw_output)
+                printf("Reading messages... (press Ctrl-C to quit)\n");
             while (1) {
-                if (cliReadReply() != REDIS_OK) exit(1);
+                if (cliReadReply(output_raw) != REDIS_OK) exit(1);
             }
         }
 
-        if (cliReadReply() != REDIS_OK)
+        if (cliReadReply(output_raw) != REDIS_OK)
             return REDIS_ERR;
     }
     return REDIS_OK;
@@ -458,6 +509,8 @@ static int parseOptions(int argc, char **argv) {
             i++;
         } else if (!strcmp(argv[i],"-h") && lastarg) {
             usage();
+        } else if (!strcmp(argv[i],"--help")) {
+            usage();
         } else if (!strcmp(argv[i],"-x")) {
             config.stdinarg = 1;
         } else if (!strcmp(argv[i],"-p") && !lastarg) {
@@ -475,19 +528,16 @@ static int parseOptions(int argc, char **argv) {
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
+        } else if (!strcmp(argv[i],"--raw")) {
+            config.raw_output = 1;
+        } else if (!strcmp(argv[i],"-d") && !lastarg) {
+            sdsfree(config.mb_delim);
+            config.mb_delim = sdsnew(argv[i+1]);
+            i++;
+        } else if (!strcmp(argv[i],"-v") || !strcmp(argv[i], "--version")) {
+            sds version = cliVersion();
+            printf("redis-cli %s\n", version);
+            sdsfree(version);
             exit(0);
         } else {
             break;
@@ -514,12 +564,33 @@ static sds readArgFromStdin(void) {
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
+"  -d <delimiter>   Multi-bulk delimiter in for raw formatting (default: \\n)\n"
+"  --raw            Use raw formatting for replies (default when STDOUT is not a tty)\n"
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
 
@@ -616,12 +687,11 @@ int main(int argc, char **argv) {
     config.shutdown = 0;
     config.monitor_mode = 0;
     config.pubsub_mode = 0;
-    config.raw_output = 0;
     config.stdinarg = 0;
     config.auth = NULL;
     config.historyfile = NULL;
-    config.tty = isatty(fileno(stdout)) || (getenv("FAKETTY") != NULL);
-    config.mb_sep = '\n';
+    config.raw_output = !isatty(fileno(stdout)) && (getenv("FAKETTY") == NULL);
+    config.mb_delim = sdsnew("\n");
     cliInitHelp();
 
     if (getenv("HOME") != NULL) {