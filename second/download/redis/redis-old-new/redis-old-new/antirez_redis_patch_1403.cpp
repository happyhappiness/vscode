@@ -49,6 +49,10 @@
 
 #define REDIS_NOTUSED(V) ((void) V)
 
+#define OUTPUT_STANDARD 0
+#define OUTPUT_RAW 1
+#define OUTPUT_CSV 2
+
 static redisContext *context;
 static struct config {
     char *hostip;
@@ -67,7 +71,7 @@ static struct config {
     int slave_mode;
     int stdinarg; /* get last arg from stdin. (-x option) */
     char *auth;
-    int raw_output; /* output mode per command */
+    int output; /* output mode, see OUTPUT_* defines */
     sds mb_delim;
     char prompt[128];
     char *eval;
@@ -435,6 +439,42 @@ static sds cliFormatReplyRaw(redisReply *r) {
     return out;
 }
 
+static sds cliFormatReplyCSV(redisReply *r) {
+    unsigned int i;
+
+    sds out = sdsempty();
+    switch (r->type) {
+    case REDIS_REPLY_ERROR:
+        out = sdscat(out,"ERROR,");
+        out = sdscatrepr(out,r->str,strlen(r->str));
+    break;
+    case REDIS_REPLY_STATUS:
+        out = sdscatrepr(out,r->str,r->len);
+    break;
+    case REDIS_REPLY_INTEGER:
+        out = sdscatprintf(out,"%lld",r->integer);
+    break;
+    case REDIS_REPLY_STRING:
+        out = sdscatrepr(out,r->str,r->len);
+    break;
+    case REDIS_REPLY_NIL:
+        out = sdscat(out,"NIL\n");
+    break;
+    case REDIS_REPLY_ARRAY:
+        for (i = 0; i < r->elements; i++) {
+            sds tmp = cliFormatReplyCSV(r->element[i]);
+            out = sdscatlen(out,tmp,sdslen(tmp));
+            if (i != r->elements-1) out = sdscat(out,",");
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
 static int cliReadReply(int output_raw_strings) {
     void *_reply;
     redisReply *reply;
@@ -490,11 +530,14 @@ static int cliReadReply(int output_raw_strings) {
         if (output_raw_strings) {
             out = cliFormatReplyRaw(reply);
         } else {
-            if (config.raw_output) {
+            if (config.output == OUTPUT_RAW) {
                 out = cliFormatReplyRaw(reply);
                 out = sdscat(out,"\n");
-            } else {
+            } else if (config.output == OUTPUT_STANDARD) {
                 out = cliFormatReplyTTY(reply,"");
+            } else if (config.output == OUTPUT_CSV) {
+                out = cliFormatReplyCSV(reply);
+                out = sdscat(out,"\n");
             }
         }
         fwrite(out,sdslen(out),1,stdout);
@@ -546,7 +589,7 @@ static int cliSendCommand(int argc, char **argv, int repeat) {
         }
 
         if (config.pubsub_mode) {
-            if (!config.raw_output)
+            if (config.output != OUTPUT_RAW)
                 printf("Reading messages... (press Ctrl-C to quit)\n");
             while (1) {
                 if (cliReadReply(output_raw) != REDIS_OK) exit(1);
@@ -604,7 +647,9 @@ static int parseOptions(int argc, char **argv) {
         } else if (!strcmp(argv[i],"-a") && !lastarg) {
             config.auth = argv[++i];
         } else if (!strcmp(argv[i],"--raw")) {
-            config.raw_output = 1;
+            config.output = OUTPUT_RAW;
+        } else if (!strcmp(argv[i],"--csv")) {
+            config.output = OUTPUT_CSV;
         } else if (!strcmp(argv[i],"--latency")) {
             config.latency_mode = 1;
         } else if (!strcmp(argv[i],"--slave")) {
@@ -896,8 +941,7 @@ static void slaveMode(void) {
     }
     *p = '\0';
     payload = strtoull(buf+1,NULL,10);
-    if (!config.raw_output)
-        printf("SYNC with master, discarding %lld bytes of bulk tranfer...\n",
+    fprintf(stderr,"SYNC with master, discarding %lld bytes of bulk tranfer...\n",
             payload);
 
     /* Discard the payload. */
@@ -909,10 +953,11 @@ static void slaveMode(void) {
         }
         payload -= nread;
     }
-    if (!config.raw_output) printf("SYNC done. Logging commands from master.\n");
+    fprintf(stderr,"SYNC done. Logging commands from master.\n");
 
     /* Now we can use the hiredis to read the incoming protocol. */
-    while (cliReadReply(config.raw_output) == REDIS_OK);
+    config.output = OUTPUT_CSV;
+    while (cliReadReply(0) == REDIS_OK);
 }
 
 int main(int argc, char **argv) {
@@ -933,7 +978,10 @@ int main(int argc, char **argv) {
     config.stdinarg = 0;
     config.auth = NULL;
     config.eval = NULL;
-    config.raw_output = !isatty(fileno(stdout)) && (getenv("FAKETTY") == NULL);
+    if (!isatty(fileno(stdout)) && (getenv("FAKETTY") == NULL))
+        config.output = OUTPUT_RAW;
+    else
+        config.output = OUTPUT_STANDARD;
     config.mb_delim = sdsnew("\n");
     cliInitHelp();
 