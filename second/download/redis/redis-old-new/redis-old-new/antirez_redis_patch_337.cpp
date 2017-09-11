@@ -112,7 +112,8 @@ static struct config {
     char prompt[128];
     char *eval;
     int eval_ldb;
-    int eval_ldb_end;
+    int eval_ldb_sync;  /* Ask for synchronous mode of the Lua debugger. */
+    int eval_ldb_end;   /* Lua debugging session ended. */
     int last_cmd_type;
 } config;
 
@@ -890,6 +891,10 @@ static int parseOptions(int argc, char **argv) {
         } else if (!strcmp(argv[i],"--ldb")) {
             config.eval_ldb = 1;
             config.output = OUTPUT_RAW;
+        } else if (!strcmp(argv[i],"--ldb-sync-mode")) {
+            config.eval_ldb = 1;
+            config.eval_ldb_sync = 1;
+            config.output = OUTPUT_RAW;
         } else if (!strcmp(argv[i],"-c")) {
             config.cluster_mode = 1;
         } else if (!strcmp(argv[i],"-d") && !lastarg) {
@@ -973,6 +978,9 @@ static void usage(void) {
 "                     The test will run for the specified amount of seconds.\n"
 "  --eval <file>      Send an EVAL command using the Lua script at <file>.\n"
 "  --ldb              Used with --eval enable the Redis Lua debugger.\n"
+"  --ldb-sync-mode    Like --ldb but uses the synchronous Lua debugger, in\n"
+"                     this mode the server is blocked and script changes are\n"
+"                     are not rolled back from the server memory.\n"
 "  --help             Output this help and exit.\n"
 "  --version          Output version and exit.\n"
 "\n"
@@ -1116,7 +1124,9 @@ static void repl(void) {
                     if (config.eval_ldb_end) {
                         config.eval_ldb_end = 0;
                         cliReadReply(0);
-                        printf("\n(Lua debugging session ended. Dataset changes rolled back)\n\n");
+                        printf("\n(Lua debugging session ended%s)\n\n",
+                            config.eval_ldb_sync ? "" :
+                            " -- dataset changes rolled back");
                     }
 
                     elapsed = mstime()-start_time;
@@ -1172,7 +1182,8 @@ static int evalMode(int argc, char **argv) {
 
     /* If we are debugging a script, enable the Lua debugger. */
     if (config.eval_ldb) {
-        redisReply *reply = redisCommand(context, "SCRIPT DEBUG yes");
+        redisReply *reply = redisCommand(context,
+                config.eval_ldb_sync ? "SCRIPT DEBUG sync": "SCRIPT DEBUG yes");
         if (reply) freeReplyObject(reply);
     }
 
@@ -2321,6 +2332,8 @@ int main(int argc, char **argv) {
     config.auth = NULL;
     config.eval = NULL;
     config.eval_ldb = 0;
+    config.eval_ldb_end = 0;
+    config.eval_ldb_sync = 0;
     config.last_cmd_type = -1;
 
     spectrum_palette = spectrum_palette_color;