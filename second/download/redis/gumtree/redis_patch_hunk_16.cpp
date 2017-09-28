         close(s);
         return ANET_ERR;
     }
     return ANET_OK;
 }
 
-int anetTcpServer(char *err, int port, char *bindaddr)
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
+static int _anetTcpServer(char *err, int port, char *bindaddr, int af)
 {
-    int s;
-    struct sockaddr_in sa;
+    int s, rv;
+    char _port[6];  /* strlen("65535") */
+    struct addrinfo hints, *servinfo, *p;
 
-    if ((s = anetCreateSocket(err,AF_INET)) == ANET_ERR)
-        return ANET_ERR;
+    snprintf(_port,6,"%d",port);
+    memset(&hints,0,sizeof(hints));
+    hints.ai_family = af;
+    hints.ai_socktype = SOCK_STREAM;
+    hints.ai_flags = AI_PASSIVE;    /* No effect if bindaddr != NULL */
 
-    memset(&sa,0,sizeof(sa));
-    sa.sin_family = AF_INET;
-    sa.sin_port = htons(port);
-    sa.sin_addr.s_addr = htonl(INADDR_ANY);
-    if (bindaddr && inet_aton(bindaddr, &sa.sin_addr) == 0) {
-        anetSetError(err, "invalid bind address");
-        close(s);
+    if ((rv = getaddrinfo(bindaddr,_port,&hints,&servinfo)) != 0) {
+        anetSetError(err, "%s", gai_strerror(rv));
         return ANET_ERR;
     }
-    if (anetListen(err,s,(struct sockaddr*)&sa,sizeof(sa)) == ANET_ERR)
-        return ANET_ERR;
+    for (p = servinfo; p != NULL; p = p->ai_next) {
+        if ((s = socket(p->ai_family,p->ai_socktype,p->ai_protocol)) == -1)
+            continue;
+
+        if (af == AF_INET6 && anetV6Only(err,s) == ANET_ERR) goto error;
+        if (anetSetReuseAddr(err,s) == ANET_ERR) goto error;
+        if (anetListen(err,s,p->ai_addr,p->ai_addrlen) == ANET_ERR) goto error;
+        goto end;
+    }
+    if (p == NULL) {
+        anetSetError(err, "unable to bind socket");
+        goto error;
+    }
+
+error:
+    s = ANET_ERR;
+end:
+    freeaddrinfo(servinfo);
     return s;
 }
 
+int anetTcpServer(char *err, int port, char *bindaddr)
+{
+    return _anetTcpServer(err, port, bindaddr, AF_INET);
+}
+
+int anetTcp6Server(char *err, int port, char *bindaddr)
+{
+    return _anetTcpServer(err, port, bindaddr, AF_INET6);
+}
+
 int anetUnixServer(char *err, char *path, mode_t perm)
 {
     int s;
     struct sockaddr_un sa;
 
     if ((s = anetCreateSocket(err,AF_LOCAL)) == ANET_ERR)
