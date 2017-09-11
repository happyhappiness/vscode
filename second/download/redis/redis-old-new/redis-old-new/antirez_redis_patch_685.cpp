@@ -602,7 +602,7 @@ int showThroughput(struct aeEventLoop *eventLoop, long long id, void *clientData
     if (config.liveclients == 0) {
         fprintf(stderr,"All clients disconnected... aborting.\n");
         exit(1);
-    } 
+    }
     if (config.csv) return 250;
     if (config.idlemode == 1) {
         printf("clients: %d\r", config.liveclients);