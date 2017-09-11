@@ -592,6 +592,11 @@ int showThroughput(struct aeEventLoop *eventLoop, long long id, void *clientData
     REDIS_NOTUSED(id);
     REDIS_NOTUSED(clientData);
 
+    if (config.liveclients == 0) {
+        fprintf(stderr,"All clients disconnected... aborting.");
+        exit(1);
+    }
+
     if (config.csv) return 250;
     float dt = (float)(mstime()-config.start)/1000.0;
     float rps = (float)config.requests_finished/dt;