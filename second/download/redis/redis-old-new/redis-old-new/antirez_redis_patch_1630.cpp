@@ -4,6 +4,7 @@
  * Copyright (c) 2010, Pieter Noordhuis <pcnoordhuis at gmail dot com>
  *
  * All rights reserved.
+ *
  * Redistribution and use in source and binary forms, with or without
  * modification, are permitted provided that the following conditions are met:
  *
@@ -32,6 +33,7 @@
 #include "fmacros.h"
 #include <sys/types.h>
 #include <sys/socket.h>
+#include <sys/select.h>
 #include <sys/un.h>
 #include <netinet/in.h>
 #include <netinet/tcp.h>
@@ -66,7 +68,7 @@ static int redisCreateSocket(redisContext *c, int type) {
     return s;
 }
 
-static int redisSetNonBlock(redisContext *c, int fd) {
+static int redisSetBlocking(redisContext *c, int fd, int blocking) {
     int flags;
 
     /* Set the socket nonblocking.
@@ -78,9 +80,15 @@ static int redisSetNonBlock(redisContext *c, int fd) {
         close(fd);
         return REDIS_ERR;
     }
-    if (fcntl(fd, F_SETFL, flags | O_NONBLOCK) == -1) {
+
+    if (blocking)
+        flags &= ~O_NONBLOCK;
+    else
+        flags |= O_NONBLOCK;
+
+    if (fcntl(fd, F_SETFL, flags) == -1) {
         __redisSetError(c,REDIS_ERR_IO,
-            sdscatprintf(sdsempty(), "fcntl(F_SETFL,O_NONBLOCK): %s", strerror(errno)));
+            sdscatprintf(sdsempty(), "fcntl(F_SETFL): %s", strerror(errno)));
         close(fd);
         return REDIS_ERR;
     }
@@ -92,19 +100,89 @@ static int redisSetTcpNoDelay(redisContext *c, int fd) {
     if (setsockopt(fd, IPPROTO_TCP, TCP_NODELAY, &yes, sizeof(yes)) == -1) {
         __redisSetError(c,REDIS_ERR_IO,
             sdscatprintf(sdsempty(), "setsockopt(TCP_NODELAY): %s", strerror(errno)));
+        close(fd);
         return REDIS_ERR;
     }
     return REDIS_OK;
 }
 
-int redisContextConnectTcp(redisContext *c, const char *addr, int port) {
+static int redisContextWaitReady(redisContext *c, int fd, const struct timeval *timeout) {
+    struct timeval to;
+    struct timeval *toptr = NULL;
+    fd_set wfd;
+    int err;
+    socklen_t errlen;
+
+    /* Only use timeout when not NULL. */
+    if (timeout != NULL) {
+        to = *timeout;
+        toptr = &to;
+    }
+
+    if (errno == EINPROGRESS) {
+        FD_ZERO(&wfd);
+        FD_SET(fd, &wfd);
+
+        if (select(FD_SETSIZE, NULL, &wfd, NULL, toptr) == -1) {
+            __redisSetError(c,REDIS_ERR_IO,
+                sdscatprintf(sdsempty(), "select(2): %s", strerror(errno)));
+            close(fd);
+            return REDIS_ERR;
+        }
+
+        if (!FD_ISSET(fd, &wfd)) {
+            errno = ETIMEDOUT;
+            __redisSetError(c,REDIS_ERR_IO,NULL);
+            close(fd);
+            return REDIS_ERR;
+        }
+
+        err = 0;
+        errlen = sizeof(err);
+        if (getsockopt(fd, SOL_SOCKET, SO_ERROR, &err, &errlen) == -1) {
+            __redisSetError(c,REDIS_ERR_IO,
+                sdscatprintf(sdsempty(), "getsockopt(SO_ERROR): %s", strerror(errno)));
+            close(fd);
+            return REDIS_ERR;
+        }
+
+        if (err) {
+            errno = err;
+            __redisSetError(c,REDIS_ERR_IO,NULL);
+            close(fd);
+            return REDIS_ERR;
+        }
+
+        return REDIS_OK;
+    }
+
+    __redisSetError(c,REDIS_ERR_IO,NULL);
+    close(fd);
+    return REDIS_ERR;
+}
+
+int redisContextSetTimeout(redisContext *c, struct timeval tv) {
+    if (setsockopt(c->fd,SOL_SOCKET,SO_RCVTIMEO,&tv,sizeof(tv)) == -1) {
+        __redisSetError(c,REDIS_ERR_IO,
+            sdscatprintf(sdsempty(), "setsockopt(SO_RCVTIMEO): %s", strerror(errno)));
+        return REDIS_ERR;
+    }
+    if (setsockopt(c->fd,SOL_SOCKET,SO_SNDTIMEO,&tv,sizeof(tv)) == -1) {
+        __redisSetError(c,REDIS_ERR_IO,
+            sdscatprintf(sdsempty(), "setsockopt(SO_SNDTIMEO): %s", strerror(errno)));
+        return REDIS_ERR;
+    }
+    return REDIS_OK;
+}
+
+int redisContextConnectTcp(redisContext *c, const char *addr, int port, struct timeval *timeout) {
     int s;
     int blocking = (c->flags & REDIS_BLOCK);
     struct sockaddr_in sa;
 
-    if ((s = redisCreateSocket(c,AF_INET)) == REDIS_ERR)
+    if ((s = redisCreateSocket(c,AF_INET)) < 0)
         return REDIS_ERR;
-    if (!blocking && redisSetNonBlock(c,s) == REDIS_ERR)
+    if (redisSetBlocking(c,s,0) != REDIS_OK)
         return REDIS_ERR;
 
     sa.sin_family = AF_INET;
@@ -126,30 +204,31 @@ int redisContextConnectTcp(redisContext *c, const char *addr, int port) {
         if (errno == EINPROGRESS && !blocking) {
             /* This is ok. */
         } else {
-            __redisSetError(c,REDIS_ERR_IO,NULL);
-            close(s);
-            return REDIS_ERR;
+            if (redisContextWaitReady(c,s,timeout) != REDIS_OK)
+                return REDIS_ERR;
         }
     }
 
-    if (redisSetTcpNoDelay(c,s) != REDIS_OK) {
-        close(s);
+    /* Reset socket to be blocking after connect(2). */
+    if (blocking && redisSetBlocking(c,s,1) != REDIS_OK)
+        return REDIS_ERR;
+
+    if (redisSetTcpNoDelay(c,s) != REDIS_OK)
         return REDIS_ERR;
-    }
 
     c->fd = s;
     c->flags |= REDIS_CONNECTED;
     return REDIS_OK;
 }
 
-int redisContextConnectUnix(redisContext *c, const char *path) {
+int redisContextConnectUnix(redisContext *c, const char *path, struct timeval *timeout) {
     int s;
     int blocking = (c->flags & REDIS_BLOCK);
     struct sockaddr_un sa;
 
-    if ((s = redisCreateSocket(c,AF_LOCAL)) == REDIS_ERR)
+    if ((s = redisCreateSocket(c,AF_LOCAL)) < 0)
         return REDIS_ERR;
-    if (!blocking && redisSetNonBlock(c,s) != REDIS_OK)
+    if (redisSetBlocking(c,s,0) != REDIS_OK)
         return REDIS_ERR;
 
     sa.sun_family = AF_LOCAL;
@@ -158,12 +237,15 @@ int redisContextConnectUnix(redisContext *c, const char *path) {
         if (errno == EINPROGRESS && !blocking) {
             /* This is ok. */
         } else {
-            __redisSetError(c,REDIS_ERR_IO,NULL);
-            close(s);
-            return REDIS_ERR;
+            if (redisContextWaitReady(c,s,timeout) != REDIS_OK)
+                return REDIS_ERR;
         }
     }
 
+    /* Reset socket to be blocking after connect(2). */
+    if (blocking && redisSetBlocking(c,s,1) != REDIS_OK)
+        return REDIS_ERR;
+
     c->fd = s;
     c->flags |= REDIS_CONNECTED;
     return REDIS_OK;