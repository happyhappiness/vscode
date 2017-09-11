@@ -219,11 +219,11 @@ static int anetCreateSocket(char *err, int domain) {
 #define ANET_CONNECT_NONBLOCK 1
 static int anetTcpGenericConnect(char *err, char *addr, int port, int flags)
 {
-    int s, rv;
-    char _port[6];  /* strlen("65535"); */
+    int s = ANET_ERR, rv;
+    char _port[6];  /* strlen("65535") + 1; */
     struct addrinfo hints, *servinfo, *p;
 
-    snprintf(_port,6,"%d",port);
+    snprintf(_port,sizeof(port),"%d",port);
     memset(&hints,0,sizeof(hints));
     hints.ai_family = AF_UNSPEC;
     hints.ai_socktype = SOCK_STREAM;
@@ -233,20 +233,26 @@ static int anetTcpGenericConnect(char *err, char *addr, int port, int flags)
         return ANET_ERR;
     }
     for (p = servinfo; p != NULL; p = p->ai_next) {
+        /* Try to create the socket and to connect it.
+         * If we fail in the socket() call, or on connect(), we retry with
+         * the next entry in servinfo. */
         if ((s = socket(p->ai_family,p->ai_socktype,p->ai_protocol)) == -1)
             continue;
-
-        /* if we set err then goto cleanup, otherwise next */
         if (anetSetReuseAddr(err,s) == ANET_ERR) goto error;
         if (flags & ANET_CONNECT_NONBLOCK && anetNonBlock(err,s) != ANET_OK)
             goto error;
         if (connect(s,p->ai_addr,p->ai_addrlen) == -1) {
-            if (errno == EINPROGRESS && flags & ANET_CONNECT_NONBLOCK) goto end;
+            /* If the socket is non-blocking, it is ok for connect() to
+             * return an EINPROGRESS error here. */
+            if (errno == EINPROGRESS && flags & ANET_CONNECT_NONBLOCK)
+                goto end;
             close(s);
+            s = ANET_ERR;
             continue;
         }
 
-        /* break with the socket */
+        /* If we ended an iteration of the for loop without errors, we
+         * have a connected socket. Let's return to the caller. */
         goto end;
     }
     if (p == NULL) {
@@ -255,7 +261,10 @@ static int anetTcpGenericConnect(char *err, char *addr, int port, int flags)
     }
 
 error:
-    s = ANET_ERR;
+    if (s != ANET_ERR) {
+        close(s);
+        s = ANET_ERR;
+    }
 end:
     freeaddrinfo(servinfo);
     return s;