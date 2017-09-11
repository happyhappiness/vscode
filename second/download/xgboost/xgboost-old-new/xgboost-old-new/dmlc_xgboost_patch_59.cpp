@@ -51,7 +51,7 @@ struct SockAddr {
     utils::Check(gethostname(&buf[0], 256) != -1, "fail to get host name");
     return std::string(buf.c_str());
   }
-  /*! 
+  /*!
    * \brief set the address
    * \param url the url of the address
    * \param port the port of address
@@ -83,7 +83,7 @@ struct SockAddr {
   }
 };
 
-/*! 
+/*!
  * \brief base class containing common operations of TCP and UDP sockets
  */
 class Socket {
@@ -95,6 +95,25 @@ class Socket {
     return sockfd;
   }
   /*!
+   * \return last error of socket operation
+   */
+  inline static int GetLastError(void) {
+#ifdef _WIN32
+    return WSAGetLastError();
+#else
+    return errno;
+#endif
+  }
+  /*! \return whether last error was would block */
+  inline static bool LastErrorWouldBlock(void) {
+    int errsv = GetLastError();
+#ifdef _WIN32
+    return errsv == WSAEWOULDBLOCK;
+#else
+    return errsv == EAGAIN || errsv == EWOULDBLOCK;
+#endif
+  }
+  /*!
    * \brief start up the socket module
    *   call this before using the sockets
    */
@@ -110,15 +129,15 @@ class Socket {
     }
 #endif
   }
-  /*! 
+  /*!
    * \brief shutdown the socket module after use, all sockets need to be closed
-   */  
+   */
   inline static void Finalize(void) {
 #ifdef _WIN32
     WSACleanup();
 #endif
   }
-  /*! 
+  /*!
    * \brief set this socket to use non-blocking mode
    * \param non_block whether set it to be non-block, if it is false
    *        it will set it back to block mode
@@ -144,8 +163,8 @@ class Socket {
     }
 #endif
   }
-  /*! 
-   * \brief bind the socket to an address 
+  /*!
+   * \brief bind the socket to an address
    * \param addr
    */
   inline void Bind(const SockAddr &addr) {
@@ -154,7 +173,7 @@ class Socket {
       Socket::Error("Bind");
     }
   }
-  /*! 
+  /*!
    * \brief try bind the socket to host, from start_port to end_port
    * \param start_port starting port number to try
    * \param end_port ending port number to try
@@ -169,11 +188,11 @@ class Socket {
         return port;
       }
 #if defined(_WIN32)
-	  if (WSAGetLastError() != WSAEADDRINUSE) {
-        Socket::Error("TryBindHost");	  
-	  }
+      if (WSAGetLastError() != WSAEADDRINUSE) {
+        Socket::Error("TryBindHost");
+      }
 #else
-	  if (errno != EADDRINUSE) {
+      if (errno != EADDRINUSE) {
         Socket::Error("TryBindHost");
       }
 #endif
@@ -216,16 +235,20 @@ class Socket {
   }
   // report an socket error
   inline static void Error(const char *msg) {
-    int errsv = errno;
+    int errsv = GetLastError();
+#ifdef _WIN32
+    utils::Error("Socket %s Error:WSAError-code=%d", msg, errsv);
+#else
     utils::Error("Socket %s Error:%s", msg, strerror(errsv));
+#endif
   }
 
  protected:
   explicit Socket(SOCKET sockfd) : sockfd(sockfd) {
   }
 };
 
-/*! 
+/*!
  * \brief a wrapper of TCP socket that hopefully be cross platform
  */
 class TCPSocket : public Socket{
@@ -238,10 +261,11 @@ class TCPSocket : public Socket{
   /*!
    * \brief enable/disable TCP keepalive
    * \param keepalive whether to set the keep alive option on
-   */  
+   */
   inline void SetKeepAlive(bool keepalive) {
     int opt = static_cast<int>(keepalive);
-    if (setsockopt(sockfd, SOL_SOCKET, SO_KEEPALIVE, reinterpret_cast<char*>(&opt), sizeof(opt)) < 0) {
+    if (setsockopt(sockfd, SOL_SOCKET, SO_KEEPALIVE,
+                   reinterpret_cast<char*>(&opt), sizeof(opt)) < 0) {
       Socket::Error("SetKeepAlive");
     }
   }
@@ -271,21 +295,21 @@ class TCPSocket : public Socket{
     return TCPSocket(newfd);
   }
   /*!
-   * \brief decide whether the socket is at OOB mark 
+   * \brief decide whether the socket is at OOB mark
    * \return 1 if at mark, 0 if not, -1 if an error occured
    */
   inline int AtMark(void) const {
 #ifdef _WIN32
-	unsigned long atmark;
+    unsigned long atmark;  // NOLINT(*)
     if (ioctlsocket(sockfd, SIOCATMARK, &atmark) != NO_ERROR) return -1;
 #else
     int atmark;
     if (ioctl(sockfd, SIOCATMARK, &atmark) == -1) return -1;
 #endif
     return static_cast<int>(atmark);
   }
-  /*! 
-   * \brief connect to an address 
+  /*!
+   * \brief connect to an address
    * \param addr the address to connect to
    * \return whether connect is successful
    */
@@ -305,8 +329,8 @@ class TCPSocket : public Socket{
     const char *buf = reinterpret_cast<const char*>(buf_);
     return send(sockfd, buf, static_cast<sock_size_t>(len), flag);
   }
-  /*! 
-   * \brief receive data using the socket 
+  /*!
+   * \brief receive data using the socket
    * \param buf_ the pointer to the buffer
    * \param len the size of the buffer
    * \param flags extra flags
@@ -330,7 +354,7 @@ class TCPSocket : public Socket{
     while (ndone <  len) {
       ssize_t ret = send(sockfd, buf, static_cast<ssize_t>(len - ndone), 0);
       if (ret == -1) {
-        if (errno == EAGAIN || errno == EWOULDBLOCK) return ndone;
+        if (LastErrorWouldBlock()) return ndone;
         Socket::Error("SendAll");
       }
       buf += ret;
@@ -352,7 +376,7 @@ class TCPSocket : public Socket{
       ssize_t ret = recv(sockfd, buf,
                          static_cast<sock_size_t>(len - ndone), MSG_WAITALL);
       if (ret == -1) {
-        if (errno == EAGAIN || errno == EWOULDBLOCK) return ndone;
+        if (LastErrorWouldBlock()) return ndone;
         Socket::Error("RecvAll");
       }
       if (ret == 0) return ndone;
@@ -362,7 +386,7 @@ class TCPSocket : public Socket{
     return ndone;
   }
   /*!
-   * \brief send a string over network 
+   * \brief send a string over network
    * \param str the string to be sent
    */
   inline void SendStr(const std::string &str) {
@@ -400,7 +424,7 @@ struct SelectHelper {
     maxfd = 0;
   }
   /*!
-   * \brief add file descriptor to watch for read 
+   * \brief add file descriptor to watch for read
    * \param fd file descriptor to be watched
    */
   inline void WatchRead(SOCKET fd) {
@@ -450,7 +474,7 @@ struct SelectHelper {
    * \param timeout the timeout counter, can be 0, which means wait until the event happen
    * \return 1 if success, 0 if timeout, and -1 if error occurs
    */
-  inline static int WaitExcept(SOCKET fd, long timeout = 0) {
+  inline static int WaitExcept(SOCKET fd, long timeout = 0) { // NOLINT(*)
     fd_set wait_set;
     FD_ZERO(&wait_set);
     FD_SET(fd, &wait_set);
@@ -463,10 +487,10 @@ struct SelectHelper {
    * \param select_write whether to watch for write event
    * \param select_except whether to watch for exception event
    * \param timeout specify timeout in micro-seconds(ms) if equals 0, means select will always block
-   * \return number of active descriptors selected, 
+   * \return number of active descriptors selected,
    *         return -1 if error occurs
    */
-  inline int Select(long timeout = 0) {
+  inline int Select(long timeout = 0) {  // NOLINT(*)
     int ret =  Select_(static_cast<int>(maxfd + 1),
                        &read_set, &write_set, &except_set, timeout);
     if (ret == -1) {
@@ -477,7 +501,7 @@ struct SelectHelper {
 
  private:
   inline static int Select_(int maxfd, fd_set *rfds,
-                            fd_set *wfds, fd_set *efds, long timeout) {
+                            fd_set *wfds, fd_set *efds, long timeout) { // NOLINT(*)
 #if !defined(_WIN32)
     utils::Assert(maxfd < FD_SETSIZE, "maxdf must be smaller than FDSETSIZE");
 #endif