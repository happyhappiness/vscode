@@ -2,8 +2,7 @@
 #define XGBOOST_UTILS_SOCKET_H
 /*!
  * \file socket.h
- * \brief this file aims to provide a platform independent wrapper 
- *        of socket
+ * \brief this file aims to provide a wrapper of sockets
  * \author Tianqi Chen
  */
 #include <fcntl.h>
@@ -63,7 +62,7 @@ class TCPSocket {
   // constructor
   TCPSocket(void) {}
   // default conversion to int
-  inline int operator()() const {
+  inline operator int() const {
     return sockfd;
   }
   /*!
@@ -122,6 +121,7 @@ class TCPSocket {
    * \return size of data actually sent
    */
   inline size_t Send(const void *buf, size_t len, int flag = 0) {
+    if (len == 0) return 0;
     ssize_t ret = send(sockfd, buf, len, flag);
     if (ret == -1) SockError("Send", errno);
     return ret;
@@ -134,6 +134,7 @@ class TCPSocket {
    * \return size of data actually received 
    */
   inline size_t Recv(void *buf, size_t len, int flags = 0) {
+    if (len == 0) return 0;
     ssize_t ret = recv(sockfd, buf, len, flags);
     if (ret == -1) SockError("Recv", errno);
     return ret;