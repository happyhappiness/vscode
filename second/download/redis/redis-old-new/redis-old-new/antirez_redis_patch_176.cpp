@@ -65,6 +65,7 @@ static struct config {
     int randomkeys_keyspacelen;
     int keepalive;
     int pipeline;
+    int showerrors;
     long long start;
     long long totlatency;
     long long *latency;
@@ -212,6 +213,16 @@ static void readHandler(aeEventLoop *el, int fd, void *privdata, int mask) {
                     exit(1);
                 }
 
+                if (config.showerrors) {
+                    static time_t lasterr_time = 0;
+                    time_t now = time(NULL);
+                    redisReply *r = reply;
+                    if (r->type == REDIS_REPLY_ERROR && lasterr_time != now) {
+                        lasterr_time = now;
+                        printf("Error from server: %s\n", r->str);
+                    }
+                }
+
                 freeReplyObject(reply);
                 /* This is an OK for prefix commands such as auth and select.*/
                 if (c->prefix_pending > 0) {
@@ -227,7 +238,7 @@ static void readHandler(aeEventLoop *el, int fd, void *privdata, int mask) {
                             c->randptr[j] -= c->prefixlen;
                         c->prefixlen = 0;
                     }
-                    continue;                
+                    continue;
                 }
 
                 if (config.requests_finished < config.requests)
@@ -518,6 +529,8 @@ int parseOptions(int argc, const char **argv) {
             config.loop = 1;
         } else if (!strcmp(argv[i],"-I")) {
             config.idlemode = 1;
+        } else if (!strcmp(argv[i],"-e")) {
+            config.showerrors = 1;
         } else if (!strcmp(argv[i],"-t")) {
             if (lastarg) goto invalid;
             /* We get the list of tests to run as a string in the form
@@ -569,6 +582,8 @@ int parseOptions(int argc, const char **argv) {
 "  is executed. Default tests use this to hit random keys in the\n"
 "  specified range.\n"
 " -P <numreq>        Pipeline <numreq> requests. Default 1 (no pipeline).\n"
+" -e                 If server replies with errors, show them on stdout.\n"
+"                    (no more than 1 error per second is displayed)\n"
 " -q                 Quiet. Just show query/sec values\n"
 " --csv              Output in CSV format\n"
 " -l                 Loop. Run the tests forever\n"
@@ -649,6 +664,7 @@ int main(int argc, const char **argv) {
     config.keepalive = 1;
     config.datasize = 3;
     config.pipeline = 1;
+    config.showerrors = 0;
     config.randomkeys = 0;
     config.randomkeys_keyspacelen = 0;
     config.quiet = 0;