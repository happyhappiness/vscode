@@ -428,15 +428,6 @@ int main(int argc, char **argv) {
         prepareForBenchmark();
         c = createClient();
         if (!c) exit(1);
-        c->obuf = sdscat(c->obuf,"PING\r\n");
-        c->replytype = REPLY_RETCODE;
-        createMissingClients(c);
-        aeMain(config.el);
-        endBenchmark("PING");
-
-        prepareForBenchmark();
-        c = createClient();
-        if (!c) exit(1);
         c->obuf = sdscatprintf(c->obuf,"SET foo_rand000000000000 %d\r\n",config.datasize);
         {
             char *data = zmalloc(config.datasize+2);
@@ -488,6 +479,15 @@ int main(int argc, char **argv) {
         aeMain(config.el);
         endBenchmark("LPOP");
 
+        prepareForBenchmark();
+        c = createClient();
+        if (!c) exit(1);
+        c->obuf = sdscat(c->obuf,"PING\r\n");
+        c->replytype = REPLY_RETCODE;
+        createMissingClients(c);
+        aeMain(config.el);
+        endBenchmark("PING");
+
         printf("\n");
     } while(config.loop);
 