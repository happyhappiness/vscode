@@ -589,6 +589,22 @@ int anetPeerToString(int fd, char *ip, size_t ip_len, int *port) {
     return -1;
 }
 
+int anetFormatIP(char *fmt, size_t fmt_len, char *ip, int port) {
+    if (port >= 0)
+        return snprintf(fmt,fmt_len,
+            strchr(ip,':') ? "[%s]:%d" : "%s:%d", ip, port);
+    else
+        return snprintf(fmt, fmt_len, strchr(ip,':') ? "[%s]" : "%s", ip);
+}
+
+int anetFormatPeer(int fd, char *fmt, size_t fmt_len) {
+    char ip[INET6_ADDRSTRLEN];
+    int port;
+
+    anetPeerToString(fd,ip,sizeof(ip),&port);
+    return anetFormatIP(fmt, fmt_len, ip, port);
+}
+
 int anetSockName(int fd, char *ip, size_t ip_len, int *port) {
     struct sockaddr_storage sa;
     socklen_t salen = sizeof(sa);
@@ -610,3 +626,11 @@ int anetSockName(int fd, char *ip, size_t ip_len, int *port) {
     }
     return 0;
 }
+
+int anetFormatSock(int fd, char *fmt, size_t fmt_len) {
+    char ip[INET6_ADDRSTRLEN];
+    int port;
+
+    anetSockName(fd,ip,sizeof(ip),&port);
+    return anetFormatIP(fmt, fmt_len, ip, port);
+}