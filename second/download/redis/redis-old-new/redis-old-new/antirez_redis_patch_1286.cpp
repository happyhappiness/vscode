@@ -45,6 +45,8 @@
 #include <errno.h>
 #include <stdarg.h>
 #include <stdio.h>
+#include <poll.h>
+#include <limits.h>
 
 #include "net.h"
 #include "sds.h"
@@ -121,28 +123,38 @@ static int redisSetTcpNoDelay(redisContext *c, int fd) {
     return REDIS_OK;
 }
 
+#define __MAX_MSEC (((LONG_MAX) - 999) / 1000)
+
 static int redisContextWaitReady(redisContext *c, int fd, const struct timeval *timeout) {
-    struct timeval to;
-    struct timeval *toptr = NULL;
-    fd_set wfd;
+    struct pollfd   wfd[1];
+    long msec;
+
+    msec          = -1;
+    wfd[0].fd     = fd;
+    wfd[0].events = POLLOUT;
 
     /* Only use timeout when not NULL. */
     if (timeout != NULL) {
-        to = *timeout;
-        toptr = &to;
+        if (timeout->tv_usec > 1000000 || timeout->tv_sec > __MAX_MSEC) {
+            close(fd);
+            return REDIS_ERR;
+        }
+
+        msec = (timeout->tv_sec * 1000) + ((timeout->tv_usec + 999) / 1000);
+
+        if (msec < 0 || msec > INT_MAX) {
+            msec = INT_MAX;
+        }
     }
 
     if (errno == EINPROGRESS) {
-        FD_ZERO(&wfd);
-        FD_SET(fd, &wfd);
+        int res;
 
-        if (select(FD_SETSIZE, NULL, &wfd, NULL, toptr) == -1) {
-            __redisSetErrorFromErrno(c,REDIS_ERR_IO,"select(2)");
+        if ((res = poll(wfd, 1, msec)) == -1) {
+            __redisSetErrorFromErrno(c, REDIS_ERR_IO, "poll(2)");
             close(fd);
             return REDIS_ERR;
-        }
-
-        if (!FD_ISSET(fd, &wfd)) {
+        } else if (res == 0) {
             errno = ETIMEDOUT;
             __redisSetErrorFromErrno(c,REDIS_ERR_IO,NULL);
             close(fd);