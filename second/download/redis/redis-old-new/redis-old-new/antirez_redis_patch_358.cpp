@@ -1455,8 +1455,10 @@ void backgroundRewriteDoneHandler(int exitcode, int bysignal) {
         serverLog(LL_VERBOSE,
             "Background AOF rewrite signal handler took %lldus", ustime()-now);
     } else if (!bysignal && exitcode != 0) {
-        server.aof_lastbgrewrite_status = C_ERR;
-
+        /* SIGUSR1 is whitelisted, so we have a way to kill a child without
+         * tirggering an error conditon. */
+        if (bysignal != SIGUSR1)
+            server.aof_lastbgrewrite_status = C_ERR;
         serverLog(LL_WARNING,
             "Background AOF rewrite terminated with error");
     } else {