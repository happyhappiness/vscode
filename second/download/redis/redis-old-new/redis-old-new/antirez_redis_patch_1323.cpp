@@ -69,6 +69,7 @@ static struct config {
     int cluster_mode;
     int cluster_reissue_command;
     int slave_mode;
+    int bigkeys;
     int stdinarg; /* get last arg from stdin. (-x option) */
     char *auth;
     int output; /* output mode, see OUTPUT_* defines */
@@ -655,6 +656,8 @@ static int parseOptions(int argc, char **argv) {
             config.latency_mode = 1;
         } else if (!strcmp(argv[i],"--slave")) {
             config.slave_mode = 1;
+        } else if (!strcmp(argv[i],"--bigkeys")) {
+            config.bigkeys = 1;
         } else if (!strcmp(argv[i],"--eval") && !lastarg) {
             config.eval = argv[++i];
         } else if (!strcmp(argv[i],"-c")) {
@@ -711,6 +714,7 @@ static void usage() {
 "  --raw            Use raw formatting for replies (default when STDOUT is not a tty)\n"
 "  --latency        Enter a special mode continuously sampling latency.\n"
 "  --slave          Simulate a slave showing commands received from the master.\n"
+"  --bigkeys        Sample Redis keys looking for big keys.\n"
 "  --eval <file>    Send an EVAL command using the Lua script at <file>.\n"
 "  --help           Output this help and exit\n"
 "  --version        Output version and exit\n"
@@ -964,6 +968,87 @@ static void slaveMode(void) {
     while (cliReadReply(0) == REDIS_OK);
 }
 
+#define TYPE_STRING 0
+#define TYPE_LIST   1
+#define TYPE_SET    2
+#define TYPE_HASH   3
+#define TYPE_ZSET   4
+
+static void findBigKeys(void) {
+    unsigned long long biggest[5] = {0,0,0,0,0};
+    unsigned long long samples = 0;
+    redisReply *reply1, *reply2, *reply3;
+    char *sizecmd, *typename[] = {"string","list","set","hash","zset"};
+    int type;
+
+    printf("\n# Press ctrl+c when you have had enough of it... :)\n");
+    printf("# You can use -i 0.1 to sleep 0.1 sec every 100 sampled keys\n");
+    printf("# in order to reduce server load (usually not needed).\n\n");
+    while(1) {
+        /* Sample with RANDOMKEY */
+        reply1 = redisCommand(context,"RANDOMKEY");
+        if (reply1 == NULL) {
+            fprintf(stderr,"\nI/O error\n");
+            exit(1);
+        } else if (reply1->type == REDIS_REPLY_ERROR) {
+            fprintf(stderr, "RANDOMKEY error: %s\n",
+                reply1->str);
+            exit(1);
+        }
+        /* Get the key type */
+        reply2 = redisCommand(context,"TYPE %s",reply1->str);
+        assert(reply2 && reply2->type == REDIS_REPLY_STATUS);
+        samples++;
+
+        /* Get the key "size" */
+        if (!strcmp(reply2->str,"string")) {
+            sizecmd = "STRLEN";
+            type = TYPE_STRING;
+        } else if (!strcmp(reply2->str,"list")) {
+            sizecmd = "LLEN";
+            type = TYPE_LIST;
+        } else if (!strcmp(reply2->str,"set")) {
+            sizecmd = "SCARD";
+            type = TYPE_SET;
+        } else if (!strcmp(reply2->str,"hash")) {
+            sizecmd = "HLEN";
+            type = TYPE_HASH;
+        } else if (!strcmp(reply2->str,"zset")) {
+            sizecmd = "ZCARD";
+            type = TYPE_ZSET;
+        } else if (!strcmp(reply2->str,"none")) {
+            freeReplyObject(reply1);
+            freeReplyObject(reply2);
+            freeReplyObject(reply3);
+            continue;
+        } else {
+            fprintf(stderr, "Unknown key type '%s' for key '%s'\n",
+                reply2->str, reply1->str);
+            exit(1);
+        }
+
+        reply3 = redisCommand(context,"%s %s", sizecmd, reply1->str);
+        if (reply3 && reply3->type == REDIS_REPLY_INTEGER) {
+            if (biggest[type] < reply3->integer) {
+                printf("Biggest %s so far: %s, size: %llu\n",
+                    typename[type], reply1->str,
+                    (unsigned long long) reply3->integer);
+                biggest[type] = reply3->integer;
+            }
+        }
+
+        if ((samples % 1000000) == 0)
+            printf("(%llu keys sampled)\n", samples);
+
+        if ((samples % 100) == 0 && config.interval)
+            usleep(config.interval);
+
+        freeReplyObject(reply1);
+        freeReplyObject(reply2);
+        if (reply3) freeReplyObject(reply3);
+    }
+}
+
 int main(int argc, char **argv) {
     int firstarg;
 
@@ -979,6 +1064,8 @@ int main(int argc, char **argv) {
     config.pubsub_mode = 0;
     config.latency_mode = 0;
     config.cluster_mode = 0;
+    config.slave_mode = 0;
+    config.bigkeys = 0;
     config.stdinarg = 0;
     config.auth = NULL;
     config.eval = NULL;
@@ -1005,6 +1092,12 @@ int main(int argc, char **argv) {
         slaveMode();
     }
 
+    /* Find big keys */
+    if (config.bigkeys) {
+        cliConnect(0);
+        findBigKeys();
+    }
+
     /* Start interactive mode when no command is provided */
     if (argc == 0 && !config.eval) {
         /* Note that in repl mode we don't abort on connection error.