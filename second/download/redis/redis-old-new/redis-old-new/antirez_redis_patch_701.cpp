@@ -90,9 +90,10 @@ typedef struct _client {
     long long start;        /* Start time of a request */
     long long latency;      /* Request latency */
     int pending;            /* Number of pending requests (replies to consume) */
-    int selectlen;  /* If non-zero, a SELECT of 'selectlen' bytes is currently
-                       used as a prefix of the pipline of commands. This gets
-                       discarded the first time it's sent. */
+    int prefix_pending;     /* If non-zero, number of pending prefix commands. Commands
+                               such as auth and select are prefixed to the pipeline of
+                               benchmark commands and discarded after the first send. */
+    int prefixlen;          /* Size in bytes of the pending prefix commands */
 } *client;
 
 /* Prototypes */
@@ -212,20 +213,21 @@ static void readHandler(aeEventLoop *el, int fd, void *privdata, int mask) {
                 }
 
                 freeReplyObject(reply);
-
-                if (c->selectlen) {
-                    size_t j;
-
-                    /* This is the OK from SELECT. Just discard the SELECT
-                     * from the buffer. */
+                // This is an OK for prefix commands such as auth and select.
+                if (c->prefix_pending > 0) {
+                    c->prefix_pending--;
                     c->pending--;
-                    sdsrange(c->obuf,c->selectlen,-1);
-                    /* We also need to fix the pointers to the strings
-                     * we need to randomize. */
-                    for (j = 0; j < c->randlen; j++)
-                        c->randptr[j] -= c->selectlen;
-                    c->selectlen = 0;
-                    continue;
+                    // Discard prefix commands on first response.
+                    if (c->prefixlen > 0) {
+                        size_t j;
+                        sdsrange(c->obuf, c->prefixlen, -1);
+                        /* We also need to fix the pointers to the strings
+                        * we need to randomize. */
+                        for (j = 0; j < c->randlen; j++)
+                            c->randptr[j] -= c->prefixlen;
+                        c->prefixlen = 0;
+                    }
+                    continue;                
                 }
 
                 if (config.requests_finished < config.requests)
@@ -299,8 +301,7 @@ static void writeHandler(aeEventLoop *el, int fd, void *privdata, int mask) {
  * 2) The offsets of the __rand_int__ elements inside the command line, used
  *    for arguments randomization.
  *
- * Even when cloning another client, the SELECT command is automatically prefixed
- * if needed. */
+ * Even when cloning another client, prefix commands are applied if needed.*/
 static client createClient(char *cmd, size_t len, client from) {
     int j;
     client c = zmalloc(sizeof(struct _client));
@@ -325,12 +326,16 @@ static client createClient(char *cmd, size_t len, client from) {
      * Queue N requests accordingly to the pipeline size, or simply clone
      * the example client buffer. */
     c->obuf = sdsempty();
-
+    /* Prefix the request buffer with AUTH and/or SELECT commands, if applicable.
+     * These commands are discarded after the first response, so if the client is
+     * reused the commands will not be used again. */
+    c->prefix_pending = 0;
     if (config.auth) {
         char *buf = NULL;
         int len = redisFormatCommand(&buf, "AUTH %s", config.auth);
         c->obuf = sdscatlen(c->obuf, buf, len);
         free(buf);
+        c->prefix_pending++;
     }
 
     /* If a DB number different than zero is selected, prefix our request
@@ -340,26 +345,23 @@ static client createClient(char *cmd, size_t len, client from) {
     if (config.dbnum != 0) {
         c->obuf = sdscatprintf(c->obuf,"*2\r\n$6\r\nSELECT\r\n$%d\r\n%s\r\n",
             (int)sdslen(config.dbnumstr),config.dbnumstr);
-        c->selectlen = sdslen(c->obuf);
-    } else {
-        c->selectlen = 0;
+        c->prefix_pending++;
     }
-
+    c->prefixlen = sdslen(c->obuf);
     /* Append the request itself. */
     if (from) {
         c->obuf = sdscatlen(c->obuf,
-            from->obuf+from->selectlen,
-            sdslen(from->obuf)-from->selectlen);
+            from->obuf+from->prefixlen,
+            sdslen(from->obuf)-from->prefixlen);
     } else {
         for (j = 0; j < config.pipeline; j++)
             c->obuf = sdscatlen(c->obuf,cmd,len);
     }
 
     c->written = 0;
-    c->pending = config.pipeline;
+    c->pending = config.pipeline+c->prefix_pending;
     c->randptr = NULL;
     c->randlen = 0;
-    if (c->selectlen) c->pending++;
 
     /* Find substrings in the output buffer that need to be randomized. */
     if (config.randomkeys) {
@@ -371,7 +373,7 @@ static client createClient(char *cmd, size_t len, client from) {
             for (j = 0; j < (int)c->randlen; j++) {
                 c->randptr[j] = c->obuf + (from->randptr[j]-from->obuf);
                 /* Adjust for the different select prefix length. */
-                c->randptr[j] += c->selectlen - from->selectlen;
+                c->randptr[j] += c->prefixlen - from->prefixlen;
             }
         } else {
             char *p = c->obuf;