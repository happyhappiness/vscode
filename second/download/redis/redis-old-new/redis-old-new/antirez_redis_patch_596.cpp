@@ -86,7 +86,7 @@ typedef struct _client {
     char **randptr;         /* Pointers to :rand: strings inside the command buf */
     size_t randlen;         /* Number of pointers in client->randptr */
     size_t randfree;        /* Number of unused pointers in client->randptr */
-    unsigned int written;   /* Bytes of 'obuf' already written */
+    size_t written;         /* Bytes of 'obuf' already written */
     long long start;        /* Start time of a request */
     long long latency;      /* Request latency */
     int pending;            /* Number of pending requests (replies to consume) */
@@ -266,7 +266,7 @@ static void writeHandler(aeEventLoop *el, int fd, void *privdata, int mask) {
 
     if (sdslen(c->obuf) > c->written) {
         void *ptr = c->obuf+c->written;
-        int nwritten = write(c->context->fd,ptr,sdslen(c->obuf)-c->written);
+        ssize_t nwritten = write(c->context->fd,ptr,sdslen(c->obuf)-c->written);
         if (nwritten == -1) {
             if (errno != EPIPE)
                 fprintf(stderr, "Writing to socket: %s\n", strerror(errno));