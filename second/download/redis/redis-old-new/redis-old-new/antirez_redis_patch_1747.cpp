@@ -64,11 +64,11 @@ int anetNonBlock(char *err, int fd)
      * Note that fcntl(2) for F_GETFL and F_SETFL can't be
      * interrupted by a signal. */
     if ((flags = fcntl(fd, F_GETFL)) == -1) {
-        anetSetError(err, "fcntl(F_GETFL): %s\n", strerror(errno));
+        anetSetError(err, "fcntl(F_GETFL): %s", strerror(errno));
         return ANET_ERR;
     }
     if (fcntl(fd, F_SETFL, flags | O_NONBLOCK) == -1) {
-        anetSetError(err, "fcntl(F_SETFL,O_NONBLOCK): %s\n", strerror(errno));
+        anetSetError(err, "fcntl(F_SETFL,O_NONBLOCK): %s", strerror(errno));
         return ANET_ERR;
     }
     return ANET_OK;
@@ -79,7 +79,7 @@ int anetTcpNoDelay(char *err, int fd)
     int yes = 1;
     if (setsockopt(fd, IPPROTO_TCP, TCP_NODELAY, &yes, sizeof(yes)) == -1)
     {
-        anetSetError(err, "setsockopt TCP_NODELAY: %s\n", strerror(errno));
+        anetSetError(err, "setsockopt TCP_NODELAY: %s", strerror(errno));
         return ANET_ERR;
     }
     return ANET_OK;
@@ -89,7 +89,7 @@ int anetSetSendBuffer(char *err, int fd, int buffsize)
 {
     if (setsockopt(fd, SOL_SOCKET, SO_SNDBUF, &buffsize, sizeof(buffsize)) == -1)
     {
-        anetSetError(err, "setsockopt SO_SNDBUF: %s\n", strerror(errno));
+        anetSetError(err, "setsockopt SO_SNDBUF: %s", strerror(errno));
         return ANET_ERR;
     }
     return ANET_OK;
@@ -99,7 +99,7 @@ int anetTcpKeepAlive(char *err, int fd)
 {
     int yes = 1;
     if (setsockopt(fd, SOL_SOCKET, SO_KEEPALIVE, &yes, sizeof(yes)) == -1) {
-        anetSetError(err, "setsockopt SO_KEEPALIVE: %s\n", strerror(errno));
+        anetSetError(err, "setsockopt SO_KEEPALIVE: %s", strerror(errno));
         return ANET_ERR;
     }
     return ANET_OK;
@@ -115,7 +115,7 @@ int anetResolve(char *err, char *host, char *ipbuf)
 
         he = gethostbyname(host);
         if (he == NULL) {
-            anetSetError(err, "can't resolve: %s\n", host);
+            anetSetError(err, "can't resolve: %s", host);
             return ANET_ERR;
         }
         memcpy(&sa.sin_addr, he->h_addr, sizeof(struct in_addr));
@@ -127,14 +127,14 @@ int anetResolve(char *err, char *host, char *ipbuf)
 static int anetCreateSocket(char *err, int domain) {
     int s, on = 1;
     if ((s = socket(domain, SOCK_STREAM, 0)) == -1) {
-        anetSetError(err, "creating socket: %s\n", strerror(errno));
+        anetSetError(err, "creating socket: %s", strerror(errno));
         return ANET_ERR;
     }
 
     /* Make sure connection-intensive things like the redis benckmark
      * will be able to close/open sockets a zillion of times */
     if (setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)) == -1) {
-        anetSetError(err, "setsockopt SO_REUSEADDR: %s\n", strerror(errno));
+        anetSetError(err, "setsockopt SO_REUSEADDR: %s", strerror(errno));
         return ANET_ERR;
     }
     return s;
@@ -157,7 +157,7 @@ static int anetTcpGenericConnect(char *err, char *addr, int port, int flags)
 
         he = gethostbyname(addr);
         if (he == NULL) {
-            anetSetError(err, "can't resolve: %s\n", addr);
+            anetSetError(err, "can't resolve: %s", addr);
             close(s);
             return ANET_ERR;
         }
@@ -172,7 +172,7 @@ static int anetTcpGenericConnect(char *err, char *addr, int port, int flags)
             flags & ANET_CONNECT_NONBLOCK)
             return s;
 
-        anetSetError(err, "connect: %s\n", strerror(errno));
+        anetSetError(err, "connect: %s", strerror(errno));
         close(s);
         return ANET_ERR;
     }
@@ -208,7 +208,7 @@ int anetUnixGenericConnect(char *err, char *path, int flags)
             flags & ANET_CONNECT_NONBLOCK)
             return s;
 
-        anetSetError(err, "connect: %s\n", strerror(errno));
+        anetSetError(err, "connect: %s", strerror(errno));
         close(s);
         return ANET_ERR;
     }
@@ -257,12 +257,12 @@ int anetWrite(int fd, char *buf, int count)
 
 static int anetListen(char *err, int s, struct sockaddr *sa, socklen_t len) {
     if (bind(s,sa,len) == -1) {
-        anetSetError(err, "bind: %s\n", strerror(errno));
+        anetSetError(err, "bind: %s", strerror(errno));
         close(s);
         return ANET_ERR;
     }
     if (listen(s, 511) == -1) { /* the magic 511 constant is from nginx */
-        anetSetError(err, "listen: %s\n", strerror(errno));
+        anetSetError(err, "listen: %s", strerror(errno));
         close(s);
         return ANET_ERR;
     }
@@ -282,7 +282,7 @@ int anetTcpServer(char *err, int port, char *bindaddr)
     sa.sin_port = htons(port);
     sa.sin_addr.s_addr = htonl(INADDR_ANY);
     if (bindaddr && inet_aton(bindaddr, &sa.sin_addr) == 0) {
-        anetSetError(err, "Invalid bind address\n");
+        anetSetError(err, "invalid bind address");
         close(s);
         return ANET_ERR;
     }
@@ -315,7 +315,7 @@ static int anetGenericAccept(char *err, int s, struct sockaddr *sa, socklen_t *l
             if (errno == EINTR)
                 continue;
             else {
-                anetSetError(err, "accept: %s\n", strerror(errno));
+                anetSetError(err, "accept: %s", strerror(errno));
                 return ANET_ERR;
             }
         }