@@ -25,6 +25,9 @@ namespace xgboost {
 namespace utils {
 #if defined(_WIN32)
 typedef int ssize_t;
+#else
+typedef int SOCKET;
+const int INVALID_SOCKET = -1;
 #endif
 
 /*! \brief data structure for network address */
@@ -92,7 +95,7 @@ class TCPSocket {
   inline void Create(int af = PF_INET) {
     sockfd = socket(PF_INET, SOCK_STREAM, 0);
     if (sockfd == INVALID_SOCKET) {
-      SockError("Create", errno);
+      SockError("Create");
     }
   }
   /*!
@@ -120,15 +123,15 @@ class TCPSocket {
 #else
     int flag = fcntl(sockfd, F_GETFL, 0);
     if (flag == -1) {
-      SockError("SetNonBlock-1", errno);
+      SockError("SetNonBlock-1");
     }
     if (non_block) {
       flag |= O_NONBLOCK;
     } else {
       flag &= ~O_NONBLOCK;
     }
     if (fcntl(sockfd, F_SETFL, flag) == -1) {
-      SockError("SetNonBlock-2", errno);
+      SockError("SetNonBlock-2");
     }
 #endif
   }
@@ -153,7 +156,7 @@ class TCPSocket {
    */
   inline void Bind(const SockAddr &addr) {
     if (bind(sockfd, (sockaddr*)&addr.addr, sizeof(addr.addr)) == -1) {
-      SockError("Bind", errno);
+      SockError("Bind");
     }
   }
   /*! 
@@ -170,7 +173,7 @@ class TCPSocket {
         return port;
       }
       if (errno != EADDRINUSE) {
-        SockError("TryBindHost", errno);
+        SockError("TryBindHost");
       }
     }
     return -1;
@@ -181,7 +184,7 @@ class TCPSocket {
    */
   inline void Connect(const SockAddr &addr) {
     if (connect(sockfd, (sockaddr*)&addr.addr, sizeof(addr.addr)) == -1) {
-      SockError("Connect", errno);
+      SockError("Connect");
     }
   }
   /*! \brief close the connection */
@@ -209,7 +212,7 @@ class TCPSocket {
     ssize_t ret = send(sockfd, buf, len, flag);
     if (ret == -1) {
       if (errno == EAGAIN || errno == EWOULDBLOCK) return 0;
-      SockError("Send", errno);
+      SockError("Send");
     }
     return ret;
   }  
@@ -225,7 +228,7 @@ class TCPSocket {
     ssize_t ret = recv(sockfd, buf, len, flags);
     if (ret == -1) {
       if (errno == EAGAIN || errno == EWOULDBLOCK) return 0;
-      SockError("Recv", errno);
+      SockError("Recv");
     }
     return ret;
   } 
@@ -243,7 +246,7 @@ class TCPSocket {
       ssize_t ret = send(sockfd, buf, static_cast<ssize_t>(len - ndone), 0);
       if (ret == -1) {
         if (errno == EAGAIN || errno == EWOULDBLOCK) return ndone;
-        SockError("Recv", errno);
+        SockError("Recv");
       }
       buf += ret;
       ndone += ret;
@@ -264,7 +267,7 @@ class TCPSocket {
       ssize_t ret = recv(sockfd, buf, len - ndone, MSG_WAITALL);
       if (ret == -1) {
         if (errno == EAGAIN || errno == EWOULDBLOCK) return ndone;
-        SockError("Recv", errno);
+        SockError("Recv");
       }
       if (ret == 0) return ndone;
       buf += ret;
@@ -275,7 +278,8 @@ class TCPSocket {
 
  private:
   // report an socket error
-  inline static void SockError(const char *msg, int errsv) {
+  inline static void SockError(const char *msg) {
+    int errsv = errno;
     char buf[256];    
     Error("Socket %s Error:%s", msg, strerror_r(errsv, buf, sizeof(buf)));
   }