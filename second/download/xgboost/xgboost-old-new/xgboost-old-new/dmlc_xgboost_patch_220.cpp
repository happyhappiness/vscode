@@ -5,6 +5,9 @@
  * \brief this file aims to provide a wrapper of sockets
  * \author Tianqi Chen
  */
+#if defined(_WIN32)
+#include <winsock2.h>
+#else
 #include <fcntl.h>
 #include <netdb.h>
 #include <errno.h>
@@ -13,12 +16,16 @@
 #include <netinet/in.h>
 #include <sys/socket.h>
 #include <sys/select.h>
+#endif
 #include <string>
 #include <cstring>
 #include "./utils.h"
 
 namespace xgboost {
 namespace utils {
+#if defined(_WIN32)
+typedef int ssize_t;
+#endif
 
 /*! \brief data structure for network address */
 struct SockAddr {
@@ -64,18 +71,18 @@ struct SockAddr {
 class TCPSocket {
  public:
   /*! \brief the file descriptor of socket */
-  int sockfd;
+  SOCKET sockfd;
   // constructor
-  TCPSocket(void) : sockfd(-1) {
+  TCPSocket(void) : sockfd(INVALID_SOCKET) {
   }
-  explicit TCPSocket(int sockfd) : sockfd(sockfd) {
+  explicit TCPSocket(SOCKET sockfd) : sockfd(sockfd) {
   }
   ~TCPSocket(void) {
     // do nothing in destructor
     // user need to take care of close
   }
   // default conversion to int
-  inline operator int() const {
+  inline operator SOCKET() const {
     return sockfd;
   }
   /*!
@@ -84,7 +91,7 @@ class TCPSocket {
    */
   inline void Create(int af = PF_INET) {
     sockfd = socket(PF_INET, SOCK_STREAM, 0);
-    if (sockfd == -1) {
+    if (sockfd == INVALID_SOCKET) {
       SockError("Create", errno);
     }
   }
@@ -105,6 +112,12 @@ class TCPSocket {
    *        it will set it back to block mode
    */
   inline void SetNonBlock(bool non_block) {
+#ifdef _WIN32  
+	u_long mode = non_block ? 1 : 0;
+	if (ioctlsocket(sockfd, FIONBIO, &mode) != NO_ERROR) {
+      SockError("SetNonBlock", WSAGetLastError());
+	}
+#else
     int flag = fcntl(sockfd, F_GETFL, 0);
     if (flag == -1) {
       SockError("SetNonBlock-1", errno);
@@ -117,6 +130,7 @@ class TCPSocket {
     if (fcntl(sockfd, F_SETFL, flag) == -1) {
       SockError("SetNonBlock-2", errno);
     }
+#endif
   }
   /*!
    * \brief perform listen of the socket
@@ -127,9 +141,9 @@ class TCPSocket {
   }
   /*! \brief get a new connection */
   TCPSocket Accept(void) {
-    int newfd = accept(sockfd, NULL, NULL);
-    if (newfd == -1) {
-      SockError("Accept", errno);
+    SOCKET newfd = accept(sockfd, NULL, NULL);
+    if (newfd == INVALID_SOCKET) {
+      SockError("Accept");
     }
     return TCPSocket(newfd);
   }
@@ -173,7 +187,12 @@ class TCPSocket {
   /*! \brief close the connection */
   inline void Close(void) {
     if (sockfd != -1) {
-      close(sockfd); sockfd = -1;
+#ifdef _WIN32
+      closesocket(sockfd);
+#else
+	  close(sockfd);
+#endif
+	  sockfd = INVALID_SOCKET;
     } else {
       Error("TCPSocket::Close double close the socket or close without create");
     }
@@ -221,7 +240,7 @@ class TCPSocket {
     const char *buf = reinterpret_cast<const char*>(buf_);
     size_t ndone = 0;
     while (ndone <  len) {
-      ssize_t ret = send(sockfd, buf, len - ndone, 0);
+      ssize_t ret = send(sockfd, buf, static_cast<ssize_t>(len - ndone), 0);
       if (ret == -1) {
         if (errno == EAGAIN || errno == EWOULDBLOCK) return ndone;
         SockError("Recv", errno);