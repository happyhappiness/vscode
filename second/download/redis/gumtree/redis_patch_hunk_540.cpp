 " with a range of values selected by the -r option.\n"
     );
     exit(exit_status);
 }
 
 int showThroughput(struct aeEventLoop *eventLoop, long long id, void *clientData) {
-    REDIS_NOTUSED(eventLoop);
-    REDIS_NOTUSED(id);
-    REDIS_NOTUSED(clientData);
+    UNUSED(eventLoop);
+    UNUSED(id);
+    UNUSED(clientData);
 
     if (config.liveclients == 0) {
         fprintf(stderr,"All clients disconnected... aborting.\n");
         exit(1);
-    } 
+    }
     if (config.csv) return 250;
     if (config.idlemode == 1) {
         printf("clients: %d\r", config.liveclients);
         fflush(stdout);
 	return 250;
     }
