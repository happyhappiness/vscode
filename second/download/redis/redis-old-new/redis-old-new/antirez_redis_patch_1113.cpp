@@ -186,17 +186,28 @@ int anetResolve(char *err, char *host, char *ipbuf, size_t ipbuf_len)
     return ANET_OK;
 }
 
+static int anetSetReuseAddr(char *err, int fd) {
+    int yes = 1;
+    /* Make sure connection-intensive things like the redis benckmark
+     * will be able to close/open sockets a zillion of times */
+    if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes)) == -1) {
+        anetSetError(err, "setsockopt SO_REUSEADDR: %s", strerror(errno));
+        return ANET_ERR;
+    }
+    return ANET_OK;
+}
+
 static int anetCreateSocket(char *err, int domain) {
-    int s, on = 1;
+    int s;
     if ((s = socket(domain, SOCK_STREAM, 0)) == -1) {
         anetSetError(err, "creating socket: %s", strerror(errno));
         return ANET_ERR;
     }
 
     /* Make sure connection-intensive things like the redis benchmark
      * will be able to close/open sockets a zillion of times */
-    if (setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)) == -1) {
-        anetSetError(err, "setsockopt SO_REUSEADDR: %s", strerror(errno));
+    if (anetSetReuseAddr(err,s) == ANET_ERR) {
+        close(s);
         return ANET_ERR;
     }
     return s;