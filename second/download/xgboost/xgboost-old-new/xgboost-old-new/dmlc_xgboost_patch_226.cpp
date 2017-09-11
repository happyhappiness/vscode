@@ -71,7 +71,8 @@ class TCPSocket {
   explicit TCPSocket(int sockfd) : sockfd(sockfd) {
   }
   ~TCPSocket(void) {
-    if (sockfd != -1) this->Close();
+    // do nothing in destructor
+    // user need to take care of close
   }
   // default conversion to int
   inline operator int() const {
@@ -99,11 +100,22 @@ class TCPSocket {
   inline static void Finalize(void) {
   }
   /*! 
-   * \brief set this socket to use async I/O 
+   * \brief set this socket to use non-blocking mode
+   * \param non_block whether set it to be non-block, if it is false
+   *        it will set it back to block mode
    */
-  inline void SetNonBlock(void) {
-    if (fcntl(sockfd, fcntl(sockfd, F_GETFL) | O_NONBLOCK) == -1) {
-      SockError("SetNonBlock", errno);
+  inline void SetNonBlock(bool non_block) {
+    int flag = fcntl(sockfd, F_GETFL, 0);
+    if (flag == -1) {
+      SockError("SetNonBlock-1", errno);
+    }
+    if (non_block) {
+      flag |= O_NONBLOCK;
+    } else {
+      flag &= ~O_NONBLOCK;
+    }
+    if (fcntl(sockfd, F_SETFL, flag) == -1) {
+      SockError("SetNonBlock-2", errno);
     }
   }
   /*!
@@ -209,7 +221,7 @@ class TCPSocket {
     const char *buf = reinterpret_cast<const char*>(buf_);
     size_t ndone = 0;
     while (ndone <  len) {
-      ssize_t ret = send(sockfd, buf, len, 0);
+      ssize_t ret = send(sockfd, buf, len - ndone, 0);
       if (ret == -1) {
         if (errno == EAGAIN || errno == EWOULDBLOCK) return ndone;
         SockError("Recv", errno);
@@ -230,7 +242,7 @@ class TCPSocket {
     char *buf = reinterpret_cast<char*>(buf_);
     size_t ndone = 0;
     while (ndone <  len) {
-      ssize_t ret = recv(sockfd, buf, len, MSG_WAITALL);
+      ssize_t ret = recv(sockfd, buf, len - ndone, MSG_WAITALL);
       if (ret == -1) {
         if (errno == EAGAIN || errno == EWOULDBLOCK) return ndone;
         SockError("Recv", errno);