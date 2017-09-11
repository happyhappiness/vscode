@@ -28,28 +28,34 @@ struct SockAddr {
   SockAddr(const char *url, int port) {
     this->Set(url, port);
   }
+  inline static std::string GetHostName(void) {
+    std::string buf; buf.resize(256);
+    utils::Check(gethostname(&buf[0], 256) != -1, "fail to get host name");
+    return std::string(buf.c_str());
+  }
   /*! 
    * \brief set the address
    * \param url the url of the address
    * \param port the port of address
    */
-  inline void Set(const char *url, int port) {
-    hostent *hp = gethostbyname(url);
-    Check(hp != NULL, "cannot obtain address of %s", url);
+  inline void Set(const char *host, int port) {
+    hostent *hp = gethostbyname(host);
+    Check(hp != NULL, "cannot obtain address of %s", host);
     memset(&addr, 0, sizeof(addr));
     addr.sin_family = AF_INET;
     addr.sin_port = htons(port);
     memcpy(&addr.sin_addr, hp->h_addr_list[0], hp->h_length);
   }
+  /*! \brief return port of the address*/
+  inline int port(void) const {
+    return ntohs(addr.sin_port);
+  }
   /*! \return a string representation of the address */
-  inline std::string ToString(void) const {
+  inline std::string AddrStr(void) const {
     std::string buf; buf.resize(256);
-    const char *s = inet_ntop(AF_INET, &addr, &buf[0], buf.length());
+    const char *s = inet_ntop(AF_INET, &addr.sin_addr, &buf[0], buf.length());
     Assert(s != NULL, "cannot decode address");
-    std::string res = s;
-    sprintf(&buf[0], "%u", ntohs(addr.sin_port));
-    res += ":" + buf;
-    return res;
+    return std::string(s);
   }
 };
 /*! 
@@ -60,12 +66,28 @@ class TCPSocket {
   /*! \brief the file descriptor of socket */
   int sockfd;
   // constructor
-  TCPSocket(void) {}
+  TCPSocket(void) : sockfd(-1) {
+  }
+  explicit TCPSocket(int sockfd) : sockfd(sockfd) {
+  }
+  ~TCPSocket(void) {
+    if (sockfd != -1) this->Close();
+  }
   // default conversion to int
   inline operator int() const {
     return sockfd;
   }
   /*!
+   * \brief create the socket, call this before using socket
+   * \param af domain
+   */
+  inline void Create(int af = PF_INET) {
+    sockfd = socket(PF_INET, SOCK_STREAM, 0);
+    if (sockfd == -1) {
+      SockError("Create", errno);
+    }
+  }
+  /*!
    * \brief start up the socket module
    *   call this before using the sockets
    */
@@ -79,9 +101,9 @@ class TCPSocket {
   /*! 
    * \brief set this socket to use async I/O 
    */
-  inline void SetAsync(void) {
+  inline void SetNonBlock(void) {
     if (fcntl(sockfd, fcntl(sockfd, F_GETFL) | O_NONBLOCK) == -1) {
-      SockError("SetAsync", errno);
+      SockError("SetNonBlock", errno);
     }
   }
   /*!
@@ -91,16 +113,43 @@ class TCPSocket {
   inline void Listen(int backlog = 16) {
     listen(sockfd, backlog);
   }
+  /*! \brief get a new connection */
+  TCPSocket Accept(void) {
+    int newfd = accept(sockfd, NULL, NULL);
+    if (newfd == -1) {
+      SockError("Accept", errno);
+    }
+    return TCPSocket(newfd);
+  }
   /*! 
    * \brief bind the socket to an address 
-   * \param 3
+   * \param addr
    */
   inline void Bind(const SockAddr &addr) {
     if (bind(sockfd, (sockaddr*)&addr.addr, sizeof(addr.addr)) == -1) {
       SockError("Bind", errno);
     }
   }
   /*! 
+   * \brief try bind the socket to host, from start_port to end_port
+   * \param start_port starting port number to try
+   * \param end_port ending port number to try
+   * \param out_addr the binding address, if successful
+   * \return whether the binding is successful
+   */
+  inline int TryBindHost(int start_port, int end_port) {    
+    for (int port = start_port; port < end_port; ++port) {
+      SockAddr addr("0.0.0.0", port);
+      if (bind(sockfd, (sockaddr*)&addr.addr, sizeof(addr.addr)) == 0) {
+        return port;
+      }
+      if (errno != EADDRINUSE) {
+        SockError("TryBindHost", errno);
+      }
+    }
+    return -1;
+  }                      
+  /*! 
    * \brief connect to an address 
    * \param addr the address to connect to
    */
@@ -111,7 +160,11 @@ class TCPSocket {
   }
   /*! \brief close the connection */
   inline void Close(void) {
-    close(sockfd);
+    if (sockfd != -1) {
+      close(sockfd); sockfd = -1;
+    } else {
+      Error("TCPSocket::Close double close the socket or close without create");
+    }
   }
   /*!
    * \brief send data using the socket 
@@ -123,22 +176,72 @@ class TCPSocket {
   inline size_t Send(const void *buf, size_t len, int flag = 0) {
     if (len == 0) return 0;
     ssize_t ret = send(sockfd, buf, len, flag);
-    if (ret == -1) SockError("Send", errno);
+    if (ret == -1) {
+      if (errno == EAGAIN || errno == EWOULDBLOCK) return 0;
+      SockError("Send", errno);
+    }
     return ret;
-  }
+  }  
   /*! 
-   * \brief send data using the socket 
+   * \brief receive data using the socket 
    * \param buf the pointer to the buffer
    * \param len the size of the buffer
    * \param flags extra flags
    * \return size of data actually received 
    */
   inline size_t Recv(void *buf, size_t len, int flags = 0) {
-    if (len == 0) return 0;
+    if (len == 0) return 0;    
     ssize_t ret = recv(sockfd, buf, len, flags);
-    if (ret == -1) SockError("Recv", errno);
+    if (ret == -1) {
+      if (errno == EAGAIN || errno == EWOULDBLOCK) return 0;
+      SockError("Recv", errno);
+    }
     return ret;
-   }
+  } 
+  /*!
+   * \brief peform block write that will attempt to send all data out
+   *    can still return smaller than request when error occurs
+   * \param buf the pointer to the buffer
+   * \param len the size of the buffer
+   * \return size of data actually sent
+   */
+  inline size_t SendAll(const void *buf_, size_t len) {
+    const char *buf = reinterpret_cast<const char*>(buf_);
+    size_t ndone = 0;
+    while (ndone <  len) {
+      ssize_t ret = send(sockfd, buf, len, 0);
+      if (ret == -1) {
+        if (errno == EAGAIN || errno == EWOULDBLOCK) return ndone;
+        SockError("Recv", errno);
+      }
+      buf += ret;
+      ndone += ret;
+    }
+    return ndone;
+  }
+  /*!
+   * \brief peforma block read that will attempt to read all data
+   *    can still return smaller than request when error occurs
+   * \param buf_ the buffer pointer
+   * \param len length of data to recv
+   * \return size of data actually sent
+   */
+  inline size_t RecvAll(void *buf_, size_t len) {
+    char *buf = reinterpret_cast<char*>(buf_);
+    size_t ndone = 0;
+    while (ndone <  len) {
+      ssize_t ret = recv(sockfd, buf, len, MSG_WAITALL);
+      if (ret == -1) {
+        if (errno == EAGAIN || errno == EWOULDBLOCK) return ndone;
+        SockError("Recv", errno);
+      }
+      if (ret == 0) return ndone;
+      buf += ret;
+      ndone += ret;
+    }
+    return ndone;
+  }
+
  private:
   // report an socket error
   inline static void SockError(const char *msg, int errsv) {
@@ -216,7 +319,7 @@ struct SelectHelper {
     if (ret == -1) {
       int errsv = errno;
       char buf[256];
-      Error("Select Error:%s", strerror_r(errsv, buf, sizeof(buf)));      
+      Error("Select Error: %s", strerror_r(errsv, buf, sizeof(buf)));      
     }
     return ret;
   }