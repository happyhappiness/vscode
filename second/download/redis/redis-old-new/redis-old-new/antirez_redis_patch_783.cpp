@@ -117,6 +117,8 @@ int anetKeepAlive(char *err, int fd, int interval)
         anetSetError(err, "setsockopt TCP_KEEPCNT: %s\n", strerror(errno));
         return ANET_ERR;
     }
+#else
+    ((void) interval); /* Avoid unused var warning for non Linux systems. */
 #endif
 
     return ANET_OK;