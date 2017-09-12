@@ -578,7 +578,7 @@ int main(int argc, char **argv) {
         prepareForBenchmark("SET");
         c = createClient();
         if (!c) exit(1);
-        c->obuf = sdscatprintf(c->obuf,"SET foo_rand000000000000 %d\r\n",config.datasize);
+        c->obuf = sdscat(c->obuf,"SET foo_rand000000000000 ");
         {
             char *data = zmalloc(config.datasize+2);
             memset(data,'x',config.datasize);
@@ -612,7 +612,7 @@ int main(int argc, char **argv) {
         prepareForBenchmark("LPUSH");
         c = createClient();
         if (!c) exit(1);
-        c->obuf = sdscat(c->obuf,"LPUSH mylist 3\r\nbar\r\n");
+        c->obuf = sdscat(c->obuf,"LPUSH mylist bar\r\n");
         prepareClientForReply(c,REPLY_INT);
         createMissingClients(c);
         aeMain(config.el);
@@ -630,7 +630,7 @@ int main(int argc, char **argv) {
         prepareForBenchmark("SADD");
         c = createClient();
         if (!c) exit(1);
-        c->obuf = sdscat(c->obuf,"SADD myset 24\r\ncounter_rand000000000000\r\n");
+        c->obuf = sdscat(c->obuf,"SADD myset counter_rand000000000000\r\n");
         prepareClientForReply(c,REPLY_RETCODE);
         createMissingClients(c);
         aeMain(config.el);
@@ -648,7 +648,7 @@ int main(int argc, char **argv) {
         prepareForBenchmark("LPUSH (again, in order to bench LRANGE)");
         c = createClient();
         if (!c) exit(1);
-        c->obuf = sdscat(c->obuf,"LPUSH mylist 3\r\nbar\r\n");
+        c->obuf = sdscat(c->obuf,"LPUSH mylist bar\r\n");
         prepareClientForReply(c,REPLY_RETCODE);
         createMissingClients(c);
         aeMain(config.el);