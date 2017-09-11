@@ -26,8 +26,8 @@ namespace utils {
 #if defined(_WIN32)
 typedef int ssize_t;
 #else
-typedef int SOCKET;
-const int INVALID_SOCKET = -1;
+typedef int sock_t;
+const int INVALID_sock_t = -1;
 #endif
 
 /*! \brief data structure for network address */
@@ -74,18 +74,18 @@ struct SockAddr {
 class TCPSocket {
  public:
   /*! \brief the file descriptor of socket */
-  SOCKET sockfd;
+  sock_t sockfd;
   // constructor
-  TCPSocket(void) : sockfd(INVALID_SOCKET) {
+  TCPSocket(void) : sockfd(INVALID_sock_t) {
   }
-  explicit TCPSocket(SOCKET sockfd) : sockfd(sockfd) {
+  explicit TCPSocket(sock_t sockfd) : sockfd(sockfd) {
   }
   ~TCPSocket(void) {
     // do nothing in destructor
     // user need to take care of close
   }
   // default conversion to int
-  inline operator SOCKET() const {
+  inline operator sock_t() const {
     return sockfd;
   }
   /*!
@@ -94,7 +94,7 @@ class TCPSocket {
    */
   inline void Create(int af = PF_INET) {
     sockfd = socket(PF_INET, SOCK_STREAM, 0);
-    if (sockfd == INVALID_SOCKET) {
+    if (sockfd == INVALID_sock_t) {
       SockError("Create");
     }
   }
@@ -118,7 +118,7 @@ class TCPSocket {
 #ifdef _WIN32  
 	u_long mode = non_block ? 1 : 0;
 	if (ioctlsocket(sockfd, FIONBIO, &mode) != NO_ERROR) {
-      SockError("SetNonBlock", WSAGetLastError());
+      SockError("SetNonBlock");
 	}
 #else
     int flag = fcntl(sockfd, F_GETFL, 0);
@@ -144,8 +144,8 @@ class TCPSocket {
   }
   /*! \brief get a new connection */
   TCPSocket Accept(void) {
-    SOCKET newfd = accept(sockfd, NULL, NULL);
-    if (newfd == INVALID_SOCKET) {
+    sock_t newfd = accept(sockfd, NULL, NULL);
+    if (newfd == INVALID_sock_t) {
       SockError("Accept");
     }
     return TCPSocket(newfd);
@@ -195,7 +195,7 @@ class TCPSocket {
 #else
 	  close(sockfd);
 #endif
-	  sockfd = INVALID_SOCKET;
+	  sockfd = INVALID_sock_t;
     } else {
       Error("TCPSocket::Close double close the socket or close without create");
     }
@@ -280,8 +280,7 @@ class TCPSocket {
   // report an socket error
   inline static void SockError(const char *msg) {
     int errsv = errno;
-    char buf[256];    
-    Error("Socket %s Error:%s", msg, strerror_r(errsv, buf, sizeof(buf)));
+    Error("Socket %s Error:%s", msg, strerror(errsv));
   }
 };
 /*! \brief helper data structure to perform select */
@@ -294,30 +293,30 @@ struct SelectHelper {
    * \brief add file descriptor to watch for read 
    * \param fd file descriptor to be watched
    */
-  inline void WatchRead(int fd) {
+  inline void WatchRead(sock_t fd) {
     read_fds.push_back(fd);
     if (fd > maxfd) maxfd = fd;
   }
   /*!
    * \brief add file descriptor to watch for write
    * \param fd file descriptor to be watched
    */
-  inline void WatchWrite(int fd) {
+  inline void WatchWrite(sock_t fd) {
     write_fds.push_back(fd);
     if (fd > maxfd) maxfd = fd;
   }
   /*!
    * \brief Check if the descriptor is ready for read
    * \param fd file descriptor to check status
    */
-  inline bool CheckRead(int fd) const {
+  inline bool CheckRead(sock_t fd) const {
     return FD_ISSET(fd, &read_set);
   }
   /*!
    * \brief Check if the descriptor is ready for write
    * \param fd file descriptor to check status
    */
-  inline bool CheckWrite(int fd) const {
+  inline bool CheckWrite(sock_t fd) const {
     return FD_ISSET(fd, &write_set);
   }
   /*!
@@ -353,8 +352,7 @@ struct SelectHelper {
     }
     if (ret == -1) {
       int errsv = errno;
-      char buf[256];
-      Error("Select Error: %s", strerror_r(errsv, buf, sizeof(buf)));      
+      Error("Select Error: %s", strerror(errsv));
     }
     return ret;
   }