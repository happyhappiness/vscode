@@ -48,6 +48,7 @@
 #define REPLY_INT 0
 #define REPLY_RETCODE 1
 #define REPLY_BULK 2
+#define REPLY_MBULK 2
 
 #define CLIENT_CONNECTING 0
 #define CLIENT_SENDQUERY 1
@@ -83,6 +84,7 @@ typedef struct _client {
     int fd;
     sds obuf;
     sds ibuf;
+    int mbulk;          /* Number of elements in an mbulk reply */
     int readlen;        /* readlen == -1 means read a single line */
     unsigned int written;        /* bytes of 'obuf' already written */
     int replytype;
@@ -136,6 +138,7 @@ static void resetClient(client c) {
     sdsfree(c->ibuf);
     c->ibuf = sdsempty();
     c->readlen = (c->replytype == REPLY_BULK) ? -1 : 0;
+    c->mbulk = -1;
     c->written = 0;
     c->state = CLIENT_SENDQUERY;
     c->start = mstime();
@@ -155,6 +158,20 @@ static void randomizeClientKey(client c) {
     memcpy(p,buf,strlen(buf));
 }
 
+static void prepareClientForReply(client c, int type) {
+    if (type == REPLY_BULK) {
+        c->replytype = REPLY_BULK;
+        c->readlen = -1;
+    } else if (type == REPLY_MBULK) {
+        c->replytype = REPLY_MBULK;
+        c->readlen = -1;
+        c->mbulk = -1;
+    } else {
+        c->replytype = type;
+        c->readlen = 0;
+    }
+}
+
 static void clientDone(client c) {
     long long latency;
     config.donerequests ++;
@@ -200,31 +217,63 @@ static void readHandler(aeEventLoop *el, int fd, void *privdata, int mask)
     }
     c->ibuf = sdscatlen(c->ibuf,buf,nread);
 
+processdata:
     if (c->replytype == REPLY_INT ||
         c->replytype == REPLY_RETCODE ||
-        (c->replytype == REPLY_BULK && c->readlen == -1)) {
+        (c->replytype == REPLY_BULK && c->readlen == -1) ||
+        (c->replytype == REPLY_MBULK && c->readlen == -1) ||
+        (c->replytype == REPLY_MBULK && c->mbulk == -1)) {
         char *p;
 
         if ((p = strchr(c->ibuf,'\n')) != NULL) {
-            if (c->replytype == REPLY_BULK) {
+            if (c->replytype == REPLY_BULK ||
+                (c->replytype == REPLY_MBULK && c->mbulk != -1))
+            {
                 *p = '\0';
                 *(p-1) = '\0';
                 c->readlen = atoi(c->ibuf+1)+2;
+                /* Handle null bulk reply "$-1" */
                 if (c->readlen-2 == -1) {
                     clientDone(c);
                     return;
                 }
+                /* Leave all the rest in the input buffer */
+                c->ibuf = sdsrange(c->ibuf,(p-c->ibuf)+1,-1);
+            } else if (c->replytype == REPLY_MBULK && c->mbulk == -1) {
+                *p = '\0';
+                *(p-1) = '\0';
+                c->mbulk = atoi(c->ibuf+1);
+                /* Handle null bulk reply "*-1" */
+                if (c->mbulk == -1) {
+                    clientDone(c);
+                    return;
+                }
+                /* Leave all the rest in the input buffer */
                 c->ibuf = sdsrange(c->ibuf,(p-c->ibuf)+1,-1);
+                goto processdata;
             } else {
                 c->ibuf = sdstrim(c->ibuf,"\r\n");
                 clientDone(c);
                 return;
             }
         }
     }
-    /* bulk read */
-    if ((unsigned)c->readlen == sdslen(c->ibuf))
-        clientDone(c);
+    /* bulk read, did we read everything? */
+    if ((c->replytype == REPLY_BULK || c->replytype == REPLY_MBULK) &&
+        (unsigned)c->readlen <= sdslen(c->ibuf))
+    {
+        if (c->replytype == REPLY_BULK) {
+            clientDone(c);
+        } else if (c->replytype == REPLY_MBULK) {
+            if (--c->mbulk == 0) {
+                clientDone(c);
+            } else {
+                c->ibuf = sdsrange(c->ibuf,c->readlen,-1);
+                c->readlen = -1;
+                goto processdata;
+            }
+        }
+    }
 }
 
 static void writeHandler(aeEventLoop *el, int fd, void *privdata, int mask)
@@ -269,6 +318,7 @@ static client createClient(void) {
     anetTcpNoDelay(NULL,c->fd);
     c->obuf = sdsempty();
     c->ibuf = sdsempty();
+    c->mbulk = -1;
     c->readlen = 0;
     c->written = 0;
     c->state = CLIENT_CONNECTING;
@@ -436,7 +486,7 @@ int main(int argc, char **argv) {
             data[config.datasize+1] = '\n';
             c->obuf = sdscatlen(c->obuf,data,config.datasize+2);
         }
-        c->replytype = REPLY_RETCODE;
+        prepareClientForReply(c,REPLY_RETCODE);
         createMissingClients(c);
         aeMain(config.el);
         endBenchmark("SET");
@@ -445,8 +495,7 @@ int main(int argc, char **argv) {
         c = createClient();
         if (!c) exit(1);
         c->obuf = sdscat(c->obuf,"GET foo_rand000000000000\r\n");
-        c->replytype = REPLY_BULK;
-        c->readlen = -1;
+        prepareClientForReply(c,REPLY_BULK);
         createMissingClients(c);
         aeMain(config.el);
         endBenchmark("GET");
@@ -455,7 +504,7 @@ int main(int argc, char **argv) {
         c = createClient();
         if (!c) exit(1);
         c->obuf = sdscat(c->obuf,"INCR counter_rand000000000000\r\n");
-        c->replytype = REPLY_INT;
+        prepareClientForReply(c,REPLY_INT);
         createMissingClients(c);
         aeMain(config.el);
         endBenchmark("INCR");
@@ -464,7 +513,7 @@ int main(int argc, char **argv) {
         c = createClient();
         if (!c) exit(1);
         c->obuf = sdscat(c->obuf,"LPUSH mylist 3\r\nbar\r\n");
-        c->replytype = REPLY_INT;
+        prepareClientForReply(c,REPLY_INT);
         createMissingClients(c);
         aeMain(config.el);
         endBenchmark("LPUSH");
@@ -473,8 +522,7 @@ int main(int argc, char **argv) {
         c = createClient();
         if (!c) exit(1);
         c->obuf = sdscat(c->obuf,"LPOP mylist\r\n");
-        c->replytype = REPLY_BULK;
-        c->readlen = -1;
+        prepareClientForReply(c,REPLY_BULK);
         createMissingClients(c);
         aeMain(config.el);
         endBenchmark("LPOP");
@@ -483,11 +531,29 @@ int main(int argc, char **argv) {
         c = createClient();
         if (!c) exit(1);
         c->obuf = sdscat(c->obuf,"PING\r\n");
-        c->replytype = REPLY_RETCODE;
+        prepareClientForReply(c,REPLY_RETCODE);
         createMissingClients(c);
         aeMain(config.el);
         endBenchmark("PING");
 
+        prepareForBenchmark();
+        c = createClient();
+        if (!c) exit(1);
+        c->obuf = sdscat(c->obuf,"LPUSH mylist 3\r\nbar\r\n");
+        prepareClientForReply(c,REPLY_RETCODE);
+        createMissingClients(c);
+        aeMain(config.el);
+        endBenchmark("LPUSH (again, in order to bench LRANGE)");
+
+        prepareForBenchmark();
+        c = createClient();
+        if (!c) exit(1);
+        c->obuf = sdscat(c->obuf,"LRANGE mylist 0 99\r\n");
+        prepareClientForReply(c,REPLY_MBULK);
+        createMissingClients(c);
+        aeMain(config.el);
+        endBenchmark("LRANGE (first 100 elements)");
+
         printf("\n");
     } while(config.loop);
 