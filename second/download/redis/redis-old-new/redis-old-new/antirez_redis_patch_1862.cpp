@@ -432,8 +432,9 @@ static void repl() {
                             cliPrintContextErrorAndExit();
                     }
                     elapsed = mstime()-start_time;
-                    if (elapsed > 500) printf("%.2f seconds\n",
-                        (double)elapsed/1000);
+                    if (elapsed >= 500) {
+                        printf("(%.2fs)\n",(double)elapsed/1000);
+                    }
                 }
             }
             /* Free the argument vector */