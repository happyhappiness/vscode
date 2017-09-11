@@ -644,6 +644,7 @@ static int cliSendCommand(int argc, char **argv, int repeat) {
             printf("Entering slave output mode...  (press Ctrl-C to quit)\n");
             slaveMode();
             config.slave_mode = 0;
+            free(argvlen);
             return REDIS_ERR;  /* Error = slaveMode lost connection to master */
         }
 