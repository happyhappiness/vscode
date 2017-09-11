@@ -75,24 +75,24 @@ int anetNonBlock(char *err, int fd)
     return ANET_OK;
 }
 
-static int _anetTcpNoDelay(char *err, int fd, int yes) 
+static int anetSetTcpNoDelay(char *err, int fd, int val)
 {
-    if (setsockopt(fd, IPPROTO_TCP, TCP_NODELAY, &yes, sizeof(yes)) == -1)
+    if (setsockopt(fd, IPPROTO_TCP, TCP_NODELAY, &val, sizeof(val)) == -1)
     {
         anetSetError(err, "setsockopt TCP_NODELAY: %s", strerror(errno));
         return ANET_ERR;
     }
     return ANET_OK;
 }
 
-int anetTcpNoDelay(char *err, int fd)
+int anetEnableTcpNoDelay(char *err, int fd)
 {
-    return _anetTcpNoDelay(err, fd, 1);
+    return anetSetTcpNoDelay(err, fd, 1);
 }
 
-int anetTcpNoDelayOff(char *err, int fd) 
+int anetDisableTcpNoDelay(char *err, int fd) 
 {
-    return _anetTcpNoDelay(err, fd, 0);
+    return anetSetTcpNoDelay(err, fd, 0);
 }
 
 