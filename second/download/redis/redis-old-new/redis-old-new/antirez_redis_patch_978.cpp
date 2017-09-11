@@ -94,6 +94,7 @@ static struct config {
 } config;
 
 static void usage();
+static void slaveMode(void);
 char *redisGitSHA1(void);
 char *redisGitDirty(void);
 
@@ -600,6 +601,8 @@ static int cliSendCommand(int argc, char **argv, int repeat) {
     if (!strcasecmp(command,"monitor")) config.monitor_mode = 1;
     if (!strcasecmp(command,"subscribe") ||
         !strcasecmp(command,"psubscribe")) config.pubsub_mode = 1;
+    if (!strcasecmp(command,"sync") ||
+        !strcasecmp(command,"psync")) config.slave_mode = 1;
 
     /* Setup argument length */
     argvlen = malloc(argc*sizeof(size_t));
@@ -621,6 +624,13 @@ static int cliSendCommand(int argc, char **argv, int repeat) {
             }
         }
 
+        if (config.slave_mode) {
+            printf("Entering slave output mode...  (press Ctrl-C to quit)\n");
+            slaveMode();
+            config.slave_mode = 0;
+            return REDIS_ERR;  /* Error = slaveMode lost connection to master */
+        }
+
         if (cliReadReply(output_raw) != REDIS_OK) {
             free(argvlen);
             return REDIS_ERR;
@@ -1061,6 +1071,7 @@ static void slaveMode(void) {
     int fd = context->fd;
     unsigned long long payload = sendSync(fd);
     char buf[1024];
+    int original_output = config.output;
 
     fprintf(stderr,"SYNC with master, discarding %llu "
                    "bytes of bulk transfer...\n", payload);
@@ -1081,6 +1092,7 @@ static void slaveMode(void) {
     /* Now we can use hiredis to read the incoming protocol. */
     config.output = OUTPUT_CSV;
     while (cliReadReply(0) == REDIS_OK);
+    config.output = original_output;
 }
 
 /* This function implements --rdb, so it uses the replication protocol in order