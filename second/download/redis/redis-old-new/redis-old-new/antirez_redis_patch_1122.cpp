@@ -58,6 +58,7 @@
 #define OUTPUT_RAW 1
 #define OUTPUT_CSV 2
 #define REDIS_CLI_KEEPALIVE_INTERVAL 15 /* seconds */
+#define REDIS_DEFAULT_PIPE_TIMEOUT 30 /* seconds */
 
 static redisContext *context;
 static struct config {
@@ -77,6 +78,7 @@ static struct config {
     int cluster_reissue_command;
     int slave_mode;
     int pipe_mode;
+    int pipe_timeout;
     int getrdb_mode;
     int stat_mode;
     char *rdb_filename;
@@ -714,6 +716,8 @@ static int parseOptions(int argc, char **argv) {
             config.rdb_filename = argv[++i];
         } else if (!strcmp(argv[i],"--pipe")) {
             config.pipe_mode = 1;
+        } else if (!strcmp(argv[i],"--pipe-timeout") && !lastarg) {
+            config.pipe_timeout = atoi(argv[++i]);
         } else if (!strcmp(argv[i],"--bigkeys")) {
             config.bigkeys = 1;
         } else if (!strcmp(argv[i],"--eval") && !lastarg) {
@@ -766,29 +770,32 @@ static void usage() {
 "redis-cli %s\n"
 "\n"
 "Usage: redis-cli [OPTIONS] [cmd [arg [arg ...]]]\n"
-"  -h <hostname>     Server hostname (default: 127.0.0.1)\n"
-"  -p <port>         Server port (default: 6379)\n"
-"  -s <socket>       Server socket (overrides hostname and port)\n"
-"  -a <password>     Password to use when connecting to the server\n"
-"  -r <repeat>       Execute specified command N times\n"
-"  -i <interval>     When -r is used, waits <interval> seconds per command.\n"
-"                    It is possible to specify sub-second times like -i 0.1\n"
-"  -n <db>           Database number\n"
-"  -x                Read last argument from STDIN\n"
-"  -d <delimiter>    Multi-bulk delimiter in for raw formatting (default: \\n)\n"
-"  -c                Enable cluster mode (follow -ASK and -MOVED redirections)\n"
-"  --raw             Use raw formatting for replies (default when STDOUT is\n"
-"                    not a tty)\n"
-"  --latency         Enter a special mode continuously sampling latency\n"
-"  --latency-history Like --latency but tracking latency changes over time.\n"
-"                    Default time interval is 15 sec. Change it using -i.\n"
-"  --slave           Simulate a slave showing commands received from the master\n"
-"  --rdb <filename>  Transfer an RDB dump from remote server to local file.\n"
-"  --pipe            Transfer raw Redis protocol from stdin to server\n"
-"  --bigkeys         Sample Redis keys looking for big keys\n"
-"  --eval <file>     Send an EVAL command using the Lua script at <file>\n"
-"  --help            Output this help and exit\n"
-"  --version         Output version and exit\n"
+"  -h <hostname>      Server hostname (default: 127.0.0.1)\n"
+"  -p <port>          Server port (default: 6379)\n"
+"  -s <socket>        Server socket (overrides hostname and port)\n"
+"  -a <password>      Password to use when connecting to the server\n"
+"  -r <repeat>        Execute specified command N times\n"
+"  -i <interval>      When -r is used, waits <interval> seconds per command.\n"
+"                     It is possible to specify sub-second times like -i 0.1\n"
+"  -n <db>            Database number\n"
+"  -x                 Read last argument from STDIN\n"
+"  -d <delimiter>     Multi-bulk delimiter in for raw formatting (default: \\n)\n"
+"  -c                 Enable cluster mode (follow -ASK and -MOVED redirections)\n"
+"  --raw              Use raw formatting for replies (default when STDOUT is\n"
+"                     not a tty)\n"
+"  --latency          Enter a special mode continuously sampling latency\n"
+"  --latency-history  Like --latency but tracking latency changes over time.\n"
+"                     Default time interval is 15 sec. Change it using -i.\n"
+"  --slave            Simulate a slave showing commands received from the master\n"
+"  --rdb <filename>   Transfer an RDB dump from remote server to local file.\n"
+"  --pipe             Transfer raw Redis protocol from stdin to server\n"
+"  --pipe-timeout <n> In --pipe mode, abort with error if after sending all data\n"
+"                     no reply is received within <n> seconds.\n"
+"                     Default timeout: %d. Use 0 to wait forever.\n"
+"  --bigkeys          Sample Redis keys looking for big keys\n"
+"  --eval <file>      Send an EVAL command using the Lua script at <file>\n"
+"  --help             Output this help and exit\n"
+"  --version          Output version and exit\n"
 "\n"
 "Examples:\n"
 "  cat /etc/passwd | redis-cli -x set mypasswd\n"
@@ -801,7 +808,7 @@ static void usage() {
 "When no command is given, redis-cli starts in interactive mode.\n"
 "Type \"help\" in interactive mode for information on available commands.\n"
 "\n",
-        version);
+        version, REDIS_DEFAULT_PIPE_TIMEOUT);
     sdsfree(version);
     exit(1);
 }
@@ -1119,6 +1126,7 @@ static void pipeMode(void) {
     int eof = 0; /* True once we consumed all the standard input. */
     int done = 0;
     char magic[20]; /* Special reply we recognize. */
+    time_t last_read_time = time(NULL);
 
     srand(time(NULL));
 
@@ -1149,7 +1157,10 @@ static void pipeMode(void) {
                         strerror(errno));
                     exit(1);
                 }
-                if (nread > 0) redisReaderFeed(reader,ibuf,nread);
+                if (nread > 0) {
+                    redisReaderFeed(reader,ibuf,nread);
+                    last_read_time = time(NULL);
+                }
             } while(nread > 0);
 
             /* Consume replies. */
@@ -1235,6 +1246,18 @@ static void pipeMode(void) {
                 if (obuf_len == 0 && eof) break;
             }
         }
+
+        /* Handle timeout, that is, we reached EOF, and we are not getting
+         * replies from the server for a few seconds, nor the final ECHO is
+         * received. */
+        if (eof && config.pipe_timeout > 0 &&
+            time(NULL)-last_read_time > config.pipe_timeout)
+        {
+            fprintf(stderr,"No replies for %d seconds: exiting.\n",
+                config.pipe_timeout);
+            errors++;
+            break;
+        }
     }
     redisReaderFree(reader);
     printf("errors: %lld, replies: %lld\n", errors, replies);
@@ -1490,6 +1513,7 @@ int main(int argc, char **argv) {
     config.getrdb_mode = 0;
     config.rdb_filename = NULL;
     config.pipe_mode = 0;
+    config.pipe_timeout = REDIS_DEFAULT_PIPE_TIMEOUT;
     config.bigkeys = 0;
     config.stdinarg = 0;
     config.auth = NULL;