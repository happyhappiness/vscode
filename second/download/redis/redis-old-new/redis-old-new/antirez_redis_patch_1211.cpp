@@ -75,9 +75,8 @@ int anetNonBlock(char *err, int fd)
     return ANET_OK;
 }
 
-int anetTcpNoDelay(char *err, int fd)
+static int _anetTcpNoDelay(char *err, int fd, int yes) 
 {
-    int yes = 1;
     if (setsockopt(fd, IPPROTO_TCP, TCP_NODELAY, &yes, sizeof(yes)) == -1)
     {
         anetSetError(err, "setsockopt TCP_NODELAY: %s", strerror(errno));
@@ -86,6 +85,17 @@ int anetTcpNoDelay(char *err, int fd)
     return ANET_OK;
 }
 
+int anetTcpNoDelay(char *err, int fd)
+{
+    return _anetTcpNoDelay(err, fd, 1);
+}
+
+int anetTcpNoDelayOff(char *err, int fd) 
+{
+    return _anetTcpNoDelay(err, fd, 0);
+}
+
+
 int anetSetSendBuffer(char *err, int fd, int buffsize)
 {
     if (setsockopt(fd, SOL_SOCKET, SO_SNDBUF, &buffsize, sizeof(buffsize)) == -1)