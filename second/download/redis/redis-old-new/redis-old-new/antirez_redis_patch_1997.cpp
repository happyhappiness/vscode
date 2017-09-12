@@ -75,6 +75,7 @@ static struct config {
     long long start;
     long long totlatency;
     int *latency;
+    char *title;
     list *clients;
     int quiet;
     int loop;
@@ -389,13 +390,13 @@ static void createMissingClients(client c) {
     }
 }
 
-static void showLatencyReport(char *title) {
+static void showLatencyReport(void) {
     int j, seen = 0;
     float perc, reqpersec;
 
     reqpersec = (float)config.donerequests/((float)config.totlatency/1000);
     if (!config.quiet) {
-        printf("====== %s ======\n", title);
+        printf("====== %s ======\n", config.title);
         printf("  %d requests completed in %.2f seconds\n", config.donerequests,
             (float)config.totlatency/1000);
         printf("  %d parallel clients\n", config.numclients);
@@ -411,20 +412,20 @@ static void showLatencyReport(char *title) {
         }
         printf("%.2f requests per second\n\n", reqpersec);
     } else {
-        printf("%s: %.2f requests per second\n", title, reqpersec);
+        printf("%s: %.2f requests per second\n", config.title, reqpersec);
     }
 }
 
-static void prepareForBenchmark(void)
-{
+static void prepareForBenchmark(char *title) {
     memset(config.latency,0,sizeof(int)*(MAX_LATENCY+1));
+    config.title = title;
     config.start = mstime();
     config.donerequests = 0;
 }
 
-static void endBenchmark(char *title) {
+static void endBenchmark(void) {
     config.totlatency = mstime()-config.start;
-    showLatencyReport(title);
+    showLatencyReport();
     freeAllClients();
 }
 
@@ -498,6 +499,18 @@ void parseOptions(int argc, char **argv) {
     }
 }
 
+int showThroughput(struct aeEventLoop *eventLoop, long long id, void *clientData) {
+    REDIS_NOTUSED(eventLoop);
+    REDIS_NOTUSED(id);
+    REDIS_NOTUSED(clientData);
+
+    float dt = (float)(mstime()-config.start)/1000.0;
+    float rps = (float)config.donerequests/dt;
+    printf("%s: %.2f\r", config.title, rps);
+    fflush(stdout);
+    return 250; /* every 250ms */
+}
+
 int main(int argc, char **argv) {
     client c;
 
@@ -509,6 +522,7 @@ int main(int argc, char **argv) {
     config.requests = 10000;
     config.liveclients = 0;
     config.el = aeCreateEventLoop();
+    aeCreateTimeEvent(config.el,1,showThroughput,NULL,NULL);
     config.keepalive = 1;
     config.donerequests = 0;
     config.datasize = 3;
@@ -532,7 +546,7 @@ int main(int argc, char **argv) {
 
     if (config.idlemode) {
         printf("Creating %d idle connections and waiting forever (Ctrl+C when done)\n", config.numclients);
-        prepareForBenchmark();
+        prepareForBenchmark("IDLE");
         c = createClient();
         if (!c) exit(1);
         c->obuf = sdsempty();
@@ -543,25 +557,25 @@ int main(int argc, char **argv) {
     }
 
     do {
-        prepareForBenchmark();
+        prepareForBenchmark("PING");
         c = createClient();
         if (!c) exit(1);
         c->obuf = sdscat(c->obuf,"PING\r\n");
         prepareClientForReply(c,REPLY_RETCODE);
         createMissingClients(c);
         aeMain(config.el);
-        endBenchmark("PING");
+        endBenchmark();
 
-        prepareForBenchmark();
+        prepareForBenchmark("PING (multi bulk)");
         c = createClient();
         if (!c) exit(1);
         c->obuf = sdscat(c->obuf,"*1\r\n$4\r\nPING\r\n");
         prepareClientForReply(c,REPLY_RETCODE);
         createMissingClients(c);
         aeMain(config.el);
-        endBenchmark("PING (multi bulk)");
+        endBenchmark();
 
-        prepareForBenchmark();
+        prepareForBenchmark("SET");
         c = createClient();
         if (!c) exit(1);
         c->obuf = sdscatprintf(c->obuf,"SET foo_rand000000000000 %d\r\n",config.datasize);
@@ -575,106 +589,106 @@ int main(int argc, char **argv) {
         prepareClientForReply(c,REPLY_RETCODE);
         createMissingClients(c);
         aeMain(config.el);
-        endBenchmark("SET");
+        endBenchmark();
 
-        prepareForBenchmark();
+        prepareForBenchmark("GET");
         c = createClient();
         if (!c) exit(1);
         c->obuf = sdscat(c->obuf,"GET foo_rand000000000000\r\n");
         prepareClientForReply(c,REPLY_BULK);
         createMissingClients(c);
         aeMain(config.el);
-        endBenchmark("GET");
+        endBenchmark();
 
-        prepareForBenchmark();
+        prepareForBenchmark("INCR");
         c = createClient();
         if (!c) exit(1);
         c->obuf = sdscat(c->obuf,"INCR counter_rand000000000000\r\n");
         prepareClientForReply(c,REPLY_INT);
         createMissingClients(c);
         aeMain(config.el);
-        endBenchmark("INCR");
+        endBenchmark();
 
-        prepareForBenchmark();
+        prepareForBenchmark("LPUSH");
         c = createClient();
         if (!c) exit(1);
         c->obuf = sdscat(c->obuf,"LPUSH mylist 3\r\nbar\r\n");
         prepareClientForReply(c,REPLY_INT);
         createMissingClients(c);
         aeMain(config.el);
-        endBenchmark("LPUSH");
+        endBenchmark();
 
-        prepareForBenchmark();
+        prepareForBenchmark("LPOP");
         c = createClient();
         if (!c) exit(1);
         c->obuf = sdscat(c->obuf,"LPOP mylist\r\n");
         prepareClientForReply(c,REPLY_BULK);
         createMissingClients(c);
         aeMain(config.el);
-        endBenchmark("LPOP");
+        endBenchmark();
 
-        prepareForBenchmark();
+        prepareForBenchmark("SADD");
         c = createClient();
         if (!c) exit(1);
         c->obuf = sdscat(c->obuf,"SADD myset 24\r\ncounter_rand000000000000\r\n");
         prepareClientForReply(c,REPLY_RETCODE);
         createMissingClients(c);
         aeMain(config.el);
-        endBenchmark("SADD");
+        endBenchmark();
 
-        prepareForBenchmark();
+        prepareForBenchmark("SPOP");
         c = createClient();
         if (!c) exit(1);
         c->obuf = sdscat(c->obuf,"SPOP myset\r\n");
         prepareClientForReply(c,REPLY_BULK);
         createMissingClients(c);
         aeMain(config.el);
-        endBenchmark("SPOP");
+        endBenchmark();
 
-        prepareForBenchmark();
+        prepareForBenchmark("LPUSH (again, in order to bench LRANGE)");
         c = createClient();
         if (!c) exit(1);
         c->obuf = sdscat(c->obuf,"LPUSH mylist 3\r\nbar\r\n");
         prepareClientForReply(c,REPLY_RETCODE);
         createMissingClients(c);
         aeMain(config.el);
-        endBenchmark("LPUSH (again, in order to bench LRANGE)");
+        endBenchmark();
 
-        prepareForBenchmark();
+        prepareForBenchmark("LRANGE (first 100 elements)");
         c = createClient();
         if (!c) exit(1);
         c->obuf = sdscat(c->obuf,"LRANGE mylist 0 99\r\n");
         prepareClientForReply(c,REPLY_MBULK);
         createMissingClients(c);
         aeMain(config.el);
-        endBenchmark("LRANGE (first 100 elements)");
+        endBenchmark();
 
-        prepareForBenchmark();
+        prepareForBenchmark("LRANGE (first 300 elements)");
         c = createClient();
         if (!c) exit(1);
         c->obuf = sdscat(c->obuf,"LRANGE mylist 0 299\r\n");
         prepareClientForReply(c,REPLY_MBULK);
         createMissingClients(c);
         aeMain(config.el);
-        endBenchmark("LRANGE (first 300 elements)");
+        endBenchmark();
 
-        prepareForBenchmark();
+        prepareForBenchmark("LRANGE (first 450 elements)");
         c = createClient();
         if (!c) exit(1);
         c->obuf = sdscat(c->obuf,"LRANGE mylist 0 449\r\n");
         prepareClientForReply(c,REPLY_MBULK);
         createMissingClients(c);
         aeMain(config.el);
-        endBenchmark("LRANGE (first 450 elements)");
+        endBenchmark();
 
-        prepareForBenchmark();
+        prepareForBenchmark("LRANGE (first 600 elements)");
         c = createClient();
         if (!c) exit(1);
         c->obuf = sdscat(c->obuf,"LRANGE mylist 0 599\r\n");
         prepareClientForReply(c,REPLY_MBULK);
         createMissingClients(c);
         aeMain(config.el);
-        endBenchmark("LRANGE (first 600 elements)");
+        endBenchmark();
 
         printf("\n");
     } while(config.loop);