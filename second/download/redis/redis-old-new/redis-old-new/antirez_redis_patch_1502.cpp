@@ -68,6 +68,7 @@ static struct config {
     const char *title;
     list *clients;
     int quiet;
+    int csv;
     int loop;
     int idlemode;
 } config;
@@ -295,7 +296,7 @@ static void showLatencyReport(void) {
     float perc, reqpersec;
 
     reqpersec = (float)config.requests_finished/((float)config.totlatency/1000);
-    if (!config.quiet) {
+    if (!config.quiet && !config.csv) {
         printf("====== %s ======\n", config.title);
         printf("  %d requests completed in %.2f seconds\n", config.requests_finished,
             (float)config.totlatency/1000);
@@ -313,6 +314,8 @@ static void showLatencyReport(void) {
             }
         }
         printf("%.2f requests per second\n\n", reqpersec);
+    } else if (config.csv) {
+        printf("\"%s\",\"%.2f\"\n", config.title, reqpersec);
     } else {
         printf("%s: %.2f requests per second\n", config.title, reqpersec);
     }
@@ -376,6 +379,8 @@ int parseOptions(int argc, const char **argv) {
                 config.randomkeys_keyspacelen = 0;
         } else if (!strcmp(argv[i],"-q")) {
             config.quiet = 1;
+        } else if (!strcmp(argv[i],"--csv")) {
+            config.csv = 1;
         } else if (!strcmp(argv[i],"-l")) {
             config.loop = 1;
         } else if (!strcmp(argv[i],"-I")) {
@@ -414,6 +419,7 @@ int parseOptions(int argc, const char **argv) {
     printf("  if set to 10 only rand000000000000 - rand000000000009\n");
     printf("  range will be allowed.\n");
     printf(" -q                 Quiet. Just show query/sec values\n");
+    printf(" --csv              Output in CSV format\n");
     printf(" -l                 Loop. Run the tests forever\n");
     printf(" -I                 Idle mode. Just open N idle connections and wait.\n");
     exit(exit_status);
@@ -424,6 +430,7 @@ int showThroughput(struct aeEventLoop *eventLoop, long long id, void *clientData
     REDIS_NOTUSED(id);
     REDIS_NOTUSED(clientData);
 
+    if (config.csv) return 250;
     float dt = (float)(mstime()-config.start)/1000.0;
     float rps = (float)config.requests_finished/dt;
     printf("%s: %.2f\r", config.title, rps);
@@ -451,6 +458,7 @@ int main(int argc, const char **argv) {
     config.randomkeys = 0;
     config.randomkeys_keyspacelen = 0;
     config.quiet = 0;
+    config.csv = 0;
     config.loop = 0;
     config.idlemode = 0;
     config.latency = NULL;
@@ -564,7 +572,7 @@ int main(int argc, const char **argv) {
         benchmark("LRANGE (first 600 elements)",cmd,len);
         free(cmd);
 
-        printf("\n");
+        if (!config.csv) printf("\n");
     } while(config.loop);
 
     return 0;