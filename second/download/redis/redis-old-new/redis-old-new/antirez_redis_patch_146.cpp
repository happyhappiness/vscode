@@ -486,7 +486,7 @@ static int _anetTcpServer(char *err, int port, char *bindaddr, int af, int backl
         goto end;
     }
     if (p == NULL) {
-        anetSetError(err, "unable to bind socket");
+        anetSetError(err, "unable to bind socket, errno: %d", errno);
         goto error;
     }
 