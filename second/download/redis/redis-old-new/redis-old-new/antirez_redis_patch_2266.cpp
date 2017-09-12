@@ -237,7 +237,7 @@ int anetTcpServer(char *err, int port, char *bindaddr)
         close(s);
         return ANET_ERR;
     }
-    if (listen(s, 64) == -1) {
+    if (listen(s, 511) == -1) { /* the magic 511 constant is from nginx */
         anetSetError(err, "listen: %s\n", strerror(errno));
         close(s);
         return ANET_ERR;