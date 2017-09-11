@@ -75,6 +75,49 @@ int anetNonBlock(char *err, int fd)
     return ANET_OK;
 }
 
+/* Set TCP keep alive option to detect dead peers. The interval option
+ * is only used for Linux as we are using Linux-specific APIs to set
+ * the probe send time, interval, and count. */
+int anetKeepAlive(char *err, int fd, int interval)
+{
+    int val = 1;
+
+    if (setsockopt(fd, SOL_SOCKET, SO_KEEPALIVE, &val, sizeof(val)) == -1)
+    {
+        anetSetError(err, "setsockopt SO_KEEPALIVE: %s", strerror(errno));
+        return ANET_ERR;
+    }
+
+#ifdef __linux__
+    /* Default settings are more or less garbage, with the keepalive time
+     * set to 7200 by default on Linux. Modify settings to make the feature
+     * actually useful. */
+
+    /* Send first probe after interval. */
+    val = interval;
+    if (setsockopt(fd, IPPROTO_TCP, TCP_KEEPIDLE, &val, sizeof(val)) < 0) {
+        anetSetError(err, "setsockopt TCP_KEEPIDLE: %s\n", strerror(errno));
+        return ANET_ERR;
+    }
+
+    /* Send next probes after interval. */
+    val = interval;
+    if (setsockopt(fd, IPPROTO_TCP, TCP_KEEPINTVL, &val, sizeof(val)) < 0) {
+        anetSetError(err, "setsockopt TCP_KEEPINTVL: %s\n", strerror(errno));
+        return ANET_ERR;
+    }
+
+    /* Consider the socket in error state after just one missing ACK reply. */
+    val = 1;
+    if (setsockopt(fd, IPPROTO_TCP, TCP_KEEPCNT, &val, sizeof(val)) < 0) {
+        anetSetError(err, "setsockopt TCP_KEEPCNT: %s\n", strerror(errno));
+        return ANET_ERR;
+    }
+#endif
+
+    return ANET_OK;
+}
+
 static int anetSetTcpNoDelay(char *err, int fd, int val)
 {
     if (setsockopt(fd, IPPROTO_TCP, TCP_NODELAY, &val, sizeof(val)) == -1)