@@ -361,17 +361,14 @@ int anetWrite(int fd, char *buf, int count)
     return totlen;
 }
 
-static int anetListen(char *err, int s, struct sockaddr *sa, socklen_t len) {
+static int anetListen(char *err, int s, struct sockaddr *sa, socklen_t len, int backlog) {
     if (bind(s,sa,len) == -1) {
         anetSetError(err, "bind: %s", strerror(errno));
         close(s);
         return ANET_ERR;
     }
 
-    /* Use a backlog of 512 entries. We pass 511 to the listen() call because
-     * the kernel does: backlogsize = roundup_pow_of_two(backlogsize + 1);
-     * which will thus give us a backlog of 512 entries */
-    if (listen(s, 511) == -1) {
+    if (listen(s, backlog) == -1) {
         anetSetError(err, "listen: %s", strerror(errno));
         close(s);
         return ANET_ERR;
@@ -389,7 +386,7 @@ static int anetV6Only(char *err, int s) {
     return ANET_OK;
 }
 
-static int _anetTcpServer(char *err, int port, char *bindaddr, int af)
+static int _anetTcpServer(char *err, int port, char *bindaddr, int af, int backlog)
 {
     int s, rv;
     char _port[6];  /* strlen("65535") */
@@ -411,7 +408,7 @@ static int _anetTcpServer(char *err, int port, char *bindaddr, int af)
 
         if (af == AF_INET6 && anetV6Only(err,s) == ANET_ERR) goto error;
         if (anetSetReuseAddr(err,s) == ANET_ERR) goto error;
-        if (anetListen(err,s,p->ai_addr,p->ai_addrlen) == ANET_ERR) goto error;
+        if (anetListen(err,s,p->ai_addr,p->ai_addrlen,backlog) == ANET_ERR) goto error;
         goto end;
     }
     if (p == NULL) {
@@ -426,17 +423,17 @@ static int _anetTcpServer(char *err, int port, char *bindaddr, int af)
     return s;
 }
 
-int anetTcpServer(char *err, int port, char *bindaddr)
+int anetTcpServer(char *err, int port, char *bindaddr, int backlog)
 {
-    return _anetTcpServer(err, port, bindaddr, AF_INET);
+    return _anetTcpServer(err, port, bindaddr, AF_INET, backlog);
 }
 
-int anetTcp6Server(char *err, int port, char *bindaddr)
+int anetTcp6Server(char *err, int port, char *bindaddr, int backlog)
 {
-    return _anetTcpServer(err, port, bindaddr, AF_INET6);
+    return _anetTcpServer(err, port, bindaddr, AF_INET6, backlog);
 }
 
-int anetUnixServer(char *err, char *path, mode_t perm)
+int anetUnixServer(char *err, char *path, mode_t perm, int backlog)
 {
     int s;
     struct sockaddr_un sa;
@@ -447,7 +444,7 @@ int anetUnixServer(char *err, char *path, mode_t perm)
     memset(&sa,0,sizeof(sa));
     sa.sun_family = AF_LOCAL;
     strncpy(sa.sun_path,path,sizeof(sa.sun_path)-1);
-    if (anetListen(err,s,(struct sockaddr*)&sa,sizeof(sa)) == ANET_ERR)
+    if (anetListen(err,s,(struct sockaddr*)&sa,sizeof(sa),backlog) == ANET_ERR)
         return ANET_ERR;
     if (perm)
         chmod(sa.sun_path, perm);