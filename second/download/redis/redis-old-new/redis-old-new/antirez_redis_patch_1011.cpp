@@ -220,15 +220,15 @@ static int anetCreateSocket(char *err, int domain) {
 static int anetTcpGenericConnect(char *err, char *addr, int port, int flags)
 {
     int s = ANET_ERR, rv;
-    char _port[6];  /* strlen("65535") + 1; */
+    char portstr[6];  /* strlen("65535") + 1; */
     struct addrinfo hints, *servinfo, *p;
 
-    snprintf(_port,sizeof(port),"%d",port);
+    snprintf(portstr,sizeof(portstr),"%d",port);
     memset(&hints,0,sizeof(hints));
     hints.ai_family = AF_UNSPEC;
     hints.ai_socktype = SOCK_STREAM;
 
-    if ((rv = getaddrinfo(addr,_port,&hints,&servinfo)) != 0) {
+    if ((rv = getaddrinfo(addr,portstr,&hints,&servinfo)) != 0) {
         anetSetError(err, "%s", gai_strerror(rv));
         return ANET_ERR;
     }