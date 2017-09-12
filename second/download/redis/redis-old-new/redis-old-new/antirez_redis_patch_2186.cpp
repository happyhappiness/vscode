@@ -464,7 +464,7 @@ void parseOptions(int argc, char **argv) {
             printf(" -n <requests>      Total number of requests (default 10000)\n");
             printf(" -d <size>          Data size of SET/GET value in bytes (default 2)\n");
             printf(" -k <boolean>       1=keep alive 0=reconnect (default 1)\n");
-            printf(" -r <keyspacelen>   Use random keys for SET/GET/INCR\n");
+            printf(" -r <keyspacelen>   Use random keys for SET/GET/INCR, random values for SADD\n");
             printf("  Using this option the benchmark will get/set keys\n");
             printf("  in the form mykey_rand000000012456 instead of constant\n");
             printf("  keys, the <keyspacelen> argument determines the max\n");
@@ -598,6 +598,24 @@ int main(int argc, char **argv) {
         prepareForBenchmark();
         c = createClient();
         if (!c) exit(1);
+        c->obuf = sdscat(c->obuf,"SADD myset 24\r\ncounter_rand000000000000\r\n");
+        prepareClientForReply(c,REPLY_RETCODE);
+        createMissingClients(c);
+        aeMain(config.el);
+        endBenchmark("SADD");
+
+        prepareForBenchmark();
+        c = createClient();
+        if (!c) exit(1);
+        c->obuf = sdscat(c->obuf,"SPOP myset\r\n");
+        prepareClientForReply(c,REPLY_BULK);
+        createMissingClients(c);
+        aeMain(config.el);
+        endBenchmark("SPOP");
+
+        prepareForBenchmark();
+        c = createClient();
+        if (!c) exit(1);
         c->obuf = sdscat(c->obuf,"LPUSH mylist 3\r\nbar\r\n");
         prepareClientForReply(c,REPLY_RETCODE);
         createMissingClients(c);