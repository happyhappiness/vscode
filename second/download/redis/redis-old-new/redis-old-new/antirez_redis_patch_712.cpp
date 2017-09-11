@@ -1357,7 +1357,8 @@ void syncWithMaster(aeEventLoop *el, int fd, void *privdata, int mask) {
 int connectWithMaster(void) {
     int fd;
 
-    fd = anetTcpNonBlockConnect(NULL,server.masterhost,server.masterport);
+    fd = anetTcpNonBlockBindConnect(NULL,
+        server.masterhost,server.masterport,REDIS_BIND_ADDR);
     if (fd == -1) {
         redisLog(REDIS_WARNING,"Unable to connect to MASTER: %s",
             strerror(errno));