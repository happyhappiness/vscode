 
     if (errno == EINPROGRESS) {
         int res;
 
         if ((res = poll(wfd, 1, msec)) == -1) {
             __redisSetErrorFromErrno(c, REDIS_ERR_IO, "poll(2)");
-            close(fd);
+            redisContextCloseFd(c);
             return REDIS_ERR;
         } else if (res == 0) {
             errno = ETIMEDOUT;
             __redisSetErrorFromErrno(c,REDIS_ERR_IO,NULL);
-            close(fd);
+            redisContextCloseFd(c);
             return REDIS_ERR;
         }
 
-        if (redisCheckSocketError(c, fd) != REDIS_OK)
+        if (redisCheckSocketError(c) != REDIS_OK)
             return REDIS_ERR;
 
         return REDIS_OK;
     }
 
     __redisSetErrorFromErrno(c,REDIS_ERR_IO,NULL);
-    close(fd);
+    redisContextCloseFd(c);
     return REDIS_ERR;
 }
 
-int redisCheckSocketError(redisContext *c, int fd) {
+int redisCheckSocketError(redisContext *c) {
     int err = 0;
     socklen_t errlen = sizeof(err);
 
-    if (getsockopt(fd, SOL_SOCKET, SO_ERROR, &err, &errlen) == -1) {
+    if (getsockopt(c->fd, SOL_SOCKET, SO_ERROR, &err, &errlen) == -1) {
         __redisSetErrorFromErrno(c,REDIS_ERR_IO,"getsockopt(SO_ERROR)");
-        close(fd);
         return REDIS_ERR;
     }
 
     if (err) {
         errno = err;
         __redisSetErrorFromErrno(c,REDIS_ERR_IO,NULL);
-        close(fd);
         return REDIS_ERR;
     }
 
     return REDIS_OK;
 }
 
-int redisContextSetTimeout(redisContext *c, struct timeval tv) {
+int redisContextSetTimeout(redisContext *c, const struct timeval tv) {
     if (setsockopt(c->fd,SOL_SOCKET,SO_RCVTIMEO,&tv,sizeof(tv)) == -1) {
         __redisSetErrorFromErrno(c,REDIS_ERR_IO,"setsockopt(SO_RCVTIMEO)");
         return REDIS_ERR;
     }
     if (setsockopt(c->fd,SOL_SOCKET,SO_SNDTIMEO,&tv,sizeof(tv)) == -1) {
         __redisSetErrorFromErrno(c,REDIS_ERR_IO,"setsockopt(SO_SNDTIMEO)");
         return REDIS_ERR;
     }
     return REDIS_OK;
 }
 
-int redisContextConnectTcp(redisContext *c, const char *addr, int port, struct timeval *timeout) {
+static int _redisContextConnectTcp(redisContext *c, const char *addr, int port,
+                                   const struct timeval *timeout,
+                                   const char *source_addr) {
     int s, rv;
     char _port[6];  /* strlen("65535"); */
-    struct addrinfo hints, *servinfo, *p;
+    struct addrinfo hints, *servinfo, *bservinfo, *p, *b;
     int blocking = (c->flags & REDIS_BLOCK);
 
     snprintf(_port, 6, "%d", port);
     memset(&hints,0,sizeof(hints));
     hints.ai_family = AF_INET;
     hints.ai_socktype = SOCK_STREAM;
