@@ -1209,10 +1209,19 @@ static int evalMode(int argc, char **argv) {
     argv2[2] = sdscatprintf(sdsempty(),"%d",keys);
 
     /* Call it */
+    int eval_ldb = config.eval_ldb; /* Save it, may be reverteed. */
     int retval = issueCommand(argc+3-got_comma, argv2);
-    if (config.eval_ldb) {
-        strncpy(config.prompt,"lua debugger> ",sizeof(config.prompt));
-        repl();
+    if (eval_ldb) {
+        if (!config.eval_ldb) {
+            /* If the debugging session ended immediately, there was an
+             * error compiling the script. Show it and don't enter
+             * the REPL at all. */
+            printf("Eval debugging session can't start:\n");
+            cliReadReply(0);
+        } else {
+            strncpy(config.prompt,"lua debugger> ",sizeof(config.prompt));
+            repl();
+        }
     }
     return retval;
 }