@@ -4486,8 +4486,8 @@ migrateCachedSocket* migrateGetSocket(redisClient *c, robj *host, robj *port, lo
     }
 
     /* Create the socket */
-    fd = anetTcpNonBlockBindConnect(server.neterr,c->argv[1]->ptr,
-                atoi(c->argv[2]->ptr),REDIS_BIND_ADDR);
+    fd = anetTcpNonBlockConnect(server.neterr,c->argv[1]->ptr,
+                                atoi(c->argv[2]->ptr));
     if (fd == -1) {
         sdsfree(name);
         addReplyErrorFormat(c,"Can't connect to target node: %s",