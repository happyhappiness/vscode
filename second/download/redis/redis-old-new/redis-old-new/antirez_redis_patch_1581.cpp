@@ -692,7 +692,6 @@ int serverCron(struct aeEventLoop *eventLoop, long long id, void *clientData) {
          }
 
          /* Trigger an AOF rewrite if needed */
-         printf("%d\n", server.auto_aofrewrite_perc);
          if (server.auto_aofrewrite_perc &&
              server.appendonly_current_size > server.auto_aofrewrite_min_size)
          {