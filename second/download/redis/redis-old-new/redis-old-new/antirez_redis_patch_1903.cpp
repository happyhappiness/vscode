@@ -76,6 +76,7 @@ static struct config {
     long long start;
     long long totlatency;
     int *latency;
+    char *title;
     list *clients;
     int quiet;
     int loop;
@@ -207,16 +208,27 @@ static void clientDone(client c) {
     }
 }
 
+/* Read a length from the buffer pointed to by *p, store the length in *len,
+ * and return the number of bytes that the cursor advanced. */
+static int readLen(char *p, int *len) {
+    char *tail = strstr(p,"\r\n");
+    if (tail == NULL)
+        return 0;
+    *tail = '\0';
+    *len = atoi(p+1);
+    return tail+2-p;
+}
+
 static void readHandler(aeEventLoop *el, int fd, void *privdata, int mask)
 {
-    char buf[1024];
-    int nread;
+    char buf[1024], *p;
+    int nread, pos=0, len=0;
     client c = privdata;
     REDIS_NOTUSED(el);
     REDIS_NOTUSED(fd);
     REDIS_NOTUSED(mask);
 
-    nread = read(c->fd, buf, 1024);
+    nread = read(c->fd,buf,sizeof(buf));
     if (nread == -1) {
         fprintf(stderr, "Reading from socket: %s\n", strerror(errno));
         freeClient(c);
@@ -229,82 +241,89 @@ static void readHandler(aeEventLoop *el, int fd, void *privdata, int mask)
     }
     c->totreceived += nread;
     c->ibuf = sdscatlen(c->ibuf,buf,nread);
+    len = sdslen(c->ibuf);
 
-processdata:
-    /* Are we waiting for the first line of the command of for  sdf 
-     * count in bulk or multi bulk operations? */
     if (c->replytype == REPLY_INT ||
-        c->replytype == REPLY_RETCODE ||
-        (c->replytype == REPLY_BULK && c->readlen == -1) ||
-        (c->replytype == REPLY_MBULK && c->readlen == -1) ||
-        (c->replytype == REPLY_MBULK && c->mbulk == -1)) {
-        char *p;
-
-        /* Check if the first line is complete. This is only true if
-         * there is a newline inside the buffer. */
-        if ((p = strchr(c->ibuf,'\n')) != NULL) {
-            if (c->replytype == REPLY_BULK ||
-                (c->replytype == REPLY_MBULK && c->mbulk != -1))
-            {
-                /* Read the count of a bulk reply (being it a single bulk or
-                 * a multi bulk reply). "$<count>" for the protocol spec. */
-                *p = '\0';
-                *(p-1) = '\0';
-                c->readlen = atoi(c->ibuf+1)+2;
-                // printf("BULK ATOI: %s\n", c->ibuf+1);
-                /* Handle null bulk reply "$-1" */
-                if (c->readlen-2 == -1) {
-                    clientDone(c);
-                    return;
-                }
-                /* Leave all the rest in the input buffer */
-                c->ibuf = sdsrange(c->ibuf,(p-c->ibuf)+1,-1);
-                /* fall through to reach the point where the code will try
-                 * to check if the bulk reply is complete. */
-            } else if (c->replytype == REPLY_MBULK && c->mbulk == -1) {
-                /* Read the count of a multi bulk reply. That is, how many
-                 * bulk replies we have to read next. "*<count>" protocol. */
-                *p = '\0';
-                *(p-1) = '\0';
-                c->mbulk = atoi(c->ibuf+1);
-                /* Handle null bulk reply "*-1" */
-                if (c->mbulk == -1) {
-                    clientDone(c);
-                    return;
+        c->replytype == REPLY_RETCODE)
+    {
+        /* Check if the first line is complete. This is everything we need
+         * when waiting for an integer or status code reply.*/
+        if ((p = strstr(c->ibuf,"\r\n")) != NULL)
+            goto done;
+    } else if (c->replytype == REPLY_BULK) {
+        int advance = 0;
+        if (c->readlen < 0) {
+            advance = readLen(c->ibuf+pos,&c->readlen);
+            if (advance) {
+                pos += advance;
+                if (c->readlen == -1) {
+                    goto done;
+                } else {
+                    /* include the trailing \r\n */
+                    c->readlen += 2;
                 }
-                // printf("%p) %d elements list\n", c, c->mbulk);
-                /* Leave all the rest in the input buffer */
-                c->ibuf = sdsrange(c->ibuf,(p-c->ibuf)+1,-1);
-                goto processdata;
             } else {
-                c->ibuf = sdstrim(c->ibuf,"\r\n");
-                clientDone(c);
-                return;
+                goto skip;
             }
         }
-    }
-    /* bulk read, did we read everything? */
-    if (((c->replytype == REPLY_MBULK && c->mbulk != -1) || 
-         (c->replytype == REPLY_BULK)) && c->readlen != -1 &&
-          (unsigned)c->readlen <= sdslen(c->ibuf))
-    {
-        // printf("BULKSTATUS mbulk:%d readlen:%d sdslen:%d\n",
-        //    c->mbulk,c->readlen,sdslen(c->ibuf));
-        if (c->replytype == REPLY_BULK) {
-            clientDone(c);
-        } else if (c->replytype == REPLY_MBULK) {
-            // printf("%p) %d (%d)) ",c, c->mbulk, c->readlen);
-            // fwrite(c->ibuf,c->readlen,1,stdout);
-            // printf("\n");
-            if (--c->mbulk == 0) {
-                clientDone(c);
+
+        int canconsume;
+        if (c->readlen > 0) {
+            canconsume = c->readlen > (len-pos) ? (len-pos) : c->readlen;
+            c->readlen -= canconsume;
+            pos += canconsume;
+        }
+
+        if (c->readlen == 0)
+            goto done;
+    } else if (c->replytype == REPLY_MBULK) {
+        int advance = 0;
+        if (c->mbulk == -1) {
+            advance = readLen(c->ibuf+pos,&c->mbulk);
+            if (advance) {
+                pos += advance;
+                if (c->mbulk == -1)
+                    goto done;
+            } else {
+                goto skip;
+            }
+        }
+
+        int canconsume;
+        while(c->mbulk > 0 && pos < len) {
+            if (c->readlen > 0) {
+                canconsume = c->readlen > (len-pos) ? (len-pos) : c->readlen;
+                c->readlen -= canconsume;
+                pos += canconsume;
+                if (c->readlen == 0)
+                    c->mbulk--;
             } else {
-                c->ibuf = sdsrange(c->ibuf,c->readlen,-1);
-                c->readlen = -1;
-                goto processdata;
+                advance = readLen(c->ibuf+pos,&c->readlen);
+                if (advance) {
+                    pos += advance;
+                    if (c->readlen == -1) {
+                        c->mbulk--;
+                        continue;
+                    } else {
+                        /* include the trailing \r\n */
+                        c->readlen += 2;
+                    }
+                } else {
+                    goto skip;
+                }
             }
         }
+
+        if (c->mbulk == 0)
+            goto done;
     }
+
+skip:
+    c->ibuf = sdsrange(c->ibuf,pos,-1);
+    return;
+done:
+    clientDone(c);
+    return;
 }
 
 static void writeHandler(aeEventLoop *el, int fd, void *privdata, int mask)
@@ -376,13 +395,13 @@ static void createMissingClients(client c) {
     }
 }
 
-static void showLatencyReport(char *title) {
+static void showLatencyReport(void) {
     int j, seen = 0;
     float perc, reqpersec;
 
     reqpersec = (float)config.donerequests/((float)config.totlatency/1000);
     if (!config.quiet) {
-        printf("====== %s ======\n", title);
+        printf("====== %s ======\n", config.title);
         printf("  %d requests completed in %.2f seconds\n", config.donerequests,
             (float)config.totlatency/1000);
         printf("  %d parallel clients\n", config.numclients);
@@ -398,20 +417,20 @@ static void showLatencyReport(char *title) {
         }
         printf("%.2f requests per second\n\n", reqpersec);
     } else {
-        printf("%s: %.2f requests per second\n", title, reqpersec);
+        printf("%s: %.2f requests per second\n", config.title, reqpersec);
     }
 }
 
-static void prepareForBenchmark(void)
-{
+static void prepareForBenchmark(char *title) {
     memset(config.latency,0,sizeof(int)*(MAX_LATENCY+1));
+    config.title = title;
     config.start = mstime();
     config.donerequests = 0;
 }
 
-static void endBenchmark(char *title) {
+static void endBenchmark(void) {
     config.totlatency = mstime()-config.start;
-    showLatencyReport(title);
+    showLatencyReport();
     freeAllClients();
 }
 
@@ -489,6 +508,18 @@ void parseOptions(int argc, char **argv) {
     }
 }
 
+int showThroughput(struct aeEventLoop *eventLoop, long long id, void *clientData) {
+    REDIS_NOTUSED(eventLoop);
+    REDIS_NOTUSED(id);
+    REDIS_NOTUSED(clientData);
+
+    float dt = (float)(mstime()-config.start)/1000.0;
+    float rps = (float)config.donerequests/dt;
+    printf("%s: %.2f\r", config.title, rps);
+    fflush(stdout);
+    return 250; /* every 250ms */
+}
+
 int main(int argc, char **argv) {
     client c;
 
@@ -500,6 +531,7 @@ int main(int argc, char **argv) {
     config.requests = 10000;
     config.liveclients = 0;
     config.el = aeCreateEventLoop();
+    aeCreateTimeEvent(config.el,1,showThroughput,NULL,NULL);
     config.keepalive = 1;
     config.donerequests = 0;
     config.datasize = 3;
@@ -524,7 +556,7 @@ int main(int argc, char **argv) {
 
     if (config.idlemode) {
         printf("Creating %d idle connections and waiting forever (Ctrl+C when done)\n", config.numclients);
-        prepareForBenchmark();
+        prepareForBenchmark("IDLE");
         c = createClient();
         if (!c) exit(1);
         c->obuf = sdsempty();
@@ -535,25 +567,25 @@ int main(int argc, char **argv) {
     }
 
     do {
-        prepareForBenchmark();
+        prepareForBenchmark("PING");
         c = createClient();
         if (!c) exit(1);
         c->obuf = sdscat(c->obuf,"PING\r\n");
         prepareClientForReply(c,REPLY_RETCODE);
         createMissingClients(c);
         aeMain(config.el);
-        endBenchmark("PING");
+        endBenchmark();
 
-        prepareForBenchmark();
+        prepareForBenchmark("PING (multi bulk)");
         c = createClient();
         if (!c) exit(1);
         c->obuf = sdscat(c->obuf,"*1\r\n$4\r\nPING\r\n");
         prepareClientForReply(c,REPLY_RETCODE);
         createMissingClients(c);
         aeMain(config.el);
-        endBenchmark("PING (multi bulk)");
+        endBenchmark();
 
-        prepareForBenchmark();
+        prepareForBenchmark("SET");
         c = createClient();
         if (!c) exit(1);
         c->obuf = sdscatprintf(c->obuf,"SET foo_rand000000000000 %d\r\n",config.datasize);
@@ -567,106 +599,106 @@ int main(int argc, char **argv) {
         prepareClientForReply(c,REPLY_RETCODE);
         createMissingClients(c);
         aeMain(config.el);
-        endBenchmark("SET");
+        endBenchmark();
 
-        prepareForBenchmark();
+        prepareForBenchmark("GET");
         c = createClient();
         if (!c) exit(1);
         c->obuf = sdscat(c->obuf,"GET foo_rand000000000000\r\n");
         prepareClientForReply(c,REPLY_BULK);
         createMissingClients(c);
         aeMain(config.el);
-        endBenchmark("GET");
+        endBenchmark();
 
-        prepareForBenchmark();
+        prepareForBenchmark("INCR");
         c = createClient();
         if (!c) exit(1);
         c->obuf = sdscat(c->obuf,"INCR counter_rand000000000000\r\n");
         prepareClientForReply(c,REPLY_INT);
         createMissingClients(c);
         aeMain(config.el);
-        endBenchmark("INCR");
+        endBenchmark();
 
-        prepareForBenchmark();
+        prepareForBenchmark("LPUSH");
         c = createClient();
         if (!c) exit(1);
         c->obuf = sdscat(c->obuf,"LPUSH mylist 3\r\nbar\r\n");
         prepareClientForReply(c,REPLY_INT);
         createMissingClients(c);
         aeMain(config.el);
-        endBenchmark("LPUSH");
+        endBenchmark();
 
-        prepareForBenchmark();
+        prepareForBenchmark("LPOP");
         c = createClient();
         if (!c) exit(1);
         c->obuf = sdscat(c->obuf,"LPOP mylist\r\n");
         prepareClientForReply(c,REPLY_BULK);
         createMissingClients(c);
         aeMain(config.el);
-        endBenchmark("LPOP");
+        endBenchmark();
 
-        prepareForBenchmark();
+        prepareForBenchmark("SADD");
         c = createClient();
         if (!c) exit(1);
         c->obuf = sdscat(c->obuf,"SADD myset 24\r\ncounter_rand000000000000\r\n");
         prepareClientForReply(c,REPLY_RETCODE);
         createMissingClients(c);
         aeMain(config.el);
-        endBenchmark("SADD");
+        endBenchmark();
 
-        prepareForBenchmark();
+        prepareForBenchmark("SPOP");
         c = createClient();
         if (!c) exit(1);
         c->obuf = sdscat(c->obuf,"SPOP myset\r\n");
         prepareClientForReply(c,REPLY_BULK);
         createMissingClients(c);
         aeMain(config.el);
-        endBenchmark("SPOP");
+        endBenchmark();
 
-        prepareForBenchmark();
+        prepareForBenchmark("LPUSH (again, in order to bench LRANGE)");
         c = createClient();
         if (!c) exit(1);
         c->obuf = sdscat(c->obuf,"LPUSH mylist 3\r\nbar\r\n");
         prepareClientForReply(c,REPLY_RETCODE);
         createMissingClients(c);
         aeMain(config.el);
-        endBenchmark("LPUSH (again, in order to bench LRANGE)");
+        endBenchmark();
 
-        prepareForBenchmark();
+        prepareForBenchmark("LRANGE (first 100 elements)");
         c = createClient();
         if (!c) exit(1);
         c->obuf = sdscat(c->obuf,"LRANGE mylist 0 99\r\n");
         prepareClientForReply(c,REPLY_MBULK);
         createMissingClients(c);
         aeMain(config.el);
-        endBenchmark("LRANGE (first 100 elements)");
+        endBenchmark();
 
-        prepareForBenchmark();
+        prepareForBenchmark("LRANGE (first 300 elements)");
         c = createClient();
         if (!c) exit(1);
         c->obuf = sdscat(c->obuf,"LRANGE mylist 0 299\r\n");
         prepareClientForReply(c,REPLY_MBULK);
         createMissingClients(c);
         aeMain(config.el);
-        endBenchmark("LRANGE (first 300 elements)");
+        endBenchmark();
 
-        prepareForBenchmark();
+        prepareForBenchmark("LRANGE (first 450 elements)");
         c = createClient();
         if (!c) exit(1);
         c->obuf = sdscat(c->obuf,"LRANGE mylist 0 449\r\n");
         prepareClientForReply(c,REPLY_MBULK);
         createMissingClients(c);
         aeMain(config.el);
-        endBenchmark("LRANGE (first 450 elements)");
+        endBenchmark();
 
-        prepareForBenchmark();
+        prepareForBenchmark("LRANGE (first 600 elements)");
         c = createClient();
         if (!c) exit(1);
         c->obuf = sdscat(c->obuf,"LRANGE mylist 0 599\r\n");
         prepareClientForReply(c,REPLY_MBULK);
         createMissingClients(c);
         aeMain(config.el);
-        endBenchmark("LRANGE (first 600 elements)");
+        endBenchmark();
 
         printf("\n");
     } while(config.loop);