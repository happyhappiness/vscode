@@ -69,6 +69,7 @@ static struct config {
     int raw_output; /* output mode per command */
     sds mb_delim;
     char prompt[32];
+    char *eval;
 } config;
 
 static void usage();
@@ -573,43 +574,37 @@ static int parseOptions(int argc, char **argv) {
 
         if (!strcmp(argv[i],"-h") && !lastarg) {
             sdsfree(config.hostip);
-            config.hostip = sdsnew(argv[i+1]);
-            i++;
+            config.hostip = sdsnew(argv[++i]);
         } else if (!strcmp(argv[i],"-h") && lastarg) {
             usage();
         } else if (!strcmp(argv[i],"--help")) {
             usage();
         } else if (!strcmp(argv[i],"-x")) {
             config.stdinarg = 1;
         } else if (!strcmp(argv[i],"-p") && !lastarg) {
-            config.hostport = atoi(argv[i+1]);
-            i++;
+            config.hostport = atoi(argv[++i]);
         } else if (!strcmp(argv[i],"-s") && !lastarg) {
-            config.hostsocket = argv[i+1];
-            i++;
+            config.hostsocket = argv[++i];
         } else if (!strcmp(argv[i],"-r") && !lastarg) {
-            config.repeat = strtoll(argv[i+1],NULL,10);
-            i++;
+            config.repeat = strtoll(argv[++i],NULL,10);
         } else if (!strcmp(argv[i],"-i") && !lastarg) {
-            double seconds = atof(argv[i+1]);
+            double seconds = atof(argv[++i]);
             config.interval = seconds*1000000;
-            i++;
         } else if (!strcmp(argv[i],"-n") && !lastarg) {
-            config.dbnum = atoi(argv[i+1]);
-            i++;
+            config.dbnum = atoi(argv[++i]);
         } else if (!strcmp(argv[i],"-a") && !lastarg) {
-            config.auth = argv[i+1];
-            i++;
+            config.auth = argv[++i];
         } else if (!strcmp(argv[i],"--raw")) {
             config.raw_output = 1;
         } else if (!strcmp(argv[i],"--latency")) {
             config.latency_mode = 1;
+        } else if (!strcmp(argv[i],"--eval") && !lastarg) {
+            config.eval = argv[++i];
         } else if (!strcmp(argv[i],"-c")) {
             config.cluster_mode = 1;
         } else if (!strcmp(argv[i],"-d") && !lastarg) {
             sdsfree(config.mb_delim);
-            config.mb_delim = sdsnew(argv[i+1]);
-            i++;
+            config.mb_delim = sdsnew(argv[++i]);
         } else if (!strcmp(argv[i],"-v") || !strcmp(argv[i], "--version")) {
             sds version = cliVersion();
             printf("redis-cli %s\n", version);
@@ -658,6 +653,7 @@ static void usage() {
 "  -c               Enable cluster mode (follow -ASK and -MOVED redirections)\n"
 "  --raw            Use raw formatting for replies (default when STDOUT is not a tty)\n"
 "  --latency        Enter a special mode continuously sampling latency.\n"
+"  --eval <file>    Send an EVAL command using the Lua script at <file>.\n"
 "  --help           Output this help and exit\n"
 "  --version        Output version and exit\n"
 "\n"
@@ -666,6 +662,8 @@ static void usage() {
 "  redis-cli get mypasswd\n"
 "  redis-cli -r 100 lpush mylist x\n"
 "  redis-cli -r 100 -i 1 info | grep used_memory_human:\n"
+"  redis-cli --eval myscript.lua key1 key2 , arg1 arg2 arg3\n"
+"  (Note: when using --eval the comma separates KEYS[] from ARGV[] items)\n"
 "\n"
 "When no command is given, redis-cli starts in interactive mode.\n"
 "Type \"help\" in interactive mode for information on available commands.\n"
@@ -790,6 +788,44 @@ static int noninteractive(int argc, char **argv) {
     return retval;
 }
 
+static int evalMode(int argc, char **argv) {
+    sds script = sdsempty();
+    FILE *fp;
+    char buf[1024];
+    size_t nread;
+    char **argv2;
+    int j, got_comma = 0, keys = 0;
+
+    /* Load the script from the file, as an sds string. */
+    fp = fopen(config.eval,"r");
+    if (!fp) {
+        fprintf(stderr,
+            "Can't open file '%s': %s\n", config.eval, strerror(errno));
+        exit(1);
+    }
+    while((nread = fread(buf,1,sizeof(buf),fp)) != 0) {
+        script = sdscatlen(script,buf,nread);
+    }
+    fclose(fp);
+
+    /* Create our argument vector */
+    argv2 = zmalloc(sizeof(sds)*(argc+3));
+    argv2[0] = sdsnew("EVAL");
+    argv2[1] = script;
+    for (j = 0; j < argc; j++) {
+        if (!got_comma && argv[j][0] == ',' && argv[j][1] == 0) {
+            got_comma = 1;
+            continue;
+        }
+        argv2[j+3-got_comma] = sdsnew(argv[j]);
+        if (!got_comma) keys++;
+    }
+    argv2[2] = sdscatprintf(sdsempty(),"%d",keys);
+
+    /* Call it */
+    return cliSendCommand(argc+3-got_comma, argv2, config.repeat);
+}
+
 static void latencyMode(void) {
     redisReply *reply;
     long long start, latency, min, max, tot, count = 0;
@@ -839,6 +875,7 @@ int main(int argc, char **argv) {
     config.cluster_mode = 0;
     config.stdinarg = 0;
     config.auth = NULL;
+    config.eval = NULL;
     config.raw_output = !isatty(fileno(stdout)) && (getenv("FAKETTY") == NULL);
     config.mb_delim = sdsnew("\n");
     cliInitHelp();
@@ -854,7 +891,7 @@ int main(int argc, char **argv) {
     }
 
     /* Start interactive mode when no command is provided */
-    if (argc == 0) {
+    if (argc == 0 && !config.eval) {
         /* Note that in repl mode we don't abort on connection error.
          * A new attempt will be performed for every command send. */
         cliConnect(0);
@@ -863,5 +900,9 @@ int main(int argc, char **argv) {
 
     /* Otherwise, we have some arguments to execute */
     if (cliConnect(0) != REDIS_OK) exit(1);
-    return noninteractive(argc,convertToSds(argc,argv));
+    if (config.eval) {
+        return evalMode(argc,argv);
+    } else {
+        return noninteractive(argc,convertToSds(argc,argv));
+    }
 }