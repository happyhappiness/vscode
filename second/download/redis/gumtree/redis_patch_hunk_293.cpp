         anetSetError(err, "setsockopt SO_KEEPALIVE: %s", strerror(errno));
         return ANET_ERR;
     }
     return ANET_OK;
 }
 
-int anetResolve(char *err, char *host, char *ipbuf, size_t ipbuf_len)
+/* anetGenericResolve() is called by anetResolve() and anetResolveIP() to
+ * do the actual work. It resolves the hostname "host" and set the string
+ * representation of the IP address into the buffer pointed by "ipbuf".
+ *
+ * If flags is set to ANET_IP_ONLY the function only resolves hostnames
+ * that are actually already IPv4 or IPv6 addresses. This turns the function
+ * into a validating / normalizing function. */
+int anetGenericResolve(char *err, char *host, char *ipbuf, size_t ipbuf_len,
+                       int flags)
 {
     struct addrinfo hints, *info;
     int rv;
 
     memset(&hints,0,sizeof(hints));
+    if (flags & ANET_IP_ONLY) hints.ai_flags = AI_NUMERICHOST;
     hints.ai_family = AF_UNSPEC;
     hints.ai_socktype = SOCK_STREAM;  /* specify socktype to avoid dups */
 
     if ((rv = getaddrinfo(host, NULL, &hints, &info)) != 0) {
         anetSetError(err, "%s", gai_strerror(rv));
         return ANET_ERR;
