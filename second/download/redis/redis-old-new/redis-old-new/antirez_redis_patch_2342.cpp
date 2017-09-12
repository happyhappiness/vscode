@@ -62,6 +62,7 @@ static struct config {
     int donerequests;
     int keysize;
     int datasize;
+    int randomkeys;
     aeEventLoop *el;
     char *hostip;
     int hostport;
@@ -341,6 +342,8 @@ void parseOptions(int argc, char **argv) {
             i++;
             if (config.datasize < 1) config.datasize=1;
             if (config.datasize > 1024*1024) config.datasize = 1024*1024;
+        } else if (!strcmp(argv[i],"-r")) {
+            config.randomkeys = 1;
         } else if (!strcmp(argv[i],"-q")) {
             config.quiet = 1;
         } else if (!strcmp(argv[i],"-l")) {
@@ -354,6 +357,7 @@ void parseOptions(int argc, char **argv) {
             printf(" -n <requests>      Total number of requests (default 10000)\n");
             printf(" -d <size>          Data size of SET/GET value in bytes (default 2)\n");
             printf(" -k <boolean>       1=keep alive 0=reconnect (default 1)\n");
+            printf(" -r                 Use random keys for SET/GET/INCR\n");
             printf(" -q                 Quiet. Just show query/sec values\n");
             printf(" -l                 Loop. Run the tests forever\n");
             exit(1);
@@ -374,6 +378,7 @@ int main(int argc, char **argv) {
     config.keepalive = 1;
     config.donerequests = 0;
     config.datasize = 3;
+    config.randomkeys = 0;
     config.quiet = 0;
     config.loop = 0;
     config.latency = NULL;
@@ -402,7 +407,7 @@ int main(int argc, char **argv) {
         prepareForBenchmark();
         c = createClient();
         if (!c) exit(1);
-        c->obuf = sdscatprintf(c->obuf,"SET foo %d\r\n",config.datasize);
+        c->obuf = sdscatprintf(c->obuf,"SET foo_rand000000000000 %d\r\n",config.datasize);
         {
             char *data = zmalloc(config.datasize+2);
             memset(data,'x',config.datasize);
@@ -418,7 +423,7 @@ int main(int argc, char **argv) {
         prepareForBenchmark();
         c = createClient();
         if (!c) exit(1);
-        c->obuf = sdscat(c->obuf,"GET foo\r\n");
+        c->obuf = sdscat(c->obuf,"GET foo_rand000000000000\r\n");
         c->replytype = REPLY_BULK;
         c->readlen = -1;
         createMissingClients(c);
@@ -428,7 +433,7 @@ int main(int argc, char **argv) {
         prepareForBenchmark();
         c = createClient();
         if (!c) exit(1);
-        c->obuf = sdscat(c->obuf,"INCR counter\r\n");
+        c->obuf = sdscat(c->obuf,"INCR counter_rand000000000000\r\n");
         c->replytype = REPLY_INT;
         createMissingClients(c);
         aeMain(config.el);