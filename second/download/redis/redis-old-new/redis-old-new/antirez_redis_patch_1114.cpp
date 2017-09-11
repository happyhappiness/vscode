@@ -163,22 +163,26 @@ int anetTcpKeepAlive(char *err, int fd)
     return ANET_OK;
 }
 
-int anetResolve(char *err, char *host, char *ipbuf)
+int anetResolve(char *err, char *host, char *ipbuf, size_t ipbuf_len)
 {
-    struct sockaddr_in sa;
+    struct addrinfo hints, *info;
+    void *addr;
+    int rv;
 
-    sa.sin_family = AF_INET;
-    if (inet_aton(host, &sa.sin_addr) == 0) {
-        struct hostent *he;
+    memset(&hints,0,sizeof(hints));
+    hints.ai_family = AF_INET;
 
-        he = gethostbyname(host);
-        if (he == NULL) {
-            anetSetError(err, "can't resolve: %s", host);
-            return ANET_ERR;
-        }
-        memcpy(&sa.sin_addr, he->h_addr, sizeof(struct in_addr));
+    if ((rv = getaddrinfo(host, NULL, &hints, &info)) != 0) {
+        anetSetError(err, "%s", gai_strerror(rv));
+        return ANET_ERR;
     }
-    strcpy(ipbuf,inet_ntoa(sa.sin_addr));
+    if (info->ai_family == AF_INET) {
+        struct sockaddr_in *sa = (struct sockaddr_in *)info->ai_addr;
+        addr = &(sa->sin_addr);
+    }
+
+    inet_ntop(info->ai_family, addr, ipbuf, ipbuf_len);
+    freeaddrinfo(info);
     return ANET_OK;
 }
 