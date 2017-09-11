@@ -1,7 +1,7 @@
 /* Extracted from anet.c to work properly with Hiredis error reporting.
  *
- * Copyright (c) 2006-2010, Salvatore Sanfilippo <antirez at gmail dot com>
- * Copyright (c) 2010, Pieter Noordhuis <pcnoordhuis at gmail dot com>
+ * Copyright (c) 2006-2011, Salvatore Sanfilippo <antirez at gmail dot com>
+ * Copyright (c) 2010-2011, Pieter Noordhuis <pcnoordhuis at gmail dot com>
  *
  * All rights reserved.
  *
@@ -49,19 +49,37 @@
 #include "net.h"
 #include "sds.h"
 
-/* Forward declaration */
-void __redisSetError(redisContext *c, int type, sds err);
+/* Defined in hiredis.c */
+void __redisSetError(redisContext *c, int type, const char *str);
+
+static void __redisSetErrorFromErrno(redisContext *c, int type, const char *prefix) {
+    char buf[128];
+    size_t len = 0;
+
+    if (prefix != NULL)
+        len = snprintf(buf,sizeof(buf),"%s: ",prefix);
+    strerror_r(errno,buf+len,sizeof(buf)-len);
+    __redisSetError(c,type,buf);
+}
+
+static int redisSetReuseAddr(redisContext *c, int fd) {
+    int on = 1;
+    if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)) == -1) {
+        __redisSetErrorFromErrno(c,REDIS_ERR_IO,NULL);
+        close(fd);
+        return REDIS_ERR;
+    }
+    return REDIS_OK;
+}
 
 static int redisCreateSocket(redisContext *c, int type) {
-    int s, on = 1;
+    int s;
     if ((s = socket(type, SOCK_STREAM, 0)) == -1) {
-        __redisSetError(c,REDIS_ERR_IO,NULL);
+        __redisSetErrorFromErrno(c,REDIS_ERR_IO,NULL);
         return REDIS_ERR;
     }
     if (type == AF_INET) {
-        if (setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)) == -1) {
-            __redisSetError(c,REDIS_ERR_IO,NULL);
-            close(s);
+        if (redisSetReuseAddr(c,s) == REDIS_ERR) {
             return REDIS_ERR;
         }
     }
@@ -75,8 +93,7 @@ static int redisSetBlocking(redisContext *c, int fd, int blocking) {
      * Note that fcntl(2) for F_GETFL and F_SETFL can't be
      * interrupted by a signal. */
     if ((flags = fcntl(fd, F_GETFL)) == -1) {
-        __redisSetError(c,REDIS_ERR_IO,
-            sdscatprintf(sdsempty(), "fcntl(F_GETFL): %s", strerror(errno)));
+        __redisSetErrorFromErrno(c,REDIS_ERR_IO,"fcntl(F_GETFL)");
         close(fd);
         return REDIS_ERR;
     }
@@ -87,8 +104,7 @@ static int redisSetBlocking(redisContext *c, int fd, int blocking) {
         flags |= O_NONBLOCK;
 
     if (fcntl(fd, F_SETFL, flags) == -1) {
-        __redisSetError(c,REDIS_ERR_IO,
-            sdscatprintf(sdsempty(), "fcntl(F_SETFL): %s", strerror(errno)));
+        __redisSetErrorFromErrno(c,REDIS_ERR_IO,"fcntl(F_SETFL)");
         close(fd);
         return REDIS_ERR;
     }
@@ -98,8 +114,7 @@ static int redisSetBlocking(redisContext *c, int fd, int blocking) {
 static int redisSetTcpNoDelay(redisContext *c, int fd) {
     int yes = 1;
     if (setsockopt(fd, IPPROTO_TCP, TCP_NODELAY, &yes, sizeof(yes)) == -1) {
-        __redisSetError(c,REDIS_ERR_IO,
-            sdscatprintf(sdsempty(), "setsockopt(TCP_NODELAY): %s", strerror(errno)));
+        __redisSetErrorFromErrno(c,REDIS_ERR_IO,"setsockopt(TCP_NODELAY)");
         close(fd);
         return REDIS_ERR;
     }
@@ -110,8 +125,6 @@ static int redisContextWaitReady(redisContext *c, int fd, const struct timeval *
     struct timeval to;
     struct timeval *toptr = NULL;
     fd_set wfd;
-    int err;
-    socklen_t errlen;
 
     /* Only use timeout when not NULL. */
     if (timeout != NULL) {
@@ -124,101 +137,115 @@ static int redisContextWaitReady(redisContext *c, int fd, const struct timeval *
         FD_SET(fd, &wfd);
 
         if (select(FD_SETSIZE, NULL, &wfd, NULL, toptr) == -1) {
-            __redisSetError(c,REDIS_ERR_IO,
-                sdscatprintf(sdsempty(), "select(2): %s", strerror(errno)));
+            __redisSetErrorFromErrno(c,REDIS_ERR_IO,"select(2)");
             close(fd);
             return REDIS_ERR;
         }
 
         if (!FD_ISSET(fd, &wfd)) {
             errno = ETIMEDOUT;
-            __redisSetError(c,REDIS_ERR_IO,NULL);
+            __redisSetErrorFromErrno(c,REDIS_ERR_IO,NULL);
             close(fd);
             return REDIS_ERR;
         }
 
-        err = 0;
-        errlen = sizeof(err);
-        if (getsockopt(fd, SOL_SOCKET, SO_ERROR, &err, &errlen) == -1) {
-            __redisSetError(c,REDIS_ERR_IO,
-                sdscatprintf(sdsempty(), "getsockopt(SO_ERROR): %s", strerror(errno)));
-            close(fd);
+        if (redisCheckSocketError(c, fd) != REDIS_OK)
             return REDIS_ERR;
-        }
-
-        if (err) {
-            errno = err;
-            __redisSetError(c,REDIS_ERR_IO,NULL);
-            close(fd);
-            return REDIS_ERR;
-        }
 
         return REDIS_OK;
     }
 
-    __redisSetError(c,REDIS_ERR_IO,NULL);
+    __redisSetErrorFromErrno(c,REDIS_ERR_IO,NULL);
     close(fd);
     return REDIS_ERR;
 }
 
+int redisCheckSocketError(redisContext *c, int fd) {
+    int err = 0;
+    socklen_t errlen = sizeof(err);
+
+    if (getsockopt(fd, SOL_SOCKET, SO_ERROR, &err, &errlen) == -1) {
+        __redisSetErrorFromErrno(c,REDIS_ERR_IO,"getsockopt(SO_ERROR)");
+        close(fd);
+        return REDIS_ERR;
+    }
+
+    if (err) {
+        errno = err;
+        __redisSetErrorFromErrno(c,REDIS_ERR_IO,NULL);
+        close(fd);
+        return REDIS_ERR;
+    }
+
+    return REDIS_OK;
+}
+
 int redisContextSetTimeout(redisContext *c, struct timeval tv) {
     if (setsockopt(c->fd,SOL_SOCKET,SO_RCVTIMEO,&tv,sizeof(tv)) == -1) {
-        __redisSetError(c,REDIS_ERR_IO,
-            sdscatprintf(sdsempty(), "setsockopt(SO_RCVTIMEO): %s", strerror(errno)));
+        __redisSetErrorFromErrno(c,REDIS_ERR_IO,"setsockopt(SO_RCVTIMEO)");
         return REDIS_ERR;
     }
     if (setsockopt(c->fd,SOL_SOCKET,SO_SNDTIMEO,&tv,sizeof(tv)) == -1) {
-        __redisSetError(c,REDIS_ERR_IO,
-            sdscatprintf(sdsempty(), "setsockopt(SO_SNDTIMEO): %s", strerror(errno)));
+        __redisSetErrorFromErrno(c,REDIS_ERR_IO,"setsockopt(SO_SNDTIMEO)");
         return REDIS_ERR;
     }
     return REDIS_OK;
 }
 
 int redisContextConnectTcp(redisContext *c, const char *addr, int port, struct timeval *timeout) {
-    int s;
+    int s, rv;
+    char _port[6];  /* strlen("65535"); */
+    struct addrinfo hints, *servinfo, *p;
     int blocking = (c->flags & REDIS_BLOCK);
-    struct sockaddr_in sa;
 
-    if ((s = redisCreateSocket(c,AF_INET)) < 0)
-        return REDIS_ERR;
-    if (redisSetBlocking(c,s,0) != REDIS_OK)
-        return REDIS_ERR;
-
-    sa.sin_family = AF_INET;
-    sa.sin_port = htons(port);
-    if (inet_aton(addr, &sa.sin_addr) == 0) {
-        struct hostent *he;
+    snprintf(_port, 6, "%d", port);
+    memset(&hints,0,sizeof(hints));
+    hints.ai_family = AF_INET;
+    hints.ai_socktype = SOCK_STREAM;
 
-        he = gethostbyname(addr);
-        if (he == NULL) {
-            __redisSetError(c,REDIS_ERR_OTHER,
-                sdscatprintf(sdsempty(),"Can't resolve: %s",addr));
-            close(s);
-            return REDIS_ERR;
-        }
-        memcpy(&sa.sin_addr, he->h_addr, sizeof(struct in_addr));
+    if ((rv = getaddrinfo(addr,_port,&hints,&servinfo)) != 0) {
+        __redisSetError(c,REDIS_ERR_OTHER,gai_strerror(rv));
+        return REDIS_ERR;
     }
-
-    if (connect(s, (struct sockaddr*)&sa, sizeof(sa)) == -1) {
-        if (errno == EINPROGRESS && !blocking) {
-            /* This is ok. */
-        } else {
-            if (redisContextWaitReady(c,s,timeout) != REDIS_OK)
-                return REDIS_ERR;
+    for (p = servinfo; p != NULL; p = p->ai_next) {
+        if ((s = socket(p->ai_family,p->ai_socktype,p->ai_protocol)) == -1)
+            continue;
+
+        if (redisSetBlocking(c,s,0) != REDIS_OK)
+            goto error;
+        if (connect(s,p->ai_addr,p->ai_addrlen) == -1) {
+            if (errno == EHOSTUNREACH) {
+                close(s);
+                continue;
+            } else if (errno == EINPROGRESS && !blocking) {
+                /* This is ok. */
+            } else {
+                if (redisContextWaitReady(c,s,timeout) != REDIS_OK)
+                    goto error;
+            }
         }
+        if (blocking && redisSetBlocking(c,s,1) != REDIS_OK)
+            goto error;
+        if (redisSetTcpNoDelay(c,s) != REDIS_OK)
+            goto error;
+
+        c->fd = s;
+        c->flags |= REDIS_CONNECTED;
+        rv = REDIS_OK;
+        goto end;
+    }
+    if (p == NULL) {
+        char buf[128];
+        snprintf(buf,sizeof(buf),"Can't create socket: %s",strerror(errno));
+        __redisSetError(c,REDIS_ERR_OTHER,buf);
+        goto error;
     }
 
-    /* Reset socket to be blocking after connect(2). */
-    if (blocking && redisSetBlocking(c,s,1) != REDIS_OK)
-        return REDIS_ERR;
-
-    if (redisSetTcpNoDelay(c,s) != REDIS_OK)
-        return REDIS_ERR;
-
-    c->fd = s;
-    c->flags |= REDIS_CONNECTED;
-    return REDIS_OK;
+error:
+    rv = REDIS_ERR;
+end:
+    freeaddrinfo(servinfo);
+    return rv;  // Need to return REDIS_OK if alright
 }
 
 int redisContextConnectUnix(redisContext *c, const char *path, struct timeval *timeout) {