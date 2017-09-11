@@ -252,8 +252,7 @@ void clusterInit(void) {
     if (saveconf) clusterSaveConfigOrDie();
     /* We need a listening TCP port for our cluster messaging needs */
     server.cfd = anetTcpServer(server.neterr,
-            server.port+REDIS_CLUSTER_PORT_INCR, server.bindaddr,
-            server.bindaddr_count);
+            server.port+REDIS_CLUSTER_PORT_INCR, server.bindaddr);
     if (server.cfd == -1) {
         redisLog(REDIS_WARNING, "Opening cluster TCP port: %s", server.neterr);
         exit(1);