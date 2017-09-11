@@ -26,8 +26,8 @@ namespace utils {
 #if defined(_WIN32)
 typedef int ssize_t;
 #else
-typedef int sock_t;
-const int INVALID_sock_t = -1;
+typedef int SOCKET;
+const int INVALID_SOCKET = -1;
 #endif
 
 /*! \brief data structure for network address */
@@ -74,18 +74,18 @@ struct SockAddr {
 class TCPSocket {
  public:
   /*! \brief the file descriptor of socket */
-  sock_t sockfd;
+  SOCKET sockfd;
   // constructor
-  TCPSocket(void) : sockfd(INVALID_sock_t) {
+  TCPSocket(void) : sockfd(INVALID_SOCKET) {
   }
-  explicit TCPSocket(sock_t sockfd) : sockfd(sockfd) {
+  explicit TCPSocket(SOCKET sockfd) : sockfd(sockfd) {
   }
   ~TCPSocket(void) {
     // do nothing in destructor
     // user need to take care of close
   }
   // default conversion to int
-  inline operator sock_t() const {
+  inline operator SOCKET() const {
     return sockfd;
   }
   /*!
@@ -94,7 +94,7 @@ class TCPSocket {
    */
   inline void Create(int af = PF_INET) {
     sockfd = socket(PF_INET, SOCK_STREAM, 0);
-    if (sockfd == INVALID_sock_t) {
+    if (sockfd == INVALID_SOCKET) {
       SockError("Create");
     }
   }
@@ -144,8 +144,8 @@ class TCPSocket {
   }
   /*! \brief get a new connection */
   TCPSocket Accept(void) {
-    sock_t newfd = accept(sockfd, NULL, NULL);
-    if (newfd == INVALID_sock_t) {
+    SOCKET newfd = accept(sockfd, NULL, NULL);
+    if (newfd == INVALID_SOCKET) {
       SockError("Accept");
     }
     return TCPSocket(newfd);
@@ -195,7 +195,7 @@ class TCPSocket {
 #else
 	  close(sockfd);
 #endif
-	  sockfd = INVALID_sock_t;
+	  sockfd = INVALID_SOCKET;
     } else {
       Error("TCPSocket::Close double close the socket or close without create");
     }
@@ -293,30 +293,30 @@ struct SelectHelper {
    * \brief add file descriptor to watch for read 
    * \param fd file descriptor to be watched
    */
-  inline void WatchRead(sock_t fd) {
+  inline void WatchRead(SOCKET fd) {
     read_fds.push_back(fd);
     if (fd > maxfd) maxfd = fd;
   }
   /*!
    * \brief add file descriptor to watch for write
    * \param fd file descriptor to be watched
    */
-  inline void WatchWrite(sock_t fd) {
+  inline void WatchWrite(SOCKET fd) {
     write_fds.push_back(fd);
     if (fd > maxfd) maxfd = fd;
   }
   /*!
    * \brief Check if the descriptor is ready for read
    * \param fd file descriptor to check status
    */
-  inline bool CheckRead(sock_t fd) const {
+  inline bool CheckRead(SOCKET fd) const {
     return FD_ISSET(fd, &read_set);
   }
   /*!
    * \brief Check if the descriptor is ready for write
    * \param fd file descriptor to check status
    */
-  inline bool CheckWrite(sock_t fd) const {
+  inline bool CheckWrite(SOCKET fd) const {
     return FD_ISSET(fd, &write_set);
   }
   /*!