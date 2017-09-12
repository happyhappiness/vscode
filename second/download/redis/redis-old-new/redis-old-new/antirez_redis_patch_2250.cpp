@@ -322,7 +322,8 @@ static void writeHandler(aeEventLoop *el, int fd, void *privdata, int mask)
         int len = sdslen(c->obuf) - c->written;
         int nwritten = write(c->fd, ptr, len);
         if (nwritten == -1) {
-            fprintf(stderr, "Writing to socket: %s\n", strerror(errno));
+            if (errno != EPIPE)
+                fprintf(stderr, "Writing to socket: %s\n", strerror(errno));
             freeClient(c);
             return;
         }