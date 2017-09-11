@@ -1723,7 +1723,10 @@ void slaveofCommand(client *c) {
         !strcasecmp(c->argv[2]->ptr,"one")) {
         if (server.masterhost) {
             replicationUnsetMaster();
-            serverLog(LL_NOTICE,"MASTER MODE enabled (user request)");
+            sds client = catClientInfoString(sdsempty(),c);
+            serverLog(LL_NOTICE,"MASTER MODE enabled (user request from '%s')",
+                client);
+            sdsfree(client);
         }
     } else {
         long port;
@@ -1741,8 +1744,10 @@ void slaveofCommand(client *c) {
         /* There was no previous master or the user specified a different one,
          * we can continue. */
         replicationSetMaster(c->argv[1]->ptr, port);
-        serverLog(LL_NOTICE,"SLAVE OF %s:%d enabled (user request)",
-            server.masterhost, server.masterport);
+        sds client = catClientInfoString(sdsempty(),c);
+        serverLog(LL_NOTICE,"SLAVE OF %s:%d enabled (user request from '%s')",
+            server.masterhost, server.masterport, client);
+        sdsfree(client);
     }
     addReply(c,shared.ok);
 }