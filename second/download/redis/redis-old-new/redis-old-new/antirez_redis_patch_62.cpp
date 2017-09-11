@@ -1,7 +1,9 @@
 /* Extracted from anet.c to work properly with Hiredis error reporting.
  *
- * Copyright (c) 2006-2011, Salvatore Sanfilippo <antirez at gmail dot com>
- * Copyright (c) 2010-2011, Pieter Noordhuis <pcnoordhuis at gmail dot com>
+ * Copyright (c) 2009-2011, Salvatore Sanfilippo <antirez at gmail dot com>
+ * Copyright (c) 2010-2014, Pieter Noordhuis <pcnoordhuis at gmail dot com>
+ * Copyright (c) 2015, Matt Stancliff <matt at genges dot com>,
+ *                     Jan-Erik Rediger <janerik at fnordig dot com>
  *
  * All rights reserved.
  *
@@ -47,6 +49,7 @@
 #include <stdio.h>
 #include <poll.h>
 #include <limits.h>
+#include <stdlib.h>
 
 #include "net.h"
 #include "sds.h"
@@ -67,7 +70,7 @@ static void __redisSetErrorFromErrno(redisContext *c, int type, const char *pref
 
     if (prefix != NULL)
         len = snprintf(buf,sizeof(buf),"%s: ",prefix);
-    strerror_r(errno,buf+len,sizeof(buf)-len);
+    __redis_strerror_r(errno, (char *)(buf + len), sizeof(buf) - len);
     __redisSetError(c,type,buf);
 }
 
@@ -138,7 +141,7 @@ int redisKeepAlive(redisContext *c, int interval) {
         return REDIS_ERR;
     }
 #else
-#ifndef __sun
+#if defined(__GLIBC__) && !defined(__FreeBSD_kernel__)
     val = interval;
     if (setsockopt(fd, IPPROTO_TCP, TCP_KEEPIDLE, &val, sizeof(val)) < 0) {
         __redisSetError(c,REDIS_ERR_OTHER,strerror(errno));
@@ -175,19 +178,15 @@ static int redisSetTcpNoDelay(redisContext *c) {
 
 #define __MAX_MSEC (((LONG_MAX) - 999) / 1000)
 
-static int redisContextWaitReady(redisContext *c, const struct timeval *timeout) {
-    struct pollfd   wfd[1];
-    long msec;
-
-    msec          = -1;
-    wfd[0].fd     = c->fd;
-    wfd[0].events = POLLOUT;
+static int redisContextTimeoutMsec(redisContext *c, long *result)
+{
+    const struct timeval *timeout = c->timeout;
+    long msec = -1;
 
     /* Only use timeout when not NULL. */
     if (timeout != NULL) {
         if (timeout->tv_usec > 1000000 || timeout->tv_sec > __MAX_MSEC) {
-            __redisSetErrorFromErrno(c, REDIS_ERR_IO, NULL);
-            redisContextCloseFd(c);
+            *result = msec;
             return REDIS_ERR;
         }
 
@@ -198,6 +197,16 @@ static int redisContextWaitReady(redisContext *c, const struct timeval *timeout)
         }
     }
 
+    *result = msec;
+    return REDIS_OK;
+}
+
+static int redisContextWaitReady(redisContext *c, long msec) {
+    struct pollfd   wfd[1];
+
+    wfd[0].fd     = c->fd;
+    wfd[0].events = POLLOUT;
+
     if (errno == EINPROGRESS) {
         int res;
 
@@ -256,10 +265,57 @@ int redisContextSetTimeout(redisContext *c, const struct timeval tv) {
 static int _redisContextConnectTcp(redisContext *c, const char *addr, int port,
                                    const struct timeval *timeout,
                                    const char *source_addr) {
-    int s, rv;
+    int s, rv, n;
     char _port[6];  /* strlen("65535"); */
     struct addrinfo hints, *servinfo, *bservinfo, *p, *b;
     int blocking = (c->flags & REDIS_BLOCK);
+    int reuseaddr = (c->flags & REDIS_REUSEADDR);
+    int reuses = 0;
+    long timeout_msec = -1;
+
+    servinfo = NULL;
+    c->connection_type = REDIS_CONN_TCP;
+    c->tcp.port = port;
+
+    /* We need to take possession of the passed parameters
+     * to make them reusable for a reconnect.
+     * We also carefully check we don't free data we already own,
+     * as in the case of the reconnect method.
+     *
+     * This is a bit ugly, but atleast it works and doesn't leak memory.
+     **/
+    if (c->tcp.host != addr) {
+        if (c->tcp.host)
+            free(c->tcp.host);
+
+        c->tcp.host = strdup(addr);
+    }
+
+    if (timeout) {
+        if (c->timeout != timeout) {
+            if (c->timeout == NULL)
+                c->timeout = malloc(sizeof(struct timeval));
+
+            memcpy(c->timeout, timeout, sizeof(struct timeval));
+        }
+    } else {
+        if (c->timeout)
+            free(c->timeout);
+        c->timeout = NULL;
+    }
+
+    if (redisContextTimeoutMsec(c, &timeout_msec) != REDIS_OK) {
+        __redisSetError(c, REDIS_ERR_IO, "Invalid timeout specified");
+        goto error;
+    }
+
+    if (source_addr == NULL) {
+        free(c->tcp.source_addr);
+        c->tcp.source_addr = NULL;
+    } else if (c->tcp.source_addr != source_addr) {
+        free(c->tcp.source_addr);
+        c->tcp.source_addr = strdup(source_addr);
+    }
 
     snprintf(_port, 6, "%d", port);
     memset(&hints,0,sizeof(hints));
@@ -271,29 +327,39 @@ static int _redisContextConnectTcp(redisContext *c, const char *addr, int port,
      * as this would add latency to every connect. Otherwise a more sensible
      * route could be: Use IPv6 if both addresses are available and there is IPv6
      * connectivity. */
-    if ((rv = getaddrinfo(addr,_port,&hints,&servinfo)) != 0) {
+    if ((rv = getaddrinfo(c->tcp.host,_port,&hints,&servinfo)) != 0) {
          hints.ai_family = AF_INET6;
          if ((rv = getaddrinfo(addr,_port,&hints,&servinfo)) != 0) {
             __redisSetError(c,REDIS_ERR_OTHER,gai_strerror(rv));
             return REDIS_ERR;
         }
     }
     for (p = servinfo; p != NULL; p = p->ai_next) {
+addrretry:
         if ((s = socket(p->ai_family,p->ai_socktype,p->ai_protocol)) == -1)
             continue;
 
         c->fd = s;
         if (redisSetBlocking(c,0) != REDIS_OK)
             goto error;
-        if (source_addr) {
+        if (c->tcp.source_addr) {
             int bound = 0;
             /* Using getaddrinfo saves us from self-determining IPv4 vs IPv6 */
-            if ((rv = getaddrinfo(source_addr, NULL, &hints, &bservinfo)) != 0) {
+            if ((rv = getaddrinfo(c->tcp.source_addr, NULL, &hints, &bservinfo)) != 0) {
                 char buf[128];
                 snprintf(buf,sizeof(buf),"Can't get addr: %s",gai_strerror(rv));
                 __redisSetError(c,REDIS_ERR_OTHER,buf);
                 goto error;
             }
+
+            if (reuseaddr) {
+                n = 1;
+                if (setsockopt(s, SOL_SOCKET, SO_REUSEADDR, (char*) &n,
+                               sizeof(n)) < 0) {
+                    goto error;
+                }
+            }
+
             for (b = bservinfo; b != NULL; b = b->ai_next) {
                 if (bind(s,b->ai_addr,b->ai_addrlen) != -1) {
                     bound = 1;
@@ -314,8 +380,15 @@ static int _redisContextConnectTcp(redisContext *c, const char *addr, int port,
                 continue;
             } else if (errno == EINPROGRESS && !blocking) {
                 /* This is ok. */
+            } else if (errno == EADDRNOTAVAIL && reuseaddr) {
+                if (++reuses >= REDIS_CONNECT_RETRIES) {
+                    goto error;
+                } else {
+                    redisContextCloseFd(c);
+                    goto addrretry;
+                }
             } else {
-                if (redisContextWaitReady(c,timeout) != REDIS_OK)
+                if (redisContextWaitReady(c,timeout_msec) != REDIS_OK)
                     goto error;
             }
         }
@@ -356,19 +429,40 @@ int redisContextConnectBindTcp(redisContext *c, const char *addr, int port,
 int redisContextConnectUnix(redisContext *c, const char *path, const struct timeval *timeout) {
     int blocking = (c->flags & REDIS_BLOCK);
     struct sockaddr_un sa;
+    long timeout_msec = -1;
 
     if (redisCreateSocket(c,AF_LOCAL) < 0)
         return REDIS_ERR;
     if (redisSetBlocking(c,0) != REDIS_OK)
         return REDIS_ERR;
 
+    c->connection_type = REDIS_CONN_UNIX;
+    if (c->unix_sock.path != path)
+        c->unix_sock.path = strdup(path);
+
+    if (timeout) {
+        if (c->timeout != timeout) {
+            if (c->timeout == NULL)
+                c->timeout = malloc(sizeof(struct timeval));
+
+            memcpy(c->timeout, timeout, sizeof(struct timeval));
+        }
+    } else {
+        if (c->timeout)
+            free(c->timeout);
+        c->timeout = NULL;
+    }
+
+    if (redisContextTimeoutMsec(c,&timeout_msec) != REDIS_OK)
+        return REDIS_ERR;
+
     sa.sun_family = AF_LOCAL;
     strncpy(sa.sun_path,path,sizeof(sa.sun_path)-1);
     if (connect(c->fd, (struct sockaddr*)&sa, sizeof(sa)) == -1) {
         if (errno == EINPROGRESS && !blocking) {
             /* This is ok. */
         } else {
-            if (redisContextWaitReady(c,timeout) != REDIS_OK)
+            if (redisContextWaitReady(c,timeout_msec) != REDIS_OK)
                 return REDIS_ERR;
         }
     }