@@ -331,9 +331,9 @@ static int anetListen(char *err, int s, struct sockaddr *sa, socklen_t len) {
     return ANET_OK;
 }
 
-int anetTcpServer(char *err, int port, char **bindaddr, int bindaddr_count)
+int anetTcpServer(char *err, int port, char *bindaddr)
 {
-    int s, j;
+    int s;
     struct sockaddr_in sa;
 
     if ((s = anetCreateSocket(err,AF_INET)) == ANET_ERR)
@@ -343,20 +343,13 @@ int anetTcpServer(char *err, int port, char **bindaddr, int bindaddr_count)
     sa.sin_family = AF_INET;
     sa.sin_port = htons(port);
     sa.sin_addr.s_addr = htonl(INADDR_ANY);
-    if (bindaddr_count) {
-        for (j = 0; j < bindaddr_count; j++) {
-            if (inet_aton(bindaddr[j], &sa.sin_addr) == 0) {
-                anetSetError(err, "invalid bind address");
-                close(s);
-                return ANET_ERR;
-            }
-            if (anetListen(err,s,(struct sockaddr*)&sa,sizeof(sa)) == ANET_ERR)
-                return ANET_ERR;
-        }
-    } else {
-        if (anetListen(err,s,(struct sockaddr*)&sa,sizeof(sa)) == ANET_ERR)
-            return ANET_ERR;
+    if (bindaddr && inet_aton(bindaddr, &sa.sin_addr) == 0) {
+        anetSetError(err, "invalid bind address");
+        close(s);
+        return ANET_ERR;
     }
+    if (anetListen(err,s,(struct sockaddr*)&sa,sizeof(sa)) == ANET_ERR)
+        return ANET_ERR;
     return s;
 }
 