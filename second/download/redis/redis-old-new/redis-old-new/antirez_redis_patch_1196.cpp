@@ -533,6 +533,7 @@ static int cliReadReply(int output_raw_strings) {
             printf("-> Redirected to slot [%d] located at %s:%d\n",
                 slot, config.hostip, config.hostport);
         config.cluster_reissue_command = 1;
+        cliRefreshPrompt();
     }
 
     if (output) {