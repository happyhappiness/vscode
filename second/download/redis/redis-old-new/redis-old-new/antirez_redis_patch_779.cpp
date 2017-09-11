@@ -597,7 +597,7 @@ int showThroughput(struct aeEventLoop *eventLoop, long long id, void *clientData
     REDIS_NOTUSED(clientData);
 
     if (config.liveclients == 0) {
-        fprintf(stderr,"All clients disconnected... aborting.");
+        fprintf(stderr,"All clients disconnected... aborting.\n");
         exit(1);
     }
 