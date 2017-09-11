@@ -71,6 +71,7 @@ static struct config {
     int csv;
     int loop;
     int idlemode;
+    char *tests;
 } config;
 
 typedef struct _client {
@@ -385,6 +386,17 @@ int parseOptions(int argc, const char **argv) {
             config.loop = 1;
         } else if (!strcmp(argv[i],"-I")) {
             config.idlemode = 1;
+        } else if (!strcmp(argv[i],"-t")) {
+            if (lastarg) goto invalid;
+            /* We get the list of tests to run as a string in the form
+             * get,set,lrange,...,test_N. Then we add a comma before and
+             * after the string in order to make sure that searching
+             * for ",testname," will always get a match if the test is
+             * enabled. */
+            config.tests = sdsnew(",");
+            config.tests = sdscat(config.tests,(char*)argv[++i]);
+            config.tests = sdscat(config.tests,",");
+            sdstolower(config.tests);
         } else if (!strcmp(argv[i],"--help")) {
             exit_status = 0;
             goto usage;
@@ -403,25 +415,38 @@ int parseOptions(int argc, const char **argv) {
     printf("Invalid option \"%s\" or option argument missing\n\n",argv[i]);
 
 usage:
-    printf("Usage: redis-benchmark [-h <host>] [-p <port>] [-c <clients>] [-n <requests]> [-k <boolean>]\n\n");
-    printf(" -h <hostname>      Server hostname (default 127.0.0.1)\n");
-    printf(" -p <port>          Server port (default 6379)\n");
-    printf(" -s <socket>        Server socket (overrides host and port)\n");
-    printf(" -c <clients>       Number of parallel connections (default 50)\n");
-    printf(" -n <requests>      Total number of requests (default 10000)\n");
-    printf(" -d <size>          Data size of SET/GET value in bytes (default 2)\n");
-    printf(" -k <boolean>       1=keep alive 0=reconnect (default 1)\n");
-    printf(" -r <keyspacelen>   Use random keys for SET/GET/INCR, random values for SADD\n");
-    printf("  Using this option the benchmark will get/set keys\n");
-    printf("  in the form mykey_rand000000012456 instead of constant\n");
-    printf("  keys, the <keyspacelen> argument determines the max\n");
-    printf("  number of values for the random number. For instance\n");
-    printf("  if set to 10 only rand000000000000 - rand000000000009\n");
-    printf("  range will be allowed.\n");
-    printf(" -q                 Quiet. Just show query/sec values\n");
-    printf(" --csv              Output in CSV format\n");
-    printf(" -l                 Loop. Run the tests forever\n");
-    printf(" -I                 Idle mode. Just open N idle connections and wait.\n");
+    printf(
+"Usage: redis-benchmark [-h <host>] [-p <port>] [-c <clients>] [-n <requests]> [-k <boolean>]\n\n"
+" -h <hostname>      Server hostname (default 127.0.0.1)\n"
+" -p <port>          Server port (default 6379)\n"
+" -s <socket>        Server socket (overrides host and port)\n"
+" -c <clients>       Number of parallel connections (default 50)\n"
+" -n <requests>      Total number of requests (default 10000)\n"
+" -d <size>          Data size of SET/GET value in bytes (default 2)\n"
+" -k <boolean>       1=keep alive 0=reconnect (default 1)\n"
+" -r <keyspacelen>   Use random keys for SET/GET/INCR, random values for SADD\n"
+"  Using this option the benchmark will get/set keys\n"
+"  in the form mykey_rand000000012456 instead of constant\n"
+"  keys, the <keyspacelen> argument determines the max\n"
+"  number of values for the random number. For instance\n"
+"  if set to 10 only rand000000000000 - rand000000000009\n"
+"  range will be allowed.\n"
+" -q                 Quiet. Just show query/sec values\n"
+" --csv              Output in CSV format\n"
+" -l                 Loop. Run the tests forever\n"
+" -t <tests>         Only run the comma separated list of tests. The test\n"
+"                    names are the same as the ones produced as output.\n"
+" -I                 Idle mode. Just open N idle connections and wait.\n\n"
+"Examples:\n\n"
+" Run the benchmark with the default configuration against 127.0.0.1:6379:\n"
+"   $ redis-benchmark\n\n"
+" Use 20 parallel clients, for a total of 100k requests, against 192.168.1.1:\n"
+"   $ redis-benchmark -h 192.168.1.1 -p 6379 -n 100000 -c 20\n\n"
+" Fill 127.0.0.1:6379 with about 1 million keys only using the SET test:\n"
+"   $ redis-benchmark -t set -n 1000000 -r 100000000\n\n"
+" Benchmark 127.0.0.1:6379 for a few commands producing CSV output:\n"
+"   $ redis-benchmark -t ping,set,get -n 100000 --csv\n\n"
+    );
     exit(exit_status);
 }
 
@@ -438,6 +463,20 @@ int showThroughput(struct aeEventLoop *eventLoop, long long id, void *clientData
     return 250; /* every 250ms */
 }
 
+/* Return true if the named test was selected using the -t command line
+ * switch, or if all the tests are selected (no -t passed by user). */
+int test_is_selected(char *name) {
+    char buf[256];
+    int l = strlen(name);
+
+    if (config.tests == NULL) return 1;
+    buf[0] = ',';
+    memcpy(buf+1,name,l);
+    buf[l+1] = ',';
+    buf[l+2] = '\0';
+    return strstr(config.tests,buf) != NULL;
+}
+
 int main(int argc, const char **argv) {
     int i;
     char *data, *cmd;
@@ -466,6 +505,7 @@ int main(int argc, const char **argv) {
     config.hostip = "127.0.0.1";
     config.hostport = 6379;
     config.hostsocket = NULL;
+    config.tests = NULL;
 
     i = parseOptions(argc,argv);
     argc -= i;
@@ -508,69 +548,104 @@ int main(int argc, const char **argv) {
         memset(data,'x',config.datasize);
         data[config.datasize] = '\0';
 
-        benchmark("PING (inline)","PING\r\n",6);
+        if (test_is_selected("ping_inline") || test_is_selected("ping"))
+            benchmark("PING_INLINE","PING\r\n",6);
 
-        len = redisFormatCommand(&cmd,"PING");
-        benchmark("PING",cmd,len);
-        free(cmd);
+        if (test_is_selected("ping_mbulk") || test_is_selected("ping")) {
+            len = redisFormatCommand(&cmd,"PING");
+            benchmark("PING_BULK",cmd,len);
+            free(cmd);
+        }
 
-        const char *argv[21];
-        argv[0] = "MSET";
-        for (i = 1; i < 21; i += 2) {
-            argv[i] = "foo:rand:000000000000";
-            argv[i+1] = data;
+        if (test_is_selected("set")) {
+            len = redisFormatCommand(&cmd,"SET foo:rand:000000000000 %s",data);
+            benchmark("SET",cmd,len);
+            free(cmd);
         }
-        len = redisFormatCommandArgv(&cmd,21,argv,NULL);
-        benchmark("MSET (10 keys)",cmd,len);
-        free(cmd);
 
-        len = redisFormatCommand(&cmd,"SET foo:rand:000000000000 %s",data);
-        benchmark("SET",cmd,len);
-        free(cmd);
+        if (test_is_selected("get")) {
+            len = redisFormatCommand(&cmd,"GET foo:rand:000000000000");
+            benchmark("GET",cmd,len);
+            free(cmd);
+        }
 
-        len = redisFormatCommand(&cmd,"GET foo:rand:000000000000");
-        benchmark("GET",cmd,len);
-        free(cmd);
+        if (test_is_selected("incr")) {
+            len = redisFormatCommand(&cmd,"INCR counter:rand:000000000000");
+            benchmark("INCR",cmd,len);
+            free(cmd);
+        }
 
-        len = redisFormatCommand(&cmd,"INCR counter:rand:000000000000");
-        benchmark("INCR",cmd,len);
-        free(cmd);
+        if (test_is_selected("lpush")) {
+            len = redisFormatCommand(&cmd,"LPUSH mylist %s",data);
+            benchmark("LPUSH",cmd,len);
+            free(cmd);
+        }
 
-        len = redisFormatCommand(&cmd,"LPUSH mylist %s",data);
-        benchmark("LPUSH",cmd,len);
-        free(cmd);
+        if (test_is_selected("lpop")) {
+            len = redisFormatCommand(&cmd,"LPOP mylist");
+            benchmark("LPOP",cmd,len);
+            free(cmd);
+        }
 
-        len = redisFormatCommand(&cmd,"LPOP mylist");
-        benchmark("LPOP",cmd,len);
-        free(cmd);
+        if (test_is_selected("sadd")) {
+            len = redisFormatCommand(&cmd,
+                "SADD myset counter:rand:000000000000");
+            benchmark("SADD",cmd,len);
+            free(cmd);
+        }
 
-        len = redisFormatCommand(&cmd,"SADD myset counter:rand:000000000000");
-        benchmark("SADD",cmd,len);
-        free(cmd);
+        if (test_is_selected("spop")) {
+            len = redisFormatCommand(&cmd,"SPOP myset");
+            benchmark("SPOP",cmd,len);
+            free(cmd);
+        }
 
-        len = redisFormatCommand(&cmd,"SPOP myset");
-        benchmark("SPOP",cmd,len);
-        free(cmd);
+        if (test_is_selected("lrange") ||
+            test_is_selected("lrange_100") ||
+            test_is_selected("lrange_300") ||
+            test_is_selected("lrange_500") ||
+            test_is_selected("lrange_600"))
+        {
+            len = redisFormatCommand(&cmd,"LPUSH mylist %s",data);
+            benchmark("LPUSH (needed to benchmark LRANGE)",cmd,len);
+            free(cmd);
+        }
 
-        len = redisFormatCommand(&cmd,"LPUSH mylist %s",data);
-        benchmark("LPUSH (again, in order to bench LRANGE)",cmd,len);
-        free(cmd);
+        if (test_is_selected("lrange") || test_is_selected("lrange_100")) {
+            len = redisFormatCommand(&cmd,"LRANGE mylist 0 99");
+            benchmark("LRANGE_100 (first 100 elements)",cmd,len);
+            free(cmd);
+        }
 
-        len = redisFormatCommand(&cmd,"LRANGE mylist 0 99");
-        benchmark("LRANGE (first 100 elements)",cmd,len);
-        free(cmd);
+        if (test_is_selected("lrange") || test_is_selected("lrange_300")) {
+            len = redisFormatCommand(&cmd,"LRANGE mylist 0 299");
+            benchmark("LRANGE_300 (first 300 elements)",cmd,len);
+            free(cmd);
+        }
 
-        len = redisFormatCommand(&cmd,"LRANGE mylist 0 299");
-        benchmark("LRANGE (first 300 elements)",cmd,len);
-        free(cmd);
+        if (test_is_selected("lrange") || test_is_selected("lrange_500")) {
+            len = redisFormatCommand(&cmd,"LRANGE mylist 0 449");
+            benchmark("LRANGE_500 (first 450 elements)",cmd,len);
+            free(cmd);
+        }
 
-        len = redisFormatCommand(&cmd,"LRANGE mylist 0 449");
-        benchmark("LRANGE (first 450 elements)",cmd,len);
-        free(cmd);
+        if (test_is_selected("lrange") || test_is_selected("lrange_600")) {
+            len = redisFormatCommand(&cmd,"LRANGE mylist 0 599");
+            benchmark("LRANGE_600 (first 600 elements)",cmd,len);
+            free(cmd);
+        }
 
-        len = redisFormatCommand(&cmd,"LRANGE mylist 0 599");
-        benchmark("LRANGE (first 600 elements)",cmd,len);
-        free(cmd);
+        if (test_is_selected("mset")) {
+            const char *argv[21];
+            argv[0] = "MSET";
+            for (i = 1; i < 21; i += 2) {
+                argv[i] = "foo:rand:000000000000";
+                argv[i+1] = data;
+            }
+            len = redisFormatCommandArgv(&cmd,21,argv,NULL);
+            benchmark("MSET (10 keys)",cmd,len);
+            free(cmd);
+        }
 
         if (!config.csv) printf("\n");
     } while(config.loop);