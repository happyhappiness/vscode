@@ -49,6 +49,10 @@
 
 #define REDIS_NOTUSED(V) ((void) V)
 
+#define OUTPUT_STANDARD 0
+#define OUTPUT_RAW 1
+#define OUTPUT_CSV 2
+
 static redisContext *context;
 static struct config {
     char *hostip;
@@ -64,9 +68,10 @@ static struct config {
     int latency_mode;
     int cluster_mode;
     int cluster_reissue_command;
+    int slave_mode;
     int stdinarg; /* get last arg from stdin. (-x option) */
     char *auth;
-    int raw_output; /* output mode per command */
+    int output; /* output mode, see OUTPUT_* defines */
     sds mb_delim;
     char prompt[128];
     char *eval;
@@ -434,10 +439,46 @@ static sds cliFormatReplyRaw(redisReply *r) {
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
-    sds out;
+    sds out = NULL;
     int output = 1;
 
     if (redisGetReply(context,&_reply) != REDIS_OK) {
@@ -457,7 +498,8 @@ static int cliReadReply(int output_raw_strings) {
 
     reply = (redisReply*)_reply;
 
-    /* Check if we need to connect to a different node and reissue the request. */
+    /* Check if we need to connect to a different node and reissue the
+     * request. */
     if (config.cluster_mode && reply->type == REDIS_REPLY_ERROR &&
         (!strncmp(reply->str,"MOVED",5) || !strcmp(reply->str,"ASK")))
     {
@@ -489,11 +531,14 @@ static int cliReadReply(int output_raw_strings) {
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
@@ -545,7 +590,7 @@ static int cliSendCommand(int argc, char **argv, int repeat) {
         }
 
         if (config.pubsub_mode) {
-            if (!config.raw_output)
+            if (config.output != OUTPUT_RAW)
                 printf("Reading messages... (press Ctrl-C to quit)\n");
             while (1) {
                 if (cliReadReply(output_raw) != REDIS_OK) exit(1);
@@ -603,9 +648,13 @@ static int parseOptions(int argc, char **argv) {
         } else if (!strcmp(argv[i],"-a") && !lastarg) {
             config.auth = argv[++i];
         } else if (!strcmp(argv[i],"--raw")) {
-            config.raw_output = 1;
+            config.output = OUTPUT_RAW;
+        } else if (!strcmp(argv[i],"--csv")) {
+            config.output = OUTPUT_CSV;
         } else if (!strcmp(argv[i],"--latency")) {
             config.latency_mode = 1;
+        } else if (!strcmp(argv[i],"--slave")) {
+            config.slave_mode = 1;
         } else if (!strcmp(argv[i],"--eval") && !lastarg) {
             config.eval = argv[++i];
         } else if (!strcmp(argv[i],"-c")) {
@@ -661,6 +710,7 @@ static void usage() {
 "  -c               Enable cluster mode (follow -ASK and -MOVED redirections)\n"
 "  --raw            Use raw formatting for replies (default when STDOUT is not a tty)\n"
 "  --latency        Enter a special mode continuously sampling latency.\n"
+"  --slave          Simulate a slave showing commands received from the master.\n"
 "  --eval <file>    Send an EVAL command using the Lua script at <file>.\n"
 "  --help           Output this help and exit\n"
 "  --version        Output version and exit\n"
@@ -866,6 +916,54 @@ static void latencyMode(void) {
     }
 }
 
+static void slaveMode(void) {
+    /* To start we need to send the SYNC command and return the payload.
+     * The hiredis client lib does not understand this part of the protocol
+     * and we don't want to mess with its buffers, so everything is performed
+     * using direct low-level I/O. */
+    int fd = context->fd;
+    char buf[1024], *p;
+    ssize_t nread;
+    unsigned long long payload;
+
+    /* Send the SYNC command. */
+    if (write(fd,"SYNC\r\n",6) != 6) {
+        fprintf(stderr,"Error writing to master\n");
+        exit(1);
+    }
+
+    /* Read $<payload>\r\n, making sure to read just up to "\n" */
+    p = buf;
+    while(1) {
+        nread = read(fd,p,1);
+        if (nread <= 0) {
+            fprintf(stderr,"Error reading bulk length while SYNCing\n");
+            exit(1);
+        }
+        if (*p == '\n') break;
+        p++;
+    }
+    *p = '\0';
+    payload = strtoull(buf+1,NULL,10);
+    fprintf(stderr,"SYNC with master, discarding %lld bytes of bulk tranfer...\n",
+            payload);
+
+    /* Discard the payload. */
+    while(payload) {
+        nread = read(fd,buf,(payload > sizeof(buf)) ? sizeof(buf) : payload);
+        if (nread <= 0) {
+            fprintf(stderr,"Error reading RDB payload while SYNCing\n");
+            exit(1);
+        }
+        payload -= nread;
+    }
+    fprintf(stderr,"SYNC done. Logging commands from master.\n");
+
+    /* Now we can use the hiredis to read the incoming protocol. */
+    config.output = OUTPUT_CSV;
+    while (cliReadReply(0) == REDIS_OK);
+}
+
 int main(int argc, char **argv) {
     int firstarg;
 
@@ -884,7 +982,10 @@ int main(int argc, char **argv) {
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
 
@@ -898,6 +999,12 @@ int main(int argc, char **argv) {
         latencyMode();
     }
 
+    /* Start in slave mode if appropriate */
+    if (config.slave_mode) {
+        cliConnect(0);
+        slaveMode();
+    }
+
     /* Start interactive mode when no command is provided */
     if (argc == 0 && !config.eval) {
         /* Note that in repl mode we don't abort on connection error.