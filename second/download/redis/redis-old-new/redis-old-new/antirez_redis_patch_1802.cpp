@@ -60,12 +60,11 @@ static struct config {
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
@@ -316,30 +315,24 @@ static void cliPrintContextErrorAndExit() {
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
@@ -375,7 +368,7 @@ static sds cliFormatReply(redisReply *r, char *prefix) {
                 out = sdscatprintf(out,_prefixfmt,i == 0 ? "" : prefix,i+1);
 
                 /* Format the multi bulk entry */
-                tmp = cliFormatReply(r->element[i],_prefix);
+                tmp = cliFormatReplyTTY(r->element[i],_prefix);
                 out = sdscatlen(out,tmp,sdslen(tmp));
                 sdsfree(tmp);
             }
@@ -389,7 +382,38 @@ static sds cliFormatReply(redisReply *r, char *prefix) {
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
 
@@ -407,24 +431,33 @@ static int cliReadReply() {
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
@@ -442,18 +475,19 @@ static int cliSendCommand(int argc, char **argv, int repeat) {
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
@@ -494,6 +528,8 @@ static int parseOptions(int argc, char **argv) {
         } else if (!strcmp(argv[i],"-a") && !lastarg) {
             config.auth = argv[i+1];
             i++;
+        } else if (!strcmp(argv[i],"--raw")) {
+            config.raw_output = 1;
         } else if (!strcmp(argv[i],"-v") || !strcmp(argv[i], "--version")) {
             sds version = cliVersion();
             printf("redis-cli %s\n", version);
@@ -536,6 +572,7 @@ static void usage() {
 "  -r <repeat>      Execute specified command N times\n"
 "  -n <db>          Database number\n"
 "  -x               Read last argument from STDIN\n"
+"  --raw            Use raw formatting for replies (default when STDOUT is not a tty)\n"
 "  --help           Output this help and exit\n"
 "  --version        Output version and exit\n"
 "\n"
@@ -645,12 +682,11 @@ int main(int argc, char **argv) {
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