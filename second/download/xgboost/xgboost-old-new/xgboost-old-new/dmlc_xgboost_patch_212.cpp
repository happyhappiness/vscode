@@ -69,7 +69,7 @@ struct SockAddr {
 #ifdef _WIN32
     const char *s = inet_ntop(AF_INET, (PVOID)&addr.sin_addr, &buf[0], buf.length());
 #else
-	const char *s = inet_ntop(AF_INET, &addr.sin_addr, &buf[0], buf.length());
+    const char *s = inet_ntop(AF_INET, &addr.sin_addr, &buf[0], buf.length());
 #endif
     Assert(s != NULL, "cannot decode address");
     return std::string(s);
@@ -111,12 +111,12 @@ class TCPSocket {
    */
   inline static void Startup(void) {
 #ifdef _WIN32
-	WSADATA wsa_data;
+    WSADATA wsa_data;
     if (WSAStartup(MAKEWORD(2, 2), &wsa_data) != -1) {
-	  SockError("Startup");
-	}
+      SockError("Startup");
+    }
     if (LOBYTE(wsa_data.wVersion) != 2 || HIBYTE(wsa_data.wVersion) != 2) {
-	  WSACleanup();
+      WSACleanup();
       utils::Error("Could not find a usable version of Winsock.dll\n");
     }
 #endif
@@ -136,10 +136,10 @@ class TCPSocket {
    */
   inline void SetNonBlock(bool non_block) {
 #ifdef _WIN32  
-	u_long mode = non_block ? 1 : 0;
-	if (ioctlsocket(sockfd, FIONBIO, &mode) != NO_ERROR) {
+    u_long mode = non_block ? 1 : 0;
+    if (ioctlsocket(sockfd, FIONBIO, &mode) != NO_ERROR) {
       SockError("SetNonBlock");
-	}
+    }
 #else
     int flag = fcntl(sockfd, F_GETFL, 0);
     if (flag == -1) {