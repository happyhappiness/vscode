@@ -362,6 +362,16 @@ static int anetListen(char *err, int s, struct sockaddr *sa, socklen_t len) {
     return ANET_OK;
 }
 
+static int anetV6Only(char *err, int s) {
+    int yes = 1;
+    if (setsockopt(s,IPPROTO_IPV6,IPV6_V6ONLY,&yes,sizeof(yes)) == -1) {
+        anetSetError(err, "setsockopt: %s", strerror(errno));
+        close(s);
+        return ANET_ERR;
+    }
+    return ANET_OK;
+}
+
 int anetTcpServer(char *err, int port, char *bindaddr)
 {
     int s, rv;