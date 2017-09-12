@@ -32,6 +32,7 @@
 
 #include <sys/types.h>
 #include <sys/socket.h>
+#include <sys/un.h>
 #include <netinet/in.h>
 #include <netinet/tcp.h>
 #include <arpa/inet.h>
@@ -123,20 +124,31 @@ int anetResolve(char *err, char *host, char *ipbuf)
     return ANET_OK;
 }
 
+static int anetCreateSocket(char *err, int domain) {
+    int s, on = 1;
+    if ((s = socket(domain, SOCK_STREAM, 0)) == -1) {
+        anetSetError(err, "creating socket: %s\n", strerror(errno));
+        return ANET_ERR;
+    }
+
+    /* Make sure connection-intensive things like the redis benckmark
+     * will be able to close/open sockets a zillion of times */
+    if (setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)) == -1) {
+        anetSetError(err, "setsockopt SO_REUSEADDR: %s\n", strerror(errno));
+        return ANET_ERR;
+    }
+    return s;
+}
+
 #define ANET_CONNECT_NONE 0
 #define ANET_CONNECT_NONBLOCK 1
 static int anetTcpGenericConnect(char *err, char *addr, int port, int flags)
 {
-    int s, on = 1;
+    int s;
     struct sockaddr_in sa;
 
-    if ((s = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
-        anetSetError(err, "creating socket: %s\n", strerror(errno));
+    if ((s = anetCreateSocket(err,AF_INET)) == ANET_ERR)
         return ANET_ERR;
-    }
-    /* Make sure connection-intensive things like the redis benckmark
-     * will be able to close/open sockets a zillion of times */
-    setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
 
     sa.sin_family = AF_INET;
     sa.sin_port = htons(port);
@@ -177,6 +189,42 @@ int anetTcpNonBlockConnect(char *err, char *addr, int port)
     return anetTcpGenericConnect(err,addr,port,ANET_CONNECT_NONBLOCK);
 }
 
+int anetUnixGenericConnect(char *err, char *path, int flags)
+{
+    int s;
+    struct sockaddr_un sa;
+
+    if ((s = anetCreateSocket(err,AF_LOCAL)) == ANET_ERR)
+        return ANET_ERR;
+
+    sa.sun_family = AF_LOCAL;
+    strncpy(sa.sun_path,path,sizeof(sa.sun_path)-1);
+    if (flags & ANET_CONNECT_NONBLOCK) {
+        if (anetNonBlock(err,s) != ANET_OK)
+            return ANET_ERR;
+    }
+    if (connect(s,(struct sockaddr*)&sa,sizeof(sa)) == -1) {
+        if (errno == EINPROGRESS &&
+            flags & ANET_CONNECT_NONBLOCK)
+            return s;
+
+        anetSetError(err, "connect: %s\n", strerror(errno));
+        close(s);
+        return ANET_ERR;
+    }
+    return s;
+}
+
+int anetUnixConnect(char *err, char *path)
+{
+    return anetUnixGenericConnect(err,path,ANET_CONNECT_NONE);
+}
+
+int anetUnixNonBlockConnect(char *err, char *path)
+{
+    return anetUnixGenericConnect(err,path,ANET_CONNECT_NONBLOCK);
+}
+
 /* Like read(2) but make sure 'count' is read before to return
  * (unless error or EOF condition is encountered) */
 int anetRead(int fd, char *buf, int count)
@@ -207,53 +255,62 @@ int anetWrite(int fd, char *buf, int count)
     return totlen;
 }
 
-int anetTcpServer(char *err, int port, char *bindaddr)
-{
-    int s, on = 1;
-    struct sockaddr_in sa;
-    
-    if ((s = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
-        anetSetError(err, "socket: %s\n", strerror(errno));
+static int anetListen(char *err, int s, struct sockaddr *sa, socklen_t len) {
+    if (bind(s,sa,len) == -1) {
+        anetSetError(err, "bind: %s\n", strerror(errno));
+        close(s);
         return ANET_ERR;
     }
-    if (setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)) == -1) {
-        anetSetError(err, "setsockopt SO_REUSEADDR: %s\n", strerror(errno));
+    if (listen(s, 511) == -1) { /* the magic 511 constant is from nginx */
+        anetSetError(err, "listen: %s\n", strerror(errno));
         close(s);
         return ANET_ERR;
     }
+    return ANET_OK;
+}
+
+int anetTcpServer(char *err, int port, char *bindaddr)
+{
+    int s;
+    struct sockaddr_in sa;
+
+    if ((s = anetCreateSocket(err,AF_INET)) == ANET_ERR)
+        return ANET_ERR;
+
     memset(&sa,0,sizeof(sa));
     sa.sin_family = AF_INET;
     sa.sin_port = htons(port);
     sa.sin_addr.s_addr = htonl(INADDR_ANY);
-    if (bindaddr) {
-        if (inet_aton(bindaddr, &sa.sin_addr) == 0) {
-            anetSetError(err, "Invalid bind address\n");
-            close(s);
-            return ANET_ERR;
-        }
-    }
-    if (bind(s, (struct sockaddr*)&sa, sizeof(sa)) == -1) {
-        anetSetError(err, "bind: %s\n", strerror(errno));
+    if (bindaddr && inet_aton(bindaddr, &sa.sin_addr) == 0) {
+        anetSetError(err, "Invalid bind address\n");
         close(s);
         return ANET_ERR;
     }
-    if (listen(s, 511) == -1) { /* the magic 511 constant is from nginx */
-        anetSetError(err, "listen: %s\n", strerror(errno));
-        close(s);
+    if (anetListen(err,s,(struct sockaddr*)&sa,sizeof(sa)) == ANET_ERR)
         return ANET_ERR;
-    }
     return s;
 }
 
-int anetAccept(char *err, int serversock, char *ip, int *port)
+int anetUnixServer(char *err, char *path)
 {
-    int fd;
-    struct sockaddr_in sa;
-    unsigned int saLen;
+    int s;
+    struct sockaddr_un sa;
+
+    if ((s = anetCreateSocket(err,AF_LOCAL)) == ANET_ERR)
+        return ANET_ERR;
+
+    memset(&sa,0,sizeof(sa));
+    sa.sun_family = AF_LOCAL;
+    strncpy(sa.sun_path,path,sizeof(sa.sun_path)-1);
+    if (anetListen(err,s,(struct sockaddr*)&sa,sizeof(sa)) == ANET_ERR)
+        return ANET_ERR;
+    return s;
+}
 
+static int anetGenericAccept(char *err, int s, struct sockaddr *sa, socklen_t *len) {
+    int fd;
     while(1) {
-        saLen = sizeof(sa);
-        fd = accept(serversock, (struct sockaddr*)&sa, &saLen);
+        fd = accept(s,sa,len);
         if (fd == -1) {
             if (errno == EINTR)
                 continue;
@@ -264,7 +321,27 @@ int anetAccept(char *err, int serversock, char *ip, int *port)
         }
         break;
     }
+    return fd;
+}
+
+int anetTcpAccept(char *err, int s, char *ip, int *port) {
+    int fd;
+    struct sockaddr_in sa;
+    socklen_t salen = sizeof(sa);
+    if ((fd = anetGenericAccept(err,s,(struct sockaddr*)&sa,&salen)) == ANET_ERR)
+        return ANET_ERR;
+
     if (ip) strcpy(ip,inet_ntoa(sa.sin_addr));
     if (port) *port = ntohs(sa.sin_port);
     return fd;
 }
+
+int anetUnixAccept(char *err, int s) {
+    int fd;
+    struct sockaddr_un sa;
+    socklen_t salen = sizeof(sa);
+    if ((fd = anetGenericAccept(err,s,(struct sockaddr*)&sa,&salen)) == ANET_ERR)
+        return ANET_ERR;
+
+    return fd;
+}