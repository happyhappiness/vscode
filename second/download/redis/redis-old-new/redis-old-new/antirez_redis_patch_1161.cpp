@@ -72,6 +72,7 @@ static struct config {
     int monitor_mode;
     int pubsub_mode;
     int latency_mode;
+    int latency_history;
     int cluster_mode;
     int cluster_reissue_command;
     int slave_mode;
@@ -701,6 +702,9 @@ static int parseOptions(int argc, char **argv) {
             config.output = OUTPUT_CSV;
         } else if (!strcmp(argv[i],"--latency")) {
             config.latency_mode = 1;
+        } else if (!strcmp(argv[i],"--latency-history")) {
+            config.latency_mode = 1;
+            config.latency_history = 1;
         } else if (!strcmp(argv[i],"--slave")) {
             config.slave_mode = 1;
         } else if (!strcmp(argv[i],"--stat")) {
@@ -754,26 +758,29 @@ static void usage() {
 "redis-cli %s\n"
 "\n"
 "Usage: redis-cli [OPTIONS] [cmd [arg [arg ...]]]\n"
-"  -h <hostname>    Server hostname (default: 127.0.0.1)\n"
-"  -p <port>        Server port (default: 6379)\n"
-"  -s <socket>      Server socket (overrides hostname and port)\n"
-"  -a <password>    Password to use when connecting to the server\n"
-"  -r <repeat>      Execute specified command N times\n"
-"  -i <interval>    When -r is used, waits <interval> seconds per command.\n"
-"                   It is possible to specify sub-second times like -i 0.1\n"
-"  -n <db>          Database number\n"
-"  -x               Read last argument from STDIN\n"
-"  -d <delimiter>   Multi-bulk delimiter in for raw formatting (default: \\n)\n"
-"  -c               Enable cluster mode (follow -ASK and -MOVED redirections)\n"
-"  --raw            Use raw formatting for replies (default when STDOUT is not a tty)\n"
-"  --latency        Enter a special mode continuously sampling latency\n"
-"  --slave          Simulate a slave showing commands received from the master\n"
-"  --rdb <filename> Transfer an RDB dump from remote server to local file.\n"
-"  --pipe           Transfer raw Redis protocol from stdin to server\n"
-"  --bigkeys        Sample Redis keys looking for big keys\n"
-"  --eval <file>    Send an EVAL command using the Lua script at <file>\n"
-"  --help           Output this help and exit\n"
-"  --version        Output version and exit\n"
+"  -h <hostname>     Server hostname (default: 127.0.0.1)\n"
+"  -p <port>         Server port (default: 6379)\n"
+"  -s <socket>       Server socket (overrides hostname and port)\n"
+"  -a <password>     Password to use when connecting to the server\n"
+"  -r <repeat>       Execute specified command N times\n"
+"  -i <interval>     When -r is used, waits <interval> seconds per command.\n"
+"                    It is possible to specify sub-second times like -i 0.1\n"
+"  -n <db>           Database number\n"
+"  -x                Read last argument from STDIN\n"
+"  -d <delimiter>    Multi-bulk delimiter in for raw formatting (default: \\n)\n"
+"  -c                Enable cluster mode (follow -ASK and -MOVED redirections)\n"
+"  --raw             Use raw formatting for replies (default when STDOUT is\n"
+"                    not a tty)\n"
+"  --latency         Enter a special mode continuously sampling latency\n"
+"  --latency-history Like --latency but tracking latency changes over time.\n"
+"                    Default time interval is 15 sec. Change it using -i.\n"
+"  --slave           Simulate a slave showing commands received from the master\n"
+"  --rdb <filename>  Transfer an RDB dump from remote server to local file.\n"
+"  --pipe            Transfer raw Redis protocol from stdin to server\n"
+"  --bigkeys         Sample Redis keys looking for big keys\n"
+"  --eval <file>     Send an EVAL command using the Lua script at <file>\n"
+"  --help            Output this help and exit\n"
+"  --version         Output version and exit\n"
 "\n"
 "Examples:\n"
 "  cat /etc/passwd | redis-cli -x set mypasswd\n"
@@ -944,10 +951,16 @@ static int evalMode(int argc, char **argv) {
     return cliSendCommand(argc+3-got_comma, argv2, config.repeat);
 }
 
+#define LATENCY_SAMPLE_RATE 10 /* milliseconds. */
+#define LATENCY_HISTORY_DEFAULT_INTERVAL 15000 /* milliseconds. */
 static void latencyMode(void) {
     redisReply *reply;
     long long start, latency, min = 0, max = 0, tot = 0, count = 0;
+    long long history_interval =
+        config.interval ? config.interval/1000 :
+                          LATENCY_HISTORY_DEFAULT_INTERVAL;
     double avg;
+    long long history_start = mstime();
 
     if (!context) exit(1);
     while(1) {
@@ -972,7 +985,13 @@ static void latencyMode(void) {
         printf("\x1b[0G\x1b[2Kmin: %lld, max: %lld, avg: %.2f (%lld samples)",
             min, max, avg, count);
         fflush(stdout);
-        usleep(10000);
+        if (config.latency_history && mstime()-history_start > history_interval)
+        {
+            printf(" -- %.2f seconds range\n", (float)(mstime()-history_start)/1000);
+            history_start = mstime();
+            min = max = tot = count = 0;
+        }
+        usleep(LATENCY_SAMPLE_RATE * 1000);
     }
 }
 
@@ -1453,6 +1472,7 @@ int main(int argc, char **argv) {
     config.monitor_mode = 0;
     config.pubsub_mode = 0;
     config.latency_mode = 0;
+    config.latency_history = 0;
     config.cluster_mode = 0;
     config.slave_mode = 0;
     config.getrdb_mode = 0;