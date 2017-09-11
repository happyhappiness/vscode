@@ -4307,8 +4307,8 @@ int migrateGetSocket(redisClient *c, robj *host, robj *port, long timeout) {
     }
 
     /* Create the socket */
-    fd = anetTcpNonBlockConnect(server.neterr,c->argv[1]->ptr,
-                atoi(c->argv[2]->ptr));
+    fd = anetTcpNonBlockBindConnect(server.neterr,c->argv[1]->ptr,
+                atoi(c->argv[2]->ptr),REDIS_BIND_ADDR);
     if (fd == -1) {
         sdsfree(name);
         addReplyErrorFormat(c,"Can't connect to target node: %s",