@@ -77,6 +77,7 @@ static struct config {
     int dbnum;
     sds dbnumstr;
     char *tests;
+    char *auth;
 } config;
 
 typedef struct _client {
@@ -213,7 +214,7 @@ static void readHandler(aeEventLoop *el, int fd, void *privdata, int mask) {
                 freeReplyObject(reply);
 
                 if (c->selectlen) {
-                    int j;
+                    size_t j;
 
                     /* This is the OK from SELECT. Just discard the SELECT
                      * from the buffer. */
@@ -325,6 +326,13 @@ static client createClient(char *cmd, size_t len, client from) {
      * the example client buffer. */
     c->obuf = sdsempty();
 
+    if (config.auth) {
+        char *buf = NULL;
+        int len = redisFormatCommand(&buf, "AUTH %s", config.auth);
+        c->obuf = sdscatlen(c->obuf, buf, len);
+        free(buf);
+    }
+
     /* If a DB number different than zero is selected, prefix our request
      * buffer with the SELECT command, that will be discarded the first
      * time the replies are received, so if the client is reused the
@@ -346,6 +354,7 @@ static client createClient(char *cmd, size_t len, client from) {
         for (j = 0; j < config.pipeline; j++)
             c->obuf = sdscatlen(c->obuf,cmd,len);
     }
+
     c->written = 0;
     c->pending = config.pipeline;
     c->randptr = NULL;
@@ -359,7 +368,7 @@ static client createClient(char *cmd, size_t len, client from) {
             c->randfree = 0;
             c->randptr = zmalloc(sizeof(char*)*c->randlen);
             /* copy the offsets. */
-            for (j = 0; j < c->randlen; j++) {
+            for (j = 0; j < (int)c->randlen; j++) {
                 c->randptr[j] = c->obuf + (from->randptr[j]-from->obuf);
                 /* Adjust for the different select prefix length. */
                 c->randptr[j] += c->selectlen - from->selectlen;
@@ -389,15 +398,6 @@ static client createClient(char *cmd, size_t len, client from) {
 
 static void createMissingClients(client c) {
     int n = 0;
-    char *buf = c->obuf;
-    size_t buflen = sdslen(c->obuf);
-
-    /* If we are cloning from a client with a SELECT prefix, skip it since the
-     * client will be created with the prefixed SELECT if needed. */
-    if (c->selectlen) {
-        buf += c->selectlen;
-        buflen -= c->selectlen;
-    }
 
     while(config.liveclients < config.numclients) {
         createClient(NULL,0,c);
@@ -489,6 +489,9 @@ int parseOptions(int argc, const char **argv) {
         } else if (!strcmp(argv[i],"-s")) {
             if (lastarg) goto invalid;
             config.hostsocket = strdup(argv[++i]);
+        } else if (!strcmp(argv[i],"-a") ) {
+            if (lastarg) goto invalid;
+            config.auth = strdup(argv[++i]);
         } else if (!strcmp(argv[i],"-d")) {
             if (lastarg) goto invalid;
             config.datasize = atoi(argv[++i]);
@@ -550,6 +553,7 @@ int parseOptions(int argc, const char **argv) {
 " -h <hostname>      Server hostname (default 127.0.0.1)\n"
 " -p <port>          Server port (default 6379)\n"
 " -s <socket>        Server socket (overrides host and port)\n"
+" -a <password>      Password for Redis Auth\n"
 " -c <clients>       Number of parallel connections (default 50)\n"
 " -n <requests>      Total number of requests (default 10000)\n"
 " -d <size>          Data size of SET/GET value in bytes (default 2)\n"
@@ -593,7 +597,7 @@ int showThroughput(struct aeEventLoop *eventLoop, long long id, void *clientData
     REDIS_NOTUSED(clientData);
 
     if (config.liveclients == 0) {
-        fprintf(stderr,"All clients disconnected... aborting.");
+        fprintf(stderr,"All clients disconnected... aborting.\n");
         exit(1);
     }
 
@@ -651,6 +655,7 @@ int main(int argc, const char **argv) {
     config.hostsocket = NULL;
     config.tests = NULL;
     config.dbnum = 0;
+    config.auth = NULL;
 
     i = parseOptions(argc,argv);
     argc -= i;