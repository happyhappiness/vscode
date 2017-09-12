@@ -137,7 +137,8 @@ static void resetClient(client c) {
     aeCreateFileEvent(config.el,c->fd, AE_WRITABLE,writeHandler,c,NULL);
     sdsfree(c->ibuf);
     c->ibuf = sdsempty();
-    c->readlen = (c->replytype == REPLY_BULK) ? -1 : 0;
+    c->readlen = (c->replytype == REPLY_BULK ||
+                  c->replytype == REPLY_MBULK) ? -1 : 0;
     c->mbulk = -1;
     c->written = 0;
     c->state = CLIENT_SENDQUERY;
@@ -238,6 +239,7 @@ static void readHandler(aeEventLoop *el, int fd, void *privdata, int mask)
                 *p = '\0';
                 *(p-1) = '\0';
                 c->readlen = atoi(c->ibuf+1)+2;
+                // printf("BULK ATOI: %s\n", c->ibuf+1);
                 /* Handle null bulk reply "$-1" */
                 if (c->readlen-2 == -1) {
                     clientDone(c);
@@ -258,6 +260,7 @@ static void readHandler(aeEventLoop *el, int fd, void *privdata, int mask)
                     clientDone(c);
                     return;
                 }
+                // printf("%p) %d elements list\n", c, c->mbulk);
                 /* Leave all the rest in the input buffer */
                 c->ibuf = sdsrange(c->ibuf,(p-c->ibuf)+1,-1);
                 goto processdata;
@@ -273,9 +276,14 @@ static void readHandler(aeEventLoop *el, int fd, void *privdata, int mask)
          (c->replytype == REPLY_BULK)) && c->readlen != -1 &&
           (unsigned)c->readlen <= sdslen(c->ibuf))
     {
+        // printf("BULKSTATUS mbulk:%d readlen:%d sdslen:%d\n",
+        //    c->mbulk,c->readlen,sdslen(c->ibuf));
         if (c->replytype == REPLY_BULK) {
             clientDone(c);
         } else if (c->replytype == REPLY_MBULK) {
+            // printf("%p) %d (%d)) ",c, c->mbulk, c->readlen);
+            // fwrite(c->ibuf,c->readlen,1,stdout);
+            // printf("\n");
             if (--c->mbulk == 0) {
                 clientDone(c);
             } else {
@@ -486,7 +494,6 @@ int main(int argc, char **argv) {
     }
 
     do {
-#if 0
         prepareForBenchmark();
         c = createClient();
         if (!c) exit(1);
@@ -548,7 +555,6 @@ int main(int argc, char **argv) {
         aeMain(config.el);
         endBenchmark("PING");
 
-#endif
         prepareForBenchmark();
         c = createClient();
         if (!c) exit(1);
@@ -558,7 +564,6 @@ int main(int argc, char **argv) {
         aeMain(config.el);
         endBenchmark("LPUSH (again, in order to bench LRANGE)");
 
-#if 0
         prepareForBenchmark();
         c = createClient();
         if (!c) exit(1);
@@ -585,7 +590,6 @@ int main(int argc, char **argv) {
         createMissingClients(c);
         aeMain(config.el);
         endBenchmark("LRANGE (first 450 elements)");
-#endif
 
         prepareForBenchmark();
         c = createClient();