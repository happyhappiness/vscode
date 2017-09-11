@@ -73,6 +73,8 @@ static struct config {
     int csv;
     int loop;
     int idlemode;
+    int dbnum;
+    sds dbnumstr;
     char *tests;
 } config;
 
@@ -85,6 +87,9 @@ typedef struct _client {
     long long start; /* start time of a request */
     long long latency; /* request latency */
     int pending;    /* Number of pending requests (sent but no reply received) */
+    int selectlen;  /* If non-zero, a SELECT of 'selectlen' bytes is currently
+                       used as a prefix of the pipline of commands. This gets
+                       discarded the first time it's sent. */
 } *client;
 
 /* Prototypes */
@@ -199,6 +204,15 @@ static void readHandler(aeEventLoop *el, int fd, void *privdata, int mask) {
 
                 freeReplyObject(reply);
 
+                if (c->selectlen) {
+                    /* This is the OK from SELECT. Just discard the SELECT
+                     * from the buffer. */
+                    c->pending--;
+                    sdsrange(c->obuf,c->selectlen,-1);
+                    c->selectlen = 0;
+                    continue;
+                }
+
                 if (config.requests_finished < config.requests)
                     config.latency[config.requests_finished++] = c->latency;
                 c->pending--;
@@ -269,13 +283,26 @@ static client createClient(char *cmd, size_t len) {
     }
     /* Suppress hiredis cleanup of unused buffers for max speed. */
     c->context->reader->maxbuf = 0;
+
     /* Queue N requests accordingly to the pipeline size. */
     c->obuf = sdsempty();
+    if (config.dbnum != 0) {
+        /* If a DB number different than zero is selected, prefix our request
+         * buffer with the SELECT command, that will be discarded the first
+         * time the replies are received, so if the client is reused the
+         * SELECT command will not be used again. */
+        c->obuf = sdscatprintf(c->obuf,"*2\r\n$6\r\nSELECT\r\n$%d\r\n%s\r\n",
+            (int)sdslen(config.dbnumstr),config.dbnumstr);
+        c->selectlen = sdslen(c->obuf);
+    } else {
+        c->selectlen = 0;
+    }
     for (j = 0; j < config.pipeline; j++)
         c->obuf = sdscatlen(c->obuf,cmd,len);
     c->randlen = 0;
     c->written = 0;
     c->pending = config.pipeline;
+    if (c->selectlen) c->pending++;
 
     /* Find substrings in the output buffer that need to be randomized. */
     if (config.randomkeys) {
@@ -286,8 +313,6 @@ static client createClient(char *cmd, size_t len) {
             p += 6;
         }
     }
-
-/*    redisSetReplyObjectFunctions(c->context,NULL); */
     aeCreateFileEvent(config.el,c->context->fd,AE_WRITABLE,writeHandler,c);
     listAddNodeTail(config.clients,c);
     config.liveclients++;
@@ -296,9 +321,18 @@ static client createClient(char *cmd, size_t len) {
 
 static void createMissingClients(client c) {
     int n = 0;
+    char *buf = c->obuf;
+    size_t buflen = sdslen(c->obuf);
+
+    /* If we are cloning from a client with a SELECT prefix, skip it since the
+     * client will be created with the prefixed SELECT if needed. */
+    if (c->selectlen) {
+        buf += c->selectlen;
+        buflen -= c->selectlen;
+    }
 
     while(config.liveclients < config.numclients) {
-        createClient(c->obuf,sdslen(c->obuf)/config.pipeline);
+        createClient(buf,buflen/config.pipeline);
 
         /* Listen backlog is quite limited on most systems */
         if (++n > 64) {
@@ -421,6 +455,10 @@ int parseOptions(int argc, const char **argv) {
             config.tests = sdscat(config.tests,(char*)argv[++i]);
             config.tests = sdscat(config.tests,",");
             sdstolower(config.tests);
+        } else if (!strcmp(argv[i],"--dbnum")) {
+            if (lastarg) goto invalid;
+            config.dbnum = atoi(argv[++i]);
+            config.dbnumstr = sdsfromlonglong(config.dbnum);
         } else if (!strcmp(argv[i],"--help")) {
             exit_status = 0;
             goto usage;
@@ -447,6 +485,7 @@ int parseOptions(int argc, const char **argv) {
 " -c <clients>       Number of parallel connections (default 50)\n"
 " -n <requests>      Total number of requests (default 10000)\n"
 " -d <size>          Data size of SET/GET value in bytes (default 2)\n"
+" -dbnum <db>        SELECT the specified db number (default 0)\n"
 " -k <boolean>       1=keep alive 0=reconnect (default 1)\n"
 " -r <keyspacelen>   Use random keys for SET/GET/INCR, random values for SADD\n"
 "  Using this option the benchmark will get/set keys\n"
@@ -535,6 +574,7 @@ int main(int argc, const char **argv) {
     config.hostport = 6379;
     config.hostsocket = NULL;
     config.tests = NULL;
+    config.dbnum = 0;
 
     i = parseOptions(argc,argv);
     argc -= i;