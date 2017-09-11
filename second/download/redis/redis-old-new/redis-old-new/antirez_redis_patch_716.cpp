@@ -34,6 +34,7 @@
 #include <sys/socket.h>
 #include <sys/stat.h>
 #include <sys/un.h>
+#include <sys/time.h>
 #include <netinet/in.h>
 #include <netinet/tcp.h>
 #include <arpa/inet.h>
@@ -57,24 +58,37 @@ static void anetSetError(char *err, const char *fmt, ...)
     va_end(ap);
 }
 
-int anetNonBlock(char *err, int fd)
-{
+int anetSetBlock(char *err, int fd, int non_block) {
     int flags;
 
-    /* Set the socket non-blocking.
+    /* Set the socket blocking (if non_block is zero) or non-blocking.
      * Note that fcntl(2) for F_GETFL and F_SETFL can't be
      * interrupted by a signal. */
     if ((flags = fcntl(fd, F_GETFL)) == -1) {
         anetSetError(err, "fcntl(F_GETFL): %s", strerror(errno));
         return ANET_ERR;
     }
-    if (fcntl(fd, F_SETFL, flags | O_NONBLOCK) == -1) {
+
+    if (non_block)
+        flags |= O_NONBLOCK;
+    else
+        flags &= ~O_NONBLOCK;
+
+    if (fcntl(fd, F_SETFL, flags) == -1) {
         anetSetError(err, "fcntl(F_SETFL,O_NONBLOCK): %s", strerror(errno));
         return ANET_ERR;
     }
     return ANET_OK;
 }
 
+int anetNonBlock(char *err, int fd) {
+    return anetSetBlock(err,fd,1);
+}
+
+int anetBlock(char *err, int fd) {
+    return anetSetBlock(err,fd,0);
+}
+
 /* Set TCP keep alive option to detect dead peers. The interval option
  * is only used for Linux as we are using Linux-specific APIs to set
  * the probe send time, interval, and count. */
@@ -165,6 +179,20 @@ int anetTcpKeepAlive(char *err, int fd)
     return ANET_OK;
 }
 
+/* Set the socket send timeout (SO_SNDTIMEO socket option) to the specified
+ * number of milliseconds, or disable it if the 'ms' argument is zero. */
+int anetSendTimeout(char *err, int fd, long long ms) {
+    struct timeval tv;
+
+    tv.tv_sec = ms/1000;
+    tv.tv_usec = (ms%1000)*1000;
+    if (setsockopt(fd, SOL_SOCKET, SO_SNDTIMEO, &tv, sizeof(tv)) == -1) {
+        anetSetError(err, "setsockopt SO_SNDTIMEO: %s", strerror(errno));
+        return ANET_ERR;
+    }
+    return ANET_OK;
+}
+
 /* anetGenericResolve() is called by anetResolve() and anetResolveIP() to
  * do the actual work. It resolves the hostname "host" and set the string
  * representation of the IP address into the buffer pointed by "ipbuf".