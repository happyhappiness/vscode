@@ -226,7 +226,7 @@ void clusterSaveConfigOrDie(void) {
 }
 
 void clusterInit(void) {
-    int saveconf = 0, j;
+    int saveconf = 0;
 
     server.cluster = zmalloc(sizeof(clusterState));
     server.cluster->myself = NULL;
@@ -252,25 +252,16 @@ void clusterInit(void) {
         saveconf = 1;
     }
     if (saveconf) clusterSaveConfigOrDie();
-    /* We need a listening TCP port for our cluster messaging needs */
+
+    /* We need a listening TCP port for our cluster messaging needs. */
     server.cfd_count = 0;
-    if (server.bindaddr_count == 0) server.bindaddr[0] = NULL;
-    for (j = 0; j < server.bindaddr_count || j == 0; j++) {
-        server.cfd[j] = anetTcpServer(
-            server.neterr, server.port+REDIS_CLUSTER_PORT_INCR,
-            server.bindaddr[j]);
-        if (server.cfd[j] == -1) {
-            redisLog(REDIS_WARNING,
-                "Opening cluster listening TCP socket %s:%d: %s",
-                    server.bindaddr[j] ? server.bindaddr[j] : "*",
-                    server.port+REDIS_CLUSTER_PORT_INCR,
-                    server.neterr);
-            exit(1);
-        }
-        if (aeCreateFileEvent(server.el, server.cfd[j], AE_READABLE,
-            clusterAcceptHandler, NULL) == AE_ERR) redisPanic("Unrecoverable error creating Redis Cluster file event.");
-        server.cfd_count++;
+    if (listenToPort(server.port+REDIS_CLUSTER_PORT_INCR,
+        server.cfd,&server.cfd_count) == REDIS_ERR)
+    {
+        exit(1);
     }
+
+    /* The slots -> keys map is a sorted set. Init it. */
     server.cluster->slots_to_keys = zslCreate();
 }
 