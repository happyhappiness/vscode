@@ -64,6 +64,7 @@ static struct config {
     int latency_mode;
     int cluster_mode;
     int cluster_reissue_command;
+    int slave_mode;
     int stdinarg; /* get last arg from stdin. (-x option) */
     char *auth;
     int raw_output; /* output mode per command */
@@ -606,6 +607,8 @@ static int parseOptions(int argc, char **argv) {
             config.raw_output = 1;
         } else if (!strcmp(argv[i],"--latency")) {
             config.latency_mode = 1;
+        } else if (!strcmp(argv[i],"--slave")) {
+            config.slave_mode = 1;
         } else if (!strcmp(argv[i],"--eval") && !lastarg) {
             config.eval = argv[++i];
         } else if (!strcmp(argv[i],"-c")) {
@@ -661,6 +664,7 @@ static void usage() {
 "  -c               Enable cluster mode (follow -ASK and -MOVED redirections)\n"
 "  --raw            Use raw formatting for replies (default when STDOUT is not a tty)\n"
 "  --latency        Enter a special mode continuously sampling latency.\n"
+"  --slave          Simulate a slave showing commands received from the master.\n"
 "  --eval <file>    Send an EVAL command using the Lua script at <file>.\n"
 "  --help           Output this help and exit\n"
 "  --version        Output version and exit\n"
@@ -866,6 +870,51 @@ static void latencyMode(void) {
     }
 }
 
+static void slaveMode(void) {
+    /* To start we need to send the SYNC command and return the payload.
+     * The hiredis client lib does not understand this part of the protocol
+     * and we don't want to mess with its buffers, so everything is performed
+     * using direct low-level I/O. */
+    int fd = context->fd;
+    char buf[1024], *p;
+    ssize_t nread;
+    unsigned long long payload;
+
+    /* Send the SYNC command. */
+    write(fd,"SYNC\r\n",6);
+
+    /* Read $<payload>\r\n, making sure to read just up to "\n" */
+    p = buf;
+    while(1) {
+        nread = read(fd,p,1);
+        if (nread <= 0) {
+            fprintf(stderr,"Error reading bulk length while SYNCing\n");
+            exit(1);
+        }
+        if (*p == '\n') break;
+        p++;
+    }
+    *p = '\0';
+    payload = strtoull(buf+1,NULL,10);
+    if (!config.raw_output)
+        printf("SYNC with master, discarding %lld bytes of bulk tranfer...\n",
+            payload);
+
+    /* Discard the payload. */
+    while(payload) {
+        nread = read(fd,buf,(payload > sizeof(buf)) ? sizeof(buf) : payload);
+        if (nread <= 0) {
+            fprintf(stderr,"Error reading RDB payload while SYNCing\n");
+            exit(1);
+        }
+        payload -= nread;
+    }
+    if (!config.raw_output) printf("SYNC done. Logging commands from master.\n");
+
+    /* Now we can use the hiredis to read the incoming protocol. */
+    while (cliReadReply(config.raw_output) == REDIS_OK);
+}
+
 int main(int argc, char **argv) {
     int firstarg;
 
@@ -898,6 +947,12 @@ int main(int argc, char **argv) {
         latencyMode();
     }
 
+    /* Start in slave mode if appropriate */
+    if (config.slave_mode) {
+        cliConnect(0);
+        slaveMode();
+    }
+
     /* Start interactive mode when no command is provided */
     if (argc == 0 && !config.eval) {
         /* Note that in repl mode we don't abort on connection error.