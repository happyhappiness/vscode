@@ -224,7 +224,7 @@ void clusterSaveConfigOrDie(void) {
 }
 
 void clusterInit(void) {
-    int saveconf = 0;
+    int saveconf = 0, j;
 
     server.cluster = zmalloc(sizeof(clusterState));
     server.cluster->myself = NULL;
@@ -251,14 +251,24 @@ void clusterInit(void) {
     }
     if (saveconf) clusterSaveConfigOrDie();
     /* We need a listening TCP port for our cluster messaging needs */
-    server.cfd = anetTcpServer(server.neterr,
-            server.port+REDIS_CLUSTER_PORT_INCR, server.bindaddr);
-    if (server.cfd == -1) {
-        redisLog(REDIS_WARNING, "Opening cluster TCP port: %s", server.neterr);
-        exit(1);
+    server.cfd_count = 0;
+    if (server.bindaddr_count == 0) server.bindaddr[0] = NULL;
+    for (j = 0; j < server.bindaddr_count || j == 0; j++) {
+        server.cfd[j] = anetTcpServer(
+            server.neterr, server.port+REDIS_CLUSTER_PORT_INCR,
+            server.bindaddr[j]);
+        if (server.cfd[j] == -1) {
+            redisLog(REDIS_WARNING,
+                "Opening cluster listening TCP socket %s:%d: %s",
+                    server.bindaddr[j] ? server.bindaddr[j] : "*",
+                    server.port+REDIS_CLUSTER_PORT_INCR,
+                    server.neterr);
+            exit(1);
+        }
+        if (aeCreateFileEvent(server.el, server.cfd[j], AE_READABLE,
+            clusterAcceptHandler, NULL) == AE_ERR) redisPanic("Unrecoverable error creating Redis Cluster file event.");
+        server.cfd_count++;
     }
-    if (aeCreateFileEvent(server.el, server.cfd, AE_READABLE,
-        clusterAcceptHandler, NULL) == AE_ERR) redisPanic("Unrecoverable error creating Redis Cluster file event.");
     server.cluster->slots_to_keys = zslCreate();
 }
 