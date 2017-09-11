@@ -54,8 +54,15 @@
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
@@ -64,11 +71,11 @@ static void __redisSetErrorFromErrno(redisContext *c, int type, const char *pref
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
@@ -80,23 +87,24 @@ static int redisCreateSocket(redisContext *c, int type) {
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
 
@@ -105,38 +113,81 @@ static int redisSetBlocking(redisContext *c, int fd, int blocking) {
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
 
@@ -152,47 +203,45 @@ static int redisContextWaitReady(redisContext *c, int fd, const struct timeval *
 
         if ((res = poll(wfd, 1, msec)) == -1) {
             __redisSetErrorFromErrno(c, REDIS_ERR_IO, "poll(2)");
-            close(fd);
+            redisContextCloseFd(c);
             return REDIS_ERR;
         } else if (res == 0) {
             errno = ETIMEDOUT;
             __redisSetErrorFromErrno(c,REDIS_ERR_IO,NULL);
-            close(fd);
+            redisContextCloseFd(c);
             return REDIS_ERR;
         }
 
-        if (redisCheckSocketError(c, fd) != REDIS_OK)
+        if (redisCheckSocketError(c) != REDIS_OK)
             return REDIS_ERR;
 
         return REDIS_OK;
     }
 
     __redisSetErrorFromErrno(c,REDIS_ERR_IO,NULL);
-    close(fd);
+    redisContextCloseFd(c);
     return REDIS_ERR;
 }
 
-int redisCheckSocketError(redisContext *c, int fd) {
+int redisCheckSocketError(redisContext *c) {
     int err = 0;
     socklen_t errlen = sizeof(err);
 
-    if (getsockopt(fd, SOL_SOCKET, SO_ERROR, &err, &errlen) == -1) {
+    if (getsockopt(c->fd, SOL_SOCKET, SO_ERROR, &err, &errlen) == -1) {
         __redisSetErrorFromErrno(c,REDIS_ERR_IO,"getsockopt(SO_ERROR)");
-        close(fd);
         return REDIS_ERR;
     }
 
     if (err) {
         errno = err;
         __redisSetErrorFromErrno(c,REDIS_ERR_IO,NULL);
-        close(fd);
         return REDIS_ERR;
     }
 
     return REDIS_OK;
 }
 
-int redisContextSetTimeout(redisContext *c, struct timeval tv) {
+int redisContextSetTimeout(redisContext *c, const struct timeval tv) {
     if (setsockopt(c->fd,SOL_SOCKET,SO_RCVTIMEO,&tv,sizeof(tv)) == -1) {
         __redisSetErrorFromErrno(c,REDIS_ERR_IO,"setsockopt(SO_RCVTIMEO)");
         return REDIS_ERR;
@@ -204,10 +253,12 @@ int redisContextSetTimeout(redisContext *c, struct timeval tv) {
     return REDIS_OK;
 }
 
-int redisContextConnectTcp(redisContext *c, const char *addr, int port, struct timeval *timeout) {
+static int _redisContextConnectTcp(redisContext *c, const char *addr, int port,
+                                   const struct timeval *timeout,
+                                   const char *source_addr) {
     int s, rv;
     char _port[6];  /* strlen("65535"); */
-    struct addrinfo hints, *servinfo, *p;
+    struct addrinfo hints, *servinfo, *bservinfo, *p, *b;
     int blocking = (c->flags & REDIS_BLOCK);
 
     snprintf(_port, 6, "%d", port);
@@ -231,25 +282,47 @@ int redisContextConnectTcp(redisContext *c, const char *addr, int port, struct t
         if ((s = socket(p->ai_family,p->ai_socktype,p->ai_protocol)) == -1)
             continue;
 
-        if (redisSetBlocking(c,s,0) != REDIS_OK)
+        c->fd = s;
+        if (redisSetBlocking(c,0) != REDIS_OK)
             goto error;
+        if (source_addr) {
+            int bound = 0;
+            /* Using getaddrinfo saves us from self-determining IPv4 vs IPv6 */
+            if ((rv = getaddrinfo(source_addr, NULL, &hints, &bservinfo)) != 0) {
+                char buf[128];
+                snprintf(buf,sizeof(buf),"Can't get addr: %s",gai_strerror(rv));
+                __redisSetError(c,REDIS_ERR_OTHER,buf);
+                goto error;
+            }
+            for (b = bservinfo; b != NULL; b = b->ai_next) {
+                if (bind(s,b->ai_addr,b->ai_addrlen) != -1) {
+                    bound = 1;
+                    break;
+                }
+            }
+            if (!bound) {
+                char buf[128];
+                snprintf(buf,sizeof(buf),"Can't bind socket: %s",strerror(errno));
+                __redisSetError(c,REDIS_ERR_OTHER,buf);
+                goto error;
+            }
+        }
         if (connect(s,p->ai_addr,p->ai_addrlen) == -1) {
             if (errno == EHOSTUNREACH) {
-                close(s);
+                redisContextCloseFd(c);
                 continue;
             } else if (errno == EINPROGRESS && !blocking) {
                 /* This is ok. */
             } else {
-                if (redisContextWaitReady(c,s,timeout) != REDIS_OK)
+                if (redisContextWaitReady(c,timeout) != REDIS_OK)
                     goto error;
             }
         }
-        if (blocking && redisSetBlocking(c,s,1) != REDIS_OK)
+        if (blocking && redisSetBlocking(c,1) != REDIS_OK)
             goto error;
-        if (redisSetTcpNoDelay(c,s) != REDIS_OK)
+        if (redisSetTcpNoDelay(c) != REDIS_OK)
             goto error;
 
-        c->fd = s;
         c->flags |= REDIS_CONNECTED;
         rv = REDIS_OK;
         goto end;
@@ -268,32 +341,41 @@ int redisContextConnectTcp(redisContext *c, const char *addr, int port, struct t
     return rv;  // Need to return REDIS_OK if alright
 }
 
-int redisContextConnectUnix(redisContext *c, const char *path, struct timeval *timeout) {
-    int s;
+int redisContextConnectTcp(redisContext *c, const char *addr, int port,
+                           const struct timeval *timeout) {
+    return _redisContextConnectTcp(c, addr, port, timeout, NULL);
+}
+
+int redisContextConnectBindTcp(redisContext *c, const char *addr, int port,
+                               const struct timeval *timeout,
+                               const char *source_addr) {
+    return _redisContextConnectTcp(c, addr, port, timeout, source_addr);
+}
+
+int redisContextConnectUnix(redisContext *c, const char *path, const struct timeval *timeout) {
     int blocking = (c->flags & REDIS_BLOCK);
     struct sockaddr_un sa;
 
-    if ((s = redisCreateSocket(c,AF_LOCAL)) < 0)
+    if (redisCreateSocket(c,AF_LOCAL) < 0)
         return REDIS_ERR;
-    if (redisSetBlocking(c,s,0) != REDIS_OK)
+    if (redisSetBlocking(c,0) != REDIS_OK)
         return REDIS_ERR;
 
     sa.sun_family = AF_LOCAL;
     strncpy(sa.sun_path,path,sizeof(sa.sun_path)-1);
-    if (connect(s, (struct sockaddr*)&sa, sizeof(sa)) == -1) {
+    if (connect(c->fd, (struct sockaddr*)&sa, sizeof(sa)) == -1) {
         if (errno == EINPROGRESS && !blocking) {
             /* This is ok. */
         } else {
-            if (redisContextWaitReady(c,s,timeout) != REDIS_OK)
+            if (redisContextWaitReady(c,timeout) != REDIS_OK)
                 return REDIS_ERR;
         }
     }
 
     /* Reset socket to be blocking after connect(2). */
-    if (blocking && redisSetBlocking(c,s,1) != REDIS_OK)
+    if (blocking && redisSetBlocking(c,1) != REDIS_OK)
         return REDIS_ERR;
 
-    c->fd = s;
     c->flags |= REDIS_CONNECTED;
     return REDIS_OK;
 }