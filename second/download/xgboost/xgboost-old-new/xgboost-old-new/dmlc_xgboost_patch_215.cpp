@@ -7,6 +7,7 @@
  */
 #if defined(_WIN32)
 #include <winsock2.h>
+#include <ws2tcpip.h>
 #else
 #include <fcntl.h>
 #include <netdb.h>
@@ -25,8 +26,10 @@ namespace xgboost {
 namespace utils {
 #if defined(_WIN32)
 typedef int ssize_t;
+typedef int sock_size_t;
 #else
 typedef int SOCKET;
+typedef size_t sock_size_t;
 const int INVALID_SOCKET = -1;
 #endif
 
@@ -63,7 +66,11 @@ struct SockAddr {
   /*! \return a string representation of the address */
   inline std::string AddrStr(void) const {
     std::string buf; buf.resize(256);
-    const char *s = inet_ntop(AF_INET, &addr.sin_addr, &buf[0], buf.length());
+#ifdef _WIN32
+    const char *s = inet_ntop(AF_INET, (PVOID)&addr.sin_addr, &buf[0], buf.length());
+#else
+	const char *s = inet_ntop(AF_INET, &addr.sin_addr, &buf[0], buf.length());
+#endif
     Assert(s != NULL, "cannot decode address");
     return std::string(s);
   }
@@ -103,11 +110,22 @@ class TCPSocket {
    *   call this before using the sockets
    */
   inline static void Startup(void) {
+#ifdef _WIN32
+	WSADATA wsa_data;
+    if (WSAStartup(MAKEWORD(2, 2), &wsa_data) != -1) {
+	  SockError("Startup");
+	}
+    if (LOBYTE(wsa_data.wVersion) != 2 || HIBYTE(wsa_data.wVersion) != 2) {
+	  WSACleanup();
+      utils::Error("Could not find a usable version of Winsock.dll\n");
+    }
+#endif
   }
   /*! 
    * \brief shutdown the socket module after use, all sockets need to be closed
    */  
   inline static void Finalize(void) {
+    WSACleanup();
   }
   /*! 
    * \brief set this socket to use non-blocking mode
@@ -207,9 +225,10 @@ class TCPSocket {
    * \param flags extra flags
    * \return size of data actually sent
    */
-  inline size_t Send(const void *buf, size_t len, int flag = 0) {
+  inline size_t Send(const void *buf_, size_t len, int flag = 0) {
+	const char *buf = reinterpret_cast<const char*>(buf_);
     if (len == 0) return 0;
-    ssize_t ret = send(sockfd, buf, len, flag);
+    ssize_t ret = send(sockfd, buf, static_cast<sock_size_t>(len), flag);
     if (ret == -1) {
       if (errno == EAGAIN || errno == EWOULDBLOCK) return 0;
       SockError("Send");
@@ -218,14 +237,15 @@ class TCPSocket {
   }  
   /*! 
    * \brief receive data using the socket 
-   * \param buf the pointer to the buffer
+   * \param buf_ the pointer to the buffer
    * \param len the size of the buffer
    * \param flags extra flags
    * \return size of data actually received 
    */
-  inline size_t Recv(void *buf, size_t len, int flags = 0) {
+  inline size_t Recv(void *buf_, size_t len, int flags = 0) {
+	char *buf = reinterpret_cast<char*>(buf_);
     if (len == 0) return 0;    
-    ssize_t ret = recv(sockfd, buf, len, flags);
+    ssize_t ret = recv(sockfd, buf, static_cast<sock_size_t>(len), flags);
     if (ret == -1) {
       if (errno == EAGAIN || errno == EWOULDBLOCK) return 0;
       SockError("Recv");
@@ -264,7 +284,7 @@ class TCPSocket {
     char *buf = reinterpret_cast<char*>(buf_);
     size_t ndone = 0;
     while (ndone <  len) {
-      ssize_t ret = recv(sockfd, buf, len - ndone, MSG_WAITALL);
+      ssize_t ret = recv(sockfd, buf, static_cast<sock_size_t>(len - ndone), MSG_WAITALL);
       if (ret == -1) {
         if (errno == EAGAIN || errno == EWOULDBLOCK) return ndone;
         SockError("Recv");
@@ -310,14 +330,14 @@ struct SelectHelper {
    * \param fd file descriptor to check status
    */
   inline bool CheckRead(SOCKET fd) const {
-    return FD_ISSET(fd, &read_set);
+    return FD_ISSET(fd, &read_set) != 0;
   }
   /*!
    * \brief Check if the descriptor is ready for write
    * \param fd file descriptor to check status
    */
   inline bool CheckWrite(SOCKET fd) const {
-    return FD_ISSET(fd, &write_set);
+    return FD_ISSET(fd, &write_set) != 0;
   }
   /*!
    * \brief clear all the monitored descriptors
@@ -343,12 +363,12 @@ struct SelectHelper {
     }
     int ret;
     if (timeout == 0) {
-      ret = select(maxfd + 1, &read_set, &write_set, NULL, NULL);
+      ret = select(static_cast<int>(maxfd + 1), &read_set, &write_set, NULL, NULL);
     } else {
       timeval tm;
       tm.tv_usec = (timeout % 1000) * 1000;
       tm.tv_sec = timeout / 1000;
-      ret = select(maxfd + 1, &read_set, &write_set, NULL, &tm);
+      ret = select(static_cast<int>(maxfd + 1), &read_set, &write_set, NULL, &tm);
     }
     if (ret == -1) {
       int errsv = errno;
@@ -358,9 +378,9 @@ struct SelectHelper {
   }
   
  private:
-  int maxfd; 
+  SOCKET maxfd; 
   fd_set read_set, write_set;
-  std::vector<int> read_fds, write_fds;
+  std::vector<SOCKET> read_fds, write_fds;
 };
 }
 }