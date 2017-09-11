@@ -1344,7 +1344,9 @@ static void repl(void) {
                     }
 
                     elapsed = mstime()-start_time;
-                    if (elapsed >= 500) {
+                    if (elapsed >= 500 &&
+                        config.output == OUTPUT_STANDARD)
+                    {
                         printf("(%.2fs)\n",(double)elapsed/1000);
                     }
                 }