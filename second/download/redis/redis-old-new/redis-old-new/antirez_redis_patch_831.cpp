@@ -39,9 +39,13 @@
 #define AF_LOCAL AF_UNIX
 #endif
 
-int redisCheckSocketError(redisContext *c, int fd);
-int redisContextSetTimeout(redisContext *c, struct timeval tv);
-int redisContextConnectTcp(redisContext *c, const char *addr, int port, struct timeval *timeout);
-int redisContextConnectUnix(redisContext *c, const char *path, struct timeval *timeout);
+int redisCheckSocketError(redisContext *c);
+int redisContextSetTimeout(redisContext *c, const struct timeval tv);
+int redisContextConnectTcp(redisContext *c, const char *addr, int port, const struct timeval *timeout);
+int redisContextConnectBindTcp(redisContext *c, const char *addr, int port,
+                               const struct timeval *timeout,
+                               const char *source_addr);
+int redisContextConnectUnix(redisContext *c, const char *path, const struct timeval *timeout);
+int redisKeepAlive(redisContext *c, int interval);
 
 #endif