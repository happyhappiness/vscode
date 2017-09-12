@@ -397,6 +397,7 @@ int showThroughput(struct aeEventLoop *eventLoop, long long id, void *clientData
 }
 
 int main(int argc, char **argv) {
+    int i;
     client c;
 
     signal(SIGHUP, SIG_IGN);
@@ -440,6 +441,10 @@ int main(int argc, char **argv) {
     }
 
     do {
+        char *data = zmalloc(config.datasize+1);
+        memset(data,'x',config.datasize);
+        data[config.datasize] = '\0';
+
         prepareForBenchmark("PING");
         c = createClient(REDIS_REPLY_STATUS);
         c->obuf = sdscat(c->obuf,"PING\r\n");
@@ -457,31 +462,16 @@ int main(int argc, char **argv) {
         prepareForBenchmark("MSET (10 keys, multi bulk)");
         c = createClient(REDIS_REPLY_ARRAY);
         c->obuf = sdscatprintf(c->obuf,"*%d\r\n$4\r\nMSET\r\n", 11);
-        {
-            int i;
-            char *data = zmalloc(config.datasize+1);
-            memset(data,'x',config.datasize);
-            data[config.datasize] = '\0';
-            for (i = 0; i < 10; i++) {
-                c->obuf = sdscatprintf(c->obuf,"$%d\r\n%s\r\n",config.datasize,data);
-            }
-            zfree(data);
-        }
+        for (i = 0; i < 10; i++) {
+            c->obuf = sdscatprintf(c->obuf,"$%d\r\n%s\r\n",config.datasize,data);
         createMissingClients(c);
         aeMain(config.el);
         endBenchmark();
 
         prepareForBenchmark("SET");
         c = createClient(REDIS_REPLY_STATUS);
         c->obuf = sdscat(c->obuf,"*3\r\n$3\r\nSET\r\n$20\r\nfoo_rand000000000000\r\n");
-        {
-            char *data = zmalloc(config.datasize+2);
-            memset(data,'x',config.datasize);
-            data[config.datasize] = '\r';
-            data[config.datasize+1] = '\n';
-            c->obuf = sdscatprintf(c->obuf,"$%d\r\n",config.datasize);
-            c->obuf = sdscatlen(c->obuf,data,config.datasize+2);
-        }
+        c->obuf = sdscatprintf(c->obuf,"$%d\r\n%s\r\n",config.datasize,data);
         createMissingClients(c);
         aeMain(config.el);
         endBenchmark();