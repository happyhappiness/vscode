     }
     return REDIS_OK;
 }
 
 #define __MAX_MSEC (((LONG_MAX) - 999) / 1000)
 
-static int redisContextWaitReady(redisContext *c, const struct timeval *timeout) {
-    struct pollfd   wfd[1];
-    long msec;
-
-    msec          = -1;
-    wfd[0].fd     = c->fd;
-    wfd[0].events = POLLOUT;
+static int redisContextTimeoutMsec(redisContext *c, long *result)
+{
+    const struct timeval *timeout = c->timeout;
+    long msec = -1;
 
     /* Only use timeout when not NULL. */
     if (timeout != NULL) {
         if (timeout->tv_usec > 1000000 || timeout->tv_sec > __MAX_MSEC) {
-            __redisSetErrorFromErrno(c, REDIS_ERR_IO, NULL);
-            redisContextCloseFd(c);
+            *result = msec;
             return REDIS_ERR;
         }
 
         msec = (timeout->tv_sec * 1000) + ((timeout->tv_usec + 999) / 1000);
 
         if (msec < 0 || msec > INT_MAX) {
             msec = INT_MAX;
         }
     }
 
+    *result = msec;
+    return REDIS_OK;
+}
+
+static int redisContextWaitReady(redisContext *c, long msec) {
+    struct pollfd   wfd[1];
+
+    wfd[0].fd     = c->fd;
+    wfd[0].events = POLLOUT;
+
     if (errno == EINPROGRESS) {
         int res;
 
         if ((res = poll(wfd, 1, msec)) == -1) {
             __redisSetErrorFromErrno(c, REDIS_ERR_IO, "poll(2)");
             redisContextCloseFd(c);
