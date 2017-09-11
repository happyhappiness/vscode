@@ -225,7 +225,7 @@ static int anetTcpGenericConnect(char *err, char *addr, int port, int flags)
 
     snprintf(_port,6,"%d",port);
     memset(&hints,0,sizeof(hints));
-    hints.ai_family = AF_INET;
+    hints.ai_family = AF_UNSPEC;
     hints.ai_socktype = SOCK_STREAM;
 
     if ((rv = getaddrinfo(addr,_port,&hints,&servinfo)) != 0) {