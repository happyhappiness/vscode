@@ -53,9 +53,10 @@ static struct config {
     int hostport;
     const char *hostsocket;
     int numclients;
-    int requests;
     int liveclients;
-    int donerequests;
+    int requests;
+    int requests_issued;
+    int requests_finished;
     int keysize;
     int datasize;
     int randomkeys;
@@ -148,7 +149,7 @@ static void randomizeClientKey(client c) {
 }
 
 static void clientDone(client c) {
-    if (config.donerequests == config.requests) {
+    if (config.requests_finished == config.requests) {
         freeClient(c);
         aeStop(config.el);
         return;
@@ -189,8 +190,8 @@ static void readHandler(aeEventLoop *el, int fd, void *privdata, int mask) {
                 exit(1);
             }
 
-            if (config.donerequests < config.requests)
-                config.latency[config.donerequests++] = c->latency;
+            if (config.requests_finished < config.requests)
+                config.latency[config.requests_finished++] = c->latency;
             clientDone(c);
         }
     }
@@ -202,8 +203,15 @@ static void writeHandler(aeEventLoop *el, int fd, void *privdata, int mask) {
     REDIS_NOTUSED(fd);
     REDIS_NOTUSED(mask);
 
-    /* When nothing was written yet, randomize keys and set start time. */
+    /* Initialize request when nothing was written. */
     if (c->written == 0) {
+        /* Enforce upper bound to number of requests. */
+        if (config.requests_issued++ >= config.requests) {
+            freeClient(c);
+            return;
+        }
+
+        /* Really initialize: randomize keys and set start time. */
         if (config.randomkeys) randomizeClientKey(c);
         c->start = ustime();
         c->latency = -1;
@@ -286,10 +294,10 @@ static void showLatencyReport(void) {
     int i, curlat = 0;
     float perc, reqpersec;
 
-    reqpersec = (float)config.donerequests/((float)config.totlatency/1000);
+    reqpersec = (float)config.requests_finished/((float)config.totlatency/1000);
     if (!config.quiet) {
         printf("====== %s ======\n", config.title);
-        printf("  %d requests completed in %.2f seconds\n", config.donerequests,
+        printf("  %d requests completed in %.2f seconds\n", config.requests_finished,
             (float)config.totlatency/1000);
         printf("  %d parallel clients\n", config.numclients);
         printf("  %d bytes payload\n", config.datasize);
@@ -314,7 +322,8 @@ static void benchmark(const char *title, const char *cmd, int len) {
     client c;
 
     config.title = title;
-    config.donerequests = 0;
+    config.requests_issued = 0;
+    config.requests_finished = 0;
 
     c = createClient(cmd,len);
     createMissingClients(c);
@@ -416,7 +425,7 @@ int showThroughput(struct aeEventLoop *eventLoop, long long id, void *clientData
     REDIS_NOTUSED(clientData);
 
     float dt = (float)(mstime()-config.start)/1000.0;
-    float rps = (float)config.donerequests/dt;
+    float rps = (float)config.requests_finished/dt;
     printf("%s: %.2f\r", config.title, rps);
     fflush(stdout);
     return 250; /* every 250ms */
@@ -438,7 +447,6 @@ int main(int argc, const char **argv) {
     config.el = aeCreateEventLoop();
     aeCreateTimeEvent(config.el,1,showThroughput,NULL,NULL);
     config.keepalive = 1;
-    config.donerequests = 0;
     config.datasize = 3;
     config.randomkeys = 0;
     config.randomkeys_keyspacelen = 0;