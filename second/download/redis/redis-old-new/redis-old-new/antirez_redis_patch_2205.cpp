@@ -528,6 +528,24 @@ int main(int argc, char **argv) {
         prepareForBenchmark();
         c = createClient();
         if (!c) exit(1);
+        c->obuf = sdscat(c->obuf,"PING\r\n");
+        prepareClientForReply(c,REPLY_RETCODE);
+        createMissingClients(c);
+        aeMain(config.el);
+        endBenchmark("PING");
+
+        prepareForBenchmark();
+        c = createClient();
+        if (!c) exit(1);
+        c->obuf = sdscat(c->obuf,"*1\r\n$4\r\nPING\r\n");
+        prepareClientForReply(c,REPLY_RETCODE);
+        createMissingClients(c);
+        aeMain(config.el);
+        endBenchmark("PING (multi bulk)");
+
+        prepareForBenchmark();
+        c = createClient();
+        if (!c) exit(1);
         c->obuf = sdscatprintf(c->obuf,"SET foo_rand000000000000 %d\r\n",config.datasize);
         {
             char *data = zmalloc(config.datasize+2);
@@ -580,15 +598,6 @@ int main(int argc, char **argv) {
         prepareForBenchmark();
         c = createClient();
         if (!c) exit(1);
-        c->obuf = sdscat(c->obuf,"PING\r\n");
-        prepareClientForReply(c,REPLY_RETCODE);
-        createMissingClients(c);
-        aeMain(config.el);
-        endBenchmark("PING");
-
-        prepareForBenchmark();
-        c = createClient();
-        if (!c) exit(1);
         c->obuf = sdscat(c->obuf,"LPUSH mylist 3\r\nbar\r\n");
         prepareClientForReply(c,REPLY_RETCODE);
         createMissingClients(c);