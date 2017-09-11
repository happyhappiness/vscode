@@ -61,6 +61,7 @@ static struct config {
     int shutdown;
     int monitor_mode;
     int pubsub_mode;
+    int latency_mode;
     int stdinarg; /* get last arg from stdin. (-x option) */
     char *auth;
     int raw_output; /* output mode per command */
@@ -567,6 +568,8 @@ static int parseOptions(int argc, char **argv) {
             i++;
         } else if (!strcmp(argv[i],"--raw")) {
             config.raw_output = 1;
+        } else if (!strcmp(argv[i],"--latency")) {
+            config.latency_mode = 1;
         } else if (!strcmp(argv[i],"-d") && !lastarg) {
             sdsfree(config.mb_delim);
             config.mb_delim = sdsnew(argv[i+1]);
@@ -617,6 +620,7 @@ static void usage() {
 "  -x               Read last argument from STDIN\n"
 "  -d <delimiter>   Multi-bulk delimiter in for raw formatting (default: \\n)\n"
 "  --raw            Use raw formatting for replies (default when STDOUT is not a tty)\n"
+"  --latency        Enter a special mode continuously sampling latency.\n"
 "  --help           Output this help and exit\n"
 "  --version        Output version and exit\n"
 "\n"
@@ -739,6 +743,37 @@ static int noninteractive(int argc, char **argv) {
     return retval;
 }
 
+static void latencyMode(void) {
+    redisReply *reply;
+    long long start, latency, min, max, tot, count = 0;
+    double avg;
+
+    if (!context) exit(1);
+    while(1) {
+        start = mstime();
+        reply = redisCommand(context,"PING");
+        if (reply == NULL) {
+            fprintf(stderr,"\nI/O error\n");
+            exit(1);
+        }
+        latency = mstime()-start;
+        freeReplyObject(reply);
+        count++;
+        if (count == 1) {
+            min = max = tot = latency;
+            avg = (double) latency;
+        } else {
+            if (latency < min) min = latency;
+            if (latency > max) max = latency;
+            avg = (double) tot/count;
+        }
+        printf("\x1b[0G\x1b[2Kmin: %lld, max: %lld, avg: %.2f (%lld samples)",
+            min, max, avg, count);
+        fflush(stdout);
+        usleep(10000);
+    }
+}
+
 int main(int argc, char **argv) {
     int firstarg;
 
@@ -752,6 +787,7 @@ int main(int argc, char **argv) {
     config.shutdown = 0;
     config.monitor_mode = 0;
     config.pubsub_mode = 0;
+    config.latency_mode = 0;
     config.stdinarg = 0;
     config.auth = NULL;
     config.raw_output = !isatty(fileno(stdout)) && (getenv("FAKETTY") == NULL);
@@ -762,6 +798,12 @@ int main(int argc, char **argv) {
     argc -= firstarg;
     argv += firstarg;
 
+    /* Start in latency mode if appropriate */
+    if (config.latency_mode) {
+        cliConnect(0);
+        latencyMode();
+    }
+
     /* Start interactive mode when no command is provided */
     if (argc == 0) {
         /* Note that in repl mode we don't abort on connection error.