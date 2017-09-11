@@ -877,6 +877,33 @@ static char **convertToSds(int count, char** args) {
   return sds;
 }
 
+static int issueCommandRepeat(int argc, char **argv, long repeat) {
+    while (1) {
+        config.cluster_reissue_command = 0;
+        if (cliSendCommand(argc,argv,repeat) != REDIS_OK) {
+            cliConnect(1);
+
+            /* If we still cannot send the command print error.
+             * We'll try to reconnect the next time. */
+            if (cliSendCommand(argc,argv,repeat) != REDIS_OK) {
+                cliPrintContextError();
+                return REDIS_ERR;
+            }
+         }
+         /* Issue the command again if we got redirected in cluster mode */
+         if (config.cluster_mode && config.cluster_reissue_command) {
+            cliConnect(1);
+         } else {
+             break;
+        }
+    }
+    return REDIS_OK;
+}
+
+static int issueCommand(int argc, char **argv) {
+    return issueCommandRepeat(argc, argv, config.repeat);
+}
+
 static void repl(void) {
     sds historyfile = NULL;
     int history = 0;
@@ -933,26 +960,8 @@ static void repl(void) {
                         repeat = 1;
                     }
 
-                    while (1) {
-                        config.cluster_reissue_command = 0;
-                        if (cliSendCommand(argc-skipargs,argv+skipargs,repeat)
-                            != REDIS_OK)
-                        {
-                            cliConnect(1);
-
-                            /* If we still cannot send the command print error.
-                             * We'll try to reconnect the next time. */
-                            if (cliSendCommand(argc-skipargs,argv+skipargs,repeat)
-                                != REDIS_OK)
-                                cliPrintContextError();
-                        }
-                        /* Issue the command again if we got redirected in cluster mode */
-                        if (config.cluster_mode && config.cluster_reissue_command) {
-                            cliConnect(1);
-                        } else {
-                            break;
-                        }
-                    }
+                    issueCommandRepeat(argc-skipargs, argv+skipargs, repeat);
+
                     elapsed = mstime()-start_time;
                     if (elapsed >= 500) {
                         printf("(%.2fs)\n",(double)elapsed/1000);
@@ -973,10 +982,9 @@ static int noninteractive(int argc, char **argv) {
     if (config.stdinarg) {
         argv = zrealloc(argv, (argc+1)*sizeof(char*));
         argv[argc] = readArgFromStdin();
-        retval = cliSendCommand(argc+1, argv, config.repeat);
+        retval = issueCommand(argc+1, argv);
     } else {
-        /* stdin is probably a tty, can be tested with S_ISCHR(s.st_mode) */
-        retval = cliSendCommand(argc, argv, config.repeat);
+        retval = issueCommand(argc, argv);
     }
     return retval;
 }
@@ -1020,7 +1028,7 @@ static int evalMode(int argc, char **argv) {
     argv2[2] = sdscatprintf(sdsempty(),"%d",keys);
 
     /* Call it */
-    return cliSendCommand(argc+3-got_comma, argv2, config.repeat);
+    return issueCommand(argc+3-got_comma, argv2);
 }
 
 /*------------------------------------------------------------------------------