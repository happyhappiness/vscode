@@ -740,7 +740,7 @@ void clusterWriteHandler(aeEventLoop *el, int fd, void *privdata, int mask) {
 
     nwritten = write(fd, link->sndbuf, sdslen(link->sndbuf));
     if (nwritten <= 0) {
-        redisLog(REDIS_NOTICE,"I/O error writing to node link: %s",
+        redisLog(REDIS_DEBUG,"I/O error writing to node link: %s",
             strerror(errno));
         handleLinkIOError(link);
         return;
@@ -788,7 +788,7 @@ void clusterReadHandler(aeEventLoop *el, int fd, void *privdata, int mask) {
 
     if (nread <= 0) {
         /* I/O error... */
-        redisLog(REDIS_NOTICE,"I/O error reading from node link: %s",
+        redisLog(REDIS_DEBUG,"I/O error reading from node link: %s",
             (nread == 0) ? "connection closed" : strerror(errno));
         handleLinkIOError(link);
         return;
@@ -1032,7 +1032,7 @@ void clusterCron(void) {
              * normal PING packets. */
             node->flags &= ~REDIS_NODE_MEET;
 
-            redisLog(REDIS_NOTICE,"Connecting with Node %.40s at %s:%d", node->name, node->ip, node->port+REDIS_CLUSTER_PORT_INCR);
+            redisLog(REDIS_DEBUG,"Connecting with Node %.40s at %s:%d", node->name, node->ip, node->port+REDIS_CLUSTER_PORT_INCR);
         }
     }
     dictReleaseIterator(di);