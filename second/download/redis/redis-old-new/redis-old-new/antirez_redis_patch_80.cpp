@@ -2362,6 +2362,11 @@ void waitCommand(client *c) {
     long numreplicas, ackreplicas;
     long long offset = c->woff;
 
+    if (server.masterhost) {
+        addReplyError(c,"WAIT cannot be used with slave instances. Please also note that since Redis 4.0 if a slave is configured to be writable (which is not the default) writes to slaves are just local and are not propagated.");
+        return;
+    }
+
     /* Argument parsing. */
     if (getLongFromObjectOrReply(c,c->argv[1],&numreplicas,NULL) != C_OK)
         return;