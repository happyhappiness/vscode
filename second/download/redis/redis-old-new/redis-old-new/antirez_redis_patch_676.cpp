@@ -589,20 +589,21 @@ int anetPeerToString(int fd, char *ip, size_t ip_len, int *port) {
     return -1;
 }
 
-int anetFormatIP(char *fmt, size_t fmt_len, char *ip, int port) {
-    if (port >= 0)
-        return snprintf(fmt,fmt_len,
-            strchr(ip,':') ? "[%s]:%d" : "%s:%d", ip, port);
-    else
-        return snprintf(fmt, fmt_len, strchr(ip,':') ? "[%s]" : "%s", ip);
+/* Format an IP,port pair into something easy to parse. If IP is IPv6
+ * (matches for ":"), the ip is surrounded by []. IP and port are just
+ * separated by colons. This the standard to display addresses within Redis. */
+int anetFormatAddr(char *buf, size_t buf_len, char *ip, int port) {
+    return snprintf(buf,buf_len, strchr(ip,':') ?
+           "[%s]:%d" : "%s:%d", ip, port);
 }
 
-int anetFormatPeer(int fd, char *fmt, size_t fmt_len) {
+/* Like anetFormatAddr() but extract ip and port from the socket's peer. */
+int anetFormatPeer(int fd, char *buf, size_t buf_len) {
     char ip[INET6_ADDRSTRLEN];
     int port;
 
     anetPeerToString(fd,ip,sizeof(ip),&port);
-    return anetFormatIP(fmt, fmt_len, ip, port);
+    return anetFormatAddr(buf, buf_len, ip, port);
 }
 
 int anetSockName(int fd, char *ip, size_t ip_len, int *port) {
@@ -632,5 +633,5 @@ int anetFormatSock(int fd, char *fmt, size_t fmt_len) {
     int port;
 
     anetSockName(fd,ip,sizeof(ip),&port);
-    return anetFormatIP(fmt, fmt_len, ip, port);
+    return anetFormatAddr(fmt, fmt_len, ip, port);
 }