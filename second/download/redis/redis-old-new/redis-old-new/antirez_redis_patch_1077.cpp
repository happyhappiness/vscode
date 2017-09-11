@@ -278,7 +278,29 @@ static void writeHandler(aeEventLoop *el, int fd, void *privdata, int mask) {
     }
 }
 
-static client createClient(char *cmd, size_t len) {
+/* Create a benchmark client, configured to send the command passed as 'cmd' of
+ * 'len' bytes.
+ *
+ * The command is copied N times in the client output buffer (that is reused
+ * again and again to send the request to the server) accordingly to the configured
+ * pipeline size.
+ *
+ * Also an initial SELECT command is prepended in order to make sure the right
+ * database is selected, if needed. The initial SELECT will be discarded as soon
+ * as the first reply is received.
+ *
+ * To create a client from scratch, the 'from' pointer is set to NULL. If instead
+ * we want to create a client using another client as reference, the 'from' pointer
+ * points to the client to use as reference. In such a case the following
+ * information is take from the 'from' client:
+ *
+ * 1) The command line to use.
+ * 2) The offsets of the __rand_int__ elements inside the command line, used
+ *    for arguments randomization.
+ *
+ * Even when cloning another client, the SELECT command is automatically prefixed
+ * if needed. */
+static client createClient(char *cmd, size_t len, client from) {
     int j;
     client c = zmalloc(sizeof(struct _client));
 
@@ -298,39 +320,65 @@ static client createClient(char *cmd, size_t len) {
     /* Suppress hiredis cleanup of unused buffers for max speed. */
     c->context->reader->maxbuf = 0;
 
-    /* Queue N requests accordingly to the pipeline size. */
+    /* Build the request buffer:
+     * Queue N requests accordingly to the pipeline size, or simply clone
+     * the example client buffer. */
     c->obuf = sdsempty();
+
+    /* If a DB number different than zero is selected, prefix our request
+     * buffer with the SELECT command, that will be discarded the first
+     * time the replies are received, so if the client is reused the
+     * SELECT command will not be used again. */
     if (config.dbnum != 0) {
-        /* If a DB number different than zero is selected, prefix our request
-         * buffer with the SELECT command, that will be discarded the first
-         * time the replies are received, so if the client is reused the
-         * SELECT command will not be used again. */
         c->obuf = sdscatprintf(c->obuf,"*2\r\n$6\r\nSELECT\r\n$%d\r\n%s\r\n",
             (int)sdslen(config.dbnumstr),config.dbnumstr);
         c->selectlen = sdslen(c->obuf);
     } else {
         c->selectlen = 0;
     }
-    for (j = 0; j < config.pipeline; j++)
-        c->obuf = sdscatlen(c->obuf,cmd,len);
-    c->randlen = 0;
-    c->randfree = RANDPTR_INITIAL_SIZE;
-    c->randptr = zmalloc(sizeof(char*)*c->randfree);
+
+    /* Append the request itself. */
+    if (from) {
+        c->obuf = sdscatlen(c->obuf,
+            from->obuf+from->selectlen,
+            sdslen(from->obuf)-from->selectlen);
+    } else {
+        for (j = 0; j < config.pipeline; j++)
+            c->obuf = sdscatlen(c->obuf,cmd,len);
+    }
     c->written = 0;
     c->pending = config.pipeline;
+    c->randptr = NULL;
+    c->randlen = 0;
     if (c->selectlen) c->pending++;
 
     /* Find substrings in the output buffer that need to be randomized. */
     if (config.randomkeys) {
-        char *p = c->obuf;
-        while ((p = strstr(p,":rand:")) != NULL) {
-            if (c->randfree == 0) {
-                c->randptr = zrealloc(c->randptr,sizeof(char*)*c->randlen*2);
-                c->randfree += c->randlen;
+        if (from) {
+            c->randlen = from->randlen;
+            c->randfree = 0;
+            c->randptr = zmalloc(sizeof(char*)*c->randlen);
+            /* copy the offsets. */
+            for (j = 0; j < c->randlen; j++) {
+                c->randptr[j] = c->obuf + (from->randptr[j]-from->obuf);
+                /* Adjust for the different select prefix length. */
+                c->randptr[j] += c->selectlen - from->selectlen;
+            }
+        } else {
+            char *p = c->obuf;
+
+            c->randlen = 0;
+            c->randfree = RANDPTR_INITIAL_SIZE;
+            c->randptr = zmalloc(sizeof(char*)*c->randfree);
+            while ((p = strstr(p,"__rand_int__")) != NULL) {
+                if (c->randfree == 0) {
+                    c->randptr = zrealloc(c->randptr,sizeof(char*)*c->randlen*2);
+                    c->randfree += c->randlen;
+                }
+                c->randptr[c->randlen++] = p;
+                c->randfree--;
+                p += 12; /* 12 is strlen("__rand_int__). */
             }
-            c->randptr[c->randlen++] = p+6;
-            c->randfree--;
-            p += 6;
         }
     }
     aeCreateFileEvent(config.el,c->context->fd,AE_WRITABLE,writeHandler,c);
@@ -352,7 +400,7 @@ static void createMissingClients(client c) {
     }
 
     while(config.liveclients < config.numclients) {
-        createClient(buf,buflen/config.pipeline);
+        createClient(NULL,0,c);
 
         /* Listen backlog is quite limited on most systems */
         if (++n > 64) {
@@ -403,7 +451,7 @@ static void benchmark(char *title, char *cmd, int len) {
     config.requests_issued = 0;
     config.requests_finished = 0;
 
-    c = createClient(cmd,len);
+    c = createClient(cmd,len,NULL);
     createMissingClients(c);
 
     config.start = mstime();
@@ -530,8 +578,12 @@ int parseOptions(int argc, const char **argv) {
 "   $ redis-benchmark -t set -n 1000000 -r 100000000\n\n"
 " Benchmark 127.0.0.1:6379 for a few commands producing CSV output:\n"
 "   $ redis-benchmark -t ping,set,get -n 100000 --csv\n\n"
+" Benchmark a specific command line:\n"
+"   $ redis-benchmark -r 10000 -n 10000 eval 'return redis.call(\"ping\")' 0\n\n"
 " Fill a list with 10000 random elements:\n"
-"   $ redis-benchmark -r 10000 -n 10000 lpush mylist ele:rand:000000000000\n\n"
+"   $ redis-benchmark -r 10000 -n 10000 lpush mylist __rand_int__\n\n"
+" On user specified command lines __rand_int__ is replaced with a random integer\n"
+" with a range of values selected by the -r option.\n"
     );
     exit(exit_status);
 }
@@ -608,7 +660,7 @@ int main(int argc, const char **argv) {
 
     if (config.idlemode) {
         printf("Creating %d idle connections and waiting forever (Ctrl+C when done)\n", config.numclients);
-        c = createClient("",0); /* will never receive a reply */
+        c = createClient("",0,NULL); /* will never receive a reply */
         createMissingClients(c);
         aeMain(config.el);
         /* and will wait for every */
@@ -647,19 +699,19 @@ int main(int argc, const char **argv) {
         }
 
         if (test_is_selected("set")) {
-            len = redisFormatCommand(&cmd,"SET foo:rand:000000000000 %s",data);
+            len = redisFormatCommand(&cmd,"SET key:__rand_int__ %s",data);
             benchmark("SET",cmd,len);
             free(cmd);
         }
 
         if (test_is_selected("get")) {
-            len = redisFormatCommand(&cmd,"GET foo:rand:000000000000");
+            len = redisFormatCommand(&cmd,"GET key:__rand_int__");
             benchmark("GET",cmd,len);
             free(cmd);
         }
 
         if (test_is_selected("incr")) {
-            len = redisFormatCommand(&cmd,"INCR counter:rand:000000000000");
+            len = redisFormatCommand(&cmd,"INCR counter:__rand_int__");
             benchmark("INCR",cmd,len);
             free(cmd);
         }
@@ -678,7 +730,7 @@ int main(int argc, const char **argv) {
 
         if (test_is_selected("sadd")) {
             len = redisFormatCommand(&cmd,
-                "SADD myset counter:rand:000000000000");
+                "SADD myset element:__rand_int__");
             benchmark("SADD",cmd,len);
             free(cmd);
         }
@@ -728,7 +780,7 @@ int main(int argc, const char **argv) {
             const char *argv[21];
             argv[0] = "MSET";
             for (i = 1; i < 21; i += 2) {
-                argv[i] = "foo:rand:000000000000";
+                argv[i] = "key:__rand_int__";
                 argv[i+1] = data;
             }
             len = redisFormatCommandArgv(&cmd,21,argv,NULL);