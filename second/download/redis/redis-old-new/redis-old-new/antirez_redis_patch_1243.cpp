@@ -61,7 +61,7 @@ int anetNonBlock(char *err, int fd)
 {
     int flags;
 
-    /* Set the socket nonblocking.
+    /* Set the socket non-blocking.
      * Note that fcntl(2) for F_GETFL and F_SETFL can't be
      * interrupted by a signal. */
     if ((flags = fcntl(fd, F_GETFL)) == -1) {
@@ -132,7 +132,7 @@ static int anetCreateSocket(char *err, int domain) {
         return ANET_ERR;
     }
 
-    /* Make sure connection-intensive things like the redis benckmark
+    /* Make sure connection-intensive things like the redis benchmark
      * will be able to close/open sockets a zillion of times */
     if (setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)) == -1) {
         anetSetError(err, "setsockopt SO_REUSEADDR: %s", strerror(errno));