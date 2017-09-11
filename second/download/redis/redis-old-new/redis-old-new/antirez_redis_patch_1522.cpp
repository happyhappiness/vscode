@@ -62,6 +62,8 @@ static struct config {
     int monitor_mode;
     int pubsub_mode;
     int latency_mode;
+    int cluster_mode;
+    int cluster_reissue_command;
     int stdinarg; /* get last arg from stdin. (-x option) */
     char *auth;
     int raw_output; /* output mode per command */
@@ -428,6 +430,7 @@ static int cliReadReply(int output_raw_strings) {
     void *_reply;
     redisReply *reply;
     sds out;
+    int output = 1;
 
     if (redisGetReply(context,&_reply) != REDIS_OK) {
         if (config.shutdown)
@@ -445,18 +448,49 @@ static int cliReadReply(int output_raw_strings) {
     }
 
     reply = (redisReply*)_reply;
-    if (output_raw_strings) {
-        out = cliFormatReplyRaw(reply);
-    } else {
-        if (config.raw_output) {
+
+    /* Check if we need to connect to a different node and reissue the request. */
+    if (config.cluster_mode && reply->type == REDIS_REPLY_ERROR &&
+        (!strncmp(reply->str,"MOVED",5) || !strcmp(reply->str,"ASK")))
+    {
+        char *p = reply->str, *s;
+        int slot;
+
+        output = 0;
+        /* Comments show the position of the pointer as:
+         *
+         * [S] for pointer 's'
+         * [P] for pointer 'p'
+         */
+        s = strchr(p,' ');      /* MOVED[S]3999 127.0.0.1:6381 */
+        p = strchr(s+1,' ');    /* MOVED[S]3999[P]127.0.0.1:6381 */
+        *p = '\0';
+        slot = atoi(s+1);
+        s = strchr(p+1,':');    /* MOVED 3999[P]127.0.0.1[S]6381 */
+        *s = '\0';
+        sdsfree(config.hostip);
+        config.hostip = sdsnew(p+1);
+        config.hostport = atoi(s+1);
+        if (config.interactive)
+            printf("-> Redirected to slot [%d] located at %s:%d\n",
+                slot, config.hostip, config.hostport);
+        config.cluster_reissue_command = 1;
+    }
+
+    if (output) {
+        if (output_raw_strings) {
             out = cliFormatReplyRaw(reply);
-            out = sdscat(out,"\n");
         } else {
-            out = cliFormatReplyTTY(reply,"");
+            if (config.raw_output) {
+                out = cliFormatReplyRaw(reply);
+                out = sdscat(out,"\n");
+            } else {
+                out = cliFormatReplyTTY(reply,"");
+            }
         }
+        fwrite(out,sdslen(out),1,stdout);
+        sdsfree(out);
     }
-    fwrite(out,sdslen(out),1,stdout);
-    sdsfree(out);
     freeReplyObject(reply);
     return REDIS_OK;
 }
@@ -570,6 +604,8 @@ static int parseOptions(int argc, char **argv) {
             config.raw_output = 1;
         } else if (!strcmp(argv[i],"--latency")) {
             config.latency_mode = 1;
+        } else if (!strcmp(argv[i],"-c")) {
+            config.cluster_mode = 1;
         } else if (!strcmp(argv[i],"-d") && !lastarg) {
             sdsfree(config.mb_delim);
             config.mb_delim = sdsnew(argv[i+1]);
@@ -619,6 +655,7 @@ static void usage() {
 "  -n <db>          Database number\n"
 "  -x               Read last argument from STDIN\n"
 "  -d <delimiter>   Multi-bulk delimiter in for raw formatting (default: \\n)\n"
+"  -c               Enable cluster mode (follow -ASK and -MOVED redirections)\n"
 "  --raw            Use raw formatting for replies (default when STDOUT is not a tty)\n"
 "  --latency        Enter a special mode continuously sampling latency.\n"
 "  --help           Output this help and exit\n"
@@ -703,16 +740,25 @@ static void repl() {
                         repeat = 1;
                     }
 
-                    if (cliSendCommand(argc-skipargs,argv+skipargs,repeat)
-                        != REDIS_OK)
-                    {
-                        cliConnect(1);
-
-                        /* If we still cannot send the command print error.
-                         * We'll try to reconnect the next time. */
+                    while (1) {
+                        config.cluster_reissue_command = 0;
                         if (cliSendCommand(argc-skipargs,argv+skipargs,repeat)
                             != REDIS_OK)
-                            cliPrintContextError();
+                        {
+                            cliConnect(1);
+
+                            /* If we still cannot send the command print error.
+                             * We'll try to reconnect the next time. */
+                            if (cliSendCommand(argc-skipargs,argv+skipargs,repeat)
+                                != REDIS_OK)
+                                cliPrintContextError();
+                        }
+                        /* Issue the command again if we got redirected in cluster mode */
+                        if (config.cluster_mode && config.cluster_reissue_command) {
+                            cliConnect(1);
+                        } else {
+                            break;
+                        }
                     }
                     elapsed = mstime()-start_time;
                     if (elapsed >= 500) {
@@ -789,6 +835,7 @@ int main(int argc, char **argv) {
     config.monitor_mode = 0;
     config.pubsub_mode = 0;
     config.latency_mode = 0;
+    config.cluster_mode = 0;
     config.stdinarg = 0;
     config.auth = NULL;
     config.raw_output = !isatty(fileno(stdout)) && (getenv("FAKETTY") == NULL);