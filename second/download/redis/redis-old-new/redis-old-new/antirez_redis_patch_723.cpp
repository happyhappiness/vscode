@@ -390,7 +390,8 @@ static client createClient(char *cmd, size_t len, client from) {
             }
         }
     }
-    aeCreateFileEvent(config.el,c->context->fd,AE_WRITABLE,writeHandler,c);
+    if (config.idlemode == 0)
+        aeCreateFileEvent(config.el,c->context->fd,AE_WRITABLE,writeHandler,c);
     listAddNodeTail(config.clients,c);
     config.liveclients++;
     return c;
@@ -599,9 +600,13 @@ int showThroughput(struct aeEventLoop *eventLoop, long long id, void *clientData
     if (config.liveclients == 0) {
         fprintf(stderr,"All clients disconnected... aborting.\n");
         exit(1);
-    }
-
+    } 
     if (config.csv) return 250;
+    if (config.idlemode == 1) {
+        printf("clients: %d\r", config.liveclients);
+        fflush(stdout);
+	return 250;
+    }
     float dt = (float)(mstime()-config.start)/1000.0;
     float rps = (float)config.requests_finished/dt;
     printf("%s: %.2f\r", config.title, rps);