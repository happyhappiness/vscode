@@ -100,15 +100,19 @@ int anetKeepAlive(char *err, int fd, int interval)
         return ANET_ERR;
     }
 
-    /* Send next probes after interval. */
-    val = interval;
+    /* Send next probes after the specified interval. Note that we set the
+     * delay as interval / 3, as we send three probes before detecting
+     * an error (see the next setsockopt call). */
+    val = interval/3;
+    if (val == 0) val = 1;
     if (setsockopt(fd, IPPROTO_TCP, TCP_KEEPINTVL, &val, sizeof(val)) < 0) {
         anetSetError(err, "setsockopt TCP_KEEPINTVL: %s\n", strerror(errno));
         return ANET_ERR;
     }
 
-    /* Consider the socket in error state after just one missing ACK reply. */
-    val = 1;
+    /* Consider the socket in error state after three we send three ACK
+     * probes without getting a reply. */
+    val = 3;
     if (setsockopt(fd, IPPROTO_TCP, TCP_KEEPCNT, &val, sizeof(val)) < 0) {
         anetSetError(err, "setsockopt TCP_KEEPCNT: %s\n", strerror(errno));
         return ANET_ERR;