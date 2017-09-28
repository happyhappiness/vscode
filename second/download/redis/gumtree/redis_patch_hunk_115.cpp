 #include "net.h"
 #include "sds.h"
 
 /* Defined in hiredis.c */
 void __redisSetError(redisContext *c, int type, const char *str);
 
+static void redisContextCloseFd(redisContext *c) {
+    if (c && c->fd >= 0) {
+        close(c->fd);
+        c->fd = -1;
+    }
+}
+
 static void __redisSetErrorFromErrno(redisContext *c, int type, const char *prefix) {
-    char buf[128];
+    char buf[128] = { 0 };
     size_t len = 0;
 
     if (prefix != NULL)
         len = snprintf(buf,sizeof(buf),"%s: ",prefix);
     strerror_r(errno,buf+len,sizeof(buf)-len);
     __redisSetError(c,type,buf);
 }
 
-static int redisSetReuseAddr(redisContext *c, int fd) {
+static int redisSetReuseAddr(redisContext *c) {
     int on = 1;
-    if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)) == -1) {
+    if (setsockopt(c->fd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)) == -1) {
         __redisSetErrorFromErrno(c,REDIS_ERR_IO,NULL);
-        close(fd);
+        redisContextCloseFd(c);
         return REDIS_ERR;
     }
     return REDIS_OK;
 }
 
 static int redisCreateSocket(redisContext *c, int type) {
     int s;
     if ((s = socket(type, SOCK_STREAM, 0)) == -1) {
         __redisSetErrorFromErrno(c,REDIS_ERR_IO,NULL);
         return REDIS_ERR;
     }
+    c->fd = s;
     if (type == AF_INET) {
-        if (redisSetReuseAddr(c,s) == REDIS_ERR) {
+        if (redisSetReuseAddr(c) == REDIS_ERR) {
             return REDIS_ERR;
         }
     }
-    return s;
+    return REDIS_OK;
 }
 
-static int redisSetBlocking(redisContext *c, int fd, int blocking) {
+static int redisSetBlocking(redisContext *c, int blocking) {
     int flags;
 
     /* Set the socket nonblocking.
      * Note that fcntl(2) for F_GETFL and F_SETFL can't be
      * interrupted by a signal. */
-    if ((flags = fcntl(fd, F_GETFL)) == -1) {
+    if ((flags = fcntl(c->fd, F_GETFL)) == -1) {
         __redisSetErrorFromErrno(c,REDIS_ERR_IO,"fcntl(F_GETFL)");
-        close(fd);
+        redisContextCloseFd(c);
         return REDIS_ERR;
     }
 
     if (blocking)
         flags &= ~O_NONBLOCK;
     else
         flags |= O_NONBLOCK;
 
-    if (fcntl(fd, F_SETFL, flags) == -1) {
+    if (fcntl(c->fd, F_SETFL, flags) == -1) {
         __redisSetErrorFromErrno(c,REDIS_ERR_IO,"fcntl(F_SETFL)");
-        close(fd);
+        redisContextCloseFd(c);
+        return REDIS_ERR;
+    }
+    return REDIS_OK;
+}
+
+int redisKeepAlive(redisContext *c, int interval) {
+    int val = 1;
+    int fd = c->fd;
+
+    if (setsockopt(fd, SOL_SOCKET, SO_KEEPALIVE, &val, sizeof(val)) == -1){
+        __redisSetError(c,REDIS_ERR_OTHER,strerror(errno));
+        return REDIS_ERR;
+    }
+
+    val = interval;
+
+#ifdef _OSX
+    if (setsockopt(fd, IPPROTO_TCP, TCP_KEEPALIVE, &val, sizeof(val)) < 0) {
+        __redisSetError(c,REDIS_ERR_OTHER,strerror(errno));
+        return REDIS_ERR;
+    }
+#else
+#ifndef __sun
+    val = interval;
+    if (setsockopt(fd, IPPROTO_TCP, TCP_KEEPIDLE, &val, sizeof(val)) < 0) {
+        __redisSetError(c,REDIS_ERR_OTHER,strerror(errno));
+        return REDIS_ERR;
+    }
+
+    val = interval/3;
+    if (val == 0) val = 1;
+    if (setsockopt(fd, IPPROTO_TCP, TCP_KEEPINTVL, &val, sizeof(val)) < 0) {
+        __redisSetError(c,REDIS_ERR_OTHER,strerror(errno));
+        return REDIS_ERR;
+    }
+
+    val = 3;
+    if (setsockopt(fd, IPPROTO_TCP, TCP_KEEPCNT, &val, sizeof(val)) < 0) {
+        __redisSetError(c,REDIS_ERR_OTHER,strerror(errno));
         return REDIS_ERR;
     }
+#endif
+#endif
+
     return REDIS_OK;
 }
 
-static int redisSetTcpNoDelay(redisContext *c, int fd) {
+static int redisSetTcpNoDelay(redisContext *c) {
     int yes = 1;
-    if (setsockopt(fd, IPPROTO_TCP, TCP_NODELAY, &yes, sizeof(yes)) == -1) {
+    if (setsockopt(c->fd, IPPROTO_TCP, TCP_NODELAY, &yes, sizeof(yes)) == -1) {
         __redisSetErrorFromErrno(c,REDIS_ERR_IO,"setsockopt(TCP_NODELAY)");
-        close(fd);
+        redisContextCloseFd(c);
         return REDIS_ERR;
     }
     return REDIS_OK;
 }
 
 #define __MAX_MSEC (((LONG_MAX) - 999) / 1000)
 
-static int redisContextWaitReady(redisContext *c, int fd, const struct timeval *timeout) {
+static int redisContextWaitReady(redisContext *c, const struct timeval *timeout) {
     struct pollfd   wfd[1];
     long msec;
 
     msec          = -1;
-    wfd[0].fd     = fd;
+    wfd[0].fd     = c->fd;
     wfd[0].events = POLLOUT;
 
     /* Only use timeout when not NULL. */
     if (timeout != NULL) {
         if (timeout->tv_usec > 1000000 || timeout->tv_sec > __MAX_MSEC) {
-            close(fd);
+            __redisSetErrorFromErrno(c, REDIS_ERR_IO, NULL);
+            redisContextCloseFd(c);
             return REDIS_ERR;
         }
 
         msec = (timeout->tv_sec * 1000) + ((timeout->tv_usec + 999) / 1000);
 
         if (msec < 0 || msec > INT_MAX) {
