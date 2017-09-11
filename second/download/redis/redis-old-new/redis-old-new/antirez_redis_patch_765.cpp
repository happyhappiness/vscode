@@ -117,6 +117,8 @@ int anetKeepAlive(char *err, int fd, int interval)
         anetSetError(err, "setsockopt TCP_KEEPCNT: %s\n", strerror(errno));
         return ANET_ERR;
     }
+#else
+    ((void) interval); /* Avoid unused var warning for non Linux systems. */
 #endif
 
     return ANET_OK;
@@ -262,7 +264,8 @@ static int anetTcpGenericConnect(char *err, char *addr, int port,
         if (source_addr) {
             int bound = 0;
             /* Using getaddrinfo saves us from self-determining IPv4 vs IPv6 */
-            if ((rv = getaddrinfo(source_addr, NULL, &hints, &bservinfo)) != 0) {
+            if ((rv = getaddrinfo(source_addr, NULL, &hints, &bservinfo)) != 0)
+            {
                 anetSetError(err, "%s", gai_strerror(rv));
                 goto end;
             }
@@ -272,6 +275,7 @@ static int anetTcpGenericConnect(char *err, char *addr, int port,
                     break;
                 }
             }
+            freeaddrinfo(bservinfo);
             if (!bound) {
                 anetSetError(err, "bind: %s", strerror(errno));
                 goto end;