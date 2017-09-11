@@ -696,7 +696,8 @@ static void repl() {
 
                         /* If we still cannot send the command print error.
                          * We'll try to reconnect the next time. */
-                        if (cliSendCommand(argc,argv,1) != REDIS_OK)
+                        if (cliSendCommand(argc-skipargs,argv+skipargs,repeat)
+                            != REDIS_OK)
                             cliPrintContextError();
                     }
                     elapsed = mstime()-start_time;