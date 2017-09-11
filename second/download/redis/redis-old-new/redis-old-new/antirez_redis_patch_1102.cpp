@@ -372,15 +372,15 @@ static int anetV6Only(char *err, int s) {
     return ANET_OK;
 }
 
-int anetTcpServer(char *err, int port, char *bindaddr)
+static int _anetTcpServer(char *err, int port, char *bindaddr, int af)
 {
     int s, rv;
     char _port[6];  /* strlen("65535") */
     struct addrinfo hints, *servinfo, *p;
 
     snprintf(_port,6,"%d",port);
     memset(&hints,0,sizeof(hints));
-    hints.ai_family = AF_INET;
+    hints.ai_family = af;
     hints.ai_socktype = SOCK_STREAM;
     hints.ai_flags = AI_PASSIVE;    /* No effect if bindaddr != NULL */
 
@@ -392,6 +392,9 @@ int anetTcpServer(char *err, int port, char *bindaddr)
         if ((s = socket(p->ai_family,p->ai_socktype,p->ai_protocol)) == -1)
             continue;
 
+        if (AF_INET6 == af && anetV6Only(err,s) == ANET_ERR)
+            goto error;    /* could continue here? */
+
         if (anetListen(err,s,p->ai_addr,p->ai_addrlen) == ANET_ERR)
             goto error;    /* could continue here? */
         goto end;
@@ -408,6 +411,16 @@ int anetTcpServer(char *err, int port, char *bindaddr)
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