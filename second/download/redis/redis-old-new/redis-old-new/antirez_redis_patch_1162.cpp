@@ -784,6 +784,10 @@ void configSetCommand(redisClient *c) {
         if (getLongLongFromObject(o,&ll) == REDIS_ERR ||
             ll <= 0) goto badfmt;
         server.slave_priority = ll;
+    } else if (!strcasecmp(c->argv[2]->ptr,"cluster-node-timeout")) {
+        if (getLongLongFromObject(o,&ll) == REDIS_ERR ||
+            ll <= 0) goto badfmt;
+        server.cluster_node_timeout = ll;
     } else {
         addReplyErrorFormat(c,"Unsupported CONFIG parameter: %s",
             (char*)c->argv[2]->ptr);