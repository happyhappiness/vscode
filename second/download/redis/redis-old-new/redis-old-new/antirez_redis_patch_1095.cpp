@@ -215,9 +215,17 @@ int redisContextConnectTcp(redisContext *c, const char *addr, int port, struct t
     hints.ai_family = AF_INET;
     hints.ai_socktype = SOCK_STREAM;
 
+    /* Try with IPv6 if no IPv4 address was found. We do it in this order since
+     * in a Redis client you can't afford to test if you have IPv6 connectivity
+     * as this would add latency to every connect. Otherwise a more sensible
+     * route could be: Use IPv6 if both addresses are available and there is IPv6
+     * connectivity. */
     if ((rv = getaddrinfo(addr,_port,&hints,&servinfo)) != 0) {
-        __redisSetError(c,REDIS_ERR_OTHER,gai_strerror(rv));
-        return REDIS_ERR;
+         hints.ai_family = AF_INET6;
+         if ((rv = getaddrinfo(addr,_port,&hints,&servinfo)) != 0) {
+            __redisSetError(c,REDIS_ERR_OTHER,gai_strerror(rv));
+            return REDIS_ERR;
+        }
     }
     for (p = servinfo; p != NULL; p = p->ai_next) {
         if ((s = socket(p->ai_family,p->ai_socktype,p->ai_protocol)) == -1)