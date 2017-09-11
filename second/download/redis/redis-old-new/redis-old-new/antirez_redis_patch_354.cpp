@@ -111,6 +111,7 @@ static struct config {
     sds mb_delim;
     char prompt[128];
     char *eval;
+    int eval_ldb;
     int last_cmd_type;
 } config;
 
@@ -141,6 +142,7 @@ static long long mstime(void) {
 static void cliRefreshPrompt(void) {
     int len;
 
+    if (config.eval_ldb) return;
     if (config.hostsocket != NULL)
         len = snprintf(config.prompt,sizeof(config.prompt),"redis %s",
                        config.hostsocket);
@@ -822,6 +824,8 @@ static int parseOptions(int argc, char **argv) {
             config.bigkeys = 1;
         } else if (!strcmp(argv[i],"--eval") && !lastarg) {
             config.eval = argv[++i];
+        } else if (!strcmp(argv[i],"--ldb")) {
+            config.eval_ldb = 1;
         } else if (!strcmp(argv[i],"-c")) {
             config.cluster_mode = 1;
         } else if (!strcmp(argv[i],"-d") && !lastarg) {
@@ -904,6 +908,7 @@ static void usage(void) {
 "  --intrinsic-latency <sec> Run a test to measure intrinsic system latency.\n"
 "                     The test will run for the specified amount of seconds.\n"
 "  --eval <file>      Send an EVAL command using the Lua script at <file>.\n"
+"  --ldb              Used with --eval enable the Redis Lua debugger.\n"
 "  --help             Output this help and exit.\n"
 "  --version          Output version and exit.\n"
 "\n"
@@ -1071,6 +1076,12 @@ static int evalMode(int argc, char **argv) {
     }
     fclose(fp);
 
+    /* If we are debugging a script, enable the Lua debugger. */
+    if (config.eval_ldb) {
+        redisReply *reply = redisCommand(context, "SCRIPT DEBUG yes");
+        if (reply) freeReplyObject(reply);
+    }
+
     /* Create our argument vector */
     argv2 = zmalloc(sizeof(sds)*(argc+3));
     argv2[0] = sdsnew("EVAL");
@@ -1086,7 +1097,12 @@ static int evalMode(int argc, char **argv) {
     argv2[2] = sdscatprintf(sdsempty(),"%d",keys);
 
     /* Call it */
-    return issueCommand(argc+3-got_comma, argv2);
+    int retval = issueCommand(argc+3-got_comma, argv2);
+    if (config.eval_ldb) {
+        strncpy(config.prompt,"lua debugger> ",sizeof(config.prompt));
+        repl();
+    }
+    return retval;
 }
 
 /*------------------------------------------------------------------------------
@@ -2210,6 +2226,7 @@ int main(int argc, char **argv) {
     config.stdinarg = 0;
     config.auth = NULL;
     config.eval = NULL;
+    config.eval_ldb = 0;
     config.last_cmd_type = -1;
 
     spectrum_palette = spectrum_palette_color;