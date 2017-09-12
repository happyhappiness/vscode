@@ -565,6 +565,15 @@ int main(int argc, char **argv) {
         aeMain(config.el);
         endBenchmark("LRANGE (first 100 elements)");
 
+        prepareForBenchmark();
+        c = createClient();
+        if (!c) exit(1);
+        c->obuf = sdscat(c->obuf,"LRANGE mylist 0 299\r\n");
+        prepareClientForReply(c,REPLY_MBULK);
+        createMissingClients(c);
+        aeMain(config.el);
+        endBenchmark("LRANGE (first 300 elements)");
+
         printf("\n");
     } while(config.loop);
 