@@ -234,11 +234,12 @@ static int anetCreateSocket(char *err, int domain) {
 
 #define ANET_CONNECT_NONE 0
 #define ANET_CONNECT_NONBLOCK 1
-static int anetTcpGenericConnect(char *err, char *addr, int port, int flags)
+static int anetTcpGenericConnect(char *err, char *addr, int port,
+                                 char *source_addr, int flags)
 {
     int s = ANET_ERR, rv;
     char portstr[6];  /* strlen("65535") + 1; */
-    struct addrinfo hints, *servinfo, *p;
+    struct addrinfo hints, *servinfo, *bservinfo, *p, *b;
 
     snprintf(portstr,sizeof(portstr),"%d",port);
     memset(&hints,0,sizeof(hints));
@@ -258,6 +259,24 @@ static int anetTcpGenericConnect(char *err, char *addr, int port, int flags)
         if (anetSetReuseAddr(err,s) == ANET_ERR) goto error;
         if (flags & ANET_CONNECT_NONBLOCK && anetNonBlock(err,s) != ANET_OK)
             goto error;
+        if (source_addr) {
+            int bound = 0;
+            /* Using getaddrinfo saves us from self-determining IPv4 vs IPv6 */
+            if ((rv = getaddrinfo(source_addr, NULL, &hints, &bservinfo)) != 0) {
+                anetSetError(err, "%s", gai_strerror(rv));
+                goto end;
+            }
+            for (b = bservinfo; b != NULL; b = b->ai_next) {
+                if (bind(s,b->ai_addr,b->ai_addrlen) != -1) {
+                    bound = 1;
+                    break;
+                }
+            }
+            if (!bound) {
+                anetSetError(err, "bind: %s", strerror(errno));
+                goto end;
+            }
+        }
         if (connect(s,p->ai_addr,p->ai_addrlen) == -1) {
             /* If the socket is non-blocking, it is ok for connect() to
              * return an EINPROGRESS error here. */
@@ -287,12 +306,17 @@ static int anetTcpGenericConnect(char *err, char *addr, int port, int flags)
 
 int anetTcpConnect(char *err, char *addr, int port)
 {
-    return anetTcpGenericConnect(err,addr,port,ANET_CONNECT_NONE);
+    return anetTcpGenericConnect(err,addr,port,NULL,ANET_CONNECT_NONE);
 }
 
 int anetTcpNonBlockConnect(char *err, char *addr, int port)
 {
-    return anetTcpGenericConnect(err,addr,port,ANET_CONNECT_NONBLOCK);
+    return anetTcpGenericConnect(err,addr,port,NULL,ANET_CONNECT_NONBLOCK);
+}
+
+int anetTcpNonBlockBindConnect(char *err, char *addr, int port, char *source_addr)
+{
+    return anetTcpGenericConnect(err,addr,port,source_addr,ANET_CONNECT_NONBLOCK);
 }
 
 int anetUnixGenericConnect(char *err, char *path, int flags)