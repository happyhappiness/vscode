@@ -1116,7 +1116,7 @@ static void repl(void) {
                     if (config.eval_ldb_end) {
                         config.eval_ldb_end = 0;
                         cliReadReply(0);
-                        printf("\n(Lua debugging session ended)\n\n");
+                        printf("\n(Lua debugging session ended. Dataset changes rolled back)\n\n");
                     }
 
                     elapsed = mstime()-start_time;