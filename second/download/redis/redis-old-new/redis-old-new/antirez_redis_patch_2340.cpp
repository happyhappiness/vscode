@@ -63,6 +63,7 @@ static struct config {
     int keysize;
     int datasize;
     int randomkeys;
+    int randomkeys_keyspacelen;
     aeEventLoop *el;
     char *hostip;
     int hostport;
@@ -138,6 +139,19 @@ static void resetClient(client c) {
     c->start = mstime();
 }
 
+static void randomizeClientKey(client c) {
+    char *p;
+    char buf[32];
+    long r;
+
+    p = strstr(c->obuf, "_rand");
+    if (!p) return;
+    p += 5;
+    r = random() % config.randomkeys_keyspacelen;
+    sprintf(buf,"%ld",r);
+    memcpy(p,buf,strlen(buf));
+}
+
 static void clientDone(client c) {
     long long latency;
     config.donerequests ++;
@@ -152,6 +166,7 @@ static void clientDone(client c) {
     }
     if (config.keepalive) {
         resetClient(c);
+        if (config.randomkeys) randomizeClientKey(c);
     } else {
         config.liveclients--;
         createMissingClients(c);
@@ -192,7 +207,7 @@ static void readHandler(aeEventLoop *el, int fd, void *privdata, int mask)
                 *p = '\0';
                 *(p-1) = '\0';
                 c->readlen = atoi(c->ibuf+1)+2;
-                if (c->readlen == -1) {
+                if (c->readlen-2 == -1) {
                     clientDone(c);
                     return;
                 }
@@ -266,6 +281,7 @@ static void createMissingClients(client c) {
         if (!new) continue;
         sdsfree(new->obuf);
         new->obuf = sdsdup(c->obuf);
+        if (config.randomkeys) randomizeClientKey(c);
         new->replytype = c->replytype;
         if (c->replytype == REPLY_BULK)
             new->readlen = -1;
@@ -342,8 +358,12 @@ void parseOptions(int argc, char **argv) {
             i++;
             if (config.datasize < 1) config.datasize=1;
             if (config.datasize > 1024*1024) config.datasize = 1024*1024;
-        } else if (!strcmp(argv[i],"-r")) {
+        } else if (!strcmp(argv[i],"-r") && !lastarg) {
             config.randomkeys = 1;
+            config.randomkeys_keyspacelen = atoi(argv[i+1]);
+            if (config.randomkeys_keyspacelen < 0)
+                config.randomkeys_keyspacelen = 0;
+            i++;
         } else if (!strcmp(argv[i],"-q")) {
             config.quiet = 1;
         } else if (!strcmp(argv[i],"-l")) {
@@ -357,7 +377,13 @@ void parseOptions(int argc, char **argv) {
             printf(" -n <requests>      Total number of requests (default 10000)\n");
             printf(" -d <size>          Data size of SET/GET value in bytes (default 2)\n");
             printf(" -k <boolean>       1=keep alive 0=reconnect (default 1)\n");
-            printf(" -r                 Use random keys for SET/GET/INCR\n");
+            printf(" -r <keyspacelen>   Use random keys for SET/GET/INCR\n");
+            printf("  Using this option the benchmark will get/set keys\n");
+            printf("  in the form mykey_rand000000012456 instead of constant\n");
+            printf("  keys, the <keyspacelen> argument determines the max\n");
+            printf("  number of values for the random number. For instance\n");
+            printf("  if set to 10 only rand000000000000 - rand000000000009\n");
+            printf("  range will be allowed.\n");
             printf(" -q                 Quiet. Just show query/sec values\n");
             printf(" -l                 Loop. Run the tests forever\n");
             exit(1);
@@ -379,6 +405,7 @@ int main(int argc, char **argv) {
     config.donerequests = 0;
     config.datasize = 3;
     config.randomkeys = 0;
+    config.randomkeys_keyspacelen = 0;
     config.quiet = 0;
     config.loop = 0;
     config.latency = NULL;