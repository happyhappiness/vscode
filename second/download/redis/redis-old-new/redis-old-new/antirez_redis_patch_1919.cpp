@@ -124,20 +124,31 @@ int anetResolve(char *err, char *host, char *ipbuf)
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
@@ -183,10 +194,9 @@ int anetUnixGenericConnect(char *err, char *path, int flags)
     int s;
     struct sockaddr_un sa;
 
-    if ((s = socket(AF_LOCAL,SOCK_STREAM,0)) == -1) {
-        anetSetError(err, "creating socket: %s\n", strerror(errno));
+    if ((s = anetCreateSocket(err,AF_LOCAL)) == ANET_ERR)
         return ANET_ERR;
-    }
+
     sa.sun_family = AF_LOCAL;
     strncpy(sa.sun_path,path,sizeof(sa.sun_path)-1);
     if (flags & ANET_CONNECT_NONBLOCK) {
@@ -245,41 +255,39 @@ int anetWrite(int fd, char *buf, int count)
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
 
@@ -288,23 +296,14 @@ int anetUnixServer(char *err, char *path)
     int s;
     struct sockaddr_un sa;
 
-    if ((s = socket(AF_LOCAL,SOCK_STREAM,0)) == -1) {
-        anetSetError(err, "socket: %s\n", strerror(errno));
+    if ((s = anetCreateSocket(err,AF_LOCAL)) == ANET_ERR)
         return ANET_ERR;
-    }
+
     memset(&sa,0,sizeof(sa));
     sa.sun_family = AF_LOCAL;
     strncpy(sa.sun_path,path,sizeof(sa.sun_path)-1);
-    if (bind(s,(struct sockaddr*)&sa,SUN_LEN(&sa)) == -1) {
-        anetSetError(err, "bind: %s\n", strerror(errno));
-        close(s);
+    if (anetListen(err,s,(struct sockaddr*)&sa,sizeof(sa)) == ANET_ERR)
         return ANET_ERR;
-    }
-    if (listen(s, 511) == -1) { /* the magic 511 constant is from nginx */
-        anetSetError(err, "listen: %s\n", strerror(errno));
-        close(s);
-        return ANET_ERR;
-    }
     return s;
 }
 