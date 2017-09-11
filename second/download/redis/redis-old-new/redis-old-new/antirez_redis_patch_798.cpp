@@ -262,7 +262,8 @@ static int anetTcpGenericConnect(char *err, char *addr, int port,
         if (source_addr) {
             int bound = 0;
             /* Using getaddrinfo saves us from self-determining IPv4 vs IPv6 */
-            if ((rv = getaddrinfo(source_addr, NULL, &hints, &bservinfo)) != 0) {
+            if ((rv = getaddrinfo(source_addr, NULL, &hints, &bservinfo)) != 0)
+            {
                 anetSetError(err, "%s", gai_strerror(rv));
                 goto end;
             }
@@ -272,6 +273,7 @@ static int anetTcpGenericConnect(char *err, char *addr, int port,
                     break;
                 }
             }
+            freeaddrinfo(bservinfo);
             if (!bound) {
                 anetSetError(err, "bind: %s", strerror(errno));
                 goto end;