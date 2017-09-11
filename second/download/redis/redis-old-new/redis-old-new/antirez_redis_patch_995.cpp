@@ -81,6 +81,8 @@ static struct config {
     int pipe_timeout;
     int getrdb_mode;
     int stat_mode;
+    int scan_mode;
+    char *pattern;
     char *rdb_filename;
     int bigkeys;
     int stdinarg; /* get last arg from stdin. (-x option) */
@@ -712,6 +714,10 @@ static int parseOptions(int argc, char **argv) {
             config.slave_mode = 1;
         } else if (!strcmp(argv[i],"--stat")) {
             config.stat_mode = 1;
+        } else if (!strcmp(argv[i],"--scan")) {
+            config.scan_mode = 1;
+        } else if (!strcmp(argv[i],"--pattern")) {
+            config.pattern = argv[++i];
         } else if (!strcmp(argv[i],"--rdb") && !lastarg) {
             config.getrdb_mode = 1;
             config.rdb_filename = argv[++i];
@@ -795,6 +801,8 @@ static void usage() {
 "                     no reply is received within <n> seconds.\n"
 "                     Default timeout: %d. Use 0 to wait forever.\n"
 "  --bigkeys          Sample Redis keys looking for big keys\n"
+"  --scan             List all keys using the SCAN command\n"
+"  --pattern <pat>    Useful with --scan to specify a SCAN pattern\n"
 "  --eval <file>      Send an EVAL command using the Lua script at <file>\n"
 "  --help             Output this help and exit\n"
 "  --version          Output version and exit\n"
@@ -1494,6 +1502,35 @@ static void statMode() {
     }
 }
 
+static void scanMode() {
+    redisReply *reply;
+    unsigned long long cur = 0;
+
+    do {
+        if (config.pattern)
+            reply = redisCommand(context,"SCAN %llu MATCH %s",
+                cur,config.pattern);
+        else
+            reply = redisCommand(context,"SCAN %llu",cur);
+        if (reply == NULL) {
+            printf("I/O error\n");
+            exit(1);
+        } else if (reply->type == REDIS_REPLY_ERROR) {
+            printf("ERROR: %s\n", reply->str);
+            exit(1);
+        } else {
+            int j;
+
+            cur = strtoull(reply->element[0]->str,NULL,10);
+            for (j = 0; j < reply->element[1]->elements; j++)
+                printf("%s\n", reply->element[1]->element[j]->str);
+        }
+        freeReplyObject(reply);
+    } while(cur != 0);
+
+    exit(0);
+}
+
 int main(int argc, char **argv) {
     int firstarg;
 
@@ -1512,6 +1549,9 @@ int main(int argc, char **argv) {
     config.cluster_mode = 0;
     config.slave_mode = 0;
     config.getrdb_mode = 0;
+    config.stat_mode = 0;
+    config.scan_mode = 0;
+    config.pattern = NULL;
     config.rdb_filename = NULL;
     config.pipe_mode = 0;
     config.pipe_timeout = REDIS_DEFAULT_PIPE_TIMEOUT;
@@ -1567,6 +1607,12 @@ int main(int argc, char **argv) {
         statMode();
     }
 
+    /* Scan mode */
+    if (config.scan_mode) {
+        if (cliConnect(0) == REDIS_ERR) exit(1);
+        scanMode();
+    }
+
     /* Start interactive mode when no command is provided */
     if (argc == 0 && !config.eval) {
         /* Note that in repl mode we don't abort on connection error.