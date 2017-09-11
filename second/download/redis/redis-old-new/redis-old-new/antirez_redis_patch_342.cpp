@@ -112,6 +112,7 @@ static struct config {
     char prompt[128];
     char *eval;
     int eval_ldb;
+    int eval_ldb_end;
     int last_cmd_type;
 } config;
 
@@ -377,14 +378,6 @@ static int cliConnect(int force) {
     if (context == NULL || force) {
         if (context != NULL) {
             redisFree(context);
-            /* Disconnection from the server signals end of EVAL
-             * debugging session. */
-            if (config.eval_ldb) {
-                printf("\n(Lua debugging session terminated)\n\n");
-                config.eval_ldb = 0;
-                config.output = OUTPUT_STANDARD;
-                cliRefreshPrompt();
-            }
         }
 
         if (config.hostsocket == NULL) {
@@ -553,7 +546,16 @@ static sds cliFormatReplyRaw(redisReply *r) {
             /* The Lua debugger replies with arrays of simple (status)
              * strings. We colorize the output for more fun if this
              * is a debugging session. */
-            out = sdsCatColorizedLdbReply(out,r->str,r->len);
+
+            /* Detect the end of a debugging session. */
+            if (strstr(r->str,"<endsession>") == r->str) {
+                config.eval_ldb = 0;
+                config.eval_ldb_end = 1; /* Signal the caller session ended. */
+                config.output = OUTPUT_STANDARD;
+                cliRefreshPrompt();
+            } else {
+                out = sdsCatColorizedLdbReply(out,r->str,r->len);
+            }
         } else {
             out = sdscatlen(out,r->str,r->len);
         }
@@ -1109,6 +1111,14 @@ static void repl(void) {
 
                     issueCommandRepeat(argc-skipargs, argv+skipargs, repeat);
 
+                    /* If our debugging session ended, show the EVAL final
+                     * reply. */
+                    if (config.eval_ldb_end) {
+                        config.eval_ldb_end = 0;
+                        cliReadReply(0);
+                        printf("\n(Lua debugging session ended)\n\n");
+                    }
+
                     elapsed = mstime()-start_time;
                     if (elapsed >= 500) {
                         printf("(%.2fs)\n",(double)elapsed/1000);